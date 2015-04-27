import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import "qml/"

import com.KernelMD.Catalog.StorageManagerPlugin 1.0

Window {
    height: 480
    width: 640

    visible: true

    Header {
        id: header

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 10 * Screen.pixelDensity

        onBackClicked: {
            if (stack.depth <= 1)
                Qt.quit();
            else
                stack.pop();
            header.headerText = stack.currentItem.title;
        }
        onSettingsClicked: stack.push({"item": "qrc:/qml/Settings.qml"})
    }

    StackView {
        id: stack

        // Make real value reachale for stack elements.
        property string pixelDensity: Screen.pixelDensity

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom

        initialItem: MainScreen {}
    }
}
