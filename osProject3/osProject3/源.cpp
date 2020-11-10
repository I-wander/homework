#include<iostream>
#include<cstring>
using namespace std;
#define MAX_SIZE 8 

//λʾͼ��ʼ��
void init(int bitmap[MAX_SIZE][MAX_SIZE]) {
	int cylinder, track, record; // ����ţ��ŵ��ţ������¼��
	char order;                  // �����ָ��
	cout << "�Ƿ������ѷ���ռ�(y or n)?" << endl;
	cin >> order;
	if (order == 'n')
		return;
	cout << "****************λʾͼ��ʼ��****************" << endl;
	while (true) {
		cout << "�������ѷ���ռ�������, �ŵ��ź������¼��: ";
		cin >> cylinder >> track >> record;
		bitmap[cylinder][4 * track + record] = 1; // ���ѷ���Ŀռ�λʾͼ��¼Ϊ1
		cout << "����(c) or �˳�(q): ";
		cin >> order;
		if (order == 'q')
			return;
	}
}

// ����ռ�
void allocate(int bitmap[MAX_SIZE][MAX_SIZE]) {
	bool flag = false;                                   // �ж��Ƿ��пɷ���ռ�
	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
			if (bitmap[i][j] == 0) {
				bitmap[i][j] = 1;                        // ����ռ�
				cout << "�ɹ�����ռ�: �����:" << i;    // �����==�ֽں�
				cout << ",�ŵ���:" << j / 4;             // �ŵ���==λ��/4
				cout << ",�����¼��:" << j % 4 << endl; // �����¼��==λ��%4
				return;
			}
	cout << "���̿ռ䲻�㣬����ʧ��" << endl;
}

// ���տռ�
void recycle(int bitmap[MAX_SIZE][MAX_SIZE]) {
	int cylinder, track, record; // ����ţ��ŵ��ţ������¼��
	cout << "�����������, �ŵ��ź������¼��: ";
	cin >> cylinder >> track >> record;
	if (bitmap[cylinder][4 * track + record] == 0)
		cout << "�ÿռ�δ���䣬����ʧ��" << endl;
	else {
		cout << "�ɹ����տռ�: �ֽںţ�" << cylinder << "��λ����" << 4 * track + record << endl;
		bitmap[cylinder][4 * track + record] = 0;
	}
}

// ��ʾλʾͼ
void show(int bitmap[MAX_SIZE][MAX_SIZE]) {
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++)
			printf("%4d", bitmap[i][j]);
		cout << endl;
	}
}

// ��λʾͼ������̴洢�ռ�
void BitMap() {
	
	int bitmap[MAX_SIZE][MAX_SIZE];
	memset(bitmap, 0, sizeof(bitmap));     // ����ֵ����Ϊ0 
	init(bitmap);                          // ��ʼ��λʾͼ
	char order;                            // ָ��
	while (true) {
		cout << "������ָ��(0:����ռ�, 1:���տռ�, 2:��ʾλʾͼ, 3:�˳�): " << endl ;
		cin >> order;
		switch (order) {
		case '0': allocate(bitmap); break;
		case '1': recycle(bitmap); break;
		case '2': show(bitmap); break;
		case '3': return;
		default: cout << "��������ȷ��ָ��!" << endl; break;
		}
	}
}

int main() {
	BitMap();
	return 0;
}