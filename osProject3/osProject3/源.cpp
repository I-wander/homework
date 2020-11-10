#include<iostream>
#include<cstring>
using namespace std;
#define MAX_SIZE 8 

//位示图初始化
void init(int bitmap[MAX_SIZE][MAX_SIZE]) {
	int cylinder, track, record; // 柱面号，磁道号，物理记录号
	char order;                  // 输入的指令
	cout << "是否输入已分配空间(y or n)?" << endl;
	cin >> order;
	if (order == 'n')
		return;
	cout << "****************位示图初始化****************" << endl;
	while (true) {
		cout << "请输入已分配空间的柱面号, 磁道号和物理记录号: ";
		cin >> cylinder >> track >> record;
		bitmap[cylinder][4 * track + record] = 1; // 将已分配的空间位示图记录为1
		cout << "继续(c) or 退出(q): ";
		cin >> order;
		if (order == 'q')
			return;
	}
}

// 分配空间
void allocate(int bitmap[MAX_SIZE][MAX_SIZE]) {
	bool flag = false;                                   // 判断是否有可分配空间
	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
			if (bitmap[i][j] == 0) {
				bitmap[i][j] = 1;                        // 分配空间
				cout << "成功分配空间: 柱面号:" << i;    // 柱面号==字节号
				cout << ",磁道号:" << j / 4;             // 磁道号==位数/4
				cout << ",物理记录号:" << j % 4 << endl; // 物理记录号==位数%4
				return;
			}
	cout << "磁盘空间不足，分配失败" << endl;
}

// 回收空间
void recycle(int bitmap[MAX_SIZE][MAX_SIZE]) {
	int cylinder, track, record; // 柱面号，磁道号，物理记录号
	cout << "请输入柱面号, 磁道号和物理记录号: ";
	cin >> cylinder >> track >> record;
	if (bitmap[cylinder][4 * track + record] == 0)
		cout << "该空间未分配，回收失败" << endl;
	else {
		cout << "成功回收空间: 字节号：" << cylinder << "，位数：" << 4 * track + record << endl;
		bitmap[cylinder][4 * track + record] = 0;
	}
}

// 显示位示图
void show(int bitmap[MAX_SIZE][MAX_SIZE]) {
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++)
			printf("%4d", bitmap[i][j]);
		cout << endl;
	}
}

// 用位示图管理磁盘存储空间
void BitMap() {
	
	int bitmap[MAX_SIZE][MAX_SIZE];
	memset(bitmap, 0, sizeof(bitmap));     // 将初值均置为0 
	init(bitmap);                          // 初始化位示图
	char order;                            // 指令
	while (true) {
		cout << "请输入指令(0:分配空间, 1:回收空间, 2:显示位示图, 3:退出): " << endl ;
		cin >> order;
		switch (order) {
		case '0': allocate(bitmap); break;
		case '1': recycle(bitmap); break;
		case '2': show(bitmap); break;
		case '3': return;
		default: cout << "请输入正确的指令!" << endl; break;
		}
	}
}

int main() {
	BitMap();
	return 0;
}