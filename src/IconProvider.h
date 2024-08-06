#pragma once

#include <QObject>
#include <QIcon>
#include <QUrl>
#include "singleton.h"

class IconProvider : public QObject
{
    Q_OBJECT

private:
    explicit IconProvider(QObject *parent = nullptr);

public:
    SINGLETON(IconProvider)

    Q_INVOKABLE QIcon iconForFile(const QString &filePath);
};
