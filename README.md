# QuickOSG
A lightweight integration of OSG in Qt Quick.

There is often the need to integrate 3D contents into our software. Instead of drawing our models using raw OpenGL commands from scrach, a handy scene graph framework is preferred. OpenSceneGraph is one of the most sophisticated frameworks.

While using OSG in Qt Widgets-based applications is quite common, using it in Qt Quick is not so much. However there are still some existing implementations.

## Existing integration methods

### osgqtquick by podsvirov

The repository is: https://github.com/podsvirov/osgqtquick. The way Podsvirov chosen is to provide qml-compatible interfaces for almost every classes of OSG. In this philosophy, you don't need C++ at all to use OSG. Although sounds reasonable, it requires a lot of work of implementation, which is obviously error-prone and hard to maintain. Every time the OSG changes, the interfaces implementaton needs changing as well.

### Using the way as integrating raw OpenGL

This is explained exhaustively in the Qt's official documentation: http://doc.qt.io/qt-5/qtquick-scenegraph-openglunderqml-example.html and http://blog.qt.io/blog/2015/05/11/integrating-custom-opengl-rendering-with-qt-quick-via-qquickframebufferobject/. 

This is the way we choose. We only provide a thin and robust integration QQuickFramebufferObject-based class, which solves the most basic problems to render an OSG view in Qt Quick, and leaving the rest of model constructing or manipulating things to users. There are huge materials available on the web of OSG programming in C++. We just provide an integration environment. That's all.

## How to use

This project not only shows how to integrate OSG into Qt Quick, but also a small, yet complete application skeleton to start with.

To compile it, follow these steps:

1. git clone, of cause;
2. Unzip the corresponding os-specific dependendis in the folder 3rd, make sure the structures are right in order to let CMake work fine. For example, 3rd/windows/x64 is the correct path for Windows;
3. Check on the option of `INSTALL_RUNTIME` in CMake if it's the first time you compile. This will make sure the corresponding dependencis are copied to the intall directory. You'd better check off this option after the first compilation to preventing copying so many files each building.
4. Enjoy!