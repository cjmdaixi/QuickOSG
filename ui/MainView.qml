import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import CppBackend 1.0
import QuickOSG 1.0

ApplicationWindow {
    id: window
    width: 1024
    height: 768
    visible: true
    title: qsTr("Surface Splatting Demo") + $app.langToken

    Rectangle{
        id: backgroundRect
        anchors{fill: parent}
        gradient: Gradient{
            GradientStop { position: 0.0; color: "#222222" }
            GradientStop { position: 1.0; color: "#1a1a1a" }
        }
        //color: "white"
        QuickOSGViewer{
            id: osgViewer
            anchors.fill: parent
            //scene: $app.loadModelFile("cessna.osg")
            focus: true
            hoverEnabled: true
            Connections{
                target: $app
                onModelLoaded:{
                    osgViewer.scene = node;
                    osgViewer.home();
                }
                onErrorHappened:{
                    console.log(msg);
                }
            }
            Component.onCompleted: $app.viewer = osgViewer

        }
        MouseArea{
            anchors.fill: osgViewer
            onPressed: {
                osgViewer.forceActiveFocus();
                mouse.accepted = false;
            }
            propagateComposedEvents: true
        }

        RowLayout{
            anchors{right: parent.right; bottom: parent.bottom; margins: 30}



            Button{
                id: createCylinderManipulatorButton

                text: qsTr("Load")
                onClicked: {
                    var path = $applicationPath + "/models/pointcloud.asc";
                    $app.loadPointCloud(path);
                }
            }
        }

        DropArea{
            id: dropArea
            anchors.fill: parent
            onDropped:{
                //console.log("dropped", drop.keys);
                var path = drop.urls[0].toString();
                // remove prefixed "file:///"
                path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
                // unescape html codes like '%23' for '#'
                var cleanPath = decodeURIComponent(path);
                console.log("clean path:", cleanPath);
                if($app.fileSuffix(cleanPath) !== "asc"){
                }else{
                    $app.loadPointCloud(cleanPath);
                }

            }
        }
    }

    overlay.modal: BluredCover{
        bluredTarget: backgroundRect
        anchors.fill: parent
    }

    Popup{
        id: progressPopup
        width: 400
        height: 50
        visible: $app.progressInfo.visible
        modal: true
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
        Item{
            anchors.fill: parent
            Label{
                id: titleLabel
                anchors{
                    left: parent.left
                    top: parent.top
                    right: parent.right
                }
                height: 20
                text: $app.progressInfo.title
            }
            ProgressBar{
                id: progressBar
                anchors{
                    left: parent.left
                    top: titleLabel.bottom
                    right: parent.right
                    bottom: parent.bottom
                }
                from: $app.progressInfo.from
                to: $app.progressInfo.to
                value: $app.progressValue
            }
        }
    }
}
