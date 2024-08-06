#include "IconProvider.h"

#include <QFileIconProvider>
#include <QDebug>

IconProvider::IconProvider(QObject *parent) : QObject(parent) {}

QImage IconProvider::getExeIcon(const QString &filePath) {
    QFileIconProvider iconProvider;
    QFileInfo fileInfo(filePath);
    QIcon icon = iconProvider.icon(fileInfo);
    QPixmap pixmap = icon.pixmap(80, 80);
    return pixmap.toImage();
}
