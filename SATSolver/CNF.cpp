#include "Global.h"

/*1.�Ӿ亯������*/
// �½��Ӿ�,����ָ���ͷ�ڵ��ָ��
ClauseNode* creatClause() {
	ClauseNode* header = (ClauseNode*)malloc(sizeof(ClauseNode));
	header->literalData = 0;
	header->next = nullptr;
	return header;
}

//����һ���Ӿ䣬����Ϊһ���Ӿ��Node
void destroyClause(ClauseNode* targetNode) {
	if (targetNode == nullptr) return;
	ClauseNode* p = targetNode;  //ͷ�ڵ�ҲҪɾ����
	ClauseNode* tmp = p;
	while (tmp) {
		p = tmp->next;
		free(tmp);
		tmp = p;
	}
}

//���ݱ�Ԫ��Ų������֣��ҵ�����ָ�룬���򷵻�nullptr
ClauseNode* getLiteral(ClauseNode* targetNode, int index) {
	if (targetNode == nullptr) return nullptr;
	ClauseNode* p = targetNode->next;
	while (p && p->literalData != index) p = p->next;
	return p;
}

//���ݱ�Ԫ���ɾ������
int deleteLiteral(FormulaNode* targetNode, int index) {
	if (targetNode == nullptr) return 0;
	ClauseNode* p = targetNode->data.clauseData;
	int changed = 0;  //����ı��ˣ�changed��Ϊ1
	while (p->next && p->next->literalData != index) p = p->next;
	if (p->next) {
		changed = 1;
		ClauseNode* tmp = p->next->next;
		free(p->next);
		p->next = tmp;
	}
	targetNode->data.num--;
	return changed;
}

//����һ�����֣�����ͷ�巨
void insertLiteral(FormulaNode* targetNode, int data){
	if (targetNode == nullptr) return;
	ClauseNode* newNode = (ClauseNode*)malloc(sizeof(newNode));
	newNode->literalData = data;
	newNode->next = targetNode->data.clauseData->next;
	targetNode->data.clauseData->next = newNode;
	targetNode->data.num++;
}

/*2.��ʽ�ĺ�������*/
//  �½���ʽ������ṹ�������ر�ͷ�ڵ�
FormulaNode* createFormula() {
	FormulaNode* header = (FormulaNode*)malloc(sizeof(FormulaNode));
	header->data.clauseData = nullptr;
	header->data.num = 0;
	header->next = nullptr;
	return header;
}

//  ���ٹ�ʽ������Ϊһ����ʽ��Node
void destroyFormula(FormulaNode* targetNode) {
	if (targetNode == nullptr) return;
	FormulaNode* p = targetNode;
	FormulaNode* tmp = nullptr;
	while (p) {
		tmp = p->next;
		destroyClause(p->data.clauseData);
		free(p);
		p = tmp;
	}
}

//  �жϹ�ʽ���Ƿ����Ӿ䣬0Ϊ��
int hasVoidClause(FormulaNode* targetNode) {
	if (targetNode == nullptr)return 0;  //����������ľ���nullptr�򷵻�0
	int result = 0;
	FormulaNode* p = targetNode->next;
	while (p) {
		if (p->data.num == 0) {
			result = 1;
			break;
		}
		p = p->next;
	}
	return result;
}

//  ���ҹ�ʽ�еĵ��Ӿ䲢�����Ӿ�ڵ�ָ�룬��������ڷ���nullptr
FormulaNode* getUnitClause(FormulaNode* targetNode) {
	if (targetNode == nullptr)return nullptr;
	FormulaNode* p = targetNode->next;
	while (p) {
		if (p->data.num == 1)return p;
		p = p->next;
	}
	return nullptr;
}

//  ɾ����ʽ�е��Ӿ�
int deleteClause(FormulaNode* header, FormulaNode* targetNode) {
	if (targetNode == nullptr)return 0;
	FormulaNode* p = targetNode;
	FormulaNode* tmp = nullptr;
	while (p->next) {
		if (p->next == targetNode) {
			tmp = p->next->next;
			free(p->next);
			p->next = tmp;
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//  ��ʽ�в����Ӿ�
FormulaNode* insertClause(FormulaNode* header) {
	FormulaNode* newNode = (FormulaNode*)malloc(sizeof(FormulaNode));
	ClauseNode* newHeader = (ClauseNode*)malloc(sizeof(ClauseNode));
	newNode->data.clauseData = newHeader;
	newNode->data.num = 0;
	newNode->next = header->next;
	header->next = newNode;
	return newNode;
}

//  ��ʽ�в����Ӿ䲢����һ���µĹ�ʽ��data��ʾ�µĵ��Ӿ�����ֵ�ֵ
FormulaNode* deepInsert(FormulaNode* header, int data) {
	//  ����һ�������ʽ
	FormulaNode* newheader = (FormulaNode*)malloc(sizeof())
}
