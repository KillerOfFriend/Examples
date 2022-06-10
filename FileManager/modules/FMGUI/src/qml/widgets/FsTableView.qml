import QtQuick 2.12
import QtQuick.Controls 1.4

Item {
    id: fsTableView

    Component {
        id: nameDelegate

        Item {
            Image {
                id: nameImage
                width: parent.height; height: parent.height
                fillMode: Image.Stretch
                source: model.imageURL
            }

            Text {
                id: nameText
                text: model.name
                anchors.left: nameImage.right
                width: parent.width - nameImage.width
                elide: Text.ElideRight
            }
        }
    }


    Component {
        id: rowDelegate

        Rectangle {
            id: rowDel
            width: parent.width; height: 30
            color: styleData.selected ? "lightsteelblue" :  "transparent"

            MouseArea {
                anchors.fill: parent
                onDoubleClicked: {
                    if (model.type === "Dir")
                        DataSource.setPath(model.objectpath);
                }
            }

        }
    }


    TableView {
        id: tableView
        anchors.fill: parent

        TableViewColumn {
            role: "name"
            title: fsModel.headerData(0, Qt.Horizontal)
            horizontalAlignment: Text.AlignHCenter
            //width: 200
            delegate: nameDelegate
        }
        TableViewColumn {
            role: "type"
            title: fsModel.headerData(1, Qt.Horizontal)
            horizontalAlignment: Text.AlignHCenter
            //width: 100
        }
        TableViewColumn {
            role: "size"
            title: fsModel.headerData(2, Qt.Horizontal)
            horizontalAlignment: Text.AlignHCenter
            //width: 50
        }
        TableViewColumn {
            role: "lastchangedate"
            title: fsModel.headerData(3, Qt.Horizontal)
            horizontalAlignment: Text.AlignHCenter
            //width: 200
        }

        rowDelegate: rowDelegate

        model: fsModel
        focus: true
    }
}
