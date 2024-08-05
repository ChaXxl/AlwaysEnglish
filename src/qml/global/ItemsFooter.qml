pragma Singleton

import QtQuick 2.15
import FluentUI 1.0

FluObject {
    property var navigationView

    id: footer_items

    FluPaneItemSeparator {}

    FluPaneItem{
        title:qsTr("Settings")
        icon:FluentIcons.Settings
        url:"qrc:/qml/page/settings.qml"
        onTap:{
            navigationView.push(url)
        }
    }
}
