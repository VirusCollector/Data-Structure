#pragma once
#include <iostream>
#if defined( DSA_REDBLACK )
#define stature(p) ((p) ? (p)->height : 0) //������ڵ�ĺڸ߶ȣ�NULL�����ⲿ�ڵ㣬��Ӧ��0��
#else
#define stature(p) ((p) ? (p)->height : -1) //����BST�нڵ�ĸ߶ȣ�NUll������������Ӧ��-1��
#endif
typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*; //�ڵ�λ��
template <typename T> struct BinNode //�������ڵ�ģ����
{ 
    T data; //��ֵ
    BinNodePosi<T> parent, lc, rc; //���ڵ㼰���Һ���
    int height; //�߶ȣ�ͨ�ã�
    int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
    RBColor color; //��ɫ���������
    BinNode() :
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }
    BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL,
        int h = 0, int l = 1, RBColor c = RB_RED) :
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }
    // �����ӿ�
    int size(); //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
    BinNodePosi<T> insertAsLC(T const&); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
    BinNodePosi<T> insertAsRC(T const&); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
    BinNodePosi<T> succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
    template <typename VST> void travLevel(BinNodePosi<T> x, VST& visit); //������α���
    template <typename VST> void travPre(BinNodePosi<T> x, VST& visit); //���������������
    template <typename VST> void travIn(BinNodePosi<T> x, VST& visit); //���������������
    template <typename VST> void travPost(BinNodePosi<T> x, VST& visit); //���������������
    template <typename VST> void r_travPre(BinNodePosi<T> x, VST& visit); //�����ݹ��������
    template <typename VST> void r_travIn(BinNodePosi<T> x, VST& visit); //�����ݹ��������
    template <typename VST> void r_travPost(BinNodePosi<T> x, VST& visit); //�����ݹ�������
    bool operator< (BinNodePosi<T>  bn) { return data < bn->data; } //С��
    bool operator== (BinNodePosi<T> bn) { return data == bn->data; } //����
    BinNodePosi<T> sibling(BinNodePosi<T> x)
    {
        if (IsLChild(x))
            return x->parent->rc;
        return x->parent->lc;
    }
};
template <typename T> int BinNode<T>::size() //ͳ�Ƶ�ǰ�ڵ���������������Ϊ����������ģ
{ 
    int s = 1; //���뱾��
    if (lc) s += lc->size(); //�ݹ������������ģ
    if (rc) s += rc->size(); //�ݹ������������ģ
    return s;
}

template <typename T> BinNodePosi<T> BinNode<T>::insertAsLC(T const& e)
{
    return lc = new BinNode(e, this);
}

template <typename T> BinNodePosi<T> BinNode<T>::insertAsRC(T const& e)
{
    return rc = new BinNode(e, this);
}

template <typename T> BinNodePosi<T> BinNode<T>::succ()
{
    BinNodePosi<T> s = this; //��¼��̵���ʱ����
    if (rc) //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
    { 
        s = rc; 
        while (HasLChild(*s)) 
            s = s->lc; //�������������С���Ľڵ�
    }
    else //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
    { 
        while (IsRChild(*s)) 
            s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
        s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
    }
    return s;
}

template <typename T> bool IsRoot(BinNodePosi<T> x)
{
    return !x->parent;
}
template <typename T> bool IsLChild(BinNodePosi<T> x)
{
    return (!IsRoot(x) && x == x->parent->lc);
}
template <typename T> bool IsRChild(BinNodePosi<T> x)
{
    return (!IsRoot(x) && x == x->parent->rc);
}
template <typename T> bool HasParent(BinNodePosi<T> x)
{
    return !IsRoot(x);
}
template <typename T> bool HasLChild(BinNodePosi<T> x)
{
    return x->lc;
}
template <typename T> bool HasRChild(BinNodePosi<T> x)
{
    return x->rc;
}
template <typename T> bool HasChild(BinNodePosi<T> x)
{
    return (HasLChild(x) || HasRChild(x));
}
template <typename T> bool HasBothChild(BinNodePosi<T> x)
{
    return (HasLChild(x) && HasRChild(x));
}
template <typename T> bool IsLeaf(BinNodePosi<T> x)
{
    return !HasChild(x);
}

