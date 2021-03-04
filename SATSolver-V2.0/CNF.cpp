#include "Global.h"

//����һ����ʽ�����ر�ͷ�ڵ�
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

//�½�һ���Ӿ䣬�������Ӿ�Ľڵ�ָ�루���ִ��б�ͷ�ڵ㣩
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
	newNode->nextClause = nullptr;
	header->nextClause = newNode;
	return newNode;
}

//���Ӿ��в���һ���µ�����
void insertLiteral(ClauseNode* clause, int data, Variable* variableList) {
	int variableID = abs(data) - 1;
	LiteralNode* newLiteral = (LiteralNode*)malloc(sizeof(LiteralNode));
	newLiteral->clause = clause;
	newLiteral->data = data;
	newLiteral->flag = 1;
	if (variableList[variableID].firstLiteral == nullptr) { //˵��Ӧ�ý����������Ϊ�����ű�Ԫ���׽��
		variableList[variableID].firstLiteral = newLiteral;
		variableList[variableID].tmp = newLiteral;
	}
	else {
		variableList[variableID].tmp->nextCounterpart = newLiteral;
		variableList[variableID].tmp = newLiteral;
	}
	newLiteral->nextCounterpart = nullptr;
	newLiteral->nextLiteral = clause->data->nextLiteral; //���ڱ�ͷ���
	clause->data->nextLiteral = newLiteral;
	clause->num++; //�ǵø��������ط���clause num, variable table, unitClause stack
}
