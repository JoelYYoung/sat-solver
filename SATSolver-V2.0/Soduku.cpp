#include "Global.h"

// 输入棋盘大小输出分配的棋盘数组指针
int* getBoard(int size) {
	int num = size * size;
	int* board = (int*)malloc(sizeof(int)*num);
	for (int i = 0; i < num; i++) {
		board[i] = 0;
	}
	return board;
}

//输入棋盘数组指针和保存结果的数组指针，以及棋盘的大小，将结果输出到棋盘中
void fillBoard(int* solution, int* board, int size) {
	int num = size * size;
	for (int i = 0; i < num; i++) {
		board[i] = solution[i];
	}
	return;
}
//输入棋盘数组指针和棋盘的大小，将棋盘打印出来,如果没填，则显示为空格
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

//输入棋盘数组指针和棋盘的大小，输出棋盘格局的
void board2CNFFile(int* board, int size) {

}

//输入棋盘数组指针和棋盘的大小，以及种子，可以产生一个只有唯一解的棋盘
void generateBoard(int* board, int size, int seed) {

}

//针对规则三，将3，4，5位辅助变元的编码变成一个对应的连续变元，i(0,1)表示行列，j,k(0到size-1)表示检查的行/列数
//l(0到size-1)表示检查的元素，m(0,1)表示变量同取得值
int variableID(int layer, int i, int j, int k, int l, int m, int size) {
	int result;
	if (layer == 2) { //最原始的变元
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