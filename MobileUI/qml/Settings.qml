import QtQuick 2.0
import QtQuick.Controls 1.3
import com.KernelMD.Catalog.StorageManagerPlugin 1.0

Rectangle {
    Button {
        id: startSync

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 1 * stack.pixelDensity
        height: 10 * stack.pixelDensity

        text: "START SYNC"

        onClicked: StorageManager.UpdateStorage()
    }
}

