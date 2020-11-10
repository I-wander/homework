#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define Process_Max 10                                         //进程数量最大值
#define Resource_Max 10                                        //资源种类最大值
using namespace std;

int Available[Resource_Max];                                    //系统当前每种资源可分配数
int Max[Process_Max][Resource_Max];                             //每个进程对每种资源最大需求
int Allocation[Process_Max][Resource_Max];                      //每个进程已分配资源
int Need[Process_Max][Resource_Max];                            //每个进程当前需求资源，等于最大减去已分配
int Work[Resource_Max];                                         //工作向量
int Finish[Process_Max];                                        //是否有足够资源分配给进程
int List[Process_Max];                                          //安全序列表
int Process_Num = 0, Resource_Num = 0;                          //进程数 资源数
int List_Num = 0;                                               //安全序列的序号

void Input_RS()                               //输入关于初始资源的配置
{
	cout<< "请输入资源种类:" << endl;
	cin>> Resource_Num;

	cout << "请输入系统当前可利用资源数:" << endl;
	for (int i = 0; i < Resource_Num; i++)
	{
		cout << "R" << i << ":";
		cin >> Available[i];
	}
}
void Input_P()                              //输入关于初始进程的配置
{
	cout << "输入进程数:" << endl;
	cin >> Process_Num;

	for (int i = 0; i < Process_Num; i++)
	{
		cout << "输入进程 P" << i << "的最大资源需求 Max:" << endl;
		for (int j = 0; j < Resource_Num; j++)
		{
			cout << "R" << j << ":";
			cin >> Max[i][j];
		}
		cout << endl;
		cout << "输入进程 P" << i << "的已分配资源 Allocation:" << endl;
		for (int j = 0; j < Resource_Num; j++)
		{
			cout << "R" << j << ":";
			cin >> Allocation[i][j];
		}
		cout << endl;
		for (int j = 0; j < Resource_Num; j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];
	}
}

void Reset_Finish()                                            //初始化finish和work数组
{
	memset(Finish, 0, sizeof(Finish));
	memset(Work, 0, sizeof(Work));
	List_Num = 0;
}

int Safe()                                                     //安全性算法
{
	int flag = 0, Count = 0;
	cout << "安全序列如下：" << endl;
	Reset_Finish();
	cout << "      Work          Need      Allocation  Work+Allocation  Finish" << endl;
	for (int i = 0; i < Resource_Num; i++)Work[i] = Available[i];
	while (List_Num < Process_Num)
	{
		for (int i = 0; i < Process_Num; i++)
		{
			if (!Finish[i])
			{
				flag = 0;
				for (int j = 0; j < Resource_Num; j++)
				{
					if (Need[i][j] > Work[j])
					{
						flag = 1;
						break;
					}
				}
				if (!flag)
				{
					List[List_Num++] = i;
					cout << "P" << i << "|";
					for (int j = 0; j < Resource_Num; j++)
					{
						printf("%3d", Work[j]);
						Work[j] += Allocation[i][j];
					}
					cout << "|   ";
					for (int j = 0; j < Resource_Num; j++)printf("%3d", Need[i][j]); cout << "|   ";
					for (int j = 0; j < Resource_Num; j++)printf("%3d", Allocation[i][j]); cout << "|   ";
					for (int j = 0; j < Resource_Num; j++)printf("%3d", Work[j]); cout << "|       ";
					Finish[i] = 1;
					printf("true\n");
				}
			}
		}
		Count++;
		if (Count >= Process_Num)break;
	}
	if (List_Num < Process_Num)
	{
		cout << "没有安全序列" << endl;
		return 0;
	}
	else {
		cout << "安全序列存在" << endl;
		return 1;
	}
}

void Show()                                                    //输出系统与进程信息
{    
	cout << "当前的进程信息如下：" << endl;
	cout << "当前可利用资源 Available:" << endl;
	for (int i = 0; i < Resource_Num; i++)
	{
		cout << "R" << i << ":" << Available[i] << "\t ";
	}
	cout << endl;
	cout << "         Max" << "     Allocation   " << "   Need   " << endl;
	for (int i = 0; i < Process_Num; i++)
	{
		cout << "P" << i << "|  ";
		for (int j = 0; j < Resource_Num; j++)printf("%3d", Max[i][j]); cout << "|  ";
		for (int j = 0; j < Resource_Num; j++)printf("%3d", Allocation[i][j]); cout << "|  ";
		for (int j = 0; j < Resource_Num; j++)printf("%3d", Need[i][j]); cout << "|  ";
		cout << endl;
	}
	cout << endl;
}

void Request()                                                  //银行家算法
{
	int pro, Request_Num[Resource_Max], inst = 0;

	while (!inst)
	{
		cout << "输入发出请求的进程 :" << endl;
		cin >> pro;
		cout << "输入请求资源数目 :" << endl;
		for (int i = 0; i < Resource_Num; i++)
		{
			cout << "R" << i << ":";
			cin >> Request_Num[i];
		}

		for (int i = 0; i < Resource_Num; i++)
		{
			if (Request_Num[i] > Need[pro][i])
			{
				cout << "请求资源数目超过所需范围，请求无效" << endl;
				return;
			}
			if (Request_Num[i] > Available[i])
			{
				cout << "没有足够资源，分配失败" << endl;
				return;
			}
		}
		for (int i = 0; i < Resource_Num; i++)                 //试分配
		{
			Available[i] -= Request_Num[i];
			Allocation[pro][i] += Request_Num[i];
			Need[pro][i] -= Request_Num[i];
		}
		if (!Safe())                                           //判断是否安全
		{
			for (int i = 0; i < Resource_Num; i++)
			{
				Available[i] += Request_Num[i];
				Allocation[pro][i] -= Request_Num[i];
				Need[pro][i] += Request_Num[i];
			}
			cout << "拒绝本次请求"<< endl;
		}
		else {
			cout << "分配成功" << endl;
			Show();
		}
		cout << "------------------------------" << endl;
		cout << "请输入指令:" << endl;
		cout << "0：继续输入请求 " << endl;
		cout << "1：退出 " << endl;
		cin >> inst;
	}
}


void Init()                                                    //初始化所有数据
{
	Process_Num = 0;
	List_Num = 0;
	Resource_Num = 0;
	memset(Allocation, 0, sizeof(Allocation));
	memset(Available, 0, sizeof(Available));
	memset(Max, 0, sizeof(Max));
	memset(Need, 0, sizeof(Need));
	memset(Work, 0, sizeof(Work));
	Reset_Finish();
}
int main()
{
	Init();             //初始化
	Input_RS();         //输入资源信息
	Input_P();          //输入进程信息
	Request();          //银行家算法
	return 0;
}
