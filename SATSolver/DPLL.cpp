#include "Global.h"
//  ������DPLL����������FormulaNodeָ�룬����Ƿ��ǿ������
int DPLL(FormulaNode* header, int* result) {
	cout << "Get into DPLL." << endl;
	if (header == nullptr) return 0;
	FormulaNode* unitClause = getUnitClause(header);
	while (unitClause) {
		int index = unitClause->data.clauseData->next->literalData;
		index > 0 ? result[index - 1] = 1 : result[-index - 1] = -1;
		deleteClause(header, unitClause); // ɾ����ʽ�е��Ӿ�
		FormulaNode* tmp = header->next;
		while (tmp) {
			ClauseNode* target = getLiteral(tmp->data.clauseData, index);
			if (target) {
				FormulaNode* n = tmp->next;
				deleteClause(header, tmp);
				cout << "DeleteClause" << endl;
				tmp = n;
				continue;
			}
			else {
				deleteLiteral(tmp, index);
			}
			tmp = tmp->next;
		}
		unitClause = getUnitClause(header);
	}
	if (header->next == nullptr) {
		return 1;
	}
	else if (hasVoidClause(header)) {
		return 0;
	}
	cout << "DPLL end." << endl;
	int chosenLiteral = header->next->data.clauseData->next->literalData;
	if (DPLL(deepInsert(header, chosenLiteral), result)) {
		return 1;
	}
	else {
		return DPLL(deepInsert(header, -chosenLiteral), result);
	}
}