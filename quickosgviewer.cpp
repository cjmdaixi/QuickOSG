#include "quickosgviewer.h"
#include "quickosgrenderer.h"
#include <QQmlEngine>
#include <QQuickWindow>
#include <QtDebug>

QuickOSGViewer::QuickOSGViewer(QQuickItem* parent)
    : QQuickFramebufferObject(parent)
{
	setMirrorVertically(true);
    setTextureFollowsItemSize(true);

    // 以下2行是C++处理鼠标事件的前提，否则所有(C++)鼠标事件直接忽略
    //setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);

	m_eventQueue = new osgGA::EventQueue;
	m_operationQueue = new osg::OperationQueue;

	qRegisterMetaType<osg::Node*>();
	qRegisterMetaType<osg::Operation*>();

	m_updateTimer.setInterval(1000 / m_framerate);
	connect(&m_updateTimer, &QTimer::timeout, this, [this]() {
		update();
	});
	m_updateTimer.start();
}

QuickOSGViewer::~QuickOSGViewer()
{
    qDebug()<<"Viewer: viewer destroyed.";
}

QQuickFramebufferObject::Renderer * QuickOSGViewer::createRenderer() const
{
    auto viewer = const_cast<QuickOSGViewer*>(this);
    auto renderer = new QuickOSGRenderer(viewer);
    return renderer;
}

void QuickOSGViewer::home()
{
	class HomeOperation : public osg::Operation
	{
	public:
		HomeOperation()
			: osg::Operation("home operation", false)
		{}
		virtual void operator()(osg::Object* caller) override 
		{
			auto viewer = dynamic_cast<osgViewer::Viewer*>(caller);
			viewer->getCameraManipulator()->home(1.0);
		}
	};
	m_operationQueue->add(new HomeOperation);
}
void QuickOSGViewer::lookAt(QVector3D eye, QVector3D center, QVector3D up)
{

}

void QuickOSGViewer::setClearColor(const QColor& newColor)
{
    if (m_clearColor == newColor) return;
    
	m_clearColor = newColor;
	class MyOperation : public osg::Operation
	{
	public:
		virtual void operator () (osg::Object*){}
	};
	m_operationQueue->add(new MyOperation);
}

void QuickOSGViewer::mousePressEvent(QMouseEvent *event)
{
    //除非非常清楚调用结果是自己想要的，否则千万不要调用注释这行！！！
    //因为QQuickItem::mousePressEvent(）里仅仅调用了event->ignore(),会导致接下来的mouseMove和mouseRelease接受不到信号
    //QQuickItem::mousePressEvent(event);

	setKeyboardModifiers(event);
	setMouseEventData(event);
	m_eventQueue->getCurrentEventState()->setModKeyMask(m_keyMask);
	m_eventQueue->mouseButtonPress(m_mouseX, m_mouseY, m_mouseBtn);
	update();
}

void QuickOSGViewer::mouseDoubleClickEvent(QMouseEvent* event)
{
	setKeyboardModifiers(event);
	setMouseEventData(event);
	m_eventQueue->getCurrentEventState()->setModKeyMask(m_keyMask);
	m_eventQueue->mouseDoubleButtonPress(m_mouseX, m_mouseY, m_mouseBtn);
	update();
}

void QuickOSGViewer::mouseMoveEvent(QMouseEvent* event)
{
    //除非非常清楚调用结果是自己想要的，否则千万不要调用注释这行！！！
    //因为QQuickItem::mouseMoveEvent(）里仅仅调用了event->ignore(),会导致接下来的mouseRelease接受不到信号
    //QQuickItem::mouseMoveEvent(event);

	setMouseEventData(event);
	m_eventQueue->mouseMotion(m_mouseX, m_mouseY);
}

//处理MouseMoveEvent的关键!!!
//不处理这个函数，mouseMoveEvent(QMouseEvent*)不会工作。
void QuickOSGViewer::hoverMoveEvent(QHoverEvent* event)
{
    QQuickItem::hoverMoveEvent(event);

	setHoverEventData(event);
	m_eventQueue->mouseMotion(m_mouseX, m_mouseY);
}

void QuickOSGViewer::mouseReleaseEvent(QMouseEvent* event)
{
	setKeyboardModifiers(event);
	setMouseEventData(event);
	m_eventQueue->getCurrentEventState()->setModKeyMask(m_keyMask);
	m_eventQueue->mouseButtonRelease(m_mouseX, m_mouseY, m_mouseBtn);
	update();
}

void QuickOSGViewer::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
	class GeometryChangeOperation : public osg::Operation
	{
	public:
		explicit GeometryChangeOperation(int x, int y, int width, int height)
			: osg::Operation("geometry change operation", false),
			m_x(x), m_y(y), m_width(width), m_height(height)
		{}
		virtual void operator()(osg::Object* caller) override
		{
			auto viewer = dynamic_cast<osgViewer::Viewer*>(caller);
			auto graphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(viewer->getCamera()->getGraphicsContext());
			graphicsWindow->resized(m_x, m_y, m_width, m_height);
		}
		int m_x, m_y, m_width, m_height;

	};

	if (newGeometry.width() > 0 && newGeometry.height() > 0)
	{
		QQuickWindow* ptrWindow = window();
		qreal retinaScale = 1.0f;
		if (ptrWindow != NULL)
		{
			retinaScale = window()->devicePixelRatio();
		}

		GeometryChangeOperation* geomChangeOperation =
			new GeometryChangeOperation(newGeometry.x(), newGeometry.y(), newGeometry.width() * retinaScale, newGeometry.height() * retinaScale);
		m_operationQueue->add(geomChangeOperation);
		m_eventQueue->windowResize(newGeometry.x(), newGeometry.y(), newGeometry.width() * retinaScale, newGeometry.height() * retinaScale);
	}
	QQuickFramebufferObject::geometryChanged(newGeometry, oldGeometry);
	update();
}

void QuickOSGViewer::wheelEvent(QWheelEvent* event)
{
	setKeyboardModifiers(event);
	if (event->orientation() == Qt::Vertical) 
    {
		osgGA::GUIEventAdapter* osgEvent = new osgGA::GUIEventAdapter(*m_eventQueue->getCurrentEventState());
		osgEvent->setEventType(osgGA::GUIEventAdapter::SCROLL);

        if (event->delta() > 0)
        {
            osgEvent->setScrollingMotion(osgGA::GUIEventAdapter::SCROLL_DOWN);
        }
        else
        {
            osgEvent->setScrollingMotion(osgGA::GUIEventAdapter::SCROLL_UP);
        }
		//osgEvent->setTime(m_eventQueue->getTime());
		m_eventQueue->addEvent(osgEvent);
	}

	QQuickItem::wheelEvent(event);
	update();
} 

void QuickOSGViewer::keyPressEvent(QKeyEvent* event)
{
    int nKey = getOsgKey(event);
    m_eventQueue->keyPress((osgGA::GUIEventAdapter::KeySymbol)nKey);
  	QQuickFramebufferObject::keyPressEvent(event);
}

void QuickOSGViewer::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
        return;
    }

    int nKey = getOsgKey(event);
    m_eventQueue->keyRelease((osgGA::GUIEventAdapter::KeySymbol)nKey);
}

void QuickOSGViewer::setMouseEventData(QMouseEvent *event)
{
    const qreal retinaScale = window()->devicePixelRatio();
    m_mouseX = event->x() * retinaScale;
    m_mouseY = event->y() * retinaScale;
    switch (event->button())
    {
    case Qt::LeftButton: 
        m_mouseBtn = 1; 
        break;
    case Qt::MidButton: 
        m_mouseBtn = 2; 
        break;
    case Qt::RightButton: 
        m_mouseBtn = 3; 
        break;
    default: 
        m_mouseBtn = 0; 
        break;
    }
}

void QuickOSGViewer::setHoverEventData(QHoverEvent* event)
{
    const qreal retinaScale = window()->devicePixelRatio();
    m_mouseX = event->pos().x() * retinaScale;
    m_mouseY = event->pos().y() * retinaScale;
    m_mouseBtn = 0;
}

void QuickOSGViewer::setHoverEnabled(bool newHoverEnabled)
{
	if (m_hoverEnabled == newHoverEnabled) return;
    setAcceptHoverEvents(m_hoverEnabled);
    emit hoverEnabledChanged();
}

osg::Node * QuickOSGViewer::scene() const
{
	return m_sceneNode.get();
}

void QuickOSGViewer::setScene(osg::Node * node)
{
	class ChangeSceneOperation : public osg::Operation
	{
	public:
		explicit ChangeSceneOperation(osg::Node* scene)
			: osg::Operation("change scene operation", false),
			m_scene(scene)
		{}
		virtual void operator()(osg::Object* caller) override
		{
			auto viewer = dynamic_cast<osgViewer::Viewer*>(caller);
			viewer->setSceneData(m_scene.get());
		}
		osg::ref_ptr<osg::Node> m_scene;
	};

	if (m_sceneNode == node) return;
	m_sceneNode = node;

	m_operationQueue->add(new ChangeSceneOperation(m_sceneNode.get()));
}

void QuickOSGViewer::setFramerate(int newFramerate)
{
	if (newFramerate <= 0 || newFramerate > 1000 || m_framerate == newFramerate) return;
	m_framerate = newFramerate;
	m_updateTimer.start(1000 / m_framerate);
}

void QuickOSGViewer::setCamera(osg::Camera * newCamera)
{
	if (m_camera.get() == newCamera) return;
	m_camera = newCamera;
	emit cameraChanged();
}

void QuickOSGViewer::setKeyboardModifiers(QInputEvent* event)
{
    int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
    m_keyMask = 0;
    if (modkey & Qt::ShiftModifier)
    {
        m_keyMask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
    }
    if (modkey & Qt::ControlModifier)
    {
        m_keyMask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
    }
    if (modkey & Qt::AltModifier) 
    {
        m_keyMask |= osgGA::GUIEventAdapter::MODKEY_ALT;
    }
}


int QuickOSGViewer::getOsgKey(QKeyEvent* event)
{
    int nKey = event->key();
    QString sTxt = event->text();
    if (!sTxt.isEmpty())
    {
        switch (nKey)
        {
        case Qt::Key_Home:
            return osgGA::GUIEventAdapter::KEY_Home;
        case Qt::Key_Left:
            return osgGA::GUIEventAdapter::KEY_Left;
        case Qt::Key_Up:
            return osgGA::GUIEventAdapter::KEY_Up;
        case Qt::Key_Right:
            return osgGA::GUIEventAdapter::KEY_Right;
        case Qt::Key_Down:
            return osgGA::GUIEventAdapter::KEY_Down;
        case Qt::Key_End:
            return osgGA::GUIEventAdapter::KEY_End;
        case Qt::Key_D:
            return osgGA::GUIEventAdapter::KEY_D;
        default:
            return nKey;
        }
    }

    return nKey;
}
