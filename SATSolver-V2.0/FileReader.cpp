#include "Global.h"

// 输入文件名，和一个接受参数的引用变量varnum，读取文件后返回创建的内部表示
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
	while (ch != 'p') { //如果首行不是'p'字符开头
		fis.getline(buf, 100);
		fis >> ch;
	}
	string cnf;
	int varNum, clauseNum;
	fis >> cnf >> varNum >> clauseNum;
	fis.get(); //换行符

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
		fis.get(); //换行符
	}
	varnum = varNum; //返回值传递
	getUnitclause(header, unitClause);
	fis.close();
	return header;
}