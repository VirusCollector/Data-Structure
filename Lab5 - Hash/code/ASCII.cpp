#include <iostream>
#include <chrono>
#include <string.h>
//#define prime 20011
//#define prime 204887
//#define prime 1000003
//#define prime 2000003
//#define prime 10000019
#define prime 30000023
using namespace std;
struct point//˫��ƽ����̽
{
	string key = "";//�ؼ���
	int value = -1;//ֵ
};
struct linkpoint//������
{
	string key = "";//�ؼ���
	int value = -1;//ֵ
	linkpoint* next = NULL;
};
point points[3];//204887
linkpoint linkpoints[30000000];
//int mod1 = 10000000;
int mod1 = 10000000;
//int mod3 = 10000000;
int mod3 = 30000000;
void way1() //��������
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
		for (int k = 0; k < len; k++)
		{
			ans += (unsigned long long)(temp[k] * ((1uLL << k) << 5));
			//ans += llabs((long long)temp[k] * (1LL << k));
			//ans += ((long long)temp[k] * ((k << 1) + k + 1));
		}
		ans %= mod1;//ȡģ��hash�������
		if (!op) //����
		{
			if (!(~linkpoints[ans].value))//�ô�δ��ͻ����ֱ�Ӳ���
			{
				linkpoints[ans].key = temp;
				linkpoints[ans].value = val;
			}
			else//���ֳ�ͻ
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
		else //����
		{
			int flag = 0;
			for (linkpoint* p = &linkpoints[ans]; p != NULL; p = p->next)//�����ô�����
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
void way2() //ƽ��̽�ⷨ
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
		for (int k = 0; k < len; k++)
		{
			ans += llabs((long long)temp[k] * (1LL << k));
		}
		ans %= prime;//ȡģ��hash�������
		if (!op) //����
		{
			int limit = (prime - 1) >> 1;
			for (int k = 0; k <= limit; k++)
			{
				long long bias = (long long)k * k;
				long long t1 = (ans + bias) % prime;
				long long t2 = (((ans - bias) % prime) + prime) % prime;
				if (!(~points[t1].value))//�ô�Ϊ��
				{
					points[t1].key = temp;
					points[t1].value = val;
					break;
				}
				if (!(~points[t2].value))//�ô�Ϊ��
				{
					points[t2].key = temp;
					points[t2].value = val;
					break;
				}
			}
		}
		else //����
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
					if (temp == points[t1].key)//��ѯ����
					{
						flag = 1;
						cout << points[t1].value << endl;
						break;
					}
					if (temp == points[t2].key)//��ѯ����
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
void way3() //��ɢ�з�
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
		unsigned long long ans = 0, hash2 = 0, len = strlen(temp.c_str());
		for (long long k = 0; k < len; k++)
		{
			ans += (unsigned long long)(temp[k] * ((1uLL << k) << 5));
			//ans += llabs((long long)temp[k] * (1LL << k));
			//ans += ((long long)temp[k] * ((k << 1) + k + 1));
			hash2 += llabs((long long)temp[k] * ((k << 1) + k + 1));
		}
		ans %= mod3;//ȡģ��hash1�������
		if (!op) //����
		{
			for (int k = 0;; k++)
			{
				int bias = (ans + hash2 * k) % mod3;
				if (!(~points[bias].value))//�ô�Ϊ��
				{
					points[bias].key = temp;
					points[bias].value = val;
					break;
				}
			}
		}
		else //����
		{
			int flag = 0;
			if (!points[ans].key.empty())
			{
				for (int k = 0;; k++)
				{
					int bias = (ans + hash2 * k) % mod3;
					if (points[bias].key.empty())
						break;
					if (temp == points[bias].key)//��ѯ����
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
	way1();
	//way2();
	//way3();
	chrono::system_clock::time_point t2 = chrono::system_clock::now();
	chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	cout << "run time = " << time_used.count() << " seconds. " << endl;
	return 10086;
}