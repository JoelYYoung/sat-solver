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
	//写入已经存在的文字
	for (int i = 0; i < size * size; i++) {
		if (board[i] == 1) {
			fos << i + 1 << " 0" << endl;
		}
		else if (board[i] == -1) {
			fos << -(i + 1) << " 0" << endl;
		}
	}
	int count1 = 0;
	//对规则一，将子句写入
	for (int i = 0; i < size; i++) { //i表示每一行 和 每一列
		for (int j = 0; j < size - 2; j++) { //选择连续的三个数
			//行(i, j)
			fos << variableID(2, 0, i, j, 0, 0, size) << " " << variableID(2, 0, i, j + 1, 0, 0, size) << " " << variableID(2, 0, i, j + 2, 0, 0, size) << " 0" << endl;
			fos << -variableID(2, 0, i, j, 0, 0, size) << " " << -variableID(2, 0, i, j + 1, 0, 0, size) << " " << -variableID(2, 0, i, j + 2, 0, 0, size) << " 0" << endl;
			//列(j, i)
			fos << variableID(2, 0, j, i, 0, 0, size) << " " << variableID(2, 0, j + 1, i, 0, 0, size) << " " << variableID(2, 0, j + 2, i, 0, 0, size) << " 0" << endl;
			fos << -variableID(2, 0, j, i, 0, 0, size) << " " << -variableID(2, 0, j + 1, i, 0, 0, size) << " " << -variableID(2, 0, j + 2, i, 0, 0, size) << " 0" << endl;
			count1 += 4;
		}
	}
	cout << "规则一 " << count1<<endl;
	//对规则二，将子句写入
	int count2 = 0;
	vector<vector<int>> ans;
	vector<int> temp;
	int count = size / 2 + 1;
	dfs(ans, temp, 1, size, count); // 生成组合数
	cout << "num of ans" << ans.size() << endl;
	while (!ans.empty()) {
		vector<int> tmp = vector<int>{ ans.back() };
		ans.pop_back();
		for (int i = 0; i < size; i++) { //开始行，列遍历
			//写入行正
			for (int j = 0; j < count; j++) {
				fos << variableID(2, 0, i, tmp[j] - 1, 0, 0, size)<<" ";
			}
			fos << "0" << endl;
			//写入行负
			for (int j = 0; j < count; j++) {
				fos << -variableID(2, 0, i, tmp[j] - 1, 0, 0, size) << " ";
			}
			fos << "0" << endl;
			//写入列正
			for (int j = 0; j < count; j++) {
				fos << variableID(2, 0, tmp[j] - 1, i, 0, 0, size) << " ";
			}
			fos << "0" << endl;
			//写入列负
			for (int j = 0; j < count; j++) {
				fos << -variableID(2, 0, tmp[j] - 1, i, 0, 0, size) << " ";
			}
			fos << "0" << endl;
			count2 += 4;
		}
	}
	cout << "规则二 " << count2 << endl;
	//对规则三，将子句写入
	int count3 = 0;
	int count4 = 0;
	int count5 = 0;
	int count6 = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = j + 1; k < size; k++) {
				//需要写入诸如157或者057的子句
				fos << variableID(3, i, j, k, 0, 0, size) << " 0" << endl; //还需要把最终代换的变元写进去
				fos << -variableID(3,i,j,k,0,0,size) << " ";
				for (int l = 0; l < size; l++) {
					fos << -variableID(4, i, j, k, l, 0, size) << " ";
				}
				fos << "0" << endl;
				count3 += 1;
				count4 += 1;
				for (int l = 0; l < size; l++) {
					fos << variableID(3, i, j, k, 0, 0, size) << " " << variableID(4, i, j, k, l, 0, size) << " 0" << endl;
					count3 += 1;
					count4 += 1;
				}
				//下一层
				for (int l = 0; l < size; l++) {
					//需要写入诸如1573或者0537的子句
					fos << -variableID(5, i, j, k, l, 1, size) << " " << variableID(4, i, j, k, l, 0, size) << " 0" << endl;
					fos << -variableID(5, i, j, k, l, 0, size) << " " << variableID(4, i, j, k, l, 0, size) << " 0" << endl;
					fos << variableID(5, i, j, k, l, 0, size) << " " << variableID(5, i, j, k, l, 1, size) << " " << -variableID(4, i, j, k, l, 0, size) << " 0"<<endl;
					count3 += 3;
					count5 += 3;
					for (int m = 0; m < 2; m++) {
						//需要写入诸如15731或者15730的子句
						if(i == 0){ //
							fos << variableID(2, 0, j, l, 0, 0, size) << " " << -variableID(5, i, j, k, l, m,size) << " 0" << endl;
							fos << variableID(2, 0, k, l, 0, 0, size) << " " << -variableID(5, i, j, k, l, m, size) << " 0" << endl;
							fos << -variableID(2, 0, j, l, 0, 0, size) << " " << -variableID(2, 0, k, l, 0, 0, size) << " " << variableID(5, i, j, k, l, m, size) << " 0" << endl;
							count3 += 3;
							count6 += 3;
						}
						else {
							fos << variableID(2, 0, l, j, 0, 0, size) << " " << -variableID(5, i, j, k, l, m, size) << " 0" << endl;
							fos << variableID(2, 0, l, k, 0, 0, size) << " " << -variableID(5, i, j, k, l, m, size) << " 0" << endl;
							fos << -variableID(2, 0, l, j, 0, 0, size) << " " << -variableID(2, 0, l, k, 0, 0, size) << " " << variableID(5, i, j, k, l, m, size) << " 0" << endl;
							count3 += 3;
							count6 += 3;
						}
					}
				}
			}
		}
	}
	cout << "规则三 " << count3 << endl;
	cout << "157 ：" << count4 << endl;
	cout << "1571 ：" << count5 << endl;
	cout << "15781 ：" << count6 << endl;
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
	result += pow(size, 1) * (size - 1) * (size + 2);
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

//计算组合数
long long C(int n, int m)
{
	if (m < n - m) m = n - m;
	long long ans = 1;
	for (int i = m + 1; i <= n; i++) ans *= i;
	for (int i = 1; i <= n - m; i++) ans /= i;
	return ans;
}

//得到拥有size/2+1位的全部组合，保存在fill中
void getCombination(int start, int size, int layer, int* fill) {
	//把数字填好

}

//组合数生成函数
void dfs(vector<vector<int>>& ans,vector<int>& temp,int cur, int n, int k) //组合函数 从n个数中选出k个出来
{
	if (temp.size() + (n - cur + 1) < k) {
		return;
	}
	// 记录合法的答案
	if (temp.size() == k) {
		ans.push_back(temp);
		return;
	}
	// 考虑选择当前位置
	temp.push_back(cur);
	dfs(ans,temp,cur + 1, n, k);
	temp.pop_back();
	// 考虑不选择当前位置
	dfs(ans,temp,cur + 1, n, k);
}