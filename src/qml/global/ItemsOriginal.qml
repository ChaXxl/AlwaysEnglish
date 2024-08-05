pragma Singleton

import QtQuick 2.15
import FluentUI 1.0

FluObject {
    property var navigationView

    FluPaneItem{
        title:qsTr("Home")
        icon:FluentIcons.Home
        url:"qrc:/qml/page/home.qml"
        onTap:{
            navigationView.push(url)
        }
    }
}
