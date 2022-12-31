#include<iostream>
using namespace std;
int root, p, lc, rc;
struct FHQ 
{
	int lc, rc;//左右孩子
	int val, size;//值和大小
	int key;//修正值
	int lazy;//懒标记
}node[600000];

void insert(int i)//添加节点 
{
	node[i].val = i;
	node[i].size = 1;
	node[i].key = rand();//随机取修正值
	node[i].lc = node[i].rc = 0;
}
void update(int i)//更新节点的大小
{
	node[i].size = node[node[i].lc].size + node[node[i].rc].size + 1;//左右孩子大小之和加1
}
void pushdown(int i) //下放操作
{
	swap(node[i].lc, node[i].rc);//交换子树
	node[node[i].lc].lazy ^= 1;//懒标记改变
	node[node[i].rc].lazy ^= 1;//懒标记改变
	node[i].lazy = 0;
}
void split(int i, int k, int& lc, int& rc) //从i子树开始分裂，k为边界
{
	if (!i) 
	{
		lc = rc = 0;
		return;
	}
	if (node[i].lazy)
		pushdown(i);
	if (node[node[i].lc].size + 1 <= k) 
	{
		lc = i;
		split(node[i].rc, k - node[node[i].lc].size - 1, node[i].rc, rc);
	}
	else 
	{
		rc = i;
		split(node[i].lc, k, lc, node[i].lc);
	}
	update(i);
}
int merge(int lc, int rc) //合并子树
{
	if (!lc)
		return rc;//有空子树直接返回
	if (!rc)
		return lc;//有空子树直接返回
	if (node[lc].key < node[rc].key) 
	{
		if (node[lc].lazy)//有懒标记则下放
			pushdown(lc);
		node[lc].rc = merge(node[lc].rc, rc);//递归地继续合并
		update(lc);
		return lc;
	}
	else //同理
	{
		if (node[rc].lazy)
			pushdown(rc);
		node[rc].lc = merge(lc, node[rc].lc);
		update(rc);
		return rc;
	}
}
void trav_In(int i) //递归式中序遍历
{
	if (node[i].lazy) 
		pushdown(i);
	if (node[i].lc)
		trav_In(node[i].lc);
	cout << node[i].val << " ";
	if (node[i].rc)
		trav_In(node[i].rc);
}
int main() 
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		insert(i);
		root = merge(root, i);
	}
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		split(root, y, lc, rc);
		split(lc, x - 1, lc, p);//形成lc，rc，p三棵子树
		node[p].lazy ^= 1;
		root = merge(merge(lc, p), rc);//然后合并
	}
	trav_In(root);//输出结果
	return 0;
}
