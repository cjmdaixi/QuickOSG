cmake_policy(VERSION 3.9)
project(QuickOSG VERSION 0.1.0)
cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_definitions(-DMAJOR_VERSION=${PROJECT_VERSION_MAJOR} -DMINOR_VERSION=${PROJECT_VERSION_MINOR} -DPATCH_VERSION=${PROJECT_VERSION_PATCH})

# whether install after building
set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD ON)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set(CMAKE_PREFIX_PATH $ENV{QTDIR595_64})

find_package(Qt5 COMPONENTS Core Gui Xml Qml Quick LinguistTools OpenGL REQUIRED)

# find OpenSceneGraph
# x86

if(MSVC)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(OSG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/windows/x86/OSG)
        set(OSG3rd_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/windows/x86/OSG_3rd)
    else()
        # x64
        set(OSG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/windows/x64/OSG)
        set(OSG3rd_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/windows/x64/OSG_3rd)
    endif()
elseif(APPLE)
    set(OSG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/macos/OSG)
endif()

find_package(OpenSceneGraph COMPONENTS  osgUtil osgDB osgText osgViewer osgGA osgManipulator osgAnimation osgWidget REQUIRED)
if(OPENSCENEGRAPH_FOUND)
    include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
endif()

set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")

set(HEADERS 
    appglobal.h
	quickosgviewer.h
	quickosgrenderer.h
)

set(SOURCES 
    main.cpp
    appglobal.cpp
	quickosgviewer.cpp
	quickosgrenderer.cpp
)

set(RESOURCES 
    qml.qrc
)

set(QMLS
    main.qml
	MainView.qml
)

## set translation using Qt LinguistTools
set(TRANSLATIONS
    i18n/qml_en.ts
    i18n/qml_zh.ts
)

source_group("UI Files" FILES ${QMLS})

SET_DIRECTORY_PROPERTIES(PROPERTIES CLEAN_NO_CUSTOM TRUE)
qt5_create_translation(qm_files ${TRANSLATIONS} ${HEADERS} ${SOURCES} ${QMLS})


# configure the project to set some debug parameters in VS
if(MSVC)
    set(TARGET_NAME ${PROJECT_NAME})
    # x86
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        configure_file(vs.user32.in ${TARGET_NAME}.vcxproj.user)
    else()
    # x64
        configure_file(vs.user64.in ${TARGET_NAME}.vcxproj.user)
    endif()    
endif()

## Console
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${RESOURCES} ${QMLS} ${qm_files} icon.rc)

## Non-console
#add_executable(${PROJECT_NAME} WIN32 ${HEADERS} ${SOURCES} ${RESOURCES} ${QMLS} ${qm_files} icon.rc)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/MP")
    # Set working directory in VS
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX})
endif()

target_link_libraries(${PROJECT_NAME}  ${OPENSCENEGRAPH_LIBRARIES} Qt5::Core Qt5::Gui Qt5::Xml Qt5::Qml Qt5::Quick)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)

option(INSTALL_RUNTIME ON)
if(INSTALL_RUNTIME)
	if(MSVC)
	    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	        # x86
	        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd/windows/x86/deploy/Debug/ DESTINATION . CONFIGURATIONS Debug)
	        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd/windows/x86/deploy/Release/ DESTINATION . CONFIGURATIONS Release)
	    else()
	        # x64
	        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd/windows/x64/deploy/Debug/ DESTINATION . CONFIGURATIONS Debug)
	        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rd/windows/x64/deploy/Release/ DESTINATION . CONFIGURATIONS Release)
	    endif()
	endif()
endif()