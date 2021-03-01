#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
// 第一种存储结构，链式存储结构

typedef struct ClauseNode {
	int literalData;
	ClauseNode* next;
}ClauseNode;

typedef struct ClauseData {
	int num;
	ClauseNode* clauseData;
}ClauseData;

typedef struct FormulaNode {
	ClauseData data;
	FormulaNode* next;
}FormulaNode;

/*1.子句的函数声明*/
//  新建子句（链表结构），返回表头结点 pass
ClauseNode* createClause();
//  销毁子句，参数为子句的头节点指针 pass
void destroyClause(ClauseNode* targetNode);
//  根据变元编号查找文字，index为需要查找的编号 pass
ClauseNode* getLiteral(ClauseNode* targetNode, int index);
//  根据变元编号删除文字 pass
int deleteLiteral(FormulaNode* targetNode, int index);  //插入FormulaNode，因为需要更改里面的数字
//  插入一个文字 pass
void insertLiteral(FormulaNode* targetNode, int data);  //插入FormulaNode，因为需要更改里面的数字

/*2.公式的函数声明*/
//  新建公式（链表结构），返回表头节点 pass
FormulaNode* createFormula(); 
//  销毁公式，参数为一个公式的Node pass（基本不要用）
void destroyFormula(FormulaNode* targetNode);
//  判断公式中是否存空子句 pass
int hasVoidClause(FormulaNode* targetNode); 
//  查找公式中的单子句并返回子句节点指针，如果不存在返回nullptr pass
FormulaNode* getUnitClause(FormulaNode* targetNode);
//  删除公式中的子句 pass
int deleteClause(FormulaNode* header, FormulaNode* targetNode);
//  向公式中插入子句 pass
FormulaNode* insertClause(FormulaNode* header);
//  向公式中插入子句并返回一个新的公式 pass
FormulaNode* deepInsert(FormulaNode* header, int data);
#endif

