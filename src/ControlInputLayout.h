#pragma once

#include <QObject>
#include <QTimer>
#include <windows.h>
#include "singleton.h"
#include "helper/SettingsHelper.h"
#include "GetActiveWindowPath.h"

class ControlInputLayout : public QObject {
Q_OBJECT

private:
    bool m_isCapLock;
    bool m_isTurnOn;

    QTimer *m_timer;
    QTimer *m_timer_always;

    SettingsHelper *m_settings = SettingsHelper::getInstance();

    GetActiveWindowPath *gw = GetActiveWindowPath::getInstance();

private:
    explicit ControlInputLayout(QObject *parent = nullptr);

    ~ControlInputLayout();

    void switchToEnglish();

    void capLock();

    bool isCapLock();

public:
SINGLETON(ControlInputLayout)

    Q_INVOKABLE void startTask();

    Q_INVOKABLE void alwaysStartTask();

    Q_INVOKABLE void stopTask();

    Q_INVOKABLE void alwaysStoptTask();

private slots:

    void onTimerTimeout();

    void onTimerTimeout_always();
};
