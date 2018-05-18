# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.QuickOSG.Debug:
/Users/jimmy/Projects/QuickOSG/build/Debug/QuickOSG:\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgUtild.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgDBd.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgTextd.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgViewerd.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgGAd.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgManipulatord.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgAnimationd.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgWidgetd.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgd.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libOpenThreadsd.dylib\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtXml.framework/QtXml\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQuick.framework/QtQuick\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtGui.framework/QtGui\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQml.framework/QtQml\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtNetwork.framework/QtNetwork\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/jimmy/Projects/QuickOSG/build/Debug/QuickOSG


PostBuild.QuickOSG.Release:
/Users/jimmy/Projects/QuickOSG/build/Release/QuickOSG:\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgUtil.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgDB.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgText.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgViewer.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgGA.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgManipulator.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgAnimation.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgWidget.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosg.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libOpenThreads.dylib\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtXml.framework/QtXml\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQuick.framework/QtQuick\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtGui.framework/QtGui\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQml.framework/QtQml\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtNetwork.framework/QtNetwork\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/jimmy/Projects/QuickOSG/build/Release/QuickOSG


PostBuild.QuickOSG.MinSizeRel:
/Users/jimmy/Projects/QuickOSG/build/MinSizeRel/QuickOSG:\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgUtil.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgDB.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgText.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgViewer.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgGA.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgManipulator.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgAnimation.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgWidget.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosg.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libOpenThreads.dylib\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtXml.framework/QtXml\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQuick.framework/QtQuick\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtGui.framework/QtGui\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQml.framework/QtQml\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtNetwork.framework/QtNetwork\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/jimmy/Projects/QuickOSG/build/MinSizeRel/QuickOSG


PostBuild.QuickOSG.RelWithDebInfo:
/Users/jimmy/Projects/QuickOSG/build/RelWithDebInfo/QuickOSG:\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgUtil.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgDB.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgText.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgViewer.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgGA.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgManipulator.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgAnimation.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgWidget.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosg.dylib\
	/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libOpenThreads.dylib\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtXml.framework/QtXml\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQuick.framework/QtQuick\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtGui.framework/QtGui\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQml.framework/QtQml\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtNetwork.framework/QtNetwork\
	/Users/jimmy/Qt/5.9.5/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/jimmy/Projects/QuickOSG/build/RelWithDebInfo/QuickOSG




# For each target create a dummy ruleso the target does not have to exist
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libOpenThreads.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libOpenThreadsd.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosg.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgAnimation.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgAnimationd.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgDB.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgDBd.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgGA.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgGAd.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgManipulator.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgManipulatord.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgText.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgTextd.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgUtil.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgUtild.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgViewer.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgViewerd.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgWidget.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgWidgetd.dylib:
/Users/jimmy/Projects/QuickOSG/3rd/macos/OSG/lib/libosgd.dylib:
/Users/jimmy/Qt/5.9.5/clang_64/lib/QtCore.framework/QtCore:
/Users/jimmy/Qt/5.9.5/clang_64/lib/QtGui.framework/QtGui:
/Users/jimmy/Qt/5.9.5/clang_64/lib/QtNetwork.framework/QtNetwork:
/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQml.framework/QtQml:
/Users/jimmy/Qt/5.9.5/clang_64/lib/QtQuick.framework/QtQuick:
/Users/jimmy/Qt/5.9.5/clang_64/lib/QtXml.framework/QtXml:
