import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Column{
        id: mainColumn
        anchors.centerIn: parent
        spacing: 20

        Label {
            id: counterValue
            text: cBackendModel ? cBackendModel.count : "Not available"
            anchors.horizontalCenter: mainColumn.horizontalCenter
        }

        Button {
            id: counterButton
            text: "Increment"
            onClicked: {
                cBackendModel.increment()
            }
            padding: 50
            anchors.horizontalCenter: mainColumn.horizontalCenter
        }
    }
}
