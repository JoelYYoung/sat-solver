#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <stack>
#include <windows.h>

using namespace std;
#define TRUE 1
#define FALSE 0
#define EXIST 1
#define DELETE 0

struct LiteralNode;

typedef struct ClauseNode {
	int num;
	int flag; //指示子句是否已经被删除
	struct ClauseNode* nextClause;
	LiteralNode* data;
}ClauseNode;

typedef struct LiteralNode {
	int data;
	int flag; //指示文字是否已经被删除
	struct LiteralNode* nextCounterpart; //指向下一个同编号的文字
	struct LiteralNode* nextLiteral; //指向子句中的下一个文字
	ClauseNode* clause; //指向改文字所在的子句的节点
}LiteralNode;

typedef struct Variable {
	LiteralNode* firstLiteral; //指示第一个包含这个子句的
	LiteralNode* tmp; //用来在创建链表的时候作为临时指针，从而实现尾插
	int flag; //指示变量是否已经被赋值过了，0表示未赋值
}Variable;

//创建一个公式并返回表头节点
ClauseNode* createFormula(Variable*& variableList, int variableNum);
//新建一个子句，并返回子句的节点指针（文字带有表头节点）
ClauseNode* insertClause(ClauseNode* header);
//在子句中插入一个新的文字
void insertLiteral(ClauseNode* clause, int data, Variable* variableList);
//传入一stack，能够找出列表中所有的单子句，然后入栈（指针）
void getUnitclause(ClauseNode* header, stack<ClauseNode*>& unitClause);

//传入文件名，读取文件并且返回variableList，以及unitClause
ClauseNode* readCNFFile(int& varnum, int& clausenum,string& filename, Variable*& variableList, stack<ClauseNode*>& unitClause);

//实现DPLL过程
int DPLL(ClauseNode* header, Variable*& variableList, stack<ClauseNode*>& clauseStack, int*& solution, int& existing);

//获取单子句的文字
int getLiteralofUnit(ClauseNode* unitClause);

// 定义一个函数，封装了DPLL过程的迭代实现（不用递归）
int DPLLIterate(ClauseNode* header, Variable*& variableList, stack<ClauseNode*>& unitClauseStack, int varnum, int clausenum, int* solution);

//Console交互函数，负责程序于客户的交互
void startProgram();

// 传入需要输出的参数，然后把求解的结果进行输出
int verifyFormula(ClauseNode* header, int clausenum, int varifynum);

/*Soduku functions and structures*/
// 输入棋盘大小输出分配的棋盘数组指针
int* getBoard(int size);
//输入棋盘数组指针和保存结果的数组指针，以及棋盘的大小，将结果输出到棋盘中
void fillBoard(int* solution, int* board, int size);
//输入棋盘数组指针和棋盘的大小，将棋盘打印出来,如果没填，则显示为空格
void showBoard(int* board, int size);
//输入棋盘数组指针和棋盘的大小，输出棋盘格局的
void board2CNFFile(int* board, int size);
//输入棋盘数组指针和棋盘的大小，以及种子，可以产生一个只有唯一解的棋盘
void generateBoard(int* board, int size, int seed);
//针对规则三，将3，4，5位辅助变元的编码变成一个对应的连续变元
int variableID(int i, int j, int k, int l, int m, int size);