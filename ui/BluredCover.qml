import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0

Item{
    id: root
    property alias bluredTarget: blur.source
    Rectangle{
        anchors.fill: parent
        color: "black"
    }
    RecursiveBlur {
        id: blur
        anchors.fill: parent
        radius: 5
        //source: stackLayout
        loops: 25
    }

    Rectangle{
        anchors.fill: parent
        color: "black"
        opacity: 0.2
    }
}
