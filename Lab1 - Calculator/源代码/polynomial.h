#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <QWidget>
#include <mylist.h>
#include <mystack.h>
#include <expression.h>

namespace Ui
{
class polynomial;
}

//表达式中每一项
struct chpol
{
    double coe;//系数
    int index;//指数
};

//表达式由每一项通过链表组成
struct pol
{
    mylist <chpol> fapol;//表达式
    QString name;//表达式名称
};

class polynomial : public QWidget
{
    Q_OBJECT

public:
    explicit polynomial(QWidget *parent = nullptr);
    ~polynomial();

    mylist <pol> pol_list;//多项式链表
    mylist <expressions> midexp;//中缀表达式
    mylist <expressions> rpn;//后缀表达式
    mystack <pol> num;//表达式作为四则运算中的数字
    mystack <expressions> symbols;//符号

    void record();//记录命令行
    void translate();//中缀转后缀
    bool Operation();//计算

private slots:
    void on_run_clicked();

private:
    Ui::polynomial *ui;
};

#endif // POLYNOMIAL_H
