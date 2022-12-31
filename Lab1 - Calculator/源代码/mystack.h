#ifndef MYSTACK_H
#define MYSTACK_H
#include <mylist.h>


//继承于自定义列表的自定义栈
template <typename T> class mystack: public mylist<T>
{
public:
    void init();//初始化
    T pop();//弹出元素
    void push(const T& t);//压入元素
    T top();//取栈顶元素
};

template <typename T> void mystack<T>::init()
{
    mylist<T>::init();
}

template <typename T> T mystack<T>::pop()
{
    T temp=mylist<T>::last();
    mylist<T>::pop_back();
    return temp;
}

template <typename T> void mystack<T>::push(const T& t)
{
    mylist<T>::push_back(t);
}

template <typename T> T mystack<T>::top()
{
    return mylist<T>::last();
}

#endif // MYSTACK_H
