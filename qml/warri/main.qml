// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 360
    height: 360
    Text {
        text: "warri sucks"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text {
        text: "Completed: " + cp.completed + " Declined: " + cp.declined
    }

    Connections {
        target: cp
        //onClipboardListChanged: list.model = cp.clipboardList();
    }

    ListView {
        clip: true
        id: list
        cacheBuffer: 1000
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 35
        anchors.fill: parent
        delegate: Item {
            height: 20
            Row {
                id: row1
                spacing: 20
                Text {
                    text: modelData.title
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    color: modelData.status === true ? "green" : "red"
                }
                Text {
                    text: (modelData.duration / 60) + " minutes"
                }
            }
        }
        model: cp.clipboardList
    }

}
