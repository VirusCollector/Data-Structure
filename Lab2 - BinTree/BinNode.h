#pragma once
#include <iostream>
#if defined( DSA_REDBLACK )
#define stature(p) ((p) ? (p)->height : 0) //红黑树节点的黑高度（NULL视作外部节点，对应于0）
#else
#define stature(p) ((p) ? (p)->height : -1) //其余BST中节点的高度（NUll视作空树，对应于-1）
#endif
typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*; //节点位置
template <typename T> struct BinNode //二叉树节点模板类
{ 
    T data; //数值
    BinNodePosi<T> parent, lc, rc; //父节点及左、右孩子
    int height; //高度（通用）
    int npl; //Null Path Length（左式堆，也可直接用height代替）
    RBColor color; //颜色（红黑树）
    BinNode() :
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }
    BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL,
        int h = 0, int l = 1, RBColor c = RB_RED) :
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }
    // 操作接口
    int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
    BinNodePosi<T> insertAsLC(T const&); //作为当前节点的左孩子插入新节点
    BinNodePosi<T> insertAsRC(T const&); //作为当前节点的右孩子插入新节点
    BinNodePosi<T> succ(); //取当前节点的直接后继
    template <typename VST> void travLevel(BinNodePosi<T> x, VST& visit); //子树层次遍历
    template <typename VST> void travPre(BinNodePosi<T> x, VST& visit); //子树迭代先序遍历
    template <typename VST> void travIn(BinNodePosi<T> x, VST& visit); //子树迭代中序遍历
    template <typename VST> void travPost(BinNodePosi<T> x, VST& visit); //子树迭代后序遍历
    template <typename VST> void r_travPre(BinNodePosi<T> x, VST& visit); //子树递归先序遍历
    template <typename VST> void r_travIn(BinNodePosi<T> x, VST& visit); //子树递归中序遍历
    template <typename VST> void r_travPost(BinNodePosi<T> x, VST& visit); //子树递归后序遍历
    bool operator< (BinNodePosi<T>  bn) { return data < bn->data; } //小于
    bool operator== (BinNodePosi<T> bn) { return data == bn->data; } //等于
    BinNodePosi<T> sibling(BinNodePosi<T> x)
    {
        if (IsLChild(x))
            return x->parent->rc;
        return x->parent->lc;
    }
};
template <typename T> int BinNode<T>::size() //统计当前节点后代总数，即以其为根的子树规模
{ 
    int s = 1; //计入本身
    if (lc) s += lc->size(); //递归计入左子树规模
    if (rc) s += rc->size(); //递归计入右子树规模
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
    BinNodePosi<T> s = this; //记录后继的临时变量
    if (rc) //若有右孩子，则直接后继必在右子树中，具体地就是
    { 
        s = rc; 
        while (HasLChild(*s)) 
            s = s->lc; //右子树中最靠左（最小）的节点
    }
    else //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
    { 
        while (IsRChild(*s)) 
            s = s->parent; //逆向地沿右向分支，不断朝左上方移动
        s = s->parent; //最后再朝右上方移动一步，即抵达直接后继（如果存在）
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

