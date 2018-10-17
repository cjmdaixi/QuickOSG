#include "quickosgviewer.h"
#include "quickosgrenderer.h"
#include <QQmlEngine>
#include <QQuickWindow>
#include <QtDebug>
#include <osgGA/OrbitManipulator>
#include <osgGA/TrackballManipulator>

class FindNamedNode: public osg::NodeVisitor
{
public:
    explicit FindNamedNode(const QString& name)
        : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
        , m_name(name.toStdString())
    {}

    virtual void apply(osg::Node& node) override
    {
        if(node.getName() == m_name){
            m_node = &node;
        }else{
            traverse(node);
        }
    }
    osg::Node* getNode() const {return m_node;}
private:
    std::string m_name;
    osg::Node* m_node = nullptr;
};

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

    m_sceneNode = new osg::Group;

    qRegisterMetaType<osg::Node*>();
    qRegisterMetaType<osg::Operation*>();
    qRegisterMetaType<osg::Vec3Array*>();
    qRegisterMetaType<osg::DrawElementsUInt*>();

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

class CameraLookAtOperation : public osg::Operation
{
public:
    explicit CameraLookAtOperation(osg::Vec3d eye, osg::Vec3d center, osg::Vec3d up)
        : osg::Operation("change camera lookat operation", false)
        , m_eye(eye), m_center(center), m_up(up)
    {}
    virtual void operator()(osg::Object* caller) override
    {
        // qDebug()<<"look at"<<m_eye.x()<<m_eye.y()<<m_eye.z();
        auto viewer = dynamic_cast<osgViewer::Viewer*>(caller);

        //viewer->getCamera()->setViewMatrixAsLookAt(m_eye, m_center, m_up);
        //viewer->getCameraManipulator()->setByMatrix(osg::Matrixd::lookAt(m_eye, m_center, m_up));


        try{
            osgGA::TrackballManipulator *m = reinterpret_cast<osgGA::TrackballManipulator*>(viewer->getCameraManipulator());
            m->setTransformation(m_eye, m_center, m_up);
        }
        catch (...)
        {
            qDebug() << "look at" << m_eye.x() << m_eye.y() << m_eye.z();
        }

        //auto orbit = dynamic_cast<osgGA::OrbitManipulator*>(viewer->getCameraManipulator());
        //orbit->setCenter(viewer->getSceneData()->getBound().center());
    }
private:
    osg::Vec3d m_eye, m_center, m_up;
};

void QuickOSGViewer::lookAt(QVector3D eye, QVector3D center, QVector3D up)
{
    if (up.length() > 1.0) return;

    addOperation(new CameraLookAtOperation(osg::Vec3d(eye.x(), eye.y(), eye.z()),
                                           osg::Vec3d(center.x(), center.y(), center.z()),
                                           osg::Vec3d(up.x(), up.y(), up.z())));
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
    qDebug() << "keyPressEvent";
    int nKey = getOsgKey(event);
    m_eventQueue->keyPress((osgGA::GUIEventAdapter::KeySymbol)nKey);
    QQuickFramebufferObject::keyPressEvent(event);
}

void QuickOSGViewer::keyReleaseEvent(QKeyEvent* event)
{
    qDebug() << "keyReleaseEvent";
    /* if (event->isAutoRepeat())
    {
        event->ignore();
        return;
    }*/

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
    m_hoverEnabled = newHoverEnabled;
    setAcceptHoverEvents(m_hoverEnabled);
    emit hoverEnabledChanged();
}

osg::Node * QuickOSGViewer::scene() const
{
    return m_sceneNode.get();
}

//class ChangeSceneOperation : public osg::Operation
//{
//public:
//    explicit ChangeSceneOperation(osg::Node* scene)
//        : osg::Operation("change scene operation", false),
//        m_scene(scene)
//    {}
//    virtual void operator()(osg::Object* caller) override
//    {
//        auto viewer = dynamic_cast<osgViewer::Viewer*>(caller);
//        viewer->setSceneData(m_scene.get());
//    }
//    osg::ref_ptr<osg::Node> m_scene;
//};

void QuickOSGViewer::setScene(osg::Node * node)
{
    if (m_sceneNode == node) return;
    m_sceneNode = node;
    emit sceneChanged();
    update();
    //m_operationQueue->add(new ChangeSceneOperation(m_sceneNode.get()));
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
        case Qt::Key_Shift:
            return osgGA::GUIEventAdapter::KEY_Shift_L;
        default:
            return nKey;
        }
    }

    return nKey;
}


//class RemoveNodeOperation : public osg::Operation
//{
//public:
//    explicit RemoveNodeOperation(osg::Node* node)
//        : osg::Operation("remove node operation", false),
//        m_node(scene)
//    {}
//    virtual void operator()(osg::Object* caller) override
//    {
//        //auto viewer = dynamic_cast<osgViewer::Viewer*>(caller);
//        for(auto i = 0; i != m_node->getNumParents(); ++i){
//            auto p = m_node->getParent(i);
//            p->removeChild(m_node.get());
//        }
//    }
//private:
//    osg::ref_ptr<osg::Node> m_node;
//};

void QuickOSGViewer::addEventhandle(osgGA::GUIEventHandler* handler)
{
    //	m_evemtHandle = handler;
    //	if (m_viewer)
    //	m_viewer->addEventHandler(handler);
}

class PostDrawFBOCallback : public osg::Camera::DrawCallback {
public:
    PostDrawFBOCallback(const QuickOSGViewer* viewer)
        : m_viewer(viewer)
    {}
    virtual void operator()(osg::RenderInfo& renderInfo) const {
        if(m_viewer->defaultFbo()) m_viewer->defaultFbo()->bind();
    }
private:
    const QuickOSGViewer* m_viewer;
};

osg::Camera *QuickOSGViewer::createRTTCamera() const
{
    osg::ref_ptr<osg::Camera> rttCamera = new osg::Camera;
    rttCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rttCamera->setClearColor(osg::Vec4(1.0f, 1.0f, 1.0f,1.0f));
    rttCamera->setClearDepth(1);
    rttCamera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
    rttCamera->setPostDrawCallback(new PostDrawFBOCallback(this));

    rttCamera->setRenderOrder(osg::Camera::PRE_RENDER);
    rttCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);

    return rttCamera.release();
}

class AddChildOperation : public osg::Operation
{
public:
    explicit AddChildOperation(osg::Node *childNode, osg::Group *parentNode)
        : osg::Operation("add child node operation", false)
        , m_childNode(childNode), m_parentNode(parentNode)
    {}
    virtual void operator()(osg::Object* caller) override
    {
        //auto viewer = dynamic_cast<osgViewer::Viewer*>(caller);
        m_parentNode->addChild(m_childNode.get());
    }
private:
    osg::ref_ptr<osg::Node> m_childNode;
    osg::ref_ptr<osg::Group> m_parentNode;
};

void QuickOSGViewer::addChild(osg::Node *childNode, osg::Node *parentNode)
{
    auto parentGroupNode = parentNode == nullptr? m_sceneNode.get()->asGroup() : parentNode->asGroup();
    if(parentGroupNode == nullptr){
        qDebug()<<"Scene node is not a group derived class!";
        return;
    }
    auto op = new AddChildOperation(childNode, parentGroupNode);
    addOperation(op);
}

osg::Node* QuickOSGViewer::getNode(QString& name)
{
    if(m_sceneNode == nullptr) return nullptr;

    FindNamedNode fnn(name);
    m_sceneNode->accept(fnn);
    auto nodeFound = fnn.getNode();
    if(nodeFound == nullptr){
        qWarning() << "cannot find node:" << name;
    }

    return nodeFound;
}
