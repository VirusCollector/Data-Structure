#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
const char* str = "0123456789abcdefghijklmnopqrstuvwxyz";
queue <string> query;
vector <string> split(string& t) //将数据按;分割
{
    vector <string> ss;
    string temp = "";
    int m = t.size();
    for (int s = 0; s < m; s++)
    {
        if (t[s] == ' ')
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
void utf8()
{
    FILE* f = fopen("C:\\Users\\Zyf11\\Desktop\\数据结构课件\\实验\\Lab5\\data\\2.txt ", "wb+");
    ifstream file;
    file.open("C:\\Users\\Zyf11\\Desktop\\数据结构课件\\实验\\Lab5\\data\\hdu.txt", ios::in);
    string temp;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 500000; i++)
    {
        getline(file, temp);
        vector <string> t = split(temp);
        int way = rand() % 2;
        string in = "0 "+ t[1] + " " + t[2] + "\n";
        string q = "1 ";
        if (way)//不删减
        {
            string s = t[1]+ "\n";
            q += s;
        }
        else
        {
            int cut = rand() % t[1].size();
            if (!cut)
                cut = 1;
            string s = "";
            for (int i = 0; i < cut; i++)
            {
                if (t[1][i] < 0)
                {
                    if ((unsigned char)t[1][i] <= 0xdf)
                    {
                        for (int r = i; r < i + 2; r++)
                        {
                            s += t[1][r];
                        }
                        i++;
                        continue;
                    }
                    else
                    {
                        for (int r = i; r < i + 3; r++)
                        {
                            s += t[1][r];
                        }
                        i += 2;
                        continue;
                    }                
                }
                s += t[1][i];
            }
            s = s + "\n";
            q += s;
        }
        fwrite(in.c_str(), 1, in.size(), f);
        query.push(q);
    }
    while (!query.empty())
    {
        string temp = query.front();
        fwrite(temp.c_str(), 1, temp.size(), f);
        query.pop();
    }
    fwrite("2\n", 1, 1, f);
}
int main()
{
    utf8();
    return 0;
    FILE* f = fopen("C:\\Users\\Zyf11\\Desktop\\数据结构课件\\实验\\Lab5\\data\\2.txt ", "wb+");
    ifstream file;
    file.open("C:\\Users\\Zyf11\\Desktop\\数据结构课件\\实验\\Lab5\\data\\poj.txt", ios::in);
    string temp;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 500000; i++)
    {
        getline(file, temp);
        vector <string> t = split(temp);
        int way = rand() % 2;
        string in = "0 " + t[1] + " " + t[2] + "\n";
        string q = "1 ";
        if (way)//不删减
        {
            string s = t[1] + "\n";
            q += s;
        }
        else
        {
            int cut = rand() % t[1].size();
            if (!cut)
                cut = 1;
            string s = "";
            for (int i = 0; i < cut; i++)
            {
                s += t[1][i];
            }
            s = s + "\n";
            q += s;
        }
        fwrite(in.c_str(), 1, in.size(), f);
        query.push(q);
    }
    while (!query.empty())
    {
        string temp = query.front();
        fwrite(temp.c_str(), 1, temp.size(), f);
        query.pop();
    }
    fwrite("2\n", 1, 1, f);
    return 0;
}