#include <iostream>
#include <cstdlib>
using namespace std;

const int Max_length = 128;              //����ڴ�Ϊ128K
int a;                                   //�����ţ������������ͣ�
struct freearea                          //����ռ�Ľṹ��
{
	int ID;                              //��ҵ�ţ���ҵ��Ϊ0��ʾ����ҵ��
	int size;                            //������С
	int address;                         //������ַ
	bool flag;                           //ʹ��״̬��0Ϊδռ�ã�1Ϊ��ռ��
};

typedef struct Node              //˫��������
{
	freearea data;               //������
	Node* prior;                 //ָ����
	Node* next;
}*LinkList;

LinkList first = new Node, last = new Node;//˫��������βָ��
void init()//���������г�ʼ��
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
	Node* p = first->next;//ָ����������е��׵�ַ
	cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
	printf("��ҵ��\t��ʼ��ַ\t������С\t����״̬\n");
	while (p)
	{
		if (p->data.ID == 0)
		{
			printf("����ҵ \t%d\t\t%d", p->data.address, p->data.size);
		}
		else
			printf("%d\t%d\t\t%d", p->data.ID, p->data.address, p->data.size);
		if (p->data.flag)
			cout << "\t\t�ѷ���\n" << endl;
		else
			cout << "\t\t����\n" << endl;
		p = p->next;
	}
}

bool first_fit(int id, int size)//�״���Ӧ�㷨
{
	Node* p = first->next;//ָ����������е��׵�ַ
	LinkList fa = new Node;//�½�һ������������ֵ
	fa->data.ID = id;
	fa->data.size = size;
	fa->data.flag = 1;//��ʾ��ռ��
	while (p)//�ڿ������б��дӵ͵�ַ��ߵ�ַ����
	{
		if (p->data.size >= size && !p->data.flag)//�ҵ����ڵ���������ڴ�Ŀ�����
		{
			if (p->data.size == size)
			{
				p->data.ID = id;
				p->data.flag = 1;
				free(fa);//����´����Ŀ�����
				
				return true;
			}
			else if (p->data.size > size)//�������������ڴ������Ҫ������ڴ������մ���
			{
				fa->data.address = p->data.address;//����������ǰ�벿�ֳַ�ȥ
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
	free(fa);                                 //����ʧ��
	return false;
}

bool allocation()//������Դ
{
	int id, size;//�������ҵ�ź��ڴ���С
	cout << "��������ҵ��ź�������ڴ��С��KB����";
	cin >> id >> size;
	if (size <= 0)//������ڴ��СС�ڵ���0������ʧ��
	{
		cout << "������ڴ��С��������������" << endl;
		return false;
	}
	if (first_fit(id, size))
	{
		cout << "�ڴ����ɹ���" << endl;
		show();//��ʾ�ڴ�ֲ�
	}
	else
		cout << "�ڴ治�㣬����ʧ�ܣ�" << endl;
	return true;
}

void recycle()//�����ڴ�
{
	int id;
	cout << "��������Ҫ�ͷŵ���ҵ�ţ�";
	cin >> id;
	Node* p = first->next;//ָ����������е��׵�ַ
	
	while (p)//������Ҫ�ͷŵ���ҵ�ĵ�ַ�����кϲ�����
	{
		if (p->data.ID == id)
		{
			p->data.ID = 0;
			p->data.flag = 0;

			if (p->next == NULL)
			{
				if (!p->prior->data.flag)//��ǰһ�����������ڣ���ϲ�
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
					if (!p->prior->data.flag)//��ǰһ�����������ڣ���ϲ�
					{
						p->prior->data.size += p->data.size;
						p->prior->next = p->next;
						p->next->prior = p->prior;
						p = p->prior;
					}
					if (!p->next->data.flag)//���һ�����������ڣ���ϲ�
					{
						p->data.size += p->next->data.size;
						p->next->next->prior = p;
						p->next = p->next->next;
					}

					break;
				}
				else if (p->prior == first && p->next != last)
				{
					if (!p->next->data.flag)//���һ�����������ڣ���ϲ�
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
					if (!p->prior->data.flag)//��ǰһ�����������ڣ���ϲ�
					{
						p->prior->data.size += p->data.size;
						p->prior->next = p->next;
						p->next->prior = p->prior;
						p = p->prior;
					}
					//	break;
					if (!p->next->data.flag)//���һ�����������ڣ���ϲ�
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
					if (!p->next->data.flag)//���һ�����������ڣ���ϲ�
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
	printf("������\t��ʼ��ַ\t����\n");
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
	init();//��ʼ��
	while (1)
	{
		cout << "****************************************************" << endl;
		cout << "*******1.�����ڴ�   2.�ͷ��ڴ�   3.��ʾ������*******" << endl;
		cout << "�������������";
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
			cout << "�˳�" << endl;
			break;
		}
	}
}