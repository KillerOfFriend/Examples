import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../widgets"

ApplicationWindow {

    visible: true

    title: qsTr("File Manager")
    width: 640
    height: 480

    ActionGroup {
        id: viewActions
        exclusive: true

        Action {
            id: iconViewAction
            checkable: true
            text: qsTr("Icon")
            onTriggered: viewLoader.source = "qrc:/qml/widgets/FsIconView.qml"
        }
        Action {
            id: tableViewAction
            checkable: true
            text: qsTr("Table")
            onTriggered: viewLoader.source = "qrc:/qml/widgets/FsTableView.qml"
        }
        Action { id: listViewAction
            checkable: true
            text: qsTr("List")
            onTriggered: viewLoader.source = "qrc:/qml/widgets/FsListView.qml"
        }
    }

    //menu containing two menu items
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: qsTr("View")

            MenuItem { action: iconViewAction }
            MenuItem { action: tableViewAction }
            MenuItem { action: listViewAction }
        }
    }

    //Content Area

//    ColumnLayout {

//        id: mainColumnLayout
//        anchors.fill: parent
//        spacing: 5
//        anchors.leftMargin: 20
//        anchors.rightMargin: 20

//        FsIconView {
//            Layout.fillHeight: true
//            Layout.fillWidth: true
//        }
//    }

    Loader {
        id: viewLoader

        anchors.fill: parent
        focus: true
    }

    Component.onCompleted: { iconViewAction.trigger() }
}
