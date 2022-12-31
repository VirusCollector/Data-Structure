#include <iostream>
#include <chrono>
#include <string.h>
#include <vector>
//#define prime 204887
//#define prime 1000003
//#define prime 2000003
//#define prime 10000019
#define prime 30000023
using namespace std;
struct point//双向平方试探
{
	string key = "";//关键码
	int value = -1;//值
};
struct linkpoint//独立链
{
	string key = "";//关键码
	int value = -1;//值
	linkpoint* next = NULL;
};
point points[30000000];//204887
//int num[30000000] = { 0 };
linkpoint linkpoints[3];
//int mod1 = 10000000;
int mod1 = 30000000;
//int mod3 = 10000000;
int mod3 = 30000000;
vector <unsigned> utf8;
void way1() //独立链法
{
	int op, val = 0;
	string temp;
	cin >> op;
	while (op != 2)
	{
		if (!op)
			cin >> temp >> val;
		else
			cin >> temp;
		unsigned long long ans = 0, len = strlen(temp.c_str());
		utf8.clear();
		for (int k = 0; k < len; k++)
		{
			unsigned uchar = temp[k] & 0xff;
			if (uchar <= 0x7f)//UTF8-1
			{
				utf8.push_back(temp[k]);
				continue;
			}
			else if (uchar >= 0xc2 && uchar <= 0xdf)//UTF8-2
			{
				unsigned sum = ((temp[k] & 0xff) << 8) + (temp[k + 1] & 0xff);
				k++;
				utf8.push_back(sum);
				continue;
			}
			else if (uchar >= 0xe0 && uchar <= 0xef)//UTF8-3
			{
				unsigned sum = ((temp[k] & 0xff) << 16) + ((temp[k + 1] & 0xff) << 8) + (temp[k + 2] & 0xff);
				k++;
				k++;
				utf8.push_back(sum);
				continue;
			}
		}
		int newlen = utf8.size();
		for (int k = 0; k < newlen; k++)
		{
			ans += (unsigned long long)(utf8[k] * ((1uLL << k) << 5));
			//ans += llabs((long long)temp[k] * (1LL << k));
			//ans += ((long long)temp[k] * ((k << 1) + k + 1));
		}
		ans %= 30000000;//取模后hash计算完成
		if (!op) //插入
		{
			if (!(~linkpoints[ans].value))//该处未冲突，则直接插入
			{
				linkpoints[ans].key = temp;
				linkpoints[ans].value = val;
			}
			else//出现冲突
			{
				if (linkpoints[ans].next == NULL)
				{
					linkpoints[ans].next = new linkpoint;
					linkpoints[ans].next->key = temp;
					linkpoints[ans].next->value = val;
					linkpoints[ans].next->next = NULL;
				}
				else
				{
					linkpoint* p = linkpoints[ans].next;
					while (p->next != NULL)
						p = p->next;
					p->next = new linkpoint;
					p->next->key = temp;
					p->next->value = val;
					p->next->next = NULL;
				}
			}
		}
		else //查找
		{
			int flag = 0;
			for (linkpoint* p = &linkpoints[ans]; p != NULL; p = p->next)//遍历该处链表
			{
				if (!temp.compare(p->key))
				{
					flag = 1;
					cout << p->value << endl;
					break;
				}
			}
			if (!flag)
				cout << "-1" << endl;
		}
		cin >> op;
	}
}
void way2() //平方探测法
{
	int op, val = 0;
	string temp;
	cin >> op;
	while (op != 2)
	{
		if (!op)
			cin >> temp >> val;
		else
			cin >> temp;
		long long ans = 0, len = strlen(temp.c_str());
		utf8.clear();
		for (int k = 0; k < len; k++)
		{
			unsigned uchar = temp[k] & 0xff;
			if (uchar <= 0x7f)//UTF8-1
			{
				utf8.push_back(temp[k]);
				continue;
			}
			else if (uchar >= 0xc2 && uchar <= 0xdf)//UTF8-2
			{
				unsigned sum = ((temp[k] & 0xff) << 8) + (temp[k + 1] & 0xff);
				k++;
				utf8.push_back(sum);
				continue;
			}
			else if (uchar >= 0xe0 && uchar <= 0xef)
			{
				unsigned sum = ((temp[k] & 0xff) << 16) + ((temp[k + 1] & 0xff) << 8) + (temp[k + 2] & 0xff);
				k++;
				k++;
				utf8.push_back(sum);
				continue;
			}
		}
		int newlen = utf8.size();
		for (int k = 0; k < newlen; k++)
		{
			ans += (unsigned long long)(utf8[k] * ((1uLL << k) << 5));
		}
		ans %= prime;//取模后hash计算完成
		if (!op) //插入
		{
			int limit = (prime - 1) >> 1;
			for (int k = 0; k <= limit; k++)
			{
				long long bias = (long long)k * k;
				long long t1 = (ans + bias) % prime;
				long long t2 = (((ans - bias) % prime) + prime) % prime;
				if (!(~points[t1].value))//该处为空
				{
					points[t1].key = temp;
					points[t1].value = val;
					break;
				}
				if (!(~points[t2].value))//该处为空
				{
					points[t2].key = temp;
					points[t2].value = val;
					break;
				}
			}
		}
		else //查找
		{
			int flag = 0;
			int limit = (prime - 1) >> 1;
			if (!points[ans].key.empty())
			{
				for (int k = 0; k <= limit; k++)
				{
					long long bias = (long long)k * k;
					long long t1 = (ans + bias) % prime;
					long long t2 = (((ans - bias) % prime) + prime) % prime;
					if (points[t1].key.empty() && points[t2].key.empty())
						break;
					if (temp == points[t1].key)//查询到了
					{
						flag = 1;
						cout << points[t1].value << endl;
						break;
					}
					if (temp == points[t2].key)//查询到了
					{
						flag = 1;
						cout << points[t2].value << endl;
						break;
					}
				}
			}
			if (!flag)
				cout << "-1" << endl;
		}
		cin >> op;
	}
}
void way3() //再散列法
{
	int op, val = 0;
	string temp;
	cin >> op;
	while (op != 2)
	{
		if (!op)
			cin >> temp >> val;
		else
			cin >> temp;
		long long ans = 0, hash2 = 0, len = strlen(temp.c_str());
		utf8.clear();
		for (int k = 0; k < len; k++)
		{
			unsigned uchar = temp[k] & 0xff;
			if (uchar <= 0x7f)//UTF8-1
			{
				utf8.push_back(temp[k]);
				continue;
			}
			else if (uchar >= 0xc2 && uchar <= 0xdf)//UTF8-2
			{
				unsigned sum = ((temp[k] & 0xff) << 8) + (temp[k + 1] & 0xff);
				k++;
				utf8.push_back(sum);
				continue;
			}
			else if (uchar >= 0xe0 && uchar <= 0xef)
			{
				unsigned sum = ((temp[k] & 0xff) << 16) + ((temp[k + 1] & 0xff) << 8) + (temp[k + 2] & 0xff);
				k++;
				k++;
				utf8.push_back(sum);
				continue;
			}
		}
		int newlen = utf8.size();
		for (long long k = 0; k < newlen; k++)
		{
			ans += (unsigned long long)(utf8[k] * ((1uLL << k) << 5));
			//ans += llabs((long long)temp[k] * (1LL << k));
			//ans += ((long long)temp[k] * ((k << 1) + k + 1));
			hash2 += llabs((long long)utf8[k] * ((k << 1) + k + 1));
		}
		ans %= mod3;//取模后hash1计算完成
		//num[ans]++;
		if (!op) //插入
		{
			for (int k = 0;; k++)
			{
				int bias = (ans + hash2 * k) % mod3;
				if (!(~points[bias].value))//该处为空
				{
					points[bias].key = temp;
					points[bias].value = val;
					break;
				}
			}
		}
		else //查找
		{
			int flag = 0;
			if (!points[ans].key.empty())
			{
				for (int k = 0;; k++)
				{
					int bias = (ans + hash2 * k) % mod3;
					if (points[bias].key.empty())
						break;
					if (temp == points[bias].key)//查询到了
					{
						flag = 1;
						cout << points[bias].value << endl;
						break;
					}
				}
			}
			if (!flag)
				cout << "-1" << endl;
		}
		cin >> op;
	}
}
int main()
{
	/*
	int flag = 1;
	for (int r = 2000000;; r++)
	{
		flag = 1;
		for (int i = 2; i <= sqrt(r) + 1; i++)
		{
			if (!(r % i))
			{
				flag = 0;
				break;
			}
		}
		if (flag && !((r + 1) % 4))
		{
			cout << r << endl;
			break;
		}
	}
	return 1;
	*/
	chrono::system_clock::time_point t1 = chrono::system_clock::now();
	//way1();
	//way2();
	way3();
	chrono::system_clock::time_point t2 = chrono::system_clock::now();
	chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	cout << "run time = " << time_used.count() << " seconds. " << endl;
	return 10086;
}