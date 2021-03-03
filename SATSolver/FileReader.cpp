# include "Global.h"

// �����ļ�������һ�����ܲ��������ñ���varnum����ȡ�ļ��󷵻ش������ڲ���ʾ
FormulaNode* readCNFFile(int &varnum, string &filename) {
	string HFilePath = R"(CNFFile\)";
	string path = HFilePath + filename;
	ifstream fis(path);
	if (!fis) {
		cout << "File can NOT open." << endl;
		exit;
	}
	char ch;
	char buf[100];
	fis >> ch;
	while (ch != 'p'){ //������в���'p'�ַ���ͷ
		fis.getline(buf, 100);
		fis >> ch;
	}
	string cnf;
	int varNum, clauseNum;
	fis >> cnf >> varNum >> clauseNum;
	fis.get(); //���з�

	FormulaNode* header = createFormula();
	for (int i = 0; i < clauseNum; i++) {
		int tmp;
		fis >> tmp;
		FormulaNode* newNode = insertClause(header);
		while (tmp != 0) {
			insertLiteral(newNode, tmp);
			fis >> tmp;
		}
		fis.get(); //���з�
	}
	varnum = varNum; //����ֵ����
	return header;
}

void printFormula(FormulaNode* header) {
	cout << "Formula is:" << endl;
	
}


