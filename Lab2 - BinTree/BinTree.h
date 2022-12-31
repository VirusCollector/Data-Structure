#pragma once
#include "BinNode.h" //����������ڵ���
#include <iostream>
template <typename T> class BinTree //������ģ����
{
public:
	int _size; BinNodePosi<T> _root; //��ģ�����ڵ�
	virtual int updateHeight(BinNodePosi<T> x); //���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi<T> x); //���½ڵ�x�������ȵĸ߶�
	BinTree() : _size(0), _root(NULL) { } //���캯��
	~BinTree() 
	{
		if (0 < _size) 
			remove(_root); 
	} //��������
	int size() const { return _size; } //��ģ
	bool empty() const { return !_root; } //�п�
	BinNodePosi<T> root() const { return _root; } //����
	BinNodePosi<T> insert(T const&); //������ڵ�
	BinNodePosi<T> insert(T const&, BinNodePosi<T>); //��������
	BinNodePosi<T> insert(BinNodePosi<T>, T const&); //�����Һ���
	//BinNodePosi<T> attach(BinTree<T>*&, BinNodePosi<T>); //����������
	//BinNodePosi<T> attach(BinNodePosi<T>, BinTree<T>*&); //����������
	int remove(BinNodePosi<T>); //����ɾ��
	//BinTree<T>* secede(BinNodePosi<T>); //��������
	template <typename VST> //������
	void travLevel(VST& visit) { if (_root) _root->travLevel(_root, visit); } //��α���
	template <typename VST> //������
	void r_travPre(VST & visit) { if (_root) _root->r_travPre(_root,visit); } //����ݹ����
	template <typename VST> //������
	void r_travIn(VST& visit) { if (_root) _root->r_travIn(_root, visit); } //����ݹ����
	template <typename VST> //������
	void r_travPost(VST& visit) { if (_root) _root->r_travPost(_root, visit); } //����ݹ����

	template <typename VST> //������
	void travPre(VST& visit) { if (_root) _root->travPre(_root, visit); } //�����������
	template <typename VST> //������
	void travIn(VST& visit) { if (_root) _root->travIn(_root, visit); } //�����������
	template <typename VST> //������
	void travPost(VST& visit) { if (_root) _root->travPost(_root, visit); } //�����������
	bool operator< (BinTree<T> const& t) //�Ƚ������������в��䣩
		{
			return _root && t._root && lt(_root, t._root);
		}
	bool operator== (BinTree<T> const& t) //�е���
		{
			return _root && t._root && (_root == t._root);
		}
}; //BinTree

template <typename T> inline int BinTree<T>::updateHeight(BinNodePosi<T> x)
	{
		return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
	}

template <typename T> inline void BinTree<T>::updateHeightAbove(BinNodePosi<T> x) //���¸߶�
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
		return 0; //�ݹ��������
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
	//release(x->data); 
	release(x); 
	return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
} 

//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
template <typename T> int BinTree<T>::remove(BinNodePosi<T> x) 
{ 
	updateHeightAbove(x->parent); //�������ȸ߶�
	int n = removeAt(x); 
	_size -= n; 
	return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}


