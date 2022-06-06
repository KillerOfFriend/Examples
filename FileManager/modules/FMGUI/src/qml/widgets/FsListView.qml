import QtQuick 2.0

Item {
    id: fsListView

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
        }
    }

    Component {
        id: fsListHighlightDelegate
        Rectangle {
            width: listView.currentItem.width; height: listView.currentItem.height
            color: "lightsteelblue"
            y: listView.currentItem.y;
            Behavior on y { SpringAnimation { spring: 5; damping: 0.2 } }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: fsModel
        delegate: fsListDelegate
        //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

        highlight: fsListHighlightDelegate
        highlightFollowsCurrentItem: false
        focus: true
    }
}
