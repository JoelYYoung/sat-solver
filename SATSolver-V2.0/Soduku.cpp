#include "Global.h"

// 输入棋盘大小输出分配的棋盘数组指针
int* getBoard(int size) {
	int num = size * size;
	int* board = (int*)malloc(sizeof(int) * num);
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
			if (k > 0) {
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
	string filepath = R"(BoardCNFFile\board.cnf)";
	ofstream fos;
	fos.open(filepath, ios::trunc);
	if (!fos) {
		cout << "File can NOT open." << endl;
		getchar();
		getchar();
	}
	int clausenum = getClausenumOfBoard(board, size);
	int varnum = getVarnumOfBoard(board, size);
	//写入文件头
	fos << "p cnf " << varnum << " " << clausenum << endl;
	//对规则一，将子句写入
	for (int i = 0; i < size; i++) { //i表示每一行 和 每一列
		for (int j = 0; j < size - 2; j++) { //选择连续的三个数
			//行(i, j)
			fos << variableID(2, 0, i, j, 0, 0, size) << " " << variableID(2, 0, i, j + 1, 0, 0, size) << " " << variableID(2, 0, i, j + 2, 0, 0, size) << " 0" << endl;
			fos << -variableID(2, 0, i, j, 0, 0, size) << " " << -variableID(2, 0, i, j + 1, 0, 0, size) << " " << -variableID(2, 0, i, j + 2, 0, 0, size) << " 0" << endl;
			//列(j, i)
			fos << variableID(2, 0, j, i, 0, 0, size) << " " << variableID(2, 0, j + 1, i, 0, 0, size) << " " << variableID(2, 0, j + 2, i, 0, 0, size) << " 0" << endl;
			fos << -variableID(2, 0, j, i, 0, 0, size) << " " << -variableID(2, 0, j + 1, i, 0, 0, size) << " " << -variableID(2, 0, j + 2, i, 0, 0, size) << " 0" << endl;
		}
	}
	//对规则二，将子句写入
	for (int i = 0; i < size; i++) { //i表示每一行，每一列
		//开始遍历多个变元

	}
	//对规则三，将子句写入
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = j + 1; k < size; k++) {
				//需要写入诸如157或者057的子句
				fos << -variableID(3,i,j,k,0,0,size) << " ";
				for (int l = 0; l < size; l++) {
					fos << -variableID(4, i, j, k, l, 0, size) << " ";
				}
				fos << "0" << endl;
				for (int l = 0; l < size; l++) {
					fos << variableID(3, i, j, k, 0, 0, size) << " " << variableID(4, i, j, k, l, 0, size) << " 0" << endl;
				}
				//下一层
				for (int l = 0; l < size; l++) {
					//需要写入诸如1573或者0537的子句
					fos << -variableID(5, i, j, k, l, 1, size) << " " << variableID(4, i, j, k, l, 0, size) << " 0" << endl;
					fos << -variableID(5, i, j, k, l, 0, size) << " " << variableID(4, i, j, k, l, 0, size) << " 0" << endl;
					fos << variableID(5, i, j, k, l, 0, size) << " " << variableID(5, i, j, k, l, 1, size) << " " << -variableID(4, i, j, k, l, 0, size) << " 0"<<endl;
					for (int m = 0; m < 2; m++) {
						//需要写入诸如15731或者15730的子句
						if(i == 0){ //
							fos << variableID(2, 0, j, l, 0, 0, size) << " " << -variableID(5, i, j, k, l, m,size) << " 0" << endl;
							fos << variableID(2, 0, k, l, 0, 0, size) << " " << -variableID(5, i, j, k, l, m, size) << " 0" << endl;
							fos << -variableID(2, 0, j, l, 0, 0, size) << " " << -variableID(2, 0, k, l, 0, 0, size) << " " << variableID(5, i, j, k, l, m, size) << " 0" << endl;
						}
						else {
							fos << variableID(2, 0, l, j, 0, 0, size) << " " << -variableID(5, i, j, k, l, m, size) << " 0" << endl;
							fos << variableID(2, 0, l, k, 0, 0, size) << " " << -variableID(5, i, j, k, l, m, size) << " 0" << endl;
							fos << -variableID(2, 0, l, j, 0, 0, size) << " " << -variableID(2, 0, l, k, 0, 0, size) << " " << variableID(5, i, j, k, l, m, size) << " 0" << endl;
						}
					}
				}
			}
		}
	}
	fos.close();
}

//输入棋盘数组指针和棋盘的大小，可以产生一个只有唯一解的棋盘
void generateBoard(int* board, int size) {

}

//针对规则三，将3，4，5位辅助变元的编码变成一个对应的连续变元，i(0,1)表示行列，j,k(0到size-1)表示检查的行/列数
//l(0到size-1)表示检查的元素，m(0,1)表示变量同取得值
int variableID(int layer, int i, int j, int k, int l, int m, int size) {
	int result;
	if (layer == 2) { //最原始的变元,j,k表示的含义是不同的，其实2的情况应该分来来看
		result = j * size + k + 1;
	}
	else if (layer == 3) {
		result = size * size + i * size * (size-1)/2 + (size-j-2)*(size-j-1)/2+(size-k-1) + 1;
	}
	else if (layer == 4) {
		result = size * size + size * (size-1) + i * size * (size-1) * size/2 + ((size - j - 2) * (size - j - 1) / 2 + (size - k - 1))*size + l + 1;
	}
	else { //layer == 5
		result = size * size + size * (size-1) + size*size*(size-1) + i * size * size * (size-1) + ((size - j - 2) * (size - j - 1) / 2 + (size - k - 1))*size*2 + l * 2 + m + 1;
	}
	return result;
}

//获取棋盘产生的子句总数
int getClausenumOfBoard(int* board, int size) {
	int varnum = size * size;
	int result = 0;
	for (int i = 0; i < varnum; i++) {
		if (board[i] != 0) result++;
	}
	//规则三
	result += 2 * pow(size, 2) * (size - 1) * 3;
	result += pow(size, 2) * (size - 1) * 3;
	result += pow(size, 1) * (size - 1) * 9;
	//规则一
	result += 2 * size * (size - 2) * 2;
	//规则二
	result += 2 * C(size, size / 2 - 1) * size * 2;
	return result;
}

//获取棋盘产生的变元总数
int getVarnumOfBoard(int* board, int size) {
	int varnum = size * size;
	int result = varnum;
	result += 2 * pow(size, 2) * (size - 1);
	result += pow(size, 2) * (size - 1);
	result += pow(size, 1) * (size - 1);
	return result;
}

//求解组合数的
long long factorial(int n)
{
	long long m = 1;
	for (int i = 1; i <= n; i++) {
		m *= i;
		return m;
	}
}
//求解组合数
int C(int n, int m)
{
	return factorial(n) / (factorial(m) * factorial(n - m));
}

//输入size，生成对应的组合数，保存在一个二维数组中

