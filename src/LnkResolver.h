#pragma once

#include <QObject>
#include <QString>
#include "singleton.h"

class LnkResolver : public QObject
{
    Q_OBJECT

private:
    explicit LnkResolver(QObject *parent = nullptr);

public:
    SINGLETON(LnkResolver)

    Q_INVOKABLE QString resolveLnk(const QString &lnkPath);
};
