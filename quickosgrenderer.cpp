#include "quickosgrenderer.h"
#include "quickosgviewer.h"
#include <QtDebug>
#include <QQuickWindow>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/LineWidth>
#include <osgViewer/GraphicsWindow>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>


QuickOSGRenderer::QuickOSGRenderer(QuickOSGViewer* viewer)
	: m_quickViewer(viewer)
{
	m_eventQueue = viewer->m_eventQueue;
	m_operationQueue = viewer->m_operationQueue;

	initOSG();
}

QuickOSGRenderer::~QuickOSGRenderer()
{
    qDebug()<<"Renderer destroyed.";
}

void QuickOSGRenderer::initOSG()
{
	m_osgViewer = new osgViewer::Viewer();
	auto manipulator = new osgGA::TrackballManipulator;
	manipulator->setAllowThrow(false);
    m_osgViewer->setCameraManipulator(manipulator);

	osg::ref_ptr<osg::Camera> camera = m_osgViewer->getCamera();
	camera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
	camera->setProjectionMatrixAsOrtho(0.0, 1.0, 0.0, 1.0, 0.5, 1000);
	camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_osgViewer->setUpViewerAsEmbeddedInWindow(0, 0, 300, 300);
    m_quickViewer->resetWidth();  // 触发geometryChanged，改变渲染窗口大小
	m_quickViewer->setCamera(camera);

	//camera->setClearColor(QColor2OSGColor(m_clearColor));
	camera->setClearColor(osg::Vec4(0.0f, 0.0f, 0.0f, 0.0f));

	m_graphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(m_osgViewer->getCamera()->getGraphicsContext());

	osg::State* state = m_graphicsWindow->getState();
	state->setUseModelViewAndProjectionUniforms(true);
	//state->setUseVertexAttributeAliasing(true);


	//auto sceneData = osgDB::readNodeFile("cow.osg");
	//m_osgViewer->setSceneData(sceneData);

	m_graphicsWindow->setEventQueue(m_eventQueue);
	m_osgViewer->setUpdateOperations(m_operationQueue);
}

// 此处不做互斥同步处理是因为Qt保证在调用该sync函数时GUI线程是阻塞的
// 看Qt源代码也可以发现，在进入该函数之前，renderer线程使用mutex进行了互斥操作
void QuickOSGRenderer::synchronize(QQuickFramebufferObject* item)
{
    m_quickViewer = dynamic_cast<QuickOSGViewer*>(item);
}

void QuickOSGRenderer::render()
{
	QOpenGLContext::currentContext()->functions()->glUseProgram(0);

	m_osgViewer->frame();

	m_quickViewer->window()->resetOpenGLState();
}

QOpenGLFramebufferObject* QuickOSGRenderer::createFramebufferObject(const QSize& size)
{
	QOpenGLFramebufferObjectFormat format;
	format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
	format.setSamples(4);
	auto fbo = new QOpenGLFramebufferObject(size, format);
	return fbo;
}