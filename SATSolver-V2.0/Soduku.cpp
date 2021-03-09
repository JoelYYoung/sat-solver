#include "Global.h"

// �������̴�С����������������ָ��
int* getBoard(int size) {
	int num = size * size;
	int* board = (int*)malloc(sizeof(int) * num);
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

//������������ָ������̵Ĵ�С��������̸�ֵ�
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
	//д���ļ�ͷ
	fos << "p cnf " << varnum << " " << clausenum << endl;
	//д���Ѿ����ڵ�����
	for (int i = 0; i < size * size; i++) {
		if (board[i] == 1) {
			fos << i + 1 << " 0" << endl;
		}
		else if (board[i] == -1) {
			fos << -(i + 1) << " 0" << endl;
		}
	}
	int count1 = 0;
	//�Թ���һ�����Ӿ�д��
	for (int i = 0; i < size; i++) { //i��ʾÿһ�� �� ÿһ��
		for (int j = 0; j < size - 2; j++) { //ѡ��������������
			//��(i, j)
			fos << variableID(2, 0, i, j, 0, 0, size) << " " << variableID(2, 0, i, j + 1, 0, 0, size) << " " << variableID(2, 0, i, j + 2, 0, 0, size) << " 0" << endl;
			fos << -variableID(2, 0, i, j, 0, 0, size) << " " << -variableID(2, 0, i, j + 1, 0, 0, size) << " " << -variableID(2, 0, i, j + 2, 0, 0, size) << " 0" << endl;
			//��(j, i)
			fos << variableID(2, 0, j, i, 0, 0, size) << " " << variableID(2, 0, j + 1, i, 0, 0, size) << " " << variableID(2, 0, j + 2, i, 0, 0, size) << " 0" << endl;
			fos << -variableID(2, 0, j, i, 0, 0, size) << " " << -variableID(2, 0, j + 1, i, 0, 0, size) << " " << -variableID(2, 0, j + 2, i, 0, 0, size) << " 0" << endl;
			count1 += 4;
		}
	}
	cout << "����һ " << count1<<endl;
	//�Թ���������Ӿ�д��
	int count2 = 0;
	vector<vector<int>> ans;
	vector<int> temp;
	int count = size / 2 + 1;
	dfs(ans, temp, 1, size, count); // ���������
	cout << "num of ans" << ans.size() << endl;
	while (!ans.empty()) {
		vector<int> tmp = vector<int>{ ans.back() };
		ans.pop_back();
		for (int i = 0; i < size; i++) { //��ʼ�У��б���
			//д������
			for (int j = 0; j < count; j++) {
				fos << variableID(2, 0, i, tmp[j] - 1, 0, 0, size)<<" ";
			}
			fos << "0" << endl;
			//д���и�
			for (int j = 0; j < count; j++) {
				fos << -variableID(2, 0, i, tmp[j] - 1, 0, 0, size) << " ";
			}
			fos << "0" << endl;
			//д������
			for (int j = 0; j < count; j++) {
				fos << variableID(2, 0, tmp[j] - 1, i, 0, 0, size) << " ";
			}
			fos << "0" << endl;
			//д���и�
			for (int j = 0; j < count; j++) {
				fos << -variableID(2, 0, tmp[j] - 1, i, 0, 0, size) << " ";
			}
			fos << "0" << endl;
			count2 += 4;
		}
	}
	cout << "����� " << count2 << endl;
	//�Թ����������Ӿ�д��
	int count3 = 0;
	int count4 = 0;
	int count5 = 0;
	int count6 = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = j + 1; k < size; k++) {
				//��Ҫд������157����057���Ӿ�
				fos << variableID(3, i, j, k, 0, 0, size) << " 0" << endl; //����Ҫ�����մ����ı�Ԫд��ȥ
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
				//��һ��
				for (int l = 0; l < size; l++) {
					//��Ҫд������1573����0537���Ӿ�
					fos << -variableID(5, i, j, k, l, 1, size) << " " << variableID(4, i, j, k, l, 0, size) << " 0" << endl;
					fos << -variableID(5, i, j, k, l, 0, size) << " " << variableID(4, i, j, k, l, 0, size) << " 0" << endl;
					fos << variableID(5, i, j, k, l, 0, size) << " " << variableID(5, i, j, k, l, 1, size) << " " << -variableID(4, i, j, k, l, 0, size) << " 0"<<endl;
					count3 += 3;
					count5 += 3;
					for (int m = 0; m < 2; m++) {
						//��Ҫд������15731����15730���Ӿ�
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
	cout << "������ " << count3 << endl;
	cout << "157 ��" << count4 << endl;
	cout << "1571 ��" << count5 << endl;
	cout << "15781 ��" << count6 << endl;
	fos.close();
}

//������������ָ������̵Ĵ�С�����Բ���һ��ֻ��Ψһ�������
void generateBoard(int* board, int size) {

}

//��Թ���������3��4��5λ������Ԫ�ı�����һ����Ӧ��������Ԫ��i(0,1)��ʾ���У�j,k(0��size-1)��ʾ������/����
//l(0��size-1)��ʾ����Ԫ�أ�m(0,1)��ʾ����ͬȡ��ֵ
int variableID(int layer, int i, int j, int k, int l, int m, int size) {
	int result;
	if (layer == 2) { //��ԭʼ�ı�Ԫ,j,k��ʾ�ĺ����ǲ�ͬ�ģ���ʵ2�����Ӧ�÷�������
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

//��ȡ���̲������Ӿ�����
int getClausenumOfBoard(int* board, int size) {
	int varnum = size * size;
	int result = 0;
	for (int i = 0; i < varnum; i++) {
		if (board[i] != 0) result++;
	}
	//������
	result += 2 * pow(size, 2) * (size - 1) * 3;
	result += pow(size, 2) * (size - 1) * 3;
	result += pow(size, 1) * (size - 1) * (size + 2);
	//����һ
	result += 2 * size * (size - 2) * 2;
	//�����
	result += 2 * C(size, size / 2 - 1) * size * 2;
	return result;
}

//��ȡ���̲����ı�Ԫ����
int getVarnumOfBoard(int* board, int size) {
	int varnum = size * size;
	int result = varnum;
	result += 2 * pow(size, 2) * (size - 1);
	result += pow(size, 2) * (size - 1);
	result += pow(size, 1) * (size - 1);
	return result;
}

//���������
long long C(int n, int m)
{
	if (m < n - m) m = n - m;
	long long ans = 1;
	for (int i = m + 1; i <= n; i++) ans *= i;
	for (int i = 1; i <= n - m; i++) ans /= i;
	return ans;
}

//�õ�ӵ��size/2+1λ��ȫ����ϣ�������fill��
void getCombination(int start, int size, int layer, int* fill) {
	//���������

}

//��������ɺ���
void dfs(vector<vector<int>>& ans,vector<int>& temp,int cur, int n, int k) //��Ϻ��� ��n������ѡ��k������
{
	if (temp.size() + (n - cur + 1) < k) {
		return;
	}
	// ��¼�Ϸ��Ĵ�
	if (temp.size() == k) {
		ans.push_back(temp);
		return;
	}
	// ����ѡ��ǰλ��
	temp.push_back(cur);
	dfs(ans,temp,cur + 1, n, k);
	temp.pop_back();
	// ���ǲ�ѡ��ǰλ��
	dfs(ans,temp,cur + 1, n, k);
}