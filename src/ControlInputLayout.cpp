#include "ControlInputLayout.h"
#include <QDebug>

#include "ControlInputLayout.h"
#include <QDebug>

bool ControlInputThread::m_isRunning = false;
bool ControlInputThread::m_isCapLock = true;

ControlInputThread::ControlInputThread(QObject *parent) : QThread(parent) {}

void ControlInputThread::run() {
    while (m_isRunning) {
        emit switchToEnglish();
        if (m_isCapLock) {
            emit capLock();
        }
        QThread::msleep(200); // 避免频繁调用
    }
}

void ControlInputThread::stop() {
    m_isRunning = false;
}

ControlInputLayout::ControlInputLayout(QObject *parent)
    : QObject(parent), m_thread(new ControlInputThread(this)) {
    connect(m_thread, &ControlInputThread::switchToEnglish, this, &ControlInputLayout::switchToEnglish);
    connect(m_thread, &ControlInputThread::capLock, this, &ControlInputLayout::capLock);
}

void ControlInputLayout::startTask() {
    ControlInputThread::m_isRunning = true;
    m_thread->start();
}

void ControlInputLayout::stopTask() {
    ControlInputThread::m_isRunning = false;
}

void ControlInputLayout::switchToEnglish()
{
    qDebug() << "switchToEnglish...";
    // 根据前台窗口的句柄获取其所属线程的线程ID, 最后获取该线程的键盘布局句柄
    HKL hkl = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));

    // 获取其键盘布局的语言ID, 判断是否为英文输入法(美式)
    if (LOWORD(hkl) != MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))
    {
        // 使用 PostMessage 和 WM_INPUTLANGCHANGEREQUEST 消息请求切换到英文输入法（语言代码 “00000409” 为美国英文）
        PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)LoadKeyboardLayout(TEXT("00000409"), KLF_ACTIVATE));
    }
}

void ControlInputLayout::capLock()
{
    qDebug() << "capLock...";
    // 检查大小写键是否按下, 如果没有则模拟按下并释放大小写键
    if (!(GetKeyState(VK_CAPITAL) & 0x0001))
    {
        keybd_event(VK_CAPITAL, 0x3a, KEYEVENTF_EXTENDEDKEY | 0, 0);
        keybd_event(VK_CAPITAL, 0x3a, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    }
}

