#pragma once

#include <QObject>
#include <QThread>
#include <windows.h>
#include "singleton.h"

class ControlInputThread : public QThread {
    Q_OBJECT

public:
    explicit ControlInputThread(QObject *parent = nullptr);
    void run() override;
    void stop();

signals:
    void switchToEnglish();
    void capLock();

public:
    static bool m_isRunning;
    static bool m_isCapLock;
};

class ControlInputLayout : public QObject
{
    Q_OBJECT

public:
    bool _iscapLock;

public:
    SINGLETON(ControlInputLayout)

    explicit ControlInputLayout(QObject *parent = nullptr);
    Q_INVOKABLE void startTask();
    Q_INVOKABLE void stopTask();

private:
    ControlInputThread *m_thread;

    void switchToEnglish();
    void capLock();
};

