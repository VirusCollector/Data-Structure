#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mylist.h>
#include <mystack.h>
#include <expression.h>
#include <polynomial.h>
#include <matrix.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void buttons_connect();//绑定按钮
    void onclicked(Buttons _type,QString _btn);//点击按钮

    void translate();//中缀转后缀
    bool checkBras();//检测中缀表达式中括号是否正确
    int checkPoint(const QString& str);//返回数据中点的个数。
    bool Operation();//运算
    void write(const QString& newExprssion);//按键后对文本框的操作
    bool checkLastChar();

    void runcmd();//命令行

    mylist <expressions> midexp;//中缀表达式
    mylist <expressions> rpn;//后缀表达式
    mylist <variants> varies;//变量
    mylist <func> funcs;//变量
    mystack <double> num;//数字
    mystack <expressions> symbols;//符号



private slots:
    void on_runpol_clicked();

    void on_runmat_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
