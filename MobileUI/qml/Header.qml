import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Window 2.0

Rectangle {
    property string headerText: "Header"
    signal backClicked()
    signal settingsClicked()

    Button {
        id: backButton

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 1 * Screen.pixelDensity

        text: "BACK"

        onClicked: parent.backClicked();
    }

    Text {
        id: header

        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: backButton.right
        anchors.right: settingsButton.left

        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pointSize: 16

        text: parent.headerText
    }

    Button {
        id: settingsButton

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 1 * Screen.pixelDensity

        text: "SETTINGS"

        onClicked: parent.settingsClicked()
    }

}

