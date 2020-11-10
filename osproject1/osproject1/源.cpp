#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct PNode {         // PCB
	struct PNode* next;        // ����ָ����һ���ڵ��ָ��
	char name[10];             // �����������������ռ�
	int All_Time;              // ����������ʱ��
	int Runed_Time;            // ����������ʱ��
	char state;                // �������״̬ Ready / End
}*Pcbs;                        

int PcbsNum;                   // �ܽ��̸���

// ��ʼ����������
void InitPCB(Pcbs& H) {
	cout << "�������ܽ��̸���: ";
	cin >> PcbsNum;                              // �����ܸ���
	int Num = PcbsNum;
	H = (Pcbs)malloc(sizeof(PNode));             // ����ͷ�ڵ�    
	H->next = NULL;
	Pcbs p = H;                                  //����һ��ָ��ָ��ͷ�ڵ�
	cout << "�ܽ��̸���Ϊ " << PcbsNum << " ��,������������Ӧ��Ϣ"<<endl;

	while (Num--) {
		p = p->next = (Pcbs)malloc(sizeof(PNode));
		cout << "������ ������ʱ�� ������ʱ�� :";
		cin >> p->name >> p->All_Time >> p->Runed_Time;
		p->state = 'R';
		p->next = NULL;
	}
	p->next = H->next;         //���һ���ڵ�nextָ���׽ڵ�
}

//��������еĽ�����Ϣ
void Display(Pcbs H) {
	Pcbs p = H->next;
	do {
		if (p->state != 'E')   //����ý��̵�״̬����End�Ļ�
		{
			cout << "������:" << p->name << "\t������ʱ��:" << p->All_Time
				<< "\t������ʱ��:" << p->Runed_Time
				<< "\t״̬:" << p->state << endl;
			p = p->next;
		}
		else p = p->next;
	} while (p != H->next);   // ��ָ���׽��ʱһֱѭ��
}

// ʱ��Ƭ��ת��
void SJP_Simulator(Pcbs& H) {
	cout << endl << "-------------------��ʼ--------------------"<<endl;
	int flag = PcbsNum;                       // ��¼ʣ�������
	int round = 0;                            // ��¼��ת��
	Pcbs p = H->next;
	while (p->All_Time > p->Runed_Time) {     // δ�����Ľ���
		round++;
		cout << endl << "Round " << round << "--�������� " << p->name << " ����" << endl;
		p->Runed_Time++;                      // �����������еĽ��̵�������ʱ��
		Display(p);                           // �����ʱΪ����״̬�Ľ��̵���Ϣ
		if (p->All_Time == p->Runed_Time) {   // ���жϸý����Ƿ����
			p->state = 'E';
			flag--;
			cout << p->name << " ���������н���,���̱�ɾ��!"<<endl;
		}
		p = p->next;
		while (flag && p->All_Time == p->Runed_Time)
			p = p->next;                      // ������ǰ�ѽ����Ľ���

	}
	cout << endl << "--------------------����---------------------"<<endl;
}


void main() {
	Pcbs H;
	InitPCB(H); // ���ݳ�ʼ��
	Display(H); // ����˿̵Ľ���״̬
	SJP_Simulator(H); // ʱ��Ƭ��ת��

}