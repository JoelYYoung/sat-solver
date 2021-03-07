#include "Global.h"

// 传入需要保存的参数以及文件名，然后保存为相应格式的的.res文件
void writeResult(int& sat, int* literal, int varnum, int time) {

}

// 传入需要输出的参数，然后把求解的结果进行输出
int verifyFormula(ClauseNode* header, int clausenum, int varifynum) {
	int shownum = varifynum < clausenum ? varifynum : clausenum;
	ClauseNode* tmpclause = header->nextClause;
	for (int i = 0; i < shownum; i++) {
		LiteralNode* tmpliteral = tmpclause->data->nextLiteral;
		for (int j = 0; j < tmpclause->num; j++) {
			cout << tmpliteral->data << " ";
			tmpliteral = tmpliteral->nextLiteral;
		}
		cout << endl;

		tmpclause = tmpclause->nextClause;
	}
	return 1;
}