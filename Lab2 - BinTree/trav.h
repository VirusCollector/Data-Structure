#pragma once
#include "BinNode.h"
#include <stack>
#include <queue>
template<typename T> template<typename VST> inline void BinNode<T>::travLevel(BinNodePosi<T> x, VST& visit)
{
	std::queue <BinNodePosi<T>> q;
	q.push(x);
	while (!q.empty())
	{
		BinNodePosi<T> r = q.front();
		visit(r);
		q.pop();
		if (HasLChild(r))
			q.push(r->lc);
		if (HasRChild(r))
			q.push(r->rc);
	}
}

template<typename T> template<typename VST> inline void BinNode<T>::travPre(BinNodePosi<T> x, VST& visit)
{
	std::stack <BinNodePosi<T>> s;
	while (true)
	{
		while (x)
		{
			visit(x);
			s.push(x->rc);
			x = x->lc;
		}
		if (s.empty())
			break;
		x = s.top();
		s.pop();
	}
}

template<typename T> template<typename VST> inline void BinNode<T>::travIn(BinNodePosi<T> x, VST& visit)
{
	std::stack <BinNodePosi<T>> s;
	while (true)
	{
		while (x)
		{
			s.push(x);
			x = x->lc;
		}
		if (s.empty())
			break;
		x = s.top();
		s.pop();
		visit(x);
		x = x->rc;
	}
}

template<typename T> template<typename VST> inline void BinNode<T>::travPost(BinNodePosi<T> x, VST& visit)
{
	std::stack <BinNodePosi<T>> s;
	if (x)
		s.push(x);
	while (!s.empty())
	{
		if (s.top() != x->parent)
		{
			while (BinNodePosi<T> t = s.top())
			{
				if (HasLChild(t))
				{
					s.push(t->rc);
					s.push(t->lc);
				}
				else
					s.push(t->rc);
			}
			s.pop();
		}
		x = s.top();
		s.pop();
		visit(x);
	}
}