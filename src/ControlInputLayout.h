#pragma once

#include <QObject>
#include <QTimer>
#include <windows.h>
#include "singleton.h"

class ControlInputLayout : public QObject {
Q_OBJECT

private:
    bool m_isCapLock;
    QTimer *m_timer;

private:
    explicit ControlInputLayout(QObject *parent = nullptr);

    ~ControlInputLayout();

    void switchToEnglish();

    void capLock();

public:
SINGLETON(ControlInputLayout)

    Q_INVOKABLE void startTask();

    Q_INVOKABLE void stopTask();

private slots:

    void onTimerTimeout();
};
