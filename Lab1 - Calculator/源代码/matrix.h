#ifndef MATRIX_H
#define MATRIX_H

#include <QWidget>
#include <mylist.h>
#include <mystack.h>
#include <expression.h>

namespace Ui
{
class matrix;
}

struct Matrix
{
    QString name;//名称
    int row;//行
    int col;//列
    double nums[10][10]={0.0};
};

class matrix : public QWidget
{
    Q_OBJECT

public:
    explicit matrix(QWidget *parent = nullptr);
    ~matrix();

    mylist <Matrix> Matrix_list;//多项式链表
    mylist <expressions> midexp;//中缀表达式
    mylist <expressions> rpn;//后缀表达式
    mystack <Matrix> num;//表达式作为四则运算中的数字
    mystack <expressions> symbols;//符号

    void translate();//中缀转后缀
    bool Operation();//计算
    double mdet(double D[10][10],int n);
    void run();

private slots:
    void on_run_clicked();

private:
    Ui::matrix *ui;
};



#endif // MATRIX_H
