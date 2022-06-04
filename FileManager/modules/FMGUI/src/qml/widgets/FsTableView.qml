import QtQuick 2.12
import QtQuick.Controls 1.4

Item {
    id: fsTableView

    TableView {
        id: tableView
        anchors.fill: parent

        Component {
            id: nameDelegate

            Item {
                Image {
                    id: nameImage
                    width: 20; height: 20
                    fillMode: Image.Stretch
                    source: model.imageURL
                }

                Text {
                    id: nameText
                    text: model.name
                    anchors.left: nameImage.right
                    width: parent.width - nameImage .width
                    elide: Text.ElideRight
                }
            }
        }

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


        model: fsModel
        focus: true
    }
}
