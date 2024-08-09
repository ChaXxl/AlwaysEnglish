#include "LnkResolver.h"
#include <Windows.h>
#include <ShlObj.h>
#include <QDir>

LnkResolver::LnkResolver(QObject *parent) : QObject(parent) {}

QString LnkResolver::resolveLnk(const QString &lnkPath) {
    HRESULT hres;
    IShellLink *psl;
    WCHAR szGotPath[MAX_PATH];
    WCHAR szDescription[MAX_PATH];
    WIN32_FIND_DATA wfd;

    // 初始化 COM
    hres = CoInitialize(NULL);
    if (FAILED(hres)) {
        return QString();
    }

    // 创建 IShellLink 接口的实例
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *) &psl);
    if (FAILED(hres)) {
        CoUninitialize();
        return QString();
    }

    // 获取 IPersistFile 接口的指针
    IPersistFile *ppf;
    hres = psl->QueryInterface(IID_IPersistFile, (void **) &ppf);
    if (FAILED(hres)) {
        psl->Release();
        CoUninitialize();
        return QString();
    }

    // 加载快捷方式
    hres = ppf->Load(reinterpret_cast<LPCOLESTR>(lnkPath.utf16()), STGM_READ);
    if (FAILED(hres)) {
        ppf->Release();
        psl->Release();
        CoUninitialize();
        return QString();
    }

    // 解析链接
    hres = psl->Resolve(NULL, 0);
    if (FAILED(hres)) {
        ppf->Release();
        psl->Release();
        CoUninitialize();
        return QString();
    }

    // 获取链接目标的路径
    hres = psl->GetPath(szGotPath, MAX_PATH, (WIN32_FIND_DATA *) &wfd, SLGP_SHORTPATH);
    if (FAILED(hres)) {
        ppf->Release();
        psl->Release();
        CoUninitialize();
        return QString();
    }

    // 释放指针
    ppf->Release();
    psl->Release();
    CoUninitialize();

    return QString::fromWCharArray(szGotPath);
}
