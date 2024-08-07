#pragma once
#include <QObject>
#include <QFileInfo>
#include <Windows.h>
#include <Psapi.h>
#include "singleton.h"

class GetActiveWindowPath : public QObject
{
    Q_OBJECT

private:
    explicit GetActiveWindowPath(QObject *parent = nullptr);

    QString GetProcessPathByWindowHandle(HWND hwnd);

public:
    SINGLETON(GetActiveWindowPath)

    Q_INVOKABLE QString getCurrentActiveWindow();
};
