#pragma once

#include <QObject>
#include <QThread>
#include <windows.h>
#include "singleton.h"

class ControlInputLayout : public QObject
{
    Q_OBJECT

private:
    bool m_isRunning;
    bool m_isCapLock;

private:
    explicit ControlInputLayout(QObject *parent = nullptr);

    void switchToEnglish();
    void capLock();

public:
    SINGLETON(ControlInputLayout)

    Q_INVOKABLE void startTask();
    Q_INVOKABLE void stopTask();
};
