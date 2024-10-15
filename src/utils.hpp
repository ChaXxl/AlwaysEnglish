#pragma once

#include <QCoreApplication>
#include <QSettings>
#include "singleton.h"

class Utils : public QObject {
    Q_OBJECT

public:
    SINGLETON(Utils)

    explicit Utils(QObject *parent = nullptr);

    Q_INVOKABLE void setAutoStart(bool enable) {
        auto appName = QCoreApplication::applicationName();
        auto appPath = QCoreApplication::applicationFilePath();

        appPath = appPath.replace("/", "\\");

        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

        if (enable) {
            settings.setValue(appName, appPath);
        }
        else {
            settings.remove(appName);
        }
    }
};

inline Utils::Utils(QObject* parent) : QObject(parent) {}
