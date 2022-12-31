#include "matrix.h"
#include "ui_matrix.h"
#include <iostream>
#include <QMessageBox>
#include <QTextBlock>

matrix::matrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::matrix)
{
    ui->setupUi(this);
    ui->cmdlog->setReadOnly(true);
    this->setWindowTitle("矩阵计算");
}

matrix::~matrix()
{
    delete ui;
}

void matrix::on_run_clicked()
{
    run();
}

void matrix::run()//运行
{
    ui->cmdlog->append(ui->input->toPlainText());
    QString com=ui->input->document()->findBlockByLineNumber(0).text();
    QStringList coms=com.split(" ");
    if(coms[0]=="#def")//读取矩阵内容
    {
        if(coms.size()!=4)
        {
            QMessageBox::warning(this, "提示","输入格式错误，运算失败！");
            return;
        }
        int r=coms[2].toInt();
        int c=coms[3].toInt();//行数和列数
        Matrix new_mat;
        new_mat.row=r; new_mat.col=c;
        new_mat.name=coms[1];
        QString tempname=coms[1];
        ListNode <Matrix> *p= Matrix_list.header->succ;
        while(p!=Matrix_list.trailer)
        {
            if(tempname==p->data.name)
            {
                QMessageBox::warning(this, "提示","该矩阵已经被定义!");
                return;
            }
            p=p->succ;
        }
         for(int i=0;i<r;i++)
         {
             QStringList temp=ui->input->document()->findBlockByLineNumber(i+1).text().split(" ");
             for(int j=0;j<c;j++)
             {
                 new_mat.nums[i][j]=temp[j].toDouble();
             }
         }
         Matrix_list.push_back(new_mat);
    }
    else if(coms[0]=="#run")
    {
        if(coms.size()!=2)
        {
            QMessageBox::warning(this, "提示","输入格式错误，运算失败！");
        }
        ui->input->clear();
        ui->input->setAlignment(Qt::AlignLeft);
        QString exp=coms[1];//name作为表达式
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

              //MonoOp（t->转置，d->行列式）
               case 't': case 'd':
            {
                QString add;
                switch(exp[pointer].toLatin1())
                {
                case 't':
                {
                    add="tra";break;
                }
                case 'd':
                {
                    add="det";break;
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
                QString mat_name;;
                while(exp[++pointer]!=']')
                {
                    mat_name+=exp[pointer];
                }
                expressions current_data(mat_name,Num);//以名称来检索相应的表达式
                midexp.push_back(current_data);
                break;
            }

             }

    }
        translate();
        if(Operation())
        {
            Matrix final=num.top();
            for(int i=0;i<final.row;i++)
            {
                QString temp="";
                for(int j=0;j<final.col;j++)
                {
                    temp+=QString::number(final.nums[i][j]);
                    temp+=" ";
                }
                ui->input->append(temp);
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

       return;
    }
}

void matrix::translate()
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

bool matrix::Operation()
{
    bool divisor=true;
    while(!rpn.empty())
    {
        switch(rpn.first().type_get())
        {
        case Num:
        {
            int found=0;
            QString tempname=rpn.first().data_get();//取得名字
            ListNode <Matrix> *p= Matrix_list.header->succ;
            while(p!=Matrix_list.trailer)
            {
                if(p->data.name==tempname)
                {
                    num.push(p->data);//根据名称查找出该矩阵，加入数字栈
                    found=1;
                    break;
                }
                p=p->succ;
            }
            if(!found)
            {
                QMessageBox::warning(this, "提示","未定义该矩阵，运算失败！");
                return 0;
            }
            rpn.pop_front();
            break;
        }
        case BinoOP:
        {
            Matrix temp1=num.top();//被减数，后乘数
            num.pop();
            Matrix temp2=num.top();//减数，先乘数
            num.pop();
            Matrix result;
            if(rpn.first().data_get()=="+")//加法
            {
               if(temp1.row==temp2.row&&temp1.col==temp2.col)
               {
                   result.row=temp1.row;
                   result.col=temp1.col;
                   for(int i=0;i<result.row;i++)
                   {
                       for(int j=0;j<result.col;j++)
                       {
                           result.nums[i][j]=temp1.nums[i][j]+temp2.nums[i][j];//若矩阵行列数相同则相加
                       }
                   }
               }
               else
               {
                   QMessageBox::warning(this, "提示","两矩阵行列数不相同，不能相加！");
               }
            }
            else if(rpn.first().data_get()=="-")//减法
            {
                if(temp1.row==temp2.row&&temp1.col==temp2.col)
                {
                    result.row=temp1.row;
                    result.col=temp1.col;
                    for(int i=0;i<result.row;i++)
                    {
                        for(int j=0;j<result.col;j++)
                        {
                            result.nums[i][j]=temp2.nums[i][j] - temp1.nums[i][j];//若矩阵行列数相同则相加
                        }
                    }
                }
                else
                {
                    QMessageBox::warning(this, "提示","两矩阵行列数不相同，不能相减！");
                }
            }
            else if(rpn.first().data_get()=="*")//乘法
            {
                  if(temp2.col==temp1.row)
                  {
                      result.row=temp2.row;
                      result.col=temp1.col;
                      for(int i=0;i<result.row;i++)
                      {
                          for(int j=0;j<result.col;j++)
                          {
                              double temp=0.0;
                              for(int r=0;r<temp2.col;r++)
                              {
                                  temp+=temp2.nums[i][r]*temp1.nums[r][j];
                              }
                              result.nums[i][j]=temp;
                          }
                      }
                  }
                  else
                  {
                      QMessageBox::warning(this, "提示","两矩阵行列数不相同，不能相乘！");
                  }
            }

            num.push(result);
            rpn.pop_front();
            break;
        }

        case MonoOp:
        {
            QString tempop=rpn.first().data_get();
            Matrix result;
            if(tempop=="tra")//转置
            {
                Matrix temp=num.top();
                result.row=temp.col;
                result.col=temp.row;
                for(int i=0;i<temp.row;i++)
                {
                    for(int j=0;j<temp.col;j++)
                    {
                        result.nums[j][i]=temp.nums[i][j];
                    }
                }
            }
            else if(tempop=="det")//计算行列式
            {

                Matrix temp=num.top();
                result.row=1;
                result.col=1;
                if(temp.row==temp.col)
                {
                   result.nums[0][0]=mdet(temp.nums,temp.row);
                }
                else
                {
                    QMessageBox::warning(this, "提示","只有方阵才能计算行列式！");
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

double matrix::mdet(double D[10][10],int n) //输入代表矩阵的二维数组、矩阵阶数，返回矩阵的行列式
{
    double d=0;
    // 一阶二阶直接计算
    if(n==1)
        d=D[0][0];
    if(n==2)
        d=D[0][0]*D[1][1]-D[0][1]*D[1][0];
    else
    {
        for(int k=0;k<n;k++)
        {
            double M[10][10]={0};

            // 为代数余子式赋值
            for(int i=0;i<n-1;i++)
                for(int j=0;j<n-1;j++)
                    M[i][j]=D[i+1][j<k?j:j+1];

            // 按第一行展开，递归计算行列式，若元素为0则不展开
            if(D[0][k])
                d+=D[0][k]*mdet(M,n-1)*(((2+k)%2)?-1:1);
            }
    }
    return d;
}
