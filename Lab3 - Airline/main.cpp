#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
using namespace std;
enum data 
{
	fid,
	dedate,
	keep,
	number,
	deport,
	arport,
	detime,
	artime,
	airid,
	airmd,
	fare
};//��������
struct flight
{
	int fid, number, deport, arport = 0;
	string keep;
	string dedate;
	string detime;
	string artime;
	int airid, airmd, fare = 0;
};//����
struct airports
{
	int num;
	vector<flight> flights;
};
struct reairports
{
	int num;
	vector<flight> reflights;
};
struct point//ʱ��ͼ��
{
	int time = 0;
	int minfare = 99999;
	int tra = 9999;
	vector <flight> pflights;
};
struct newports//ʱ��ͼ
{
	vector <point> points;//�ڵ㰴ʱ��˳�����У�����������ɴ˲���
};
struct node
{
	string start;//������ʱ��
	string last;//��ǰ���ʱ��
	int lastair;//�����ػ���
	int time = 0;//���ĵ�ʱ��
	vector <int> flight;//����·��
	int trans = 0;//��ת����
	int fare = 0;//�ܺ���
	int found[80] = { false };//������·���Ƿ��ظ�
};
class timecmp
{
public:
	bool operator()(const node& a, const node& b)
	{
		return a.time > b.time;
	}
};//ʱ��Ƚ�
class farecmp
{
public:
	bool operator()(const node& a, const node& b)
	{
		return a.fare > b.fare;
	}
};//���ñȽ�
class transcmp
{
public:
	bool operator()(const node& a, const node& b)
	{
		return a.trans > b.trans;
	}
};//ת�������Ƚ�
airports all[80] = { 0 };//һ��79������
reairports reall[80] = { 0 };//�������
newports newall[80];//�µ�ͼҲ��79������
int found[80] = { 0 };
queue <int> bfs_que;//���Ѷ���
vector <int> reaches;//���ѹ��ѻ�������
vector <string> split(string& t) //�����ݰ�;�ָ�
{
	vector <string> ss;
	string temp = "";
	int m = t.size();
	for (int s = 0; s < m; s++)
	{
		if (t[s] == ',')
		{
			ss.push_back(temp);
			temp = "";
			continue;
		}
		else
		{
			temp += t[s];
		}
	}
	ss.push_back(temp);
	return ss;
}
vector <int> gettime(string& a) //�ַ������ʱ��
{
	int date = a[2] - 48;
	int hour = 0;
	int min = 0;
	string temp = "";
	int r = 0;
	for (r = 9;; r++)
	{
		if (a[r] == ':')
		{
			break;
		}
		temp += a[r];
	}
	hour = atoi(temp.c_str());
	temp = "";
	temp += a[++r];
	temp += a[++r];
	min = atoi(temp.c_str());
	vector <int> res;
	res.push_back(date);
	res.push_back(hour);
	res.push_back(min);
	return res;
}
int caltime(string& before, string& later) //����ʱ���
{
	vector <int> a = gettime(before);
	vector <int> b = gettime(later);
	int time= (b[0] - a[0]) * 1440 + (b[1] - a[1]) * 60 + b[2] - a[2];
	return time;
}
bool compare(int a, int b)//�ֵ�����
{
	int t = 0, s = 0;
	if (a < 10)
		t = a;
	else
		t = a / 10;
	if (b < 10)
		s = b;
	else
		s = b / 10;
	if (t < s)
		return 1;
	else if (t == s)
	{
		return a < b;
	}
	else
		return 0;
}
bool scmp(point& a, point& b)//ʱ�������
{
	return a.time < b.time;
}
void dfs(int id)//�������������������ͨ����
{
	found[id] = 1;
	reaches.push_back(id);
	int s = all[id].flights.size();
	for (int a = 0; a < s; a++)//�����û������к���
	{
		int target = all[id].flights[a].arport;//�ҵ�ĳһ������Ŀ�Ļ���
		if (!found[target])//���δ���óɿɵ���
		{
			found[target] = 1;//�����óɿɵ���
			dfs(target);//��������
		}
	}
}
void bfs(int id)//�������������������ͨ����
{
	found[id] = 1;
	reaches.push_back(id);
	while (!bfs_que.empty())
	{
		int from = bfs_que.front();
		bfs_que.pop();
		int s = all[from].flights.size();
		for (int a = 0; a < s; a++)//�����û������к���
		{
			int target = all[from].flights[a].arport;//�ҵ�ĳһ������Ŀ�Ļ���
			if (!found[target])//���δ���óɿɵ���
			{
				found[target] = 1;
				reaches.push_back(target);
				bfs_que.push(target);
			}
		}
	}
}
int main()
{
	string org = "5/1/2017 0:00";//����ʱ��ת���ʱ��
	ifstream file;
	file.open("C:\\Users\\Zyf11\\Desktop\\lab3\\data.csv", ios::in);
	string tt;
	vector <string> temp;
	getline(file, tt);
one:
	while (getline(file, tt))
	{
		temp = split(tt);
		int airid = atoi(temp[data::deport].c_str());
		all[airid].num = airid;
		flight tflight;
		tflight.fid= atoi(temp[data::fid].c_str());
		tflight.dedate = temp[data::fid];
		tflight.keep = temp[data::fid];
		tflight.number = atoi(temp[data::number].c_str());
		tflight.deport = atoi(temp[data::deport].c_str());
		tflight.arport = atoi(temp[data::arport].c_str());
		tflight.detime = temp[data::detime];
		tflight.artime = temp[data::artime];
		tflight.airid = atoi(temp[data::airid].c_str());
		tflight.airmd = atoi(temp[data::airmd].c_str());
		tflight.fare = atoi(temp[data::fare].c_str());
		all[airid].flights.push_back(tflight);
		reall[tflight.arport].reflights.push_back(tflight);

		int ttime = caltime(org, tflight.detime);
		for (auto s = newall[airid].points.begin(); s != newall[airid].points.end(); s++)
		{
			if (s->time == ttime)
			{
				s->pflights.push_back(tflight);
				goto one;
			}
		}
		point temp;
		temp.time = ttime;
		temp.pflights.push_back(tflight);
		newall[airid].points.push_back(temp);
	}
	for (int i = 1; i < 80; i++)
	{
		sort(newall[i].points.begin(), newall[i].points.end(), scmp);
		//cout << newall[i].points.size() << " ";
	}
	std::cout << "Please input the service number:";
	int service;
	cin >> service;//212-260�о�Ϊ��ȡ����
	switch (service)
	{
	case 1:
	{
		int tempid;
		cin >> tempid;
		if(1)
			dfs(tempid);//������Ե��������㷨
		else
		{
			bfs_que.push(tempid);
			bfs(tempid);//������Ե��ù����㷨
		}
		sort(reaches.begin(), reaches.end(), compare);
		for (auto i = reaches.begin(); i != reaches.end(); i++)
		{
			cout << *i << " ";
		}
		cout << endl;
		break;
	}
	case 2:
	{
		
		char res[80][80] = { 0 };//�������
		char found[80]= { 0 };
		int road[80][80] = { 0 };//�����Ƿ���ͨ
		memset(res, 100, 6400);
		for (int i = 1; i < 80; i++)
		{
			for (flight it : all[i].flights)
			{
				road[i][it.arport] = 1;
			}
		}
		for (int i = 1; i < 80; i++)
		{
			memset(found, 0, 80);
			int time = 0;
			pair<int, int> node;
			node.first = i;
			node.second = time;
			queue <pair<int, int>> temp;
			temp.push(node);
			found[i] = 1;
			while (!temp.empty())
			{
				int port = temp.front().first;//��ɻ���
				int t_time= temp.front().second;//��ɻ���
				temp.pop();
				for (int j = 1; j < 80; j++)
				{
					if (road[port][j])//���i��j��ͨ
					{
						if (t_time < res[i][j])
							res[i][j] = t_time;//��¼���߾���
						if (!found[j])//��j������û����������
						{
							found[j] = 1;
							pair<int, int> n;
							n.first = j;
							n.second = t_time + 1;
							temp.push(n);
						}
					}	
				}
			}
			res[i][i] = -1;
		}
		for (int i = 1; i < 80; i++)
		{
			for (int j = 1; j < 80; j++)
			{
				printf("%d ", res[i][j]);
			}
			puts("\n");
		}
		break;
	}
	case 3:
	{
		int st, end, num;
		int res = 0;//���
		cin >> st >> end >> num;
		if (!num)//����ת
		{
			for (auto t = all[st].flights.begin(); t != all[st].flights.end(); t++)
			{
				if ((*t).arport == end)//��Ŀ�ĵػ���
					res++;
			}
		}
		else if (num == 1)//��תһ��
		{
			for (auto t = all[st].flights.begin(); t != all[st].flights.end(); t++)//������ʼ��������
			{
				vector <int> at = gettime((*t).artime);//����ת����ʱ��
				int id = (*t).arport;//��ת����
				for (auto s = all[id].flights.begin(); s != all[id].flights.end(); s++)
				{
					if((*s).arport == end)
					{ 
						vector <int> leave = gettime((*s).detime);
						if (at[0] < leave[0])
							res++;
						else if (at[0] == leave[0])
						{
							if (at[1] < leave[1])
								res++;
							else if (at[1] == leave[1])
							{
								if (at[2] <= leave[2])
									res++;
							}
						}
					}
				}
			}
		}
		else
			cout << "Error input!" << endl;
		cout << res << endl;
		break;
	}
	case 4:
	{
		priority_queue <node, vector<node>, timecmp> que;
		int sid, eid;//��������
		int minres = 999999;
		cin >> sid >> eid;
		for (auto s = all[sid].flights.begin(); s != all[sid].flights.end(); s++)//��������������к���
		{
			int flag = 0;
			vector <int> c = gettime((*s).detime);
			vector <int> d = gettime((*s).artime);
			int temptime = (d[0] - c[0]) * 1440 + (d[1] - c[1]) * 60 + d[2] - c[2];
			if ((*s).arport == eid)
			{
				flag = 1;
				if (temptime < minres)
					minres = temptime;
			}
			if (flag)
				goto two;
		}
		for (auto s = all[sid].flights.begin(); s != all[sid].flights.end(); s++)//��������������к���
		{
			int next = (*s).arport;
			
			int min_time[80];//��ɻ���ͨ���������ߵ�������ڵ����Сֵ
			for (int i = 0; i < 80; i++)
			{
				min_time[i] = 9999;
			}
			for (auto t = all[next].flights.begin(); t != all[next].flights.end(); t++)//��������������к���
			{
				if (found[(*t).arport])//��������������
					continue;
				vector <int> a = gettime((*s).artime);
				vector <int> b = gettime((*t).detime);//���뱣��ʱ���ϵ
				if (a[0] > b[0])
					continue;
				else if (a[0] == b[0])
				{
					if (a[1] > b[1])
						continue;
					else if (a[1] == b[1])
					{
						if (a[2] > b[2])
							continue;
					}
				}
				node temp;
				temp.found[(*s).deport] = true;
				temp.found[(*t).deport] = true;
				temp.found[(*t).arport] = true;
				temp.start = (*s).detime;
				temp.last = (*t).artime;
				temp.lastair = (*t).arport;
				vector <int> c = gettime((*s).detime);
				vector <int> d = gettime((*t).artime);
				int temptime = (d[0] - c[0]) * 1440 + (d[1] - c[1]) * 60 + d[2] - c[2];
				temp.time = temptime;
				if (temp.time < min_time[(*t).arport])
				{
					min_time[(*t).arport] = temp.time;
					que.push(temp);
				}
			}
			while (!que.empty())
			{
				node local = que.top();
				que.pop();
				if (local.found[eid])//����Ѿ�����Ŀ�ĵ�
				{
					if (local.time < minres)
						minres = local.time;
					break;
				}
				if (local.time > minres)//�������ʱ����ֱ�Ӽ�֦
					continue;
				int start = local.lastair;//��һ����ɵĻ���
				for (auto r = all[start].flights.begin(); r != all[start].flights.end(); r++)//��������������к���
				{
					if (local.found[(*r).arport])//��������������
						continue;
					vector <int> a = gettime(local.last);
					vector <int> b = gettime((*r).detime);//���뱣��ʱ���ϵ
					if (a[0] > b[0])
						continue;
					else if (a[0] == b[0])
					{
						if (a[1] > b[1])
							continue;
						else if (a[1] == b[1])
						{
							if (a[2] > b[2])
								continue;
						}
					}
					//��ʱʱ������ͨ��
					node temp = local;
					temp.found[(*r).arport] = true;
					temp.last = (*r).artime;
					temp.lastair = (*r).arport;
					vector <int> c = gettime((*s).detime);
					vector <int> d = gettime((*r).artime);
					temp.time = (d[0] - c[0]) * 1440 + (d[1] - c[1]) * 60 + d[2] - c[2];
					if (temp.time < min_time[(*r).arport])
					{
						min_time[(*r).arport] = temp.time;
						que.push(temp);
					}
				}
			}
			while (!que.empty())
				que.pop();
		}
two:
		if (minres == 999999 || sid == eid)
			minres = -1;
		std::cout << minres << endl;
		break;
	}
	case 5:
	{
		int number;
		cin >> number;
		if (number == 1)
		{
			int flag = 0;
			int sid, eid, k;
			string tmax, tmin;
			cin >> sid >> eid >> k;
			getchar();
			getline(std::cin, tmax);
			getline(std::cin, tmin);
			vector <int> max = gettime(tmax);
			vector <int> min = gettime(tmin);
			string orgs = "5/1/2017 0:20";
			vector <int> org = gettime(orgs);
			queue <node> que1;
			int mintime[80];
			for (int i = 0; i < 80; i++)
				mintime[i] = 99999;
			for (auto s = all[sid].flights.begin(); s != all[sid].flights.end(); s++)
			{
				vector <int> local = gettime((*s).detime);
				{
					if (local[0] < min[0])
						continue;
					else if (local[0] == min[0])
					{
						if (local[1] < min[1])
							continue;
						else if (local[1] == min[1])
						{
							if (local[2] < min[2])
								continue;
						}
					}
				}
				{
					if (local[0] > max[0])
						continue;
					else if (local[0] == max[0])
					{
						if (local[1] > max[1])
							continue;
						else if (local[1] == max[1])
						{
							if (local[2] > max[2])
								continue;
						}
					}
				}
				//��ʱ������ʱ�䷶Χ��
				vector <int> at = gettime((*s).artime);
				int temptime= (at[0] - org[0]) * 1440 + (at[1] - org[1]) * 60 + at[2] - org[2];
				if (temptime < mintime[(*s).arport])//��ǰ���ʱ���������,��������
				{
					mintime[(*s).arport] = temptime;
					node temp;
					temp.found[sid] = true;
					temp.found[(*s).arport] = true;
					temp.last = (*s).artime;
					temp.lastair = (*s).arport;
					temp.flight.push_back((*s).fid);
					temp.time = temptime;
					que1.push(temp);
				}
			}
			while (!que1.empty())
			{
				node local = que1.front();
				que1.pop();
				if (local.time > mintime[local.lastair])
					continue;
				if (local.trans > k)
					continue;
				int start = local.lastair;
				if (start == eid)
				{
					flag = 1;
					for (auto r = local.flight.begin(); r != local.flight.end(); r++)
					{
						cout << (*r) << " ";
					}
					cout << endl;
					break;
				}
				for (auto t = all[start].flights.begin(); t != all[start].flights.end(); t++)
				{
					if (local.found[(*t).arport])//��������������
						continue;
					vector <int> a = gettime(local.last);
					vector <int> b = gettime((*t).detime);//���뱣��ʱ���ϵ
					if (a[0] > b[0])
						continue;
					else if (a[0] == b[0])
					{
						if (a[1] > b[1])
							continue;
						else if (a[1] == b[1])
						{
							if (a[2] > b[2])
								continue;
						}
					}
					//��ͨ��ʱ����
					vector <int> at = gettime((*t).artime);
					int temptime = (at[0] - org[0]) * 1440 + (at[1] - org[1]) * 60 + at[2] - org[2];
					if (temptime < mintime[(*t).arport])//��ǰ���ʱ���������,��������
					{
						mintime[(*t).arport] = temptime;
						node temp = local;
						temp.found[(*t).arport] = true;
						temp.lastair = (*t).arport;
						temp.flight.push_back((*t).fid);
						temp.time = temptime;
						temp.last = (*t).artime;
						temp.trans++;
						que1.push(temp);
					}
				}
			}
			if (!flag)
				cout << -1 << endl;
		}
		else if (number == 2)
		{	
			int flag = 0;
			int sid, eid, k;
			string tmax, tmin;
			cin >> sid >> eid >> k;
			getchar();
			getline(std::cin, tmax);
			getline(std::cin, tmin);
			vector <int> max = gettime(tmax);
			vector <int> min = gettime(tmin);
			string orgs = "5/1/2017 0:20";
			vector <int> org = gettime(orgs);
			queue <node> que2;
			int maxtime[80];
			for (int i = 0; i < 80; i++)
				maxtime[i] = -20;
			for (auto s = reall[eid].reflights.begin(); s != reall[eid].reflights.end(); s++)
			{
				vector <int> local = gettime((*s).artime);
				{	
					if (local[0] < min[0])
						continue;
					else if (local[0] == min[0])
					{
						if (local[1] < min[1])
							continue;
					else if (local[1] == min[1])
					{
						if (local[2] < min[2])
							continue;
					}
				}
			}
				{
					if (local[0] > max[0])
					continue;
					else if (local[0] == max[0])
					{
						if (local[1] > max[1])
							continue;
					else if (local[1] == max[1])
					{
						if (local[2] > max[2])
							continue;
					}
				}
			}
				//��ʱ������ʱ�䷶Χ��
				vector <int> before = gettime((*s).detime);//�������ʱ��
				int temptime = (before[0] - org[0]) * 1440 + (before[1] - org[1]) * 60 + before[2] - org[2];
				if (temptime > maxtime[(*s).deport])//��ǰ���ʱ���������,��������
				{
					maxtime[(*s).deport] = temptime;
					node temp;
					temp.found[eid] = true;
					temp.found[(*s).deport] = true;
					temp.last = (*s).detime;
					temp.lastair = (*s).deport;
					temp.flight.push_back((*s).fid);
					temp.time = temptime;
					que2.push(temp);
				}
			}
			while (!que2.empty())
			{
				node local = que2.front();
				que2.pop();
				if (local.time < maxtime[local.lastair])
					continue;
				if (local.trans > k)
					continue;
				int start = local.lastair;
				if (start == sid)//�Ѿ����򵽴���ɻ���
				{
					flag = 1;
					for (auto r = local.flight.rbegin(); r != local.flight.rend(); r++)
					{
						cout << (*r) << " ";//���������Ϊ������
					}
					cout << endl;
					break;
				}
				for (auto t = reall[start].reflights.begin(); t != reall[start].reflights.end(); t++)
				{
					if (local.found[(*t).deport])//��������������
						continue;
					vector <int> a = gettime((*t).artime);
					vector <int> b = gettime(local.last);//���뱣��ʱ���ϵ
					if (a[0] > b[0])
						continue;
					else if (a[0] == b[0])
					{
						if (a[1] > b[1])
							continue;
						else if (a[1] == b[1])
						{
							if (a[2] > b[2])
								continue;
						}
					}
					//��ͨ��ʱ����
					vector <int> at = gettime((*t).detime);
					int temptime = (at[0] - org[0]) * 1440 + (at[1] - org[1]) * 60 + at[2] - org[2];
					if (temptime > maxtime[(*t).deport])//��ǰ���ʱ���������,��������
					{
						maxtime[(*t).deport] = temptime;
						node temp = local;
						temp.found[(*t).deport] = true;
						temp.lastair = (*t).deport;
						temp.last = (*t).detime;
						temp.flight.push_back((*t).fid);
						temp.time = temptime;
						temp.trans++;
						que2.push(temp);
					}
				}
			}
			if (!flag)
				cout << -1 << endl;

		}
		else if (number == 3)
		{
			int flag = 0;
			int sid, eid, k, mode;
			cin >> sid >> eid >> k >> mode;
			string orgs = "5/1/2017 0:20";
			vector <int> org = gettime(orgs);
			queue <node> que3;
			int mintime[80];
			for (int i = 0; i < 80; i++)
				mintime[i] = 99999;
			for (auto s = all[sid].flights.begin(); s != all[sid].flights.end(); s++)
			{
				if ((*s).airmd != mode)
					continue;
				//��ʱ�����ڻ��ͷ�Χ��
				vector <int> at = gettime((*s).artime);
				int temptime = (at[0] - org[0]) * 1440 + (at[1] - org[1]) * 60 + at[2] - org[2];
				if (temptime < mintime[(*s).arport])//��ǰ���ʱ���������,��������
				{
					mintime[(*s).arport] = temptime;
					node temp;
					temp.found[sid] = true;
					temp.found[(*s).arport] = true;
					temp.last = (*s).artime;
					temp.lastair = (*s).arport;
					temp.flight.push_back((*s).fid);
					temp.time = temptime;
					que3.push(temp);
				}
			}	
			while (!que3.empty())
			{
				node local = que3.front();
				que3.pop();
				if (local.time > mintime[local.lastair])
					continue;
				if (local.trans > k)
					continue;
				int start = local.lastair;
				if (start == eid)
				{
					flag = 1;
					for (auto r = local.flight.begin(); r != local.flight.end(); r++)
					{
						cout << (*r) << " ";
					}
					cout << endl;
					break;
				}
				for (auto t = all[start].flights.begin(); t != all[start].flights.end(); t++)
				{
					if (local.found[(*t).arport])//��������������
						continue;
					vector <int> a = gettime(local.last);
					vector <int> b = gettime((*t).detime);//���뱣��ʱ���ϵ
					if (a[0] > b[0])
						continue;
					else if (a[0] == b[0])
					{
						if (a[1] > b[1])
							continue;
						else if (a[1] == b[1])
						{
							if (a[2] > b[2])
								continue;
						}
					}
					//��ͨ��ʱ����
					vector <int> at = gettime((*t).artime);
					int temptime = (at[0] - org[0]) * 1440 + (at[1] - org[1]) * 60 + at[2] - org[2];
					if (temptime < mintime[(*t).arport])//��ǰ���ʱ���������,��������
					{
						mintime[(*t).arport] = temptime;
						node temp = local;
						temp.found[(*t).arport] = true;
						temp.lastair = (*t).arport;
						temp.flight.push_back((*t).fid);
						temp.time = temptime;
						temp.last = (*t).artime;
						temp.trans++;
						que3.push(temp);
					}
				}
			}
			if (!flag)
				cout << -1 << endl;
		}
		break;
	}
	case 6:
	{
		int number;
		cin >> number;
		if (1)
		{
			int flag = 0;
			int minfare = 999999;
			priority_queue <node, vector<node>, farecmp> que1;
			int sid, eid, k, high, low;
			string tmax, tmin;
			cin >> sid >> eid;
			getchar();
			if (number == 1 || number == 2)
			{
				getline(std::cin, tmax);
				getline(std::cin, tmin);
				high = caltime(org, tmax);
				low = caltime(org, tmin);
			}
			else
				cin >> k;
			for (auto s = newall[sid].points.begin(); s != newall[sid].points.end(); s++)
			{
				if (number == 1)
				{
					if (s->time >= low && s->time <= high)//��ʱ�䷶Χ��
					{
						for (auto t = s->pflights.begin(); t != s->pflights.end(); t++)//���ڸ�ʱ����ÿ������
						{
							node temp;
							temp.flight.push_back(t->fid);
							temp.found[sid] = true;
							temp.found[t->arport] = true;
							temp.fare += t->fare;
							temp.last = t->artime;
							temp.lastair = t->arport;
							que1.push(temp);
						}
					}
				}
				else if(number == 2)
				{
					for (auto t = s->pflights.begin(); t != s->pflights.end(); t++)//���ڸ�ʱ����ÿ������
					{
						node temp;
						temp.flight.push_back(t->fid);
						temp.found[sid] = true;
						temp.found[t->arport] = true;
						temp.fare += t->fare;
						temp.last = t->artime;
						temp.lastair = t->arport;
						que1.push(temp);
					}
				}
				else
				{
					for (auto t = s->pflights.begin(); t != s->pflights.end(); t++)//���ڸ�ʱ����ÿ������
					{
						if (t->airmd != k)//��������
							continue;
						node temp;
						temp.flight.push_back(t->fid);
						temp.found[sid] = true;
						temp.found[t->arport] = true;
						temp.fare += t->fare;
						temp.last = t->artime;
						temp.lastair = t->arport;
						que1.push(temp);
					}
				}
			}
			while (!que1.empty())
			{
				node local = que1.top();
				que1.pop();
				int start = local.lastair;
				int stime = caltime(org, local.last);//����ʱ��
				if (start == eid)
				{
					if (number == 2)//���ƽ���ʱ��
					{
						if (stime < low || stime > high)
							continue;
					}
					if (local.fare < minfare)
					{
						flag = 1;
						for (auto t = local.flight.begin(); t != local.flight.end(); t++)
						{
							cout << (*t) << " ";
						}
						cout << endl << local.fare << endl;
						break;
					}
				}
				for (auto s = newall[start].points.begin(); s != newall[start].points.end(); s++)
				{
					if (s->time >= stime)//��ת����ʱ�������ʱ���
					{
						if (local.fare < s->minfare)//ֻ�е����ʱ���ķ��ý�Сʱ
						{
							//�Ž���ʱ����·��ѹջ
							s->minfare = local.fare;
							for (; s != newall[start].points.end(); s++)//����ʣ�������ʱ���
							{
								for (auto t = s->pflights.begin(); t != s->pflights.end(); t++)//���ڸ�ʱ����ÿ������
								{
									if (local.found[t->arport])
										continue;
									node temp = local;
									temp.flight.push_back(t->fid);
									temp.fare += t->fare;
									temp.last = t->artime;
									temp.lastair = t->arport;
									temp.found[t->arport] = true;
									que1.push(temp);
								}
							}
						}
						break;
					}
				}
			}
			if (!flag)
				cout << -1 << endl;
		}
		break;
	}
	case 7:
	{
		int sid, eid, k, m;
		int flag = 0;
		priority_queue <node, vector<node>, transcmp> que1;
		cin >> sid >> eid >> k >> m;
		for (auto s = newall[sid].points.begin(); s != newall[sid].points.end(); s++)
		{
			for (auto t = s->pflights.begin(); t != s->pflights.end(); t++)//���ڸ�ʱ����ÿ������
			{
				node temp;
				temp.flight.push_back(t->fid);
				temp.found[sid] = true;
				temp.found[t->arport] = true;
				temp.last = t->artime;
				temp.lastair = t->arport;
				que1.push(temp);
			}
		}
		while (!que1.empty())
		{
			node local = que1.top();
			que1.pop();
			int start = local.lastair;
			int stime = caltime(org, local.last);//����ʱ��
			if (start == eid)
			{
				if (local.time <= m)//����תʱ��������
				{
					flag = 1;
					for (auto t = local.flight.begin(); t != local.flight.end(); t++)
					{
						cout << (*t) << " ";
					}
					break;
				}
				else
					continue;
			}
			for (auto s = newall[start].points.begin(); s != newall[start].points.end(); s++)
			{
				if (s->time >= stime)//��ת����ʱ�������ʱ���
				{
					for (; s != newall[start].points.end(); s++)//����֮�������ʱ���
					{
						for (auto t = s->pflights.begin(); t != s->pflights.end(); t++)//���ڸ�ʱ����ÿ������
						{
							node temp = local;
							temp.flight.push_back(t->fid);
							temp.time += (s->time - stime);
							temp.last = t->artime;
							temp.lastair = t->arport;
							temp.found[t->arport] = true;
							temp.trans++;
							if (temp.trans > k || temp.time > m)
								continue;
							que1.push(temp);
						}
					}
					break;
				}
			}
		}
		if (!flag)
			cout << -1 << endl;
		break;
	}
	case 8:
	{
		int size = 0;
		int flag = 0;
		int minfare = 999999;
		priority_queue <node, vector<node>, farecmp> que1;
		int sid, eid, m;
		cin >> sid >> eid >> m;
		for (auto s = newall[sid].points.begin(); s != newall[sid].points.end(); s++)
		{
			for (auto t = s->pflights.begin(); t != s->pflights.end(); t++)//���ڸ�ʱ����ÿ������
			{
				node temp;
				temp.flight.push_back(t->fid);
				temp.found[sid] = true;
				temp.found[t->arport] = true;
				temp.fare += t->fare;
				temp.last = t->artime;
				temp.lastair = t->arport;
				que1.push(temp);
			}
		}
		while (!que1.empty())
		{
			node local = que1.top();
			que1.pop();
			int start = local.lastair;
			int stime = caltime(org, local.last);//����ʱ��
			if (local.lastair == eid)
			{
				if (local.fare < minfare)
				{
					minfare = local.fare;
					flag = 1;
					for (auto t = local.flight.begin(); t != local.flight.end(); t++)
					{
						cout << (*t) << " ";
					}
					cout << endl << minfare << endl;
					goto end;
				}
			}
			for (auto s = newall[start].points.begin(); s != newall[start].points.end(); s++)
			{
				if (s->time >= stime)//��ת����ʱ�������ʱ���
				{
					for (; s != newall[start].points.end(); s++)//����ʣ�������ʱ���
					{
						for (auto t = s->pflights.begin(); t != s->pflights.end(); t++)//���ڸ�ʱ����ÿ������
						{
							node temp = local;
							temp.flight.push_back(t->fid);
							temp.time += (s->time - stime);
							if (temp.time > m)
								continue;
							temp.fare += t->fare;
							temp.last = t->artime;
							temp.lastair = t->arport;
							temp.found[t->arport] = true;
							
							que1.push(temp);
						}
					}
					break;
				}
			}
		}
	end:
		if (!flag)
			cout << -1 << endl;
		break;
	}
	default:
		cout << "error input!" << endl;
		break;
	}
}