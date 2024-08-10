#pragma once

#include <QObject>
#include <QTimer>
#include <windows.h>
#include "singleton.h"
#include "helper/SettingsHelper.h"

class ControlInputLayout : public QObject {
Q_OBJECT

private:
    bool m_isCapLock;
    bool m_isTurnOn;

    QTimer *m_timer;

    SettingsHelper *m_settings = SettingsHelper::getInstance();

private:
    explicit ControlInputLayout(QObject *parent = nullptr);

    ~ControlInputLayout();

    void switchToEnglish();

    void capLock();
    bool isCapLock();

public:
SINGLETON(ControlInputLayout)

    Q_INVOKABLE void startTask();

    Q_INVOKABLE void stopTask();

private slots:

    void onTimerTimeout();
};
