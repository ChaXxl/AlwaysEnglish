#include "IconProvider.h"

#include <QFileIconProvider>
#include <QDebug>

IconProvider::IconProvider(QObject *parent) : QObject(parent) {}

QIcon IconProvider::iconForFile(const QString &filePath) {
    QFileIconProvider iconProvider;
    return iconProvider.icon(QFileInfo(filePath));
}
