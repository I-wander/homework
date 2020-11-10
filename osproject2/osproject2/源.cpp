#include <iostream>
#include <cstdlib>
using namespace std;

const int Max_length = 128;              //最大内存为128K
int a;                                   //操作号（决定操作类型）
struct freearea                          //主存空间的结构体
{
	int ID;                              //作业号（作业号为0表示无作业）
	int size;                            //分区大小
	int address;                         //分区地址
	bool flag;                           //使用状态，0为未占用，1为已占用
};

typedef struct Node              //双向链表结点
{
	freearea data;               //数据域
	Node* prior;                 //指针域
	Node* next;
}*LinkList;

LinkList first = new Node, last = new Node;//双向链表首尾指针
void init()//空闲区队列初始化
{
	first->prior = NULL;
	first->next = last;
	last->prior = first;
	last->next = NULL;
	first->data.size = 0;
	last->data.address = 0;
	last->data.size = Max_length;
	last->data.ID = 0;
	last->data.flag = 0;           
}

void show()
{
	Node* p = first->next;//指向空闲区队列的首地址
	cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
	printf("作业号\t起始地址\t分区大小\t分区状态\n");
	while (p)
	{
		if (p->data.ID == 0)
		{
			printf("无作业 \t%d\t\t%d", p->data.address, p->data.size);
		}
		else
			printf("%d\t%d\t\t%d", p->data.ID, p->data.address, p->data.size);
		if (p->data.flag)
			cout << "\t\t已分配\n" << endl;
		else
			cout << "\t\t空闲\n" << endl;
		p = p->next;
	}
}

bool first_fit(int id, int size)//首次适应算法
{
	Node* p = first->next;//指向空闲区队列的首地址
	LinkList fa = new Node;//新建一个空闲区并赋值
	fa->data.ID = id;
	fa->data.size = size;
	fa->data.flag = 1;//表示被占用
	while (p)//在空闲区列表中从低地址向高地址查找
	{
		if (p->data.size >= size && !p->data.flag)//找到大于等于所需的内存的空闲区
		{
			if (p->data.size == size)
			{
				p->data.ID = id;
				p->data.flag = 1;
				free(fa);//清空新创建的空闲区
				
				return true;
			}
			else if (p->data.size > size)//空闲区比所需内存大，则需要将多的内存作回收处理
			{
				fa->data.address = p->data.address;//将空闲区的前半部分分出去
				p->data.address += size;
				p->data.size -= size;
				p->prior->next = fa;
				fa->next = p;
				fa->prior = p->prior;
				p->prior = fa;
				return true;
			}
		}
		p = p->next;
	}
	free(fa);                                 //分配失败
	return false;
}

bool allocation()//分配资源
{
	int id, size;//输入的作业号和内存块大小
	cout << "请输入作业编号和申请的内存大小（KB）：";
	cin >> id >> size;
	if (size <= 0)//申请的内存大小小于等于0，申请失败
	{
		cout << "申请的内存大小错误！请重新输入" << endl;
		return false;
	}
	if (first_fit(id, size))
	{
		cout << "内存分配成功！" << endl;
		show();//显示内存分布
	}
	else
		cout << "内存不足，分配失败！" << endl;
	return true;
}

void recycle()//回收内存
{
	int id;
	cout << "请输入想要释放的作业号：";
	cin >> id;
	Node* p = first->next;//指向空闲区队列的首地址
	
	while (p)//查找需要释放的作业的地址并进行合并工作
	{
		if (p->data.ID == id)
		{
			p->data.ID = 0;
			p->data.flag = 0;

			if (p->next == NULL)
			{
				if (!p->prior->data.flag)//与前一个空闲区相邻，则合并
				{
					p->prior->data.size += p->data.size;
					p->prior->next = p->next;
					p = p->prior;
					break;
				}
			}
			else {

				if (p->prior != first && p->next != last)
				{
					if (!p->prior->data.flag)//与前一个空闲区相邻，则合并
					{
						p->prior->data.size += p->data.size;
						p->prior->next = p->next;
						p->next->prior = p->prior;
						p = p->prior;
					}
					if (!p->next->data.flag)//与后一个空闲区相邻，则合并
					{
						p->data.size += p->next->data.size;
						p->next->next->prior = p;
						p->next = p->next->next;
					}

					break;
				}
				else if (p->prior == first && p->next != last)
				{
					if (!p->next->data.flag)//与后一个空闲区相邻，则合并
					{
						p->data.size += p->next->data.size;
						p->next->next->prior = p;
						p->next = p->next->next;
					}
					break;
				}
				//else if(p->prior!=first&&p->next->next==NULL)
				else if (p->prior != first && p->next == last)
				{
					if (!p->prior->data.flag)//与前一个空闲区相邻，则合并
					{
						p->prior->data.size += p->data.size;
						p->prior->next = p->next;
						p->next->prior = p->prior;
						p = p->prior;
					}
					//	break;
					if (!p->next->data.flag)//与后一个空闲区相邻，则合并
					{
						last->data.size += p->data.size;
						last->data.address = p->data.address;
						last->prior = p->prior;
						p->prior->next = last;
						p = last;
					}
					break;
				}
				else if (p->prior == first && p->next == last)
				{
					if (!p->next->data.flag)//与后一个空闲区相邻，则合并
					{
						last->data.size += p->data.size;
						last->data.address = p->data.address;
						p->prior->next = last;

					}
					break;
				}
			}
		}
		p = p->next;
	}
	show();
}

void print()
{
	Node* p = first->next;
	int i = 1;
	cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
	printf("分区号\t起始地址\t长度\n");
	while (p)
	{
		if (p->data.ID == 0)
		{
			printf("%d\t%d\t\t%d\n", i, p->data.address, p->data.size);
			i++;
		}
		p = p->next;
	}
}

int main()
{
	init();//初始化
	while (1)
	{
		cout << "****************************************************" << endl;
		cout << "*******1.申请内存   2.释放内存   3.显示空闲区*******" << endl;
		cout << "请输入操作数：";
		cin >> a;
		switch (a)
		{
		case 1:
			allocation();
			break;
		case 2:
			recycle();
			break;
		case 3:
			print();
			break;
		default:
			cout << "退出" << endl;
			break;
		}
	}
}