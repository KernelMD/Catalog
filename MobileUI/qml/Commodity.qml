import QtQuick 2.0
import com.KernelMD.Catalog.StorageManagerPlugin 1.0

Rectangle {
    property Commodity commodity
    property string title: commodity.name

    Flickable {
        anchors.fill: parent

        Image {
            id: image

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: (commodity.imageName != "") ? 50 * stack.pixelDensity : 0

            source: (commodity.imageName != "") ?
                    StorageManager.cachePath + commodity.imageName : ""
            fillMode: Image.Stretch
            sourceSize.height: height
            sourceSize.width: width
        }

        Text {
            id: description

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: image.bottom
            anchors.leftMargin: 4 * stack.pixelDensity
            anchors.rightMargin: 4 * stack.pixelDensity
            anchors.topMargin: 4 * stack.pixelDensity

            text: commodity.description

            wrapMode: Text.WordWrap
        }

        Text {
            id: cost

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: description.bottom
            anchors.margins: 4 * stack.pixelDensity

            text: commodity.cost
            horizontalAlignment: Text.AlignRight
        }
    }

    Component.onCompleted: header.headerText = title
}

