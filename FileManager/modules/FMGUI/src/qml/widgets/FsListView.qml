import QtQuick 2.0

Item {
    id: fsListView

    PopUpMenu {
        id: veiwPopupMenu
    }

    Component {
        id: fsListDelegate

        Item {
            width: parent.width
            height: 40
            Image {
                id: nameImage
                width: 40; height: 40
                fillMode: Image.Stretch
                source: model.imageURL
            }

            Text {
                id: nameText
                text: model.name
                anchors.left: nameImage.right
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked: {
                    listView.currentIndex = index

                    if(mouse.button & Qt.RightButton) {
                        veiwPopupMenu.popup()
                    }
                }

                onDoubleClicked: {
                    if (mouse.button & Qt.LeftButton && model.type === "Dir")
                        DataSource.setPath(model.objectpath);
                }
            }
        }
    }

    Component {
        id: fsListHighlightDelegate
        Rectangle {
            width: listView.currentItem.width; height: listView.currentItem.height
            color: "lightsteelblue"
            y: listView.currentItem.y;
            Behavior on y { SpringAnimation { spring: 4; damping: 0.2 } }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: fsModel
        delegate: fsListDelegate

        highlight: fsListHighlightDelegate
        highlightFollowsCurrentItem: false
        focus: true
    }
}
