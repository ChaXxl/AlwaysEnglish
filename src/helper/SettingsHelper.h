#pragma once

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>
#include <QSettings>
#include <QScopedPointer>
#include <QCoreApplication>
#include <QDir>
#include "../singleton.h"

class SettingsHelper : public QObject {

    Q_OBJECT

private:
    explicit SettingsHelper(QObject *parent = nullptr);

public:
    SINGLETON(SettingsHelper)

    ~SettingsHelper() override;

    void init(char *argv[]);

    // 夜间模式
    Q_INVOKABLE void saveDarkMode(int darkModel) {
        save("darkMode", darkModel);
    }

    Q_INVOKABLE int getDarkMode() {
        return get("darkMode", QVariant(0)).toInt();
    }

    // 窗口置顶
    Q_INVOKABLE void saveStayTop(int darkModel) {
        save("stayTop", darkModel);
    }

    Q_INVOKABLE int getStayTop() {
        return get("stayTop", QVariant(0)).toInt();
    }

    // 是否一直打开大小写键
    Q_INVOKABLE void saveCapLock(int darkModel) {
        save("capLock", darkModel);
    }

    Q_INVOKABLE int getCapLock() {
        return get("capLock", QVariant(0)).toInt();
    }

    // 语言
    Q_INVOKABLE void saveLanguage(const QString &language) {
        save("language", language);
    }

    Q_INVOKABLE QString getLanguage() {
        return get("language", QVariant("en_US")).toString();
    }

private:
    void save(const QString &key, QVariant val);
    QVariant get(const QString &key, QVariant def = {});

private:
    QScopedPointer<QSettings> m_settings;
};
