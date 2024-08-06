#pragma once

#include <QObject>
#include <QImage>
#include "singleton.h"

class IconProvider : public QObject
{
    Q_OBJECT

private:
    explicit IconProvider(QObject *parent = nullptr);

public:
    SINGLETON(IconProvider)

    Q_INVOKABLE QImage getExeIcon(const QString &filePath);
};
