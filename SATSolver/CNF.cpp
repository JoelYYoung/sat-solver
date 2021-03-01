#include "Global.h"

/*1.子句函数声明*/
// 新建子句,返回指向表头节点的指针
ClauseNode* createClause() {
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
	while (p && (p->literalData != index && p->literalData != (-index))) {
		cout << "p->literalData = " << p->literalData << endl;
		cout << "index = " << index << endl;
		p = p->next;
	}
	return p;
}

//根据变元编号删除文字
int deleteLiteral(FormulaNode* targetNode, int index) {
	if (targetNode == nullptr) return 0;
	ClauseNode* p = targetNode->data.clauseData;
	int changed = 0;  //如果改变了，changed变为1
	while (p->next && p->next->literalData != index && p->next->literalData != -index) p = p->next;
	if (p->next) {
		changed = 1;
		ClauseNode* tmp = p->next->next;
		free(p->next);
		p->next = tmp;
	}
	targetNode->data.num--;
	return changed;
}

//插入一个文字，采用头插法
void insertLiteral(FormulaNode* targetNode, int data){
	if (targetNode == nullptr) return;
	ClauseNode* newNode = (ClauseNode*)malloc(sizeof(newNode));
	newNode->literalData = data;
	newNode->next = targetNode->data.clauseData->next;
	targetNode->data.clauseData->next = newNode;
	targetNode->data.num++;
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
FormulaNode* getUnitClause(FormulaNode* targetNode) {
	if (targetNode == nullptr)return nullptr;
	FormulaNode* p = targetNode->next;
	while (p) {
		if (p->data.num == 1)return p;
		p = p->next;
	}
	return nullptr;
}

//  删除公式中的子句
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

//  向公式中插入子句
FormulaNode* insertClause(FormulaNode* header) {
	FormulaNode* newNode = (FormulaNode*)malloc(sizeof(FormulaNode));
	ClauseNode* newHeader = createClause();
	newNode->data.clauseData = newHeader;
	newNode->data.num = 0;
	newNode->next = header->next;
	header->next = newNode;
	return newNode;
}

//  向公式中插入子句并返回一个新的公式，data表示新的单子句的文字的值
FormulaNode* deepInsert(FormulaNode* header, int data) {
	//  复制一遍这个公式
	FormulaNode* newheader = (FormulaNode*)malloc(sizeof(FormulaNode));
	newheader->data.clauseData = nullptr;
	newheader->data.num = 0;
	FormulaNode* fp = newheader;
	FormulaNode* fq = header->next;
	//cout << '\n'  <<  "newxt"<< fq->data.clauseData->next->literalData<<endl;
	FormulaNode* newNode = (FormulaNode*)malloc(sizeof(FormulaNode));
	ClauseNode* newClause = (ClauseNode*)malloc(sizeof(ClauseNode));
	ClauseNode* newClauseHeader = (ClauseNode*)malloc(sizeof(ClauseNode));
	newClauseHeader->literalData = 0;
	newClauseHeader->next = newClause;
	newClause->literalData = data;
	newClause->next = nullptr;
	newNode->data.clauseData = newClauseHeader;
	newNode->data.num = 1;
	fp->next = newNode;
	fp = fp->next;
	while (fq) {  //如果有的话
		ClauseNode* cp = (ClauseNode*)malloc(sizeof(ClauseNode));
		cp->literalData = 0;
		cp->next = nullptr;
		ClauseNode* cq = fq->data.clauseData->next;
		//cout << "cq->literal is" << cq->literalData<< endl;
		while (cq) {
			cp->next = (ClauseNode*)malloc(sizeof(ClauseNode));
			cp = cp->next;
			cp->literalData = cq->literalData;
			cp->next = nullptr;
			cq = cq->next;
		}
		fp->next = (FormulaNode*)malloc(sizeof(FormulaNode));
		fp = fp->next;
		fp->data.clauseData = cp;
		fp->data.num = fq->data.num;
		fp->next = nullptr;
		fq = fq->next;
	}
	return newheader;
}
