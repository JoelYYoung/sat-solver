#include "Global.h"

//创建一个公式并返回表头节点
ClauseNode* createFormula(Variable*& variableList, int variableNum) {
	ClauseNode* header = (ClauseNode*)malloc(sizeof(ClauseNode));
	header->data = nullptr;
	header->num = 0;
	header->flag = 1;
	header->nextClause = nullptr;
	for (int i = 0; i < variableNum; i++) {
		variableList[i].firstLiteral = nullptr;
		variableList[i].tmp = nullptr;
	}
	return header;
}

//新建一个子句，并返回子句的节点指针（文字带有表头节点）
ClauseNode* insertClause(ClauseNode* header) {
	ClauseNode* newNode = (ClauseNode*)malloc(sizeof(ClauseNode));
	LiteralNode* literalHeader = (LiteralNode*)malloc(sizeof(LiteralNode));
	literalHeader->clause = newNode;
	literalHeader->data = 0;
	literalHeader->flag = 1;
	literalHeader->nextCounterpart = nullptr;
	literalHeader->nextLiteral = nullptr;
	newNode->data = literalHeader;
	newNode->flag = 1;
	newNode->num = 0;
	newNode->nextClause = header->nextClause;
	header->nextClause = newNode;
	return newNode;
}

//在子句中插入一个新的文字
void insertLiteral(ClauseNode* clause, int data, Variable* variableList) {
	int variableID = abs(data) - 1;
	LiteralNode* newLiteral = (LiteralNode*)malloc(sizeof(LiteralNode));
	newLiteral->clause = clause;
	newLiteral->data = data;
	newLiteral->flag = 1;
	if (variableList[variableID].firstLiteral == nullptr) { //说明应该将这个文字作为这个编号变元的首结点
		variableList[variableID].firstLiteral = newLiteral;
		variableList[variableID].tmp = newLiteral;
	}
	else {
		variableList[variableID].tmp->nextCounterpart = newLiteral;
		variableList[variableID].tmp = newLiteral;
	}
	newLiteral->nextCounterpart = nullptr;
	newLiteral->nextLiteral = clause->data->nextLiteral; //存在表头结点
	clause->data->nextLiteral = newLiteral;
	clause->num++; //记得更新三个地方，clause num, variable table, unitClause stack
}

//传入一stack，能够找出列表中所有的单子句，然后入栈（指针）
void getUnitclause(ClauseNode* header, stack<ClauseNode*>& unitClause) {
	ClauseNode* tmp = header->nextClause;
	while (tmp) {
		if (tmp->num == 1) unitClause.push(tmp);
		tmp = tmp->nextClause;
	}
}
