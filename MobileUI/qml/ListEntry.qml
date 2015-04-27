import QtQuick 2.0

Rectangle {
    property string iconPath
    property string primaryText
    property string secondaryText

    signal clicked()

    Image {
        id: icon
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 1 * stack.pixelDensity
        height: 5 * stack.pixelDensity
        width: 5 * stack.pixelDensity

        source: parent.iconPath
    }

    Text {
        id: primary

        anchors.bottom: parent.bottom
        anchors.left: icon.right
        anchors.right: secondary.left
        anchors.top: parent.top
        anchors.margins: 1 * stack.pixelDensity

        clip: true
        font.pointSize: 14
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        text: parent.primaryText
    }

    Text {
        id: secondary

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 1 * stack.pixelDensity
        width: (secondary.text == "") ? 0 : 15 * stack.pixelDensity

        font.pointSize: 10
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter

        text: parent.secondaryText
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}

