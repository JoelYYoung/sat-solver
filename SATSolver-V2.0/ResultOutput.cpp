#include "Global.h"

// ������Ҫ����Ĳ����Լ��ļ�����Ȼ�󱣴�Ϊ��Ӧ��ʽ�ĵ�.res�ļ�
void writeResult(int& sat, int* literal, int varnum, int time) {

}

// ������Ҫ����Ĳ�����Ȼ������Ľ���������
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