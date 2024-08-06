import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import FluentUI 1.0

FluContentPage {

    id:root
    title: qsTr("App-specific settings")

    property bool selectedAll: true

    // 显示图标
    Component{
        id:com_ico
        Item{
            FluClip{
                anchors.centerIn: parent
                width: 40
                height: 40
                radius: [20,20,20,20]
                Image{
                    anchors.fill: parent
                    source: {
                        if(options && options.avatar){
                            return options.avatar
                        }
                        return ""
                    }
                    sourceSize: Qt.size(80,80)
                }
            }
        }
    }

    // 是否启用
    Component {
        id: com_column_turn_on
        Item {
            RowLayout {
                anchors.centerIn: parent
                FluToggleSwitch {

                }
            }
        }
    }

    // 是否开启大小写
    Component {
        id: com_column_caps
        Item {
            RowLayout {
                anchors.centerIn: parent
                FluToggleSwitch {

                }
            }
        }
    }

    // 移除
    Component {
        id: com_action
        Item {
            RowLayout {
                anchors.centerIn: parent
                FluButton {
                    text: qsTr("Remove")
                    onClicked: {
                        table_view.closeEditor()
                        table_view.removeRow(row)
                    }
                }
            }
        }
    }

    FluFrame{
        id:layout_controls
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
            topMargin: 20
        }
        height: 50

        Row{
            spacing: 10
            anchors{
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }

            // 停用
            FluToggleButton {
                text: qsTr("Deactivate")
                onClicked: {
                    table_view.enabled = !checked
                }
            }

            // 添加
            FluButton{
                text: qsTr("Add an APP")
                onClicked: {
                    table_view.appendRow(getObject())
                }
            }
        }
    }

    FluTableView{
        id:table_view
        anchors{
            left: parent.left
            right: parent.right
            top: layout_controls.bottom
            bottom: parent.bottom
        }
        anchors.topMargin: 5

        columnSource:[
            {
                title: qsTr("icon"),
                dataIndex: 'icon',
                readOnly: true
            },
            {
                title: "App",
                dataIndex: 'name',
                width: 250,
                readOnly: true
            },
            {
                title: qsTr("Turn on"),
                dataIndex: 'turnon',
            },
            {
                title: qsTr("Caps"),
                dataIndex: 'Caps',
            },
            {
                title: qsTr("Options"),
                dataIndex: 'action',
                frozen: true
            }
        ]

        DropArea {
            anchors.fill: parent
            onDropped: function (drop) {
                if (drop.hasUrls) {
                    for (var i = 0; i < drop.urls.length; i++) {
                        var filePath = drop.urls[i];
                        var fileName = filePath.toString().split("/").pop();

                        table_view.appendRow({
                            // icon:
                            name: fileName,
                            turnon: table_view.customItem(com_column_turn_on),
                            Caps: table_view.customItem(com_column_caps),
                            action: table_view.customItem(com_action),
                            _key:FluTools.uuid()
                        })
                    }
                }
            }
        }
    }

    function getObject(){
        var names = ["Photoshop", "Microsoft Word", "Moonlight", "SunloginClient"];
        function getRandomName(){
            var randomIndex = Math.floor(Math.random() * names.length);
            return names[randomIndex];
        }
        var avatars = ["qrc:/example/res/svg/avatar_1.svg", "qrc:/example/res/svg/avatar_2.svg"];
        function getAvatar(){
            var randomIndex = Math.floor(Math.random() * avatars.length);
            return avatars[randomIndex];
        }
        return {
            // icon: table_view.customItem(com_ico,{avatar:getAvatar()}),
            Caps: table_view.customItem(com_column_caps),
            // name:
            turnon: table_view.customItem(com_column_turn_on),
            action: table_view.customItem(com_action),
            _minimumHeight: 50,
            _key:FluTools.uuid()
        }
    }
}
