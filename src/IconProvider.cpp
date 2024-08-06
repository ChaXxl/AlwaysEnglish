#include "IconProvider.h"

#include <QFileIconProvider>
#include <QImage>
#include <QImageReader>
#include <QByteArray>
#include <QBuffer>

IconProvider::IconProvider(QObject *parent) : QObject(parent) {}

QString IconProvider::getExeIcon(const QString &filePath) {
    QFileIconProvider iconProvider;
    QFileInfo fileInfo(filePath);
    QIcon icon = iconProvider.icon(fileInfo);
    QPixmap pixmap = icon.pixmap(80, 80);

    // 转换为 QImage
    QImage image = pixmap.toImage();

    // 转换为 Base64
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG"); // 保存为 PNG 格式
    QString base64Image = "data:image/png;base64," + QString(byteArray.toBase64());

    return base64Image; // 返回 Base64 编码的图像
}
