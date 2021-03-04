#include "Global.h"

// �����ļ�������һ�����ܲ��������ñ���varnum����ȡ�ļ��󷵻ش������ڲ���ʾ
ClauseNode* readCNFFile(int& varnum, string& filename, Variable*& variableList, stack<ClauseNode*>& unitClause) {
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
	while (ch != 'p') { //������в���'p'�ַ���ͷ
		fis.getline(buf, 100);
		fis >> ch;
	}
	string cnf;
	int varNum, clauseNum;
	fis >> cnf >> varNum >> clauseNum;
	fis.get(); //���з�

	Variable* variableList_in = (Variable*)malloc(sizeof(Variable) * varNum);
	variableList = variableList_in;

	ClauseNode* header = createFormula(variableList, varNum);
	for (int i = 0; i < clauseNum; i++) {
		int tmp;
		fis >> tmp;
		ClauseNode* newNode = insertClause(header);
		while (tmp != 0) {
			insertLiteral(newNode, tmp, variableList);
			fis >> tmp;
		}
		fis.get(); //���з�
	}
	varnum = varNum; //����ֵ����
	getUnitclause(header, unitClause);
	fis.close();
	return header;
}