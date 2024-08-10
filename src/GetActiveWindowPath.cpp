#include "GetActiveWindowPath.h"
#include <QRegularExpression>
#include <QDebug>

GetActiveWindowPath::GetActiveWindowPath(QObject *parent) : QObject(parent) {}

QString GetActiveWindowPath::GetProcessPathByWindowHandle(HWND hwnd) {
    DWORD processId;
    DWORD threadId = GetWindowThreadProcessId(hwnd, &processId);

    if (threadId == 0) {
        return "error: 无法获取窗口线程 ID";
    }

    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (processHandle == NULL) {
        qDebug() << "无法打开进程，错误代码: " << GetLastError();
        return "error: 无法打开进程，错误代码: ";
    }

    WCHAR processPath[MAX_PATH];

    if (0 == GetModuleFileNameEx(processHandle, NULL, processPath, MAX_PATH)) {
        CloseHandle(processHandle);
        return "error: 无法获取窗口线程的信息";
    }

    CloseHandle(processHandle);

    QFileInfo fileInfo(QString::fromWCharArray(processPath));

    return fileInfo.filePath();
}

QString GetActiveWindowPath::getCurrentActiveWindow() {
    HWND foreGroundWindowHwnd = GetForegroundWindow();

    if (NULL == foreGroundWindowHwnd) {
        return "error: 无法获取前台窗口句柄";
    }

    if (!IsWindow(foreGroundWindowHwnd)) {
        return "error: 前台窗口句柄无效";
    }

    QString processPath = GetProcessPathByWindowHandle(foreGroundWindowHwnd);
    if (processPath.isEmpty()) {
        return "error: 无法获取进程路径";
    }

    return processPath;
}

QString GetActiveWindowPath::extractExeName(const QString &path) {
    // 定义正则表达式模式
    QRegularExpression pattern(R"(([^/\\]+)\.exe$)");
    QRegularExpressionMatch match = pattern.match(path);

    // 检查匹配是否成功
    if (match.hasMatch()) {
        // 提取匹配的组
        return match.captured(1);
    }
    return "";
}

bool GetActiveWindowPath::isTargetWindow() {
    // 获取当前正在使用的窗口的软件所在路径
    exePath = getCurrentActiveWindow();

    // 提取软件的名称
    exeName = extractExeName(exePath);
    if (exeName.isEmpty()) {
        return false;
    }

    // 将列表字符串用 , 分割
    QString exes = m_settings->getExistingFilePath();
    auto fileList = exes.split(",");

    // 判断列表里面有没有当前窗口
    for (const auto &i: fileList) {
        if (i.contains(exeName)) {
            return true;
        }
    }

    qDebug() << exeName << "不在列表";

    return false;
}
