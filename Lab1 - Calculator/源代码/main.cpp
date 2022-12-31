#include "mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{
    int nWidth = GetSystemMetrics(SM_CXSCREEN);
    int nHeight = GetSystemMetrics(SM_CYSCREEN);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.move ((nWidth - w.width())/2,(nHeight - w.height())/2-40);
    return a.exec();
}
