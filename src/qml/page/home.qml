import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform
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
                width: 30
                height: 30
                Image{
                    anchors.fill: parent
                    source: options && options.icon ? options.icon : ""
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
                onClicked: fileDialog.open()
            }
        }
    }

    // APP 选择对话框
    FileDialog {
        id: fileDialog
        title: qsTr("select an APP")
        fileMode: FileDialog.OpenFile
        nameFilters: ["exe Shortcuts(*.exe *.link *.lnk)"]
        onAccepted: {
            var filePath = fileDialog.file.toString();
            var fileName = filePath.split("/").pop();
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
                if (!drop.hasUrls) {
                    return;
                }

                for (var i = 0; i < drop.urls.length; i++) {
                    // 文件的路径
                    var filePath = drop.urls[i].toString();

                    // 分割路径提取带扩展名的文件名
                    var fileName = filePath.split("/").pop();

                    // 获取扩展名
                    const extension = fileName.split(".").pop();

                    // 如果不是 .exe 或者 快捷方式则跳过
                    if (extension !== "exe" && extension !== "link" && extension !== "lnk") {
                        continue;
                    }

                    // 没有扩展名的文件名
                    const fileNameWithoutExtension = fileName.split(".")[0];

                    // 提取不带 file:/// 的路径
                    filePath = filePath.replace(/^file:\/{3}/, "");

                    // 根据快捷方式的路径拿到快捷方式所指向的 exe 路径
                    var resolvedPath = LnkResolver.resolveLnk(filePath);

                    // 根据 exe 路径来找到它的图标, 拿到的是 Base64 格式
                    var fileIcon = iconProvider.getExeIcon(resolvedPath);

                    table_view.appendRow({
                        icon: table_view.customItem(com_ico,{icon: fileIcon}),
                        name: fileNameWithoutExtension,
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
