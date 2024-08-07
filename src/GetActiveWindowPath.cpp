#include "GetActiveWindowPath.h"
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

QString GetActiveWindowPath::getCurrentActiveWindow()
{
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
