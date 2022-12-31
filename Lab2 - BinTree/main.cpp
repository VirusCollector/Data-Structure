#include <iostream>
#include "BinNode.h"
#include "BinTree.h"
#include "r_trav.h"
#include <crtdbg.h>
#include <queue>
#include "trav.h"
int d0, d1, d2 = 0;
std::string s;
std::queue <BinNodePosi<char>> binque;
BinTree <char> tree;
template <typename T> void visit(BinNodePosi<T> x)
{
	if (x->data == '%')
		return;
	std::cout << x->data << " ";
}
template <typename T> void count(BinNodePosi<T> x)
{
	int sum = 0;
	if (x == NULL || x->data == '%')
		return;
	if (x->lc != NULL && x->lc->data != '%')
		sum++;
	if (x->rc != NULL && x->rc->data != '%')
		sum++;
	if (sum == 0)
		d0++;
	else if (sum == 1)
		d1++;
	else if (sum == 2)
		d2++;
	return;
}
template <typename T> void (*p)(BinNodePosi<T> x) = &visit;
template <typename T> void (*q)(BinNodePosi<T> x) = &count;
int main()
{
	int pointer = 0;
	std::cin >> s;
	while (s != "#end")
	{
		if (s == "#add")//添加元素
		{
			pointer = 0;
			std::cin >> s;
			if (tree.empty())
			{
				if (!isspace(s[0]))
				{
					binque.push(tree.insert(s[0]));//将根节点入树
					pointer = 1;
				}
				else
				{
					std::cout << "Error input!!" << std::endl;
					return -1;
				}
			}
			for (int i = pointer; s[i]; i++)//遍历所有非空字符
			{
				if (!isspace(s[i]))
				{
					if (binque.front()->lc == NULL)
					{
						binque.push(tree.insert(s[i], binque.front()));
						continue;
					}
					else if (binque.front()->rc == NULL)
					{
						binque.push(tree.insert(binque.front(), s[i]));
						binque.pop();
					}
				}
				else
				{
					std::cout << "Error input!!" << std::endl;
					return -1;
				}
			}		
		}
		else if (s == "#rPre")//先序递归
		{
			tree.r_travPre(p<char>);
			puts("\n");
		}
		else if (s == "#rIn")//中序递归
		{
			tree.r_travIn(p<char>);
			puts("\n");
		}
		else if (s == "#rPost")//后序递归
		{
			tree.r_travPost(p<char>);
			puts("\n");
		}
		else if (s == "#Pre")
		{
			tree.travPre(p<char>);
			puts("\n");
		}
		else if (s == "#In")
		{
			tree.travIn(p<char>);
			puts("\n");
		}
		else if (s == "#Post")
		{
			tree.travPost(p<char>);
			puts("\n");
		}
		else if (s == "#level")
		{
			tree.travLevel(p<char>);
			puts("\n");
		}
		else if (s == "#degree")
		{
			d0 = 0;
			d1 = 0;
			d2 = 0;
			tree.travPre(q<char>);
			printf("degree0 counts:%d\n", d0);
			printf("degree1 counts:%d\n", d1);
			printf("degree2 counts:%d\n", d2);
		}
		else if (s == "#height")
		{
			printf("height:%d\n", tree._root->height);
		}
		else
		{
			puts("Error input!\n");
			return -2;
		}
		std::cin >> s;
	}


	return 10086;
}