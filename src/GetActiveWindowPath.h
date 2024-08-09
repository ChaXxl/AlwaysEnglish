#pragma once

#include <QObject>
#include <QFileInfo>
#include <Windows.h>
#include <Psapi.h>
#include "singleton.h"
#include "helper/SettingsHelper.h"

class GetActiveWindowPath : public QObject {
Q_OBJECT

private:
    explicit GetActiveWindowPath(QObject *parent = nullptr);

    QString GetProcessPathByWindowHandle(HWND hwnd);

    QString extractExeName(const QString &path);

public:
SINGLETON(GetActiveWindowPath)

    Q_INVOKABLE QString getCurrentActiveWindow();

    Q_INVOKABLE bool isTargetWindow();

private:
    SettingsHelper *m_settings = SettingsHelper::getInstance();
};
