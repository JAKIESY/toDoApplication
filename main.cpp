#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.hpp"

static void setupDarkTheme() {
    // 使用平台无关的 Fusion 样式，便于统一配色
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;

    // 背景类
    darkPalette.setColor(QPalette::Window, QColor(43, 43, 43)); // 主窗口背景 #2b2b2b
    darkPalette.setColor(QPalette::WindowText, QColor(187, 187, 187)); // 窗口文字
    darkPalette.setColor(QPalette::Base, QColor(35, 35, 35)); // 文本编辑框背景
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(255, 255, 220));
    darkPalette.setColor(QPalette::ToolTipText, QColor(0, 0, 0));

    // 文本
    darkPalette.setColor(QPalette::Text, QColor(169, 183, 198)); // 编辑器文字 #a9b7c6
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53)); // 按钮背景
    darkPalette.setColor(QPalette::ButtonText, QColor(187, 187, 187)); // 按钮文字
    darkPalette.setColor(QPalette::BrightText, QColor(255, 0, 0));

    // 高亮 & 链接
    darkPalette.setColor(QPalette::Highlight, QColor(75, 110, 175)); // 选中项高亮 #4b6eaf
    darkPalette.setColor(QPalette::HighlightedText, QColor(255, 255, 255));
    darkPalette.setColor(QPalette::Link, QColor(104, 151, 187));

    // 禁用状态
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(120, 120, 120));
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(120, 120, 120));
    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(120, 120, 120));

    QApplication::setPalette(darkPalette);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    setupDarkTheme();

    MainWindow w;
    w.show();

    return QApplication::exec();
}
