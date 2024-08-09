pragma Singleton

import QtQuick 2.15
import FluentUI 1.0

QtObject {
    property int testInt: 0
    property bool stayTop: false
    property bool isAlwaysCapLock: true

    // 使用 Set 来存储表格的软件路径
    property var existingFilePath: new Set()

    // 使用 Object 来存储表格每项软件的信息 (路径/名称/是否启动/是否开启大小写键)
    property var exeInfos: ({})
}
