#include<iostream>
using namespace std;
int root, p, lc, rc;
struct FHQ 
{
	int lc, rc;//���Һ���
	int val, size;//ֵ�ʹ�С
	int key;//����ֵ
	int lazy;//�����
}node[600000];

void insert(int i)//��ӽڵ� 
{
	node[i].val = i;
	node[i].size = 1;
	node[i].key = rand();//���ȡ����ֵ
	node[i].lc = node[i].rc = 0;
}
void update(int i)//���½ڵ�Ĵ�С
{
	node[i].size = node[node[i].lc].size + node[node[i].rc].size + 1;//���Һ��Ӵ�С֮�ͼ�1
}
void pushdown(int i) //�·Ų���
{
	swap(node[i].lc, node[i].rc);//��������
	node[node[i].lc].lazy ^= 1;//����Ǹı�
	node[node[i].rc].lazy ^= 1;//����Ǹı�
	node[i].lazy = 0;
}
void split(int i, int k, int& lc, int& rc) //��i������ʼ���ѣ�kΪ�߽�
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
int merge(int lc, int rc) //�ϲ�����
{
	if (!lc)
		return rc;//�п�����ֱ�ӷ���
	if (!rc)
		return lc;//�п�����ֱ�ӷ���
	if (node[lc].key < node[rc].key) 
	{
		if (node[lc].lazy)//����������·�
			pushdown(lc);
		node[lc].rc = merge(node[lc].rc, rc);//�ݹ�ؼ����ϲ�
		update(lc);
		return lc;
	}
	else //ͬ��
	{
		if (node[rc].lazy)
			pushdown(rc);
		node[rc].lc = merge(lc, node[rc].lc);
		update(rc);
		return rc;
	}
}
void trav_In(int i) //�ݹ�ʽ�������
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
		split(lc, x - 1, lc, p);//�γ�lc��rc��p��������
		node[p].lazy ^= 1;
		root = merge(merge(lc, p), rc);//Ȼ��ϲ�
	}
	trav_In(root);//������
	return 0;
}
