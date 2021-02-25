#include "Global.h"

/*1.子句函数声明*/
// 新建子句,返回指向表头节点的指针
ClauseNode* creatClause() {
	ClauseNode* header = (ClauseNode*)malloc(sizeof(ClauseNode));
	header->literalData = 0;
	header->next = nullptr;
	return header;
}

//销毁一个子句，参数为一个子句的Node
void destroyClause(ClauseNode* targetNode) {
	if (targetNode == nullptr) return;
	ClauseNode* p = targetNode;  //头节点也要删除了
	ClauseNode* tmp = p;
	while (tmp) {
		p = tmp->next;
		free(tmp);
		tmp = p;
	}
}

//根据变元编号查找文字，找到返回指针，否则返回nullptr
ClauseNode* getLiteral(ClauseNode* targetNode, int index) {
	if (targetNode == nullptr) return nullptr;
	ClauseNode* p = targetNode->next;
	while (p && p->literalData != index) p = p->next;
	return p;
}

//根据变元编号删除文字
int deleteLiteral(ClauseNode* targetNode, int index) {
	if (targetNode == nullptr) return 0;
	ClauseNode* p = targetNode;
	int changed = 0;  //如果改变了，changed变为1
	while (p->next && p->next->literalData != index) p = p->next;
	if (p->next) {
		changed = 1;
		ClauseNode* tmp = p->next->next;
		free(p->next);
		p->next = tmp;
	}
	return changed;
}

//插入一个文字，采用头插法
void insertLiteral(ClauseNode* targetNode, int data){
	if (targetNode == nullptr) return;
	ClauseNode* newNode = (ClauseNode*)malloc(sizeof(newNode));
	newNode->literalData = data;
	newNode->next = targetNode->next;
	targetNode->next = newNode;
}

/*2.公式的函数声明*/
//  新建公式（链表结构），返回表头节点
FormulaNode* createFormula() {
	FormulaNode* header = (FormulaNode*)malloc(sizeof(FormulaNode));
	header->data.clauseData = nullptr;
	header->data.num = 0;
	header->next = nullptr;
	return header;
}

//  销毁公式，参数为一个公式的Node
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

//  判断公式中是否存空子句，0为无
int hasVoidClause(FormulaNode* targetNode) {
	if (targetNode == nullptr)return 0;  //如果传进来的就是nullptr则返回0
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

//  查找公式中的单子句并返回子句节点指针，如果不存在返回nullptr
ClauseNode* getUnitClause(FormulaNode* targetNode) {

}

//  删除公式中的子句
int deleteClause(FormulaNode* header, FormulaNode* targetNode);
//  向公式中插入子句并返回一个新的公式