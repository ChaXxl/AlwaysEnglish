#pragma once
#include <QObject>
#include <Windows.h>
#include "singleton.h"

class GetActiveWindowPath : public QObject
{
    Q_OBJECT

private:
    explicit GetActiveWindowPath(QObject *parent = nullptr);

public:
    SINGLETON(GetActiveWindowPath)

};
