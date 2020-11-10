#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define Process_Max 10                                         //�����������ֵ
#define Resource_Max 10                                        //��Դ�������ֵ
using namespace std;

int Available[Resource_Max];                                    //ϵͳ��ǰÿ����Դ�ɷ�����
int Max[Process_Max][Resource_Max];                             //ÿ�����̶�ÿ����Դ�������
int Allocation[Process_Max][Resource_Max];                      //ÿ�������ѷ�����Դ
int Need[Process_Max][Resource_Max];                            //ÿ�����̵�ǰ������Դ����������ȥ�ѷ���
int Work[Resource_Max];                                         //��������
int Finish[Process_Max];                                        //�Ƿ����㹻��Դ���������
int List[Process_Max];                                          //��ȫ���б�
int Process_Num = 0, Resource_Num = 0;                          //������ ��Դ��
int List_Num = 0;                                               //��ȫ���е����

void Input_RS()                               //������ڳ�ʼ��Դ������
{
	cout<< "��������Դ����:" << endl;
	cin>> Resource_Num;

	cout << "������ϵͳ��ǰ��������Դ��:" << endl;
	for (int i = 0; i < Resource_Num; i++)
	{
		cout << "R" << i << ":";
		cin >> Available[i];
	}
}
void Input_P()                              //������ڳ�ʼ���̵�����
{
	cout << "���������:" << endl;
	cin >> Process_Num;

	for (int i = 0; i < Process_Num; i++)
	{
		cout << "������� P" << i << "�������Դ���� Max:" << endl;
		for (int j = 0; j < Resource_Num; j++)
		{
			cout << "R" << j << ":";
			cin >> Max[i][j];
		}
		cout << endl;
		cout << "������� P" << i << "���ѷ�����Դ Allocation:" << endl;
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

void Reset_Finish()                                            //��ʼ��finish��work����
{
	memset(Finish, 0, sizeof(Finish));
	memset(Work, 0, sizeof(Work));
	List_Num = 0;
}

int Safe()                                                     //��ȫ���㷨
{
	int flag = 0, Count = 0;
	cout << "��ȫ�������£�" << endl;
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
		cout << "û�а�ȫ����" << endl;
		return 0;
	}
	else {
		cout << "��ȫ���д���" << endl;
		return 1;
	}
}

void Show()                                                    //���ϵͳ�������Ϣ
{    
	cout << "��ǰ�Ľ�����Ϣ���£�" << endl;
	cout << "��ǰ��������Դ Available:" << endl;
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

void Request()                                                  //���м��㷨
{
	int pro, Request_Num[Resource_Max], inst = 0;

	while (!inst)
	{
		cout << "���뷢������Ľ��� :" << endl;
		cin >> pro;
		cout << "����������Դ��Ŀ :" << endl;
		for (int i = 0; i < Resource_Num; i++)
		{
			cout << "R" << i << ":";
			cin >> Request_Num[i];
		}

		for (int i = 0; i < Resource_Num; i++)
		{
			if (Request_Num[i] > Need[pro][i])
			{
				cout << "������Դ��Ŀ�������跶Χ��������Ч" << endl;
				return;
			}
			if (Request_Num[i] > Available[i])
			{
				cout << "û���㹻��Դ������ʧ��" << endl;
				return;
			}
		}
		for (int i = 0; i < Resource_Num; i++)                 //�Է���
		{
			Available[i] -= Request_Num[i];
			Allocation[pro][i] += Request_Num[i];
			Need[pro][i] -= Request_Num[i];
		}
		if (!Safe())                                           //�ж��Ƿ�ȫ
		{
			for (int i = 0; i < Resource_Num; i++)
			{
				Available[i] += Request_Num[i];
				Allocation[pro][i] -= Request_Num[i];
				Need[pro][i] += Request_Num[i];
			}
			cout << "�ܾ���������"<< endl;
		}
		else {
			cout << "����ɹ�" << endl;
			Show();
		}
		cout << "------------------------------" << endl;
		cout << "������ָ��:" << endl;
		cout << "0�������������� " << endl;
		cout << "1���˳� " << endl;
		cin >> inst;
	}
}


void Init()                                                    //��ʼ����������
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
	Init();             //��ʼ��
	Input_RS();         //������Դ��Ϣ
	Input_P();          //���������Ϣ
	Request();          //���м��㷨
	return 0;
}
