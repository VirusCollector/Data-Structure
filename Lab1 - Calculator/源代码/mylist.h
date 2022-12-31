#ifndef MYLIST_H
#define MYLIST_H

#include <cstddef>

//自定义链表
template <typename T> struct ListNode
{
public:
    T data; ListNode* pred; ListNode* succ;


    //构造函数
    ListNode(){};
    ListNode(T e, ListNode*p=NULL, ListNode* s=NULL)
    {
        data=e; pred=p; succ=s;
    }
    ListNode* insertback(const T & e);
    ListNode* insertfront(const T & e);
};

template <typename T> class mylist
{
public:
    int _size; ListNode<T>* header; ListNode<T>* trailer;



    void init();//初始化
    void clear();//清空列表

    mylist(){init();}//构造函数
    int size();//规模
    bool empty(){return _size<=0;};//判断是否为空
    T front(){return header->succ->data;};//取出第一个元素
    T first(){return header->succ->data;};//取出第一个元素
    T back(){return trailer->pred->data;};//取出最后一个元素
    T last(){return trailer->pred->data;};//取出最后一个元素
    ListNode <T>*  push_back(const T &e);//从末尾插入新元素
    ListNode <T>* insertafter(ListNode<T>* p, const T q);//插入指定位置
    void pop_back();//弹出末尾元素
    void pop_front();//弹出首元素
};

template <typename T> void mylist<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ=trailer;
    trailer->pred=header;
    _size=0;
}

template <typename T> ListNode<T>* mylist<T>::push_back(const T &e)
{
    ListNode<T>* p=new ListNode<T>;
    p->data=e;
    p->pred=trailer->pred;
    p->succ=trailer;
    trailer->pred->succ=p;
    trailer->pred=p;
    _size++;
    return p;
}

template <typename T> ListNode<T>* mylist<T>::insertafter(ListNode<T>* p, const T q)
{
    if(!empty())
    {

        ListNode<T>* temp=new ListNode<T>;
        temp->data=q;
        temp->pred=p;
        temp->succ=p->succ;
        p->succ->pred=temp;
        p->succ=temp;
        _size++;
        return temp;
    }
}

template <typename T> void mylist<T>::pop_back()
{
    if(!empty())
    {
        ListNode<T>*p = trailer->pred;
        p->pred->succ=p->succ;
        p->succ->pred=p->pred;
        delete p;
        _size--;
        return;
    }
}

template <typename T> void mylist<T>::pop_front()
{
    if(!empty())
    {
        ListNode<T>*p = header->succ;
        p->pred->succ=p->succ;
        p->succ->pred=p->pred;
        delete p;
        _size--;
        return;
    }
}

template <typename T> void mylist<T>::clear()
{
    while(_size>0)
        pop_back();
}

#endif // MYLIST_H
