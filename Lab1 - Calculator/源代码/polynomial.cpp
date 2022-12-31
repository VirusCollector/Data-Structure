#include "polynomial.h"
#include "ui_polynomial.h"
#include <iostream>
#include <QMessageBox>

polynomial::polynomial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::polynomial)
{
    ui->setupUi(this);
    ui->output->setReadOnly(true);
    this->setWindowTitle("多项式计算");
}

polynomial::~polynomial()
{
    delete ui;
}

//运行
void polynomial::on_run_clicked()
{
    record();
    QStringList coms=ui->input->toPlainText().split(' ');
    if(coms.size()<2)
    {
        QMessageBox::warning(this, "提示","输入格式错误，运算失败！");
        return;
    }
    if(coms[0]=="#def")//创建多项式
    {
        if(coms.size()!=3)
        {
            QMessageBox::warning(this, "提示","输入格式错误，运算失败！");
            return;
        }
        pol newpol;
        QString name=coms[1];
        newpol.name=name;
        ListNode <pol> *p= pol_list.header->succ;
        while(p!=pol_list.trailer)
        {
            if(name==p->data.name)
            {
                QMessageBox::warning(this, "提示","该多项式已经被定义!");
                return;
            }
            p=p->succ;
        }
        QStringList childs=coms[2].split(';');//分离系数和指数
        for(int m=0;m<childs.size();m++)
        {
            QStringList content=childs[m].split(',');
            chpol new_chpol;//每一项子表达式
            if(content.size()!=2)
            {
                QMessageBox::warning(this, "提示","输入格式错误，运算失败！");
                return;
            }
            new_chpol.coe=content[0].toDouble();
            new_chpol.index=content[1].toInt();
            newpol.fapol.push_back(new_chpol);//子表达式入父表达式链表
        }
        pol_list.push_back(newpol);//父表达式入表达式链表
    }
    else if(coms[0]=="#run")//计算
    {
        ui->input->clear();
        ui->input->setAlignment(Qt::AlignLeft);
        QString exp=coms[1];
        for(int pointer=0;pointer<exp.size();pointer++)//遍历整个字符串
        {
            switch(exp[pointer].toLatin1())
            {
               //LeftBra
               case '(':
            {
                expressions current_data(QString(exp[pointer]),LeftBra);
                midexp.push_back(current_data);
                break;
            }

               //RightBra
               case ')':
             {
                 expressions current_data(")",RightBra);
                 midexp.push_back(current_data);
                 break;
             }

              //MonoOp（s->积分，d->微分）
               case 's': case 'd':
            {
                QString add;
                switch(exp[pointer].toLatin1())
                {
                case 's':
                {
                    add="sum";break;
                }
                case 'd':
                {
                    add="dif";break;
                }
                }

                expressions current_data(add,MonoOp);
                midexp.push_back(current_data);
                break;
            }

              //BinoOp
               case '+': case'-': case '*':
            {
                expressions cur_data1(QString(exp[pointer]),BinoOP);
                midexp.push_back(cur_data1);
                break;
            }

              //expression
               case '[':
            {
                QString pol_name;;
                while(exp[++pointer]!=']')
                {
                    pol_name+=exp[pointer];
                }
                expressions current_data(pol_name,Num);//以名称来检索相应的表达式
                midexp.push_back(current_data);
                break;
            }
            default:
            {
                QMessageBox::warning(this, "提示","输入格式错误，计算失败！");
                return;
            }
        }

    }

        translate();

        ListNode <expressions> *s= rpn.header->succ;
        while(s!=rpn.trailer)
        {
            std::cout<<s->data.data_get().toStdString()<<" ";
            s=s->succ;
        }
        std::cout<<std::endl;

        if(Operation())
        {
            int zero_num=0;//0的项
            QString final_result="";
            pol result=num.top();
            ListNode <chpol> *p= result.fapol.header->succ;
            while(p!=result.fapol.trailer)
            {
                if(p->data.index)//指数不为0
                {
                    zero_num++;
                    QString temp="";
                    if(p->data.coe==0)
                    {
                        p=p->succ;
                        continue;
                    }
                    if(p->data.coe<0)
                    {
                        final_result=final_result.mid(0,final_result.size()-1);//除去最后一个加号
                        if(p->data.coe!=-1)
                            temp+=QString::number(p->data.coe);
                        else
                            temp+="-";
                    }
                    else if(p->data.coe!=1)
                    {
                        temp+=QString::number(p->data.coe);
                    }
                    if(p->data.index==1)
                    {
                        temp+="x+";
                    }
                    else
                    {
                        temp+="x^(";
                        temp+=QString::number(p->data.index);
                        temp+=")+";
                    }
                    final_result+=temp;
                    p=p->succ;
                }
                else //为常数项
                {
                    if(p->data.coe==0)
                    {
                        p=p->succ;
                        continue;
                    }
                    zero_num++;
                    QString temp=QString::number(p->data.coe);
                    temp+="+";
                    final_result+=temp;
                    p=p->succ;
                }
            }
            if(!zero_num&&final_result=="")
                final_result+="0";
            else
                final_result=final_result.mid(0,final_result.size()-1);
            ui->input->clear();
            ui->input->append(final_result);
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

       return;
    }

    }



void polynomial::translate()
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

bool polynomial::Operation()
{
    bool divisor=true;
    while(!rpn.empty())
    {
        //qDebug()<<rpn.first().data_get();
        switch(rpn.first().type_get())
        {
        case Num:
        {
            int found=0;
            QString tempname=rpn.first().data_get();//取得名字
            ListNode <pol> *p= pol_list.header->succ;
            while(p!=pol_list.trailer)
            {
                if(p->data.name==tempname)
                {
                    num.push(p->data);//根据名称查找出该表达式，加入数字栈
                    found=1;
                    break;
                }
                p=p->succ;
            }
            if(!found)
            {
                QMessageBox::warning(this, "提示","未定义该多项式，运算失败！");
                return 0;
            }
            rpn.pop_front();
            break;
        }
        case BinoOP:
        {
            pol temp1=num.top();//被减数
            num.pop();
            pol temp2=num.top();//减数
            num.pop();
            pol result;
            if(rpn.first().data_get()=="+")
            {
                ListNode <chpol> *p1= temp1.fapol.header->succ;
                ListNode <chpol> *p2= temp2.fapol.header->succ;
                while(p1!=temp1.fapol.trailer || p2!=temp2.fapol.trailer)
                {
                    if(p1==temp1.fapol.trailer)//p1已经到末尾
                    {
                        result.fapol.push_back(p2->data);//直接追加p2到结果表达式
                        p2=p2->succ;
                    }
                    else if(p2==temp2.fapol.trailer)//p2已经到末尾
                    {
                        result.fapol.push_back(p1->data);//直接追加p2到结果表达式
                        p1=p1->succ;
                    }
                    else//两者都未到末尾
                    {
                        if(p1->data.index==p2->data.index)//两者指数相同，可以合并
                        {
                            if(p1->data.coe+p2->data.coe!=0)//两者系数和不为0,则相加存入result中
                            {
                                chpol temp;
                                temp.coe=p1->data.coe+p2->data.coe;
                                temp.index=p1->data.index;
                                result.fapol.push_back(temp);
                                p1=p1->succ; p2=p2->succ;
                            }
                            else //都直接移动到下一项
                            {
                                p1=p1->succ; p2=p2->succ;
                            }
                        }
                        else //两者指数不同，则放入指数较小的那一项
                        {
                            if(p1->data.index<p2->data.index)
                            {
                                result.fapol.push_back(p1->data);
                                p1=p1->succ;
                            }
                            else
                            {
                                result.fapol.push_back(p2->data);
                                p2=p2->succ;
                            }
                        }
                    }
                }
            }
            else if(rpn.first().data_get()=="-")
            {
                ListNode <chpol> *p= temp1.fapol.header->succ;
                ListNode <chpol> *p1= temp2.fapol.header->succ;
                pol change;//定义改变后的表达式
                change.name=temp2.name;
                while(p!=temp1.fapol.trailer)
                {
                    chpol ch_change;
                    ch_change.coe= -p->data.coe;//将temp2系数取相反数，化减法为加法
                    ch_change.index=p->data.index;
                    change.fapol.push_back(ch_change);
                    p=p->succ;
                }
                ListNode <chpol> *p2= change.fapol.header->succ;//被减数系数全部取反后化为加法
                while(p1!=temp2.fapol.trailer || p2!=change.fapol.trailer)
                {
                    if(p1==temp2.fapol.trailer)//p1已经到末尾
                    {
                        result.fapol.push_back(p2->data);//直接追加p2到结果表达式
                        p2=p2->succ;
                    }
                    else if(p2==change.fapol.trailer)//p2已经到末尾
                    {
                        result.fapol.push_back(p1->data);//直接追加p2到结果表达式
                        p1=p1->succ;
                    }
                    else//两者都未到末尾
                    {
                        if(p1->data.index==p2->data.index)//两者指数相同，可以合并
                        {
                            if(p1->data.coe+p2->data.coe!=0)//两者系数和不为0,则相加存入result中
                            {
                                chpol temp;
                                temp.coe=p1->data.coe+p2->data.coe;
                                temp.index=p1->data.index;
                                result.fapol.push_back(temp);
                                p1=p1->succ; p2=p2->succ;
                            }
                            else //都直接移动到下一项
                            {
                                p1=p1->succ; p2=p2->succ;
                            }
                        }
                        else //两者指数不同，则放入指数较小的那一项
                        {
                            if(p1->data.index<p2->data.index)
                            {
                                result.fapol.push_back(p1->data);
                                p1=p1->succ;
                            }
                            else
                            {
                                result.fapol.push_back(p2->data);
                                p2=p2->succ;
                            }
                        }
                    }
                }
            }
            else if(rpn.first().data_get()=="*")
            {
                ListNode <chpol> *p1= temp1.fapol.header->succ;
                while(p1!=temp1.fapol.trailer)//对于p1每一个子表达式
                {
                    ListNode <chpol> *p2= temp2.fapol.header->succ;
                    while(p2!=temp2.fapol.trailer)//与p2每一个子表达式相乘
                    {
                        chpol new_chpol;
                        new_chpol.coe=p1->data.coe*p2->data.coe;
                        new_chpol.index=p1->data.index+p2->data.index;//先相乘
                        if(result.fapol.empty())//结果子表达式为空
                        {
                            result.fapol.push_back(new_chpol);
                        }
                        else
                        {
                            ListNode <chpol> *p= result.fapol.trailer->pred;
                            while(p!=result.fapol.header)//从末尾遍历结果每个子表达式
                            {
                                if(new_chpol.index>p->data.index)//指数大则插入它后面
                                {
                                    result.fapol.insertafter(p,new_chpol);
                                    break;
                                }
                                else if(new_chpol.index==p->data.index)//指数相等则系数相加
                                {
                                    p->data.coe+=new_chpol.coe;
                                    break;
                                }
                                p=p->pred;
                            }
                        }
                        p2=p2->succ;
                    }
                    p1=p1->succ;
                }
            }

            num.push(result);
            rpn.pop_front();
            break;
        }

        case MonoOp:
        {
            QString tempop=rpn.first().data_get();
            pol temp=num.top();//操作表达式
            pol result;//结果
            if(tempop=="sum")//积分
            {
                ListNode <chpol> *p= temp.fapol.header->succ;
                while(p!=temp.fapol.trailer)
                {
                    chpol new_chpol;
                    new_chpol.coe=p->data.coe / (p->data.index+1);
                    new_chpol.index=p->data.index+1;
                    result.fapol.push_back(new_chpol);
                    p=p->succ;
                }
            }
            else if(tempop=="dif")//微分
            {
                ListNode <chpol> *p= temp.fapol.header->succ;
                while(p!=temp.fapol.trailer)
                {
                    chpol new_chpol;
                    if(p->data.index==0)//常数项直接变成0
                    {
                        new_chpol.coe=0;
                        new_chpol.index=0;
                    }
                    else
                    {
                        new_chpol.coe=p->data.coe * p->data.index;
                        new_chpol.index=p->data.index-1;
                    }
                    result.fapol.push_back(new_chpol);
                    p=p->succ;
                }
            }
            num.pop();
            num.push(result);
            rpn.pop_front();
           break;
        }

        default:break;
        }
    }
    return divisor;
}

void polynomial::record()
{
    ui->output->append(ui->input->toPlainText());
}

