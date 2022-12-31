#ifndef midexpession_H
#define midexpession_H


#include <QObject>

enum Buttons
{
    Num,//数字
    Point,//点
    BinoOP,//双目操作符
    MonoOp,//单目运算符
    Special,//特殊符号
    LeftBra,//左括号
    RightBra,//右括号
    Percent,//百分号
    Index,//指数
    Back,//退格
    Equal,//等于
    Clear,//清除
};

//变量
struct variants
{
    QString name;
    double value;
};

//函数
struct func
{
    QString name;
    QString fexp;
};

//表达式
class expressions
{

public:
    expressions(){};
    expressions(QString mydata,Buttons mytype):data(mydata),type(mytype){};
    QString data_get();//获取名称
    Buttons type_get();//获取类型

private:
    QString data;
    Buttons type;
};


#endif
