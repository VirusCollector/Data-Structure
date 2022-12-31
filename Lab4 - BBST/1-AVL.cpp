#include <iostream>
template<typename T> struct AVL //AVL��
{
	struct node	//ÿ���ڵ�
	{
		node* left, * right;//���ӣ��Һ���
		T value;//
		int height;//����
		int size;//����ģ
		int recount;//��ǰ�����ظ�����
		node(T v) { left = right = NULL; value = v; height = size = recount = 1; }
		node() { left = right = NULL; value = 0; height = size = recount = 1; }
	};
	int total;//����
	node* root;//���ڵ�
	node all[1000000];//���ڹ����ڴ�
	AVL() { root = NULL; total = 0; }//���캯��
	int height(node* n)//��ø߶�
	{
		if (!n)
			return 0;
		return n->height;
	}
	int size(node* n)//��ù�ģ
	{
		if (!n)
			return 0;
		return n->size;
	}
	T Max(const T& a, const T& b) 
	{ 
		return a > b ? a : b; 
	}
	int findrank(T rank)//����3
	{
		node* temp = root;
		int t = 0;
		while (temp)
		{
			if (temp->value < rank)
			{
				t += size(temp->left) + temp->recount;
				temp = temp->right;
			}
			else if (temp->value > rank)
				temp = temp->left;
			else 
				return t + size(temp->left) + 1;
		}
		return -1;
	}
	int findindex(node* n, int index)//����4
	{
		int sleft = size(n->left);
		int repeat = n->recount;
		if (index <= sleft)
			return findindex(n->left, index);
		else if (index > sleft + repeat)
			return findindex(n->right, index - (sleft + repeat));
		return n->value;
	}
	node* zag(node* n)//����
	{
		node* temp = n->right;
		n->right = temp->left;
		temp->left = n;
		n->size = size(n->left) + size(n->right) + n->recount;
		n->height = Max(height(n->left), height(n->right)) + 1;
		temp->size = size(temp->left) + size(temp->right) + temp->recount;
		temp->height = Max(height(temp->left), height(temp->right)) + 1;
		return temp;
	}
	node* zig(node* n)//����
	{
		node* temp = n->left;
		n->left = temp->right;
		temp->right = n;
		n->size = size(n->left) + size(n->right) + n->recount;
		n->height = Max(height(n->left), height(n->right)) + 1;
		temp->size = size(temp->left) + size(temp->right) + temp->recount;
		temp->height = Max(height(temp->left), height(temp->right)) + 1;
		return temp;
	}
	node* zagzig(node* n)//������
	{
		n->left = zag(n->left);
		return zig(n);
	}
	node* zigzag(node* n)//������
	{
		n->right = zig(n->right);
		return zag(n);
	}
	node* balance(node* n)//����ƽ��
	{
		if (height(n->left) == height(n->right) + 2)
		{
			if (height(n->left->left) > height(n->left->right))
				n = zig(n);
			else 
				n = zagzig(n);
		}
		else if (height(n->right) == height(n->left) + 2)
		{
			if (height(n->right->right) > height(n->right->left))
				n = zag(n);
			else 
				n = zigzag(n);
		}
		return n;
	}
	node* insert(node* n, T val)//����ڵ�
	{
		if (!n)
		{
			n = all + (total++);//�½��ڵ�
			n->value = val;
			return n;
		}
		if (val == n->value)
			n->recount++;
		else if (val < n->value)
			n->left = insert(n->left, val);
		else 
			n->right = insert(n->right, val);
		n->size = size(n->left) + size(n->right) + n->recount;
		n->height = Max(height(n->left), height(n->right)) + 1;
		return balance(n);
	}
	node* remove(node* n, T val)//ɾ���ڵ�
	{
		if (!n)
			return NULL;
		if (n->value > val)
			n->left = remove(n->left, val);
		else if (n->value < val)
			n->right = remove(n->right, val);
		else if (n->recount > 1)
			n->recount--;
		else if (n->left && n->right)
		{
			node* temp = n->right;
			while (temp->left)
				temp = temp->left;
			n->value = temp->value;
			n->recount = temp->recount;
			temp->recount = 1;
			n->right = remove(n->right, n->value);
		}
		else if (n->left || n->right)
		{
			if (n->left)
				n = n->left;
			else
				n = n->right;
		}
		else 
			return n = NULL;
		n->height = Max(height(n->left), height(n->right)) + 1;
		n->size = size(n->left) + size(n->right) + n->recount;
		return balance(n);
	}
	node* lower(T val)//����5
	{
		node* temp = root;
		node* ans = NULL;
		while (temp)
		{
			if (temp->value >= val)
				temp = temp->left;
			else
			{
				if (!ans || temp->value > ans->value)
					ans = temp;
				temp = temp->right;
			}
		}
		return ans;
	}
	node* succ(T val)//����6
	{
		node* temp = root;
		node* ans = NULL;
		while (temp)
		{
			if (temp->value <= val)
				temp = temp->right;
			else
			{
				if (!ans || temp->value < ans->value)
					ans = temp;
				temp = temp->left;
			}
		}
		return ans;
	}
	void insert(T val)//����ӿ�
	{ 
		root = insert(root, val); 
	}
	void remove(T val)//ɾ���ӿ�
	{ 
		root = remove(root, val); 
	}
};

AVL <int> tree;//����

int main()
{
	int size;
	std::cin >> size;
	for (int a = 0; a < size; a++)
	{
		int tempop, val;
		std::cin >> tempop >> val;
		switch (tempop)
		{
		case 1:
			tree.insert(val); 
			break;
		case 2:
			tree.remove(val); 
			break;
		case 3:
			printf("%d\n", tree.findrank(val)); 
			break;
		case 4:
			printf("%d\n", tree.findindex(tree.root, val)); 
			break;
		case 5:
			printf("%d\n", tree.lower(val)->value); 
			break;
		case 6:
			printf("%d\n", tree.succ(val)->value);
			break;
		default:
			break;
		}
	}
	return 0;
}