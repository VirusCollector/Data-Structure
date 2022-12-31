#pragma once
#include "BinNode.h"
template<typename T> template<typename VST> inline void BinNode<T>::r_travPre(BinNodePosi<T> x, VST& visit)
{
	if (!x)
		return;
	visit(x);
	r_travPre(x->lc,visit);
	r_travPre(x->rc,visit);
}

template<typename T> template<typename VST> inline void BinNode<T>::r_travIn(BinNodePosi<T> x, VST& visit)
{
	if (!x)
		return;
	r_travIn(x->lc,visit);
	visit(x);
	r_travIn(x->rc,visit);
}

template<typename T> template<typename VST> inline void BinNode<T>::r_travPost(BinNodePosi<T> x, VST& visit)
{
	if (!x)
		return;
	r_travPost(x->lc, visit);
	r_travPost(x->rc, visit);
	visit(x);
}
