#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct PNode {         // PCB
	struct PNode* next;        // 定义指向下一个节点的指针
	char name[10];             // 定义进程名，并分配空间
	int All_Time;              // 定义总运行时间
	int Runed_Time;            // 定义已运行时间
	char state;                // 定义进程状态 Ready / End
}*Pcbs;                        

int PcbsNum;                   // 总进程个数

// 初始化就绪队列
void InitPCB(Pcbs& H) {
	cout << "请输入总进程个数: ";
	cin >> PcbsNum;                              // 进程总个数
	int Num = PcbsNum;
	H = (Pcbs)malloc(sizeof(PNode));             // 建立头节点    
	H->next = NULL;
	Pcbs p = H;                                  //定义一个指针指向头节点
	cout << "总进程个数为 " << PcbsNum << " 个,请依次输入相应信息"<<endl;

	while (Num--) {
		p = p->next = (Pcbs)malloc(sizeof(PNode));
		cout << "进程名 总运行时间 已运行时间 :";
		cin >> p->name >> p->All_Time >> p->Runed_Time;
		p->state = 'R';
		p->next = NULL;
	}
	p->next = H->next;         //最后一个节点next指回首节点
}

//输出运行中的进程信息
void Display(Pcbs H) {
	Pcbs p = H->next;
	do {
		if (p->state != 'E')   //如果该进程的状态不是End的话
		{
			cout << "进程名:" << p->name << "\t总运行时间:" << p->All_Time
				<< "\t已运行时间:" << p->Runed_Time
				<< "\t状态:" << p->state << endl;
			p = p->next;
		}
		else p = p->next;
	} while (p != H->next);   // 不指向首结点时一直循环
}

// 时间片轮转法
void SJP_Simulator(Pcbs& H) {
	cout << endl << "-------------------开始--------------------"<<endl;
	int flag = PcbsNum;                       // 记录剩余进程数
	int round = 0;                            // 记录轮转数
	Pcbs p = H->next;
	while (p->All_Time > p->Runed_Time) {     // 未结束的进程
		round++;
		cout << endl << "Round " << round << "--正在运行 " << p->name << " 进程" << endl;
		p->Runed_Time++;                      // 更改正在运行的进程的已运行时间
		Display(p);                           // 输出此时为就绪状态的进程的信息
		if (p->All_Time == p->Runed_Time) {   // 并判断该进程是否结束
			p->state = 'E';
			flag--;
			cout << p->name << " 进程已运行结束,进程被删除!"<<endl;
		}
		p = p->next;
		while (flag && p->All_Time == p->Runed_Time)
			p = p->next;                      // 跳过先前已结束的进程

	}
	cout << endl << "--------------------结束---------------------"<<endl;
}


void main() {
	Pcbs H;
	InitPCB(H); // 数据初始化
	Display(H); // 输出此刻的进程状态
	SJP_Simulator(H); // 时间片轮转法

}