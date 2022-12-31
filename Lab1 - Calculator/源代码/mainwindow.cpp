#include "mainwindow.h"
#include "expression.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>

static int iscalculated=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("计算器");
    this->setFixedSize(810,793);
    buttons_connect();
    ui->input->setReadOnly(true);
    ui->output->setReadOnly(true);
    ui->cmdlog->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttons_connect()
{
    //数字键
    connect(ui->Zero,&QPushButton::clicked,[this](){onclicked(Num,"0");});
    connect(ui->One,&QPushButton::clicked,[this](){onclicked(Num,"1");});
    connect(ui->Two,&QPushButton::clicked,[this](){onclicked(Num,"2");});
    connect(ui->Three,&QPushButton::clicked,[this](){onclicked(Num,"3");});
    connect(ui->Four,&QPushButton::clicked,[this](){onclicked(Num,"4");});
    connect(ui->Five,&QPushButton::clicked,[this](){onclicked(Num,"5");});
    connect(ui->Six,&QPushButton::clicked,[this](){onclicked(Num,"6");});
    connect(ui->Seven,&QPushButton::clicked,[this](){onclicked(Num,"7");});
    connect(ui->Eight,&QPushButton::clicked,[this](){onclicked(Num,"8");});
    connect(ui->Nine,&QPushButton::clicked,[this](){onclicked(Num,"9");});

    //双目运算符
    connect(ui->Mul,&QPushButton::clicked,[this](){onclicked(BinoOP,"*");});
    connect(ui->Div,&QPushButton::clicked,[this](){onclicked(BinoOP,"÷");});
    connect(ui->Plus,&QPushButton::clicked,[this](){onclicked(BinoOP,"+");});
    connect(ui->Sub,&QPushButton::clicked,[this](){onclicked(BinoOP,"-");});

    //指数
    connect(ui->Semicolon,&QPushButton::clicked,[this](){onclicked(Index,"^(-1)");});
    connect(ui->Square,&QPushButton::clicked,[this](){onclicked(Index,"^(2)");});
    connect(ui->Index,&QPushButton::clicked,[this](){onclicked(Index,"^");});

    //点
    connect(ui->Point,&QPushButton::clicked,[this](){onclicked(Point,".");});

    //单目运算符绑定
    connect(ui->Root,&QPushButton::clicked,[this](){onclicked(MonoOp,"√");});
    connect(ui->Ln,&QPushButton::clicked,[this](){onclicked(MonoOp,"ln");});
    connect(ui->Log,&QPushButton::clicked,[this](){onclicked(MonoOp,"log");});
    connect(ui->Sin,&QPushButton::clicked,[this](){onclicked(MonoOp,"sin");});
    connect(ui->Cos,&QPushButton::clicked,[this](){onclicked(MonoOp,"cos");});
    connect(ui->Tan,&QPushButton::clicked,[this](){onclicked(MonoOp,"tan");});
    connect(ui->Factorial,&QPushButton::clicked,[this](){onclicked(MonoOp,"!");});

    //百分号
    connect(ui->Percent,&QPushButton::clicked,[this](){onclicked(Percent,"%");});

    //括号绑定
    connect(ui->LeftBra,&QPushButton::clicked,[this](){onclicked(LeftBra,"(");});
    connect(ui->RightBra,&QPushButton::clicked,[this](){onclicked(RightBra,")");});

    //特殊符号绑定
    connect(ui->const_E,&QPushButton::clicked,[this](){onclicked(Special,"e");});
    connect(ui->const_Pai,&QPushButton::clicked,[this](){onclicked(Special,"π");});

    //清空
    connect(ui->Clear,&QPushButton::clicked,[this](){onclicked(Clear,"");});

    //退格
    connect(ui->Back,&QPushButton::clicked,[this](){onclicked(Back,"");});

    //等于
    connect(ui->Equal,&QPushButton::clicked,[this](){onclicked(Equal,"");});

    //命令行运行
    connect(ui->CmdRun,&QPushButton::clicked,[this](){runcmd();});

}

void MainWindow::onclicked(Buttons type, QString btn)
{
    if(iscalculated)//已经完成计算
    {
        if(type!=Clear)
        {
            QMessageBox::warning(this, "提示","计算完成，请点击Clear键后再进行输入！");
            return;
        }
    }
    int local_row=ui->input->document()->lineCount();//已经被iscalculated替代用来检测是否完成运算

        switch (type)//根据按钮类型执行相应效果
        {
        case Num:
        {
            if(1)
            {
                if(!midexp.empty())
                {
                    switch (midexp.back().type_get())//取前一位
                    {
                    case Num:
                    {
                        QString preNum=midexp.back().data_get();
                        if(!checkPoint(preNum))//前一数字中无小数点，则取出前面的数乘以10再加上当前数
                        {
                            double tempNum;
                            tempNum=midexp.back().data_get().toDouble();
                            tempNum*=10;
                            tempNum+=btn.toDouble();
                            midexp.pop_back();
                            expressions current_data(QString::number(tempNum),type);
                            midexp.push_back(current_data);

                            QString current_exp=ui->input->toPlainText();
                            current_exp+=btn;
                            write(current_exp);
                            break;
                        }
                       else if(checkPoint(preNum))//前一数字中有小数点
                        {
                            QString tempNum=midexp.back().data_get();
                            tempNum+=btn;
                            midexp.pop_back();
                            expressions current_data(tempNum,type);
                            midexp.push_back(current_data);

                            QString current_exp=ui->input->toPlainText();
                            current_exp+=btn;
                            write(current_exp);
                            break;
                        }
                        break;
                    }
                    case Special: case RightBra: case Percent://自动检测可省略的乘号
                    {
                        expressions multiply("*",BinoOP);
                        midexp.push_back(multiply);

                        QString current_exp=ui->input->toPlainText();
                        current_exp+=btn;
                        write(current_exp);
                        expressions current_data(btn,type);
                        midexp.push_back(current_data);
                        break;
                    }
                    case LeftBra: case BinoOP:
                    {
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=btn;
                        write(current_exp);
                        expressions current_data(btn,type);
                        midexp.push_back(current_data);
                        break;
                    }
                    default:break;
                    }
                }
                else
                {
                    QString current_exp=ui->input->toPlainText();
                    current_exp+=btn;
                    write(current_exp);
                    expressions current_data(btn,type);
                    midexp.push_back(current_data);
                    break;
                }
                break;
            }
            break;
        }
        case Point:
        {
            if(!midexp.empty()&&midexp.back().type_get()==Num)//表达式不为空且前一位为数字
            {
               QString preNum=midexp.back().data_get();
               if(checkPoint(preNum)==0)//前一数字中无小数点
               {
                   QString current_exp=ui->input->toPlainText();
                   current_exp+=btn;
                   write(current_exp);
                   midexp.pop_back();
                   preNum+=btn;
                   expressions current_data(preNum,Num);
                   midexp.push_back(current_data);
                   break;
               }
            }
            break;
        }
        case LeftBra: case Special:
        {
            if(local_row==0||local_row==1)
            {
                if(!midexp.empty())
                {
                    switch(midexp.back().type_get())//取前一位字符
                    {
                    case Num://为数字则补充上省略的乘号
                    {
                        QString finChar=ui->input->toPlainText();
                        finChar=finChar.mid(finChar.size()-1,1);
                        if(finChar!=".")
                        {
                            expressions multiply("*",BinoOP);
                            midexp.push_back(multiply);

                            QString current_exp=ui->input->toPlainText();
                            current_exp+=btn;
                            write(current_exp);
                            expressions current_data(btn,type);
                            midexp.push_back(current_data);
                        }
                         break;
                    }
                    case RightBra:  case Special: case Percent:
                    {
                         expressions multiply("*",BinoOP);
                         midexp.push_back(multiply);

                         QString current_exp=ui->input->toPlainText();
                         current_exp+=btn;
                         write(current_exp);
                         expressions current_data(btn,type);
                         midexp.push_back(current_data);
                         break;
                    }
                    case BinoOP: case LeftBra://前一字符为双目运算符或左括号时，直接将当前符号输入中缀表达式中
                    {
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=btn;
                        write(current_exp);
                        expressions current_data(btn,type);
                        midexp.push_back(current_data);
                        break;
                    }
                        default:break;
                    }
                }
                else //左括号为第一个符号，直接输入中缀表达式中
                {
                    QString current_exp=ui->input->toPlainText();
                    current_exp+=btn;
                    write(current_exp);
                    expressions current_data(btn,type);
                    midexp.push_back(current_data);
                    break;
                }
            }
            break;
        }
        case RightBra:
        {
            if(!midexp.empty()&&checkBras())
            {
                switch(midexp.back().type_get())
                {
                case RightBra: case Num: case Special: case Percent: case MonoOp://右括号的前一符号只可为右括号，数字、特殊符号、百分号
                {
                    if(midexp.back().type_get()==MonoOp&&midexp.back().data_get()!="!")
                        break;
                    QString current_exp=ui->input->toPlainText();
                    current_exp+=btn;
                    write(current_exp);
                    expressions current_data(btn,type);
                    midexp.push_back(current_data);
                    break;
                }
                    default:break;
                }
            }
            break;
        }
        case Percent:
        {
            //前一符号只可为右括号，数字、特殊符号、百分号；
            if(!midexp.empty()&&(midexp.back().type_get()==Percent||midexp.back().type_get()==Num||midexp.back().type_get()==RightBra))
            {
                QString current_exp=ui->input->toPlainText();
                current_exp+=btn;
                write(current_exp);
                expressions current_data(btn,type);
                midexp.push_back(current_data);
                break;
            }
            break;
        }
        case MonoOp:
        {
            if(local_row==1)
            {
                //如果为阶乘符号，其前面只能跟整数
                if(btn=="!")
                {
                    QString preNum=midexp.back().data_get();
                    if(!checkPoint(preNum))
                    {
                        expressions current_data("!",MonoOp);
                        midexp.push_back(current_data);
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=btn;
                        write(current_exp);
                    }
                    break;
                }
                //前一符号为数字或右括号、百分号，补充省略乘号
                if(!midexp.empty()&&(midexp.back().type_get()==Num||midexp.back().type_get()==RightBra||midexp.back().type_get()==Percent||midexp.back().type_get()==Special))
                {
                    expressions multiply("*",BinoOP);
                    midexp.push_back(multiply);

                    QString current_exp=ui->input->toPlainText();
                    current_exp+=btn;
                    current_exp+="(";
                    write(current_exp);
                    expressions current_data(btn,type);
                    midexp.push_back(current_data);
                    expressions cur_data1("(",LeftBra);
                    midexp.push_back(cur_data1);
                    break;
                }

                else if(midexp.empty()||midexp.back().type_get()==LeftBra||midexp.back().type_get()==Index||midexp.back().type_get()==BinoOP)
                {
                    QString current_exp=ui->input->toPlainText();
                    current_exp+=btn;
                    current_exp+="(";
                    write(current_exp);
                    expressions current_data(btn,type);
                    midexp.push_back(current_data);
                    expressions cur_data1("(",LeftBra);
                    midexp.push_back(cur_data1);
                    break;
                }
            }
            break;
        }
        case BinoOP:
        {
            if(local_row==1)
            {
                if(!midexp.empty()&&midexp.back().type_get()!=Point)//表达式非空且前一字符不为点
                {
                    //符号为减号且前一符号为左括号、双目运算符时
                    if(btn=="-"&&(midexp.back().type_get()==LeftBra||midexp.back().data_get()=="*"||midexp.back().data_get()=="÷"))
                    {
                         expressions current_data("0",Num);//在减号前加上0，来实现按负号的功能
                         midexp.push_back(current_data);
                         QString current_exp=ui->input->toPlainText();
                         current_exp+=btn;
                         write(current_exp);
                         expressions cur_data1(btn,type);
                         midexp.push_back(cur_data1);
                         break;
                    }
                    //当前符号为乘号或除号时，前一字符不可为其他双目运算符或左括号及点
                    else if((btn=="*"||btn=="÷")&&(midexp.back().type_get()!=BinoOP&&midexp.back().type_get()!=LeftBra))
                    {
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=btn;
                        write(current_exp);
                        expressions current_data(btn,type);
                        midexp.push_back(current_data);
                        break;
                    }
                    //当前符号为加号或减号时(减号不表示负号)，前一字符不可为其他双目运算符或左括号
                    else if((btn=="+"||btn=="-")&&midexp.back().type_get()!=BinoOP&&midexp.back().type_get()!=LeftBra)
                    {
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=btn;
                        write(current_exp);
                        expressions current_data(btn,type);
                        midexp.push_back(current_data);
                        break;
                    }
                }
                //表达式不为空，第一个符号为减号
                else if(midexp.empty()&&btn=="-")
                {
                    expressions current_data("0",Num);//在减号前加上0，来实现按负号的功能
                    midexp.push_back(current_data);

                    QString current_exp=ui->input->toPlainText();
                    current_exp+=btn;
                    write(current_exp);
                    expressions cur_data1(btn,type);
                    midexp.push_back(cur_data1);
                    break;
                }
            }

            break;
        }
        case Index:
        {
            if(local_row==1)
            {
                //当前符号为^且前一符号为数字或右括号时
                if(!midexp.empty()&&(midexp.back().type_get()==Num||midexp.back().type_get()==RightBra||midexp.back().type_get()==Special))
                {
                    if(btn=="^")
                    {
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=btn;
                        current_exp+="(";
                        write(current_exp);
                        expressions current_data(btn,type);
                        midexp.push_back(current_data);
                        expressions cur_data1("(",LeftBra);
                        midexp.push_back(cur_data1);
                        break;
                    }
                    else if(btn=="^(-1)")
                    {
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=btn;
                        write(current_exp);

                        expressions current_data("^",type);
                        midexp.push_back(current_data);
                        expressions cur_data1("(",LeftBra);
                        midexp.push_back(cur_data1);
                        expressions cur_data2("0",Num);
                        midexp.push_back(cur_data2);
                        expressions cur_data3("-",BinoOP);
                        midexp.push_back(cur_data3);
                        expressions cur_data4("1",Num);
                        midexp.push_back(cur_data4);
                        expressions cur_data5(")",RightBra);
                        midexp.push_back(cur_data5);
                        break;
                    }
                    else if(btn=="^(2)")//当前符号为^时，且前一符号为数字或右括号
                    {
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=btn;
                        write(current_exp);

                        expressions current_data("^",type);
                        midexp.push_back(current_data);
                        expressions cur_data1("(",LeftBra);
                        midexp.push_back(cur_data1);
                        expressions cur_data2("2",Num);
                        midexp.push_back(cur_data2);
                        expressions cur_data3(")",RightBra);
                        midexp.push_back(cur_data3);
                        break;
                    }
                    break;
                }
            }
            break;
        }
        case Back:
        {
             QString curExpression=ui->input->toPlainText();//获取文本框中显示的表达式
             if(!midexp.empty())
             {
                 curExpression=curExpression.mid(0,curExpression.size()-1);//去掉当前表达式的最后一个字符(即所删掉的字符)
                 switch(midexp.back().type_get())
                 {
                 case RightBra: case BinoOP: case Percent://最后的字符为右括号、双目运算符或百分号可直接从表达式中删除
                 {
                     midexp.pop_back();//删除中缀表达式中最后的字符
                     break;
                 }
                 case Num:
                 {
                     if(midexp.back().data_get().size()>1)//该数据长度大于1
                     {
                         QString data=midexp.back().data_get().mid(0,midexp.back().data_get().size()-1);
                         midexp.pop_back();
                         expressions cur_data(data,Num);
                         midexp.push_back(cur_data);
                         break;
                     }
                     else//该数据长度为1
                     {
                         QString final=curExpression.mid(curExpression.size()-1,1);
                         midexp.pop_back();
                         if(final==")"||final=="%"||final=="e"||final=="π")//在文本框中该数字的前一个字符为右括号、百分号或特殊字符时，则对应的中缀表达式中多一个乘号，需将乘号删除
                         {
                             midexp.pop_back();//删除中缀表达式中的乘号
                         }
                         break;
                     }
                     break;
                 }
                 case Special:
                 {
                     midexp.pop_back();
                     if(curExpression.size()>0)
                     {
                         QString final=curExpression.mid(curExpression.size()-1,1);
                         if(final==")"||final=="%"||final=="e"||final=="π"||(final>="0"&&final<="9"))//在文本框中该数字的前一个字符为右括号、百分号、特殊字符或数字时，则对应的中缀表达式中多一个乘号，需将乘号删除
                         {
                             midexp.pop_back();//删除中缀表达式中的乘号
                         }
                     }
                     break;
                 }
                 case LeftBra:
                 {
                     midexp.pop_back();//删除中缀表达式中的数字(及所需删除的左括号)
                     if(curExpression.size()>0)
                     {
                         QString final=curExpression.mid(curExpression.size()-1,1);//取表达式最后的一个字符
                         //在文本框中该左括号的前一个字符为右括号、百分号、特殊字符或数字时，则对应的中缀表达式中多一个乘号，需将乘号删除
                         if(final==")"||final=="%"||final=="e"||final=="π"||(final>="0"&&final<="9"))
                         {
                             midexp.pop_back();//删除中缀表达式中的乘号
                         }
                         //在文本框中该左括号的前一个字符为指数符号或单目运算符
                         else if(final=="^"||final=="n"||final=="g"||final=="s"||final=="√")
                         {
                             Buttons cur_dataType=midexp.back().type_get();
                             QString cur_data=midexp.back().data_get();
                             midexp.pop_back();//将当前符号从中缀表达式中删除
                             switch(cur_dataType)
                             {
                             case MonoOp:
                             {
                                 if(cur_data=="cos"||cur_data=="sin"||cur_data=="tan"||cur_data=="log")
                                 {
                                     curExpression=curExpression.mid(0,curExpression.size()-3);
                                     final=curExpression.mid(curExpression.size()-1,1);//取表达式最后的一个字符
                                     if(final==")"||final=="%"||final=="e"||final=="π"||(final>="0"&&final<="9"))
                                     {
                                         midexp.pop_back();
                                     }
                                 }
                                 else if(cur_data=="ln")
                                 {
                                     curExpression=curExpression.mid(0,curExpression.size()-2);
                                     final=curExpression.mid(curExpression.size()-1,1);//取表达式最后的一个字符
                                     if(final==")"||final=="%"||final=="e"||final=="π"||(final>="0"&&final<="9"))
                                     {
                                         midexp.pop_back();
                                     }
                                 }
                                 else if(cur_data=="√")
                                 {
                                     curExpression=curExpression.mid(0,curExpression.size()-1);
                                     final=curExpression.mid(curExpression.size()-1,1);//取表达式最后的一个字符
                                     if(final==")"||final=="%"||final=="e"||final=="π"||(final>="0"&&final<="9"))
                                     {
                                         midexp.pop_back();
                                     }
                                 }
                                 else if(cur_data=="^")
                                 {
                                     curExpression=curExpression.mid(0,curExpression.size()-1);
                                 }
                                 break;
                             }
                             case Index:
                             {
                                 curExpression=curExpression.mid(0,curExpression.size()-1);//获取文本框中除去最后字符的表达式(即删掉原表达式中末尾的"^"符号)
                                 break;
                             }
                             default:break;
                             }
                         }
                     }
                     break;
                 }
                 case MonoOp:
                 {
                     if(midexp.back().data_get()=="!")//如果为阶乘符号
                     {
                         midexp.pop_back();//删除中缀表达式中最后的字符
                         break;
                     }
                 }
                 default:break;
                 }
                 write(curExpression);
             }
             break;
        }
        case Clear:
        {
            ui->input->clear();
            ui->input->setAlignment(Qt::AlignLeft);
            ui->output->clear();
            iscalculated=0;
           while(!midexp.empty())
           {
               midexp.pop_back();
           }
           while(!rpn.empty())
           {
               rpn.pop_back();
           }
            break;
        }
        case Equal:
        {

            if(!iscalculated&&!checkBras()&&checkLastChar())
            {
                translate();
                if(Operation())
                {
                    ui->output->append(QString::number(num.top()));
                    iscalculated=1;
                }
            }
        }
            default:break;
        }

}

int MainWindow::checkPoint(const QString& str)
{
    int point=0;//记录点的个数
    for(int i=0;i<str.size();i++)
    {
        if(str.mid(i,1)==".")
            point++;
    }
    return point;
}

bool MainWindow::checkBras()//检测括号匹配
{
    int leftcount=0;//记录缺少对应右括号的左括号的总数
    if(!midexp.empty())
    {
        ListNode <expressions> *p= midexp.header->succ;
        while(p!=midexp.trailer)
        {
            if(p->data.type_get()==LeftBra)
                leftcount++;
            if(p->data.type_get()==RightBra)
                leftcount--;
            p=p->succ;
        }
    }
    if(leftcount>0)
        return true;
    else
        return false;
}

void MainWindow::runcmd()
{
    ui->cmdlog->append(ui->Cmd->toPlainText());//记录命令行
    //以空格分为三段，第一段为指令，第二段为名称，第三段为值或表达式
    QStringList coms=ui->Cmd->toPlainText().split(' ');

    if(coms[0]=="#def")//定义变量
    {
        if(coms.size()!=3)
        {
            QMessageBox::warning(this, "提示","输入格式错误，运算失败！");
            return;
        }
        QString tempname=coms[1];
        ListNode <variants> *p= varies.header->succ;
        while(p!=varies.trailer)
        {
            if(tempname==p->data.name)
            {
                QMessageBox::warning(this, "提示","该变量已经被定义!");
                return;
            }
            p=p->succ;
        }
        variants new_var;
        new_var.name=coms[1];
        new_var.value=coms[2].toDouble();
        varies.push_back(new_var);
    }
    else if(coms[0]=="#let")//改变变量值
    {
        if(coms.size()!=3)
        {
            QMessageBox::warning(this, "提示","输入格式错误，运算失败！");
            return;
        }
        int flag=0;
        QString tempname=coms[1];
        ListNode <variants> *p= varies.header->succ;
        while(p!=varies.trailer)
        {
            if(tempname==p->data.name)
            {
                p->data.value=coms[2].toDouble();
                flag=1;
                break;
            }
            p=p->succ;
        }
        if(!flag)
        {
            QMessageBox::warning(this, "提示","该变量未定义，不可更改值!");
            return;
        }
    }
    else if(coms[0]=="#fuc")
    {
        if(coms.size()!=3)
        {
            QMessageBox::warning(this, "提示","输入格式错误，运算失败！");
            return;
        }
        QString tempname=coms[1];
        ListNode <func> *p= funcs.header->succ;
        while(p!=funcs.trailer)
        {
            if(tempname==p->data.name)
            {
                QMessageBox::warning(this, "提示","该函数已经被定义!");
                return;
            }
            p=p->succ;
        }
        func new_func;
        new_func.name=coms[1];
        new_func.fexp=coms[2];
        funcs.push_back(new_func);
    }
    else if(coms[0]=="#run")//计算表达式或函数式
    {
        if(coms.size()!=2)
        {
            QMessageBox::warning(this, "提示","输入格式错误，运算失败！");
            return;
        }
        ui->input->clear();
        ui->input->setAlignment(Qt::AlignLeft);
        ui->output->clear();
        QString exp=coms[1];
        //替换sin，cos，tan，ln，log为s，c，t，n，g单字符
        exp.replace("sin","s");
        exp.replace("cos","c");
        exp.replace("tan","t");
        exp.replace("ln","n");
        exp.replace("log","g");
        exp.replace("π","p");
        exp.replace("÷","/");

        for(int pointer=0;pointer<exp.size();pointer++)//替换函数成为表达式
        {
            int start=0,len=0;
            if(exp[pointer]=='@')
            {
                int found=0;
                start=pointer;
                QString fuc_name="";
                QString fuc_exp="(";
                QString fuc_num="";
                while(exp[++pointer]!='(')
                {
                    fuc_name+=QString(exp[pointer]);//获取函数名
                }
                fuc_num+="(";
                while(exp[++pointer]!=')')
                { 
                    fuc_num+=QString(exp[pointer]);//获取自变量值
                }
                fuc_num+=")";
                len=pointer-start+1;
                ListNode <func> *p= funcs.header->succ;
                while(p!=funcs.trailer)
                {
                    if(fuc_name==p->data.name)
                    {
                        fuc_exp+=p->data.fexp;
                        found=1;
                        break;
                    }
                    p=p->succ;
                }
                if(!found)
                {
                    QMessageBox::warning(this, "提示","找不到该函数！");
                    return;
                }
                fuc_exp.replace("x",fuc_num);
                fuc_exp+=")";
                exp.replace(start,len,fuc_exp);
            }
        }

        for(int pointer=0;pointer<exp.size();pointer++)//遍历整个字符串
        {
            switch(exp[pointer].toLatin1())
            {
               //Num
               case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':  case '9':
               {
                if(!midexp.empty())
                {
                    switch (midexp.back().type_get())//取前一位
                    {
                    case Num:
                    {
                        QString preNum=midexp.back().data_get();
                        if(!checkPoint(preNum))//前一数字中无小数点，则取出前面的数乘以10再加上当前数
                        {
                            double tempNum;
                            tempNum=midexp.back().data_get().toDouble();
                            tempNum*=10;
                            tempNum+=(double)(exp[pointer].toLatin1()-48);
                            midexp.pop_back();
                            expressions current_data(QString::number(tempNum),Num);
                            midexp.push_back(current_data);

                            QString current_exp=ui->input->toPlainText();
                            current_exp+=QString(exp[pointer]);
                            write(current_exp);
                            break;
                        }
                       else if(checkPoint(preNum))//前一数字中有小数点
                        {
                            QString tempNum=midexp.back().data_get();
                            tempNum+=QString(exp[pointer]);
                            midexp.pop_back();
                            expressions current_data(tempNum,Num);
                            midexp.push_back(current_data);

                            QString current_exp=ui->input->toPlainText();
                            current_exp+=QString(exp[pointer]);
                            write(current_exp);
                            break;
                        }
                        break;
                    }
                    case LeftBra: case BinoOP:
                    {
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=QString(exp[pointer]);
                        write(current_exp);
                        expressions current_data(QString(exp[pointer]),Num);
                        midexp.push_back(current_data);
                        break;
                    }
                    }
                }
                else
                {
                    QString current_exp=ui->input->toPlainText();
                    current_exp+=QString(exp[pointer]);
                    write(current_exp);
                    expressions current_data(QString(exp[pointer]),Num);
                    midexp.push_back(current_data);
                    break;
                }
                break;
               }

               //Point
               case '.':
                {
                if(!midexp.empty()&&midexp.back().type_get()==Num)//表达式不为空且前一位为数字
                {
                    QString preNum=midexp.back().data_get();
                    if(checkPoint(preNum)==0)//前一数字中无小数点
                    {
                        QString current_exp=ui->input->toPlainText();
                        current_exp+=QString(exp[pointer]);
                        write(current_exp);
                        midexp.pop_back();
                        preNum+=QString(exp[pointer]);
                        expressions current_data(preNum,Num);
                        midexp.push_back(current_data);
                        break;
                    }
                }
                  break;
                }

               //LeftBra
               case '(':
            {
                QString current_exp=ui->input->toPlainText();
                current_exp+=QString(exp[pointer]);
                write(current_exp);
                expressions current_data(QString(exp[pointer]),LeftBra);
                midexp.push_back(current_data);
                break;
            }

               //RightBra
               case ')':
             {
                 QString current_exp=ui->input->toPlainText();
                 current_exp+=QString(exp[pointer]);
                 write(current_exp);
                 expressions current_data(")",RightBra);
                 midexp.push_back(current_data);
                 break;
             }

               //e和π
               case 'e': case'p':
            {
                if(exp[pointer]=='e')
                {
                    QString current_exp=ui->input->toPlainText();
                    current_exp+="e";
                    write(current_exp);
                    expressions current_data("e",Special);
                    midexp.push_back(current_data);
                    break;
                }
                else
                {
                    QString current_exp=ui->input->toPlainText();
                    current_exp+="π";
                    write(current_exp);
                    expressions current_data("π",Special);
                    midexp.push_back(current_data);
                    break;
                }
                break;
            }

               //Percent
               case '%':
            {
                QString current_exp=ui->input->toPlainText();
                current_exp+="%";
                write(current_exp);
                expressions current_data("%",Percent);
                midexp.push_back(current_data);
                break;
            }

              //MonoOp
               case 's': case 'c': case 't': case 'n': case 'g': case '!':
            {
                QString add;
                switch(exp[pointer].toLatin1())
                {
                case 's':
                {
                    add="sin";break;
                }
                case 'c':
                {
                    add="cos";break;
                }
                case 't':
                {
                    add="tan";break;
                }
                case 'n':
                {
                    add="ln";break;
                }
                case 'g':
                {
                    add="log";break;
                }
                case '!':
                {
                add="!";break;
                }

                }
                QString current_exp=ui->input->toPlainText();
                current_exp+=add;
                write(current_exp);
                expressions current_data(add,MonoOp);
                midexp.push_back(current_data);
                break;
            }

              //BinoOp
               case '+': case'-': case '*': case '/':
            {
                if(exp[pointer]=='-'&&midexp.back().type_get()==LeftBra)
                {//符号为减号且前一符号为左括号
                     expressions current_data("0",Num);//在减号前加上0，来实现按负号的功能
                     midexp.push_back(current_data);
                }
                QString current_exp=ui->input->toPlainText();
                if(exp[pointer]=='/')
                    current_exp+="÷";
                else
                    current_exp+=QString(exp[pointer]);
                write(current_exp);
                if(exp[pointer]=='/')
                {
                    expressions cur_data1("÷",BinoOP);
                    midexp.push_back(cur_data1);
                }
                else
                {
                    expressions cur_data1(QString(exp[pointer]),BinoOP);
                    midexp.push_back(cur_data1);
                }

                break;
            }

              //Index
               case '^':
            {
                QString current_exp=ui->input->toPlainText();
                current_exp+="^";
                write(current_exp);
                expressions current_data("^",Index);
                midexp.push_back(current_data);
                break;
            }

              //variant
               case '[':
            {
                int found=0;
                QString var_name;
                double tempNum=0;
                while(exp[++pointer]!=']')
                {
                    var_name+=exp[pointer];
                }
                ListNode <variants> *p= varies.header->succ;
                while(p!=varies.trailer)
                {
                    if(var_name==p->data.name)
                    {
                        tempNum=p->data.value;
                        found=1;
                        break;
                    }
                    p=p->succ;
                }
                if(!found)
                {
                    QMessageBox::warning(this, "提示","该变量未定义，计算失败！");
                    return;
                }
                expressions current_data1(QString(exp[pointer]),LeftBra);
                midexp.push_back(current_data1);
                expressions current_data2(QString::number(tempNum),Num);
                midexp.push_back(current_data2);
                expressions current_data3(")",RightBra);
                midexp.push_back(current_data3);

                QString current_exp=ui->input->toPlainText();
                current_exp+="(";
                current_exp+=QString::number(tempNum);
                current_exp+=")";
                write(current_exp);

                break;
            }

            default:
            {
                QMessageBox::warning(this, "提示","输入格式错误，计算失败！");
                return;
            }
            }
        }

        if(!iscalculated&&!checkBras()&&checkLastChar())
        {
            translate();
            if(Operation())
            {
                ui->output->append(QString::number(num.top()));
            }
            else
            {
                QMessageBox::warning(this, "提示","输入格式错误，计算失败！");
            }
        }
        else
        {
            QMessageBox::warning(this, "提示","输入格式错误，计算失败！");
        }

       while(!midexp.empty())
       {
           midexp.pop_back();
       }
       while(!rpn.empty())
       {
           rpn.pop_back();
       }
       ui->Cmd->clear();
    }

    ui->Cmd->clear();
}

void MainWindow::translate()
{
    while(!midexp.empty())
    {
        switch(midexp.first().type_get())
        {
        case Num: case Special: //数字直接输入后缀表达式
        {
            expressions current_data(midexp.first().data_get(),midexp.first().type_get());
            rpn.push_back(current_data);
            break;
        }
        case LeftBra: //左括号优先级最高直接压入符号栈
        {
            expressions cur_char(midexp.first().data_get(),midexp.first().type_get());
            symbols.push(cur_char);
            break;
        }
        case RightBra: //符号为右括号则将符号栈中符号一一出栈并输入后缀表达式，直到碰到左括号
        {
            while(symbols.top().type_get()!=LeftBra)
            {
                expressions cur_char(symbols.top().data_get(),symbols.top().type_get());
                rpn.push_back(cur_char);
                symbols.pop();
            }
            symbols.pop();//左括号出栈
            break;
        }
        case BinoOP: //双目运算符
        {
            if(midexp.first().data_get()=="+"||midexp.first().data_get()=="-") //+、-的优先级最低
            {
                while(!symbols.empty()&&symbols.top().type_get()!=LeftBra)//将符号栈中元素出栈直到符号栈为空或遇到左括号
                {
                    expressions cur_char(symbols.top().data_get(),symbols.top().type_get());
                    rpn.push_back(cur_char);
                    symbols.pop();
                }
                expressions cur_char(midexp.first().data_get(),midexp.first().type_get());
                symbols.push(cur_char);
                break;
            }
            if(midexp.first().data_get()=="*"||midexp.first().data_get()=="÷")//*、÷的优先级只高于+、-
            {
                //将符号栈中元素出栈直到符号栈为空或遇到左括号或+、-
                while(!symbols.empty()&&(symbols.top().type_get()!=LeftBra&&symbols.top().data_get()!="+"&&symbols.top().data_get()!="-"))
                {
                    expressions cur_char(symbols.top().data_get(),symbols.top().type_get());
                    rpn.push_back(cur_char);
                    symbols.pop();
                }
                expressions cur_char(midexp.first().data_get(),midexp.first().type_get());
                symbols.push(cur_char);
                break;
            }
            break;
        }
        case MonoOp: case Index: case Percent://优先级仅次于左括号
        {
            //符号栈不为空，且栈顶元素为单目运算符或指数符号、百分号时，将栈顶元素输入到后缀表达式中并删除栈顶元素
            while(!symbols.empty()&&(symbols.top().type_get()==MonoOp||symbols.top().type_get()==Index||symbols.top().type_get()==Percent))
            {
                expressions cur_char(symbols.top().data_get(),symbols.top().type_get());
                rpn.push_back(cur_char);
                symbols.pop();
            }
            //当前符号入栈
            expressions cur_char(midexp.first().data_get(),midexp.first().type_get());
            symbols.push(cur_char);
            break;
        }
        default:break;
        }
        midexp.pop_front();
    }
    if(midexp.empty()&&!symbols.empty())
    {
        //将符号栈中剩余符号依次出栈输入到后缀表达式中
        while(!symbols.empty())
        {
            expressions cur_char(symbols.top().data_get(),symbols.top().type_get());
            rpn.push_back(cur_char);
            symbols.pop();
        }
    }
}

bool MainWindow::Operation()//根据后缀表达式计算出结果
{
    bool divisor=true;
    while(!rpn.empty())
    {
        switch(rpn.first().type_get())
        {
        case Num:
        {
            double temp=rpn.first().data_get().toDouble();
            num.push(temp);
            rpn.pop_front();
            break;
        }
        case BinoOP:
        {
            double temp1=num.top();//操作数1
            num.pop();
            double temp2=num.top();//操作数2
            num.pop();
            double temp;
            if(rpn.first().data_get()=="+")
            {
                 temp=temp2+temp1;
            }
            else if(rpn.first().data_get()=="-")
            {
                 temp=temp2-temp1;
            }
            else if(rpn.first().data_get()=="*")
            {
                 temp=temp2*temp1;
            }
            else if(rpn.first().data_get()=="÷")
            {
                if(temp1==0)
                {
                    QMessageBox::warning(this, "提示","除数不可为0！");
                    iscalculated=1;
                    return 0;
                }
                else
                    temp=temp2/temp1;
            }
            num.push(temp);
            rpn.pop_front();
            break;
        }
        case Percent:
        {//百分比
            double temp1=num.top();//操作数
            num.pop();
            double temp=temp1/100;
            num.push(temp);
            rpn.pop_front();
            break;
        }
        case Special:
        {
            double temp;
            if(rpn.first().data_get()=="e")
                temp=exp(1);
            else if(rpn.first().data_get()=="π")
                temp=acos(-1);
            num.push(temp);
            rpn.pop_front();
            break;
        }
        case Index:
        {
            double temp1=num.top();//操作数1
            num.pop();
            double temp2=num.top();//操作数2
            num.pop();
            double temp;
            temp=pow(temp2,temp1);
            num.push(temp);
            rpn.pop_front();
            break;
        }
        case MonoOp:
        {
            QString tempop=rpn.first().data_get();
            double temp=num.top();//操作数
            if(tempop=="√")
                temp=sqrt(temp);
            else if(tempop=="sin")
                temp=sin(temp);
            else if(tempop=="cos")
                temp=cos(temp);
            else if(tempop=="tan")
                temp=tan(temp);
            else if(tempop=="ln")
                temp=log(temp);
            else if(tempop=="log")
                temp=log10(temp);
            else if(tempop=="!")
             {
                double copy=temp;
                while(--copy>0)
                    temp*=copy;
            }
            num.pop();
            num.push(temp);
            rpn.pop_front();
           break;
        }
        default:break;
        }
    }
    return divisor;
}

//在文本框中填入新的表达式
void MainWindow::write(const QString& newexpression)
{
    ui->input->clear();
    ui->input->setAlignment(Qt::AlignLeft);
    ui->input->insertPlainText(newexpression);
}

bool MainWindow::checkLastChar()
{
    bool checkResult=false;
    if(!midexp.empty())
    {
        switch(midexp.back().type_get())
        {
        case LeftBra: case MonoOp: case BinoOP:case Point:case Index:
        {
            if(midexp.back().data_get()=="!")
                checkResult=true;
            else
                checkResult=false;
            break;
        }
        case Num:
        {
            QString lastChar=midexp.back().data_get();
            lastChar=lastChar.mid(lastChar.size()-1,1);
            if(lastChar==".")
               checkResult=false;
            else
               checkResult=true;
            break;
        }
        case Special: case RightBra:case Percent:
        {
            checkResult=true;
            break;
        }
        default:checkResult=true;
        }
    }

    return checkResult;
}

//打开多项式计算窗口
void MainWindow::on_runpol_clicked()
{
    polynomial* new_pol=new polynomial;
    new_pol->setAttribute(Qt::WA_DeleteOnClose, true);
    new_pol->show();
}

void MainWindow::on_runmat_clicked()
{
    matrix* new_mat=new matrix;
    new_mat->setAttribute(Qt::WA_DeleteOnClose, true);
    new_mat->show();
}

