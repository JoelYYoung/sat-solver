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
//  新建子句（链表结构），返回表头结点
ClauseNode* creatClause();
//  销毁子句，参数为子句的头节点指针
void destroyClause(ClauseNode* targetNode);
//  根据变元编号查找文字，index为需要查找的编号
ClauseNode* getLiteral(ClauseNode* targetNode, int index);
//  根据变元编号删除文字
int deleteLiteral(ClauseNode* targetNode, int index);
//  插入一个文字
void insertLiteral(ClauseNode* targetNode, int data);

/*2.公式的函数声明*/
//  新建公式（链表结构），返回表头节点
FormulaNode* createFormula();
//  销毁公式，参数为一个公式的Node
void destroyFormula(FormulaNode* targetNode);
//  判断公式中是否存空子句
int hasVoidClause(FormulaNode* targetNode);
//  查找公式中的单子句并返回子句节点指针，如果不存在返回nullptr
ClauseNode* getUnitClause(FormulaNode* targetNode);
//  删除公式中的子句
int deleteClause(FormulaNode* header, FormulaNode* targetNode);
//  向公式中插入子句并返回一个新的公式
#endif

