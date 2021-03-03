#pragma once

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
#define TRUE 1
#define FALSE 0
#define EXIST 1
#define DELETE 0

typedef struct ClauseNode {
	int num;
	int flag; //指示子句是否已经被删除
	struct ClauseNode* nextClause;

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
	int num; //存储文字被包含在多少个子句中
}Variable;
