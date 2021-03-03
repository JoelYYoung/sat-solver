#include "Global.h"
//  基本的DPLL函数，传入FormulaNode指针，输出是否是可满足的
int DPLL(FormulaNode* header) {
	cout << "Get into DPLL." << endl;
	if (header == nullptr) return 0;
	FormulaNode* unitClause = getUnitClause(header);
	while (unitClause) {
		int index = unitClause->data.clauseData->next->literalData;
		cout << "index is " << index<<endl;
		cout << "Deleted? " << deleteClause(header, unitClause)<<endl; // 删除公式中的子句
		FormulaNode* tmp = header->next;
		//cout << "tmp is:"<<tmp->data.clauseData->next->literalData<<endl;
		while (tmp) {
			ClauseNode* target = getLiteral(tmp->data.clauseData,index);
			if (target) {
				FormulaNode* n = tmp->next;
				deleteClause(header, tmp);
				cout << "DeleteClause"<<endl;
				tmp = n;
				continue;
			}
			else {
				deleteLiteral(tmp, index);
			}
			tmp = tmp->next;
			cout << 2 << endl;
		}
		cout << 3 << endl;
		unitClause = getUnitClause(header);
		
		if (unitClause != nullptr) {
			cout << "unitClause!=nullptr" << endl;
		}
		else {
			cout << "unitClause == nullptr" << endl;
		}
	}
	if (header->next == nullptr) {
		cout << "return 1" << endl;
		return 1;
	}
	else if (hasVoidClause(header)) {
		cout << "return 0" << endl;
		return 0;
	}
	cout << "DPLL end." << endl;
	int chosenLiteral = header->next->data.clauseData->next->literalData;
	return DPLL(deepInsert(header, chosenLiteral)) || DPLL(deepInsert(header, -chosenLiteral));
}