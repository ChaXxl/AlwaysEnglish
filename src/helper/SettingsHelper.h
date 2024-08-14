#pragma once

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>
#include <QSettings>
#include <QScopedPointer>
#include <QJSValue>
#include <QJsonDocument>
#include <QJsonObject>
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
    Q_INVOKABLE void saveStayTop(int stayTop) {
        save("stayTop", stayTop);
    }

    Q_INVOKABLE int getStayTop() {
        return get("stayTop", QVariant(0)).toInt();
    }

    // 是否一直打开大小写键
    Q_INVOKABLE void saveCapLock(bool capLock) {
        save("capLock", capLock);
    }

    Q_INVOKABLE bool getCapLock() {
        return get("capLock", QVariant(0)).toBool();
    }

    // 语言
    Q_INVOKABLE void saveLanguage(const QString &language) {
        save("language", language);
    }

    Q_INVOKABLE QString getLanguage() {
        return get("language", QVariant("en_US")).toString();
    }

    // 表格里软件的详细信息
    Q_INVOKABLE void saveExeInfos(const QString &exeInfos) {
        save("exeInfos", exeInfos);
    }

    Q_INVOKABLE QString getExeInfos() {
        return get("exeInfos", QVariant("")).toString();
    }

    // 软件列表
    Q_INVOKABLE void saveExistingFilePath(const QString &existingFilePath) {
        save("existingFilePath", existingFilePath);
    }

    Q_INVOKABLE QString getExistingFilePath() {
        return get("existingFilePath", QVariant("")).toString();
    }

    // 记录软件打开次数
    Q_INVOKABLE void saveOpenCount(const int &openCount) {
        save("openCount", openCount);
    }

    Q_INVOKABLE int getOpenCount() {
        return get("openCount", QVariant("")).toInt();
    }

private:
    void save(const QString &key, QVariant val);

    QVariant get(const QString &key, QVariant def = {});

private:
    QScopedPointer<QSettings> m_settings;
};
