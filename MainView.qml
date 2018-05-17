import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QuickOSG 1.0

ApplicationWindow {
	id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("QuickOSG")

	QuickOSGViewer{
		id: viewer
		anchors.fill: parent
		framerate: 100
		scene: $app.loadModelFile("cow.osg")
	}
}
