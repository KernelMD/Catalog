import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle {
    id: mainScreen

    property string logoPath
    property string title: "MAIN SCREEN"

    Image {
        id: logo

        anchors.bottom: buttonBox.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        source: mainScreen.logoPath
    }

    Rectangle {
        id: buttonBox

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 10 * stack.pixelDensity

        Button {
            id: catalogButton

            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 1 * stack.pixelDensity
            width: buttonBox.width / 2 - 1.5 * stack.pixelDensity

            text: "CATALOG"

            onClicked: stack.push({item: "qrc:/qml/Catalog.qml"})
        }

        Button {
            id: contactButton

            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 1 * stack.pixelDensity
            width: buttonBox.width / 2 - 1.5 * stack.pixelDensity

            text: "CONTACTS"

            onClicked: stack.push({item: "qrc:/qml/ContactSelector.qml"})
        }
    }

    Component.onCompleted: header.headerText = mainScreen.title
}

