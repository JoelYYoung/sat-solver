#include "Global.h"

// �������̴�С����������������ָ��
int* getBoard(int size) {
	int num = size * size;
	int* board = (int*)malloc(sizeof(int)*num);
	for (int i = 0; i < num; i++) {
		board[i] = 0;
	}
	return board;
}

//������������ָ��ͱ�����������ָ�룬�Լ����̵Ĵ�С������������������
void fillBoard(int* solution, int* board, int size) {
	int num = size * size;
	for (int i = 0; i < num; i++) {
		board[i] = solution[i];
	}
	return;
}
//������������ָ������̵Ĵ�С�������̴�ӡ����,���û�����ʾΪ�ո�
void showBoard(int* board, int size) {
	for (int i = 0; i < size; i++) {
		cout << " ---";
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << "|";
		for (int j = 0; j < size; j++) {
			int k = board[i * size + j];
			if(k > 0){
				cout << " " << 1 << " |";
			}
			else if (k == 0) {
				cout << "   |";
			}
			else {
				cout << " " << 0 << " |";
			}
		}
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << " ---";
		}
		cout << endl;
	}
	return;
}

//������������ָ������̵Ĵ�С��������̸�ֵ�
void board2CNFFile(int* board, int size) {

}

//������������ָ������̵Ĵ�С���Լ����ӣ����Բ���һ��ֻ��Ψһ�������
void generateBoard(int* board, int size, int seed) {

}

//��Թ���������3��4��5λ������Ԫ�ı�����һ����Ӧ��������Ԫ��i(0,1)��ʾ���У�j,k(0��size-1)��ʾ������/����
//l(0��size-1)��ʾ����Ԫ�أ�m(0,1)��ʾ����ͬȡ��ֵ
int variableID(int layer, int i, int j, int k, int l, int m, int size) {
	int result;
	if (layer == 2) { //��ԭʼ�ı�Ԫ
		result = i * size + j;
	}
	else if (layer == 3) {
		result = size * size + i * size * size * 2 + k * size * size + l * size;
	}
	else if (layer == 4) {
		result = size*size + 2*size*size + 
	}
	else { //layer == 5

	}
}