#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <stack>

using namespace std;
#define TRUE 1
#define FALSE 0
#define EXIST 1
#define DELETE 0

struct LiteralNode;

typedef struct ClauseNode {
	int num;
	int flag; //ָʾ�Ӿ��Ƿ��Ѿ���ɾ��
	struct ClauseNode* nextClause;
	LiteralNode* data;
}ClauseNode;

typedef struct LiteralNode {
	int data;
	int flag; //ָʾ�����Ƿ��Ѿ���ɾ��
	struct LiteralNode* nextCounterpart; //ָ����һ��ͬ��ŵ�����
	struct LiteralNode* nextLiteral; //ָ���Ӿ��е���һ������
	ClauseNode* clause; //ָ����������ڵ��Ӿ�Ľڵ�
}LiteralNode;

typedef struct Variable {
	LiteralNode* firstLiteral; //ָʾ��һ����������Ӿ��
	LiteralNode* tmp; //�����ڴ��������ʱ����Ϊ��ʱָ�룬�Ӷ�ʵ��β��
	int flag; //ָʾ�����Ƿ��Ѿ�����ֵ���ˣ�0��ʾδ��ֵ
}Variable;

//����һ����ʽ�����ر�ͷ�ڵ�
ClauseNode* createFormula(Variable*& variableList, int variableNum);
//�½�һ���Ӿ䣬�������Ӿ�Ľڵ�ָ�루���ִ��б�ͷ�ڵ㣩
ClauseNode* insertClause(ClauseNode* header);
//���Ӿ��в���һ���µ�����
void insertLiteral(ClauseNode* clause, int data, Variable* variableList);
//����һstack���ܹ��ҳ��б������еĵ��Ӿ䣬Ȼ����ջ��ָ�룩
void getUnitclause(ClauseNode* header, stack<ClauseNode*>& unitClause);

//�����ļ�������ȡ�ļ����ҷ���variableList���Լ�unitClause
ClauseNode* readCNFFile(int& varnum, int& clausenum,string& filename, Variable*& variableList, stack<ClauseNode*>& unitClause);

//ʵ��DPLL����
int DPLL(ClauseNode* header, Variable*& variableList, stack<ClauseNode*>& clauseStack, int*& solution, int& existing);

//��ȡ���Ӿ������
int getLiteralofUnit(ClauseNode* unitClause);