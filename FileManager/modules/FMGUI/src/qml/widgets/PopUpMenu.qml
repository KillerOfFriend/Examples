import QtQuick 2.0
import QtQuick.Controls 2.12

Menu {
    ActionGroup {
        id: fsActions
        exclusive: true

        Action {
            id: copyAction
            text: qsTr("copy")

            icon.color: "transparent"
            icon.source: "qrc:/img/copy_past.png"

            onTriggered: { console.log("copy"); }
        }

        Action {
            id: cutAction
            text: qsTr("cut")

            icon.source: "qrc:/img/cut.png"
            icon.color: "transparent"

            onTriggered: { console.log("cut"); }
        }

        Action {
            id: pastAction
            text: qsTr("past")

            icon.source: "qrc:/img/copy_past.png"
            icon.color: "transparent"

            onTriggered: { console.log("past"); }
        }


        Action {
            id: deleteAction
            text: qsTr("delete")

            icon.source: "qrc:/img/delete.png"
            icon.color: "transparent"

            onTriggered: { console.log("delete"); }
        }
    }

    property string targetObjectPath: ""

    MenuItem { action: copyAction }
    MenuItem { action: cutAction }
    MenuItem { action: pastAction }
    MenuItem { action: deleteAction }
}

