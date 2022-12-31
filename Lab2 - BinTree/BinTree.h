#pragma once
#include "BinNode.h" //引入二叉树节点类
#include <iostream>
template <typename T> class BinTree //二叉树模板类
{
public:
	int _size; BinNodePosi<T> _root; //规模、根节点
	virtual int updateHeight(BinNodePosi<T> x); //更新节点x的高度
	void updateHeightAbove(BinNodePosi<T> x); //更新节点x及其祖先的高度
	BinTree() : _size(0), _root(NULL) { } //构造函数
	~BinTree() 
	{
		if (0 < _size) 
			remove(_root); 
	} //析构函数
	int size() const { return _size; } //规模
	bool empty() const { return !_root; } //判空
	BinNodePosi<T> root() const { return _root; } //树根
	BinNodePosi<T> insert(T const&); //插入根节点
	BinNodePosi<T> insert(T const&, BinNodePosi<T>); //插入左孩子
	BinNodePosi<T> insert(BinNodePosi<T>, T const&); //插入右孩子
	//BinNodePosi<T> attach(BinTree<T>*&, BinNodePosi<T>); //接入左子树
	//BinNodePosi<T> attach(BinNodePosi<T>, BinTree<T>*&); //接入右子树
	int remove(BinNodePosi<T>); //子树删除
	//BinTree<T>* secede(BinNodePosi<T>); //子树分离
	template <typename VST> //操作器
	void travLevel(VST& visit) { if (_root) _root->travLevel(_root, visit); } //层次遍历
	template <typename VST> //操作器
	void r_travPre(VST & visit) { if (_root) _root->r_travPre(_root,visit); } //先序递归遍历
	template <typename VST> //操作器
	void r_travIn(VST& visit) { if (_root) _root->r_travIn(_root, visit); } //中序递归遍历
	template <typename VST> //操作器
	void r_travPost(VST& visit) { if (_root) _root->r_travPost(_root, visit); } //后序递归遍历

	template <typename VST> //操作器
	void travPre(VST& visit) { if (_root) _root->travPre(_root, visit); } //先序迭代遍历
	template <typename VST> //操作器
	void travIn(VST& visit) { if (_root) _root->travIn(_root, visit); } //中序迭代遍历
	template <typename VST> //操作器
	void travPost(VST& visit) { if (_root) _root->travPost(_root, visit); } //后序迭代遍历
	bool operator< (BinTree<T> const& t) //比较器（其余自行补充）
		{
			return _root && t._root && lt(_root, t._root);
		}
	bool operator== (BinTree<T> const& t) //判等器
		{
			return _root && t._root && (_root == t._root);
		}
}; //BinTree

template <typename T> inline int BinTree<T>::updateHeight(BinNodePosi<T> x)
	{
		return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
	}

template <typename T> inline void BinTree<T>::updateHeightAbove(BinNodePosi<T> x) //更新高度
	{
		while (x)
		{
			updateHeight(x);
			x = x->parent;
		}
	}

template <typename T> BinNodePosi<T> BinTree<T>::insert(T const& e)
	{
		_size = 1;
		return _root = new BinNode<T>(e);
	}

template <typename T> BinNodePosi<T> BinTree<T>::insert(T const& e, BinNodePosi<T> x)
	{
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->lc;
	}

template <typename T> BinNodePosi<T> BinTree<T>::insert(BinNodePosi<T> x, T const& e)
	{
		_size++;
		x->insertAsRC(e);
		updateHeightAbove(x);
		return x->rc;
	}

template <typename T> static void release(BinNodePosi<T> x)
{
	if (x != NULL)
	{
		delete x;
		x = NULL;
	}
}

template <typename T> static int removeAt(BinNodePosi<T> x)
{
	if (!x) 
		return 0; //递归基：空树
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //递归释放左、右子树
	//release(x->data); 
	release(x); 
	return n; //释放被摘除节点，并返回删除节点总数
} 

//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
template <typename T> int BinTree<T>::remove(BinNodePosi<T> x) 
{ 
	updateHeightAbove(x->parent); //更新祖先高度
	int n = removeAt(x); 
	_size -= n; 
	return n; //删除子树x，更新规模，返回删除节点总数
}


