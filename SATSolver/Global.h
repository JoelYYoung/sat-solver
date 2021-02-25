#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
// ��һ�ִ洢�ṹ����ʽ�洢�ṹ

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

/*1.�Ӿ�ĺ�������*/
//  �½��Ӿ䣨����ṹ�������ر�ͷ���
ClauseNode* creatClause();
//  �����Ӿ䣬����Ϊ�Ӿ��ͷ�ڵ�ָ��
void destroyClause(ClauseNode* targetNode);
//  ���ݱ�Ԫ��Ų������֣�indexΪ��Ҫ���ҵı��
ClauseNode* getLiteral(ClauseNode* targetNode, int index);
//  ���ݱ�Ԫ���ɾ������
int deleteLiteral(ClauseNode* targetNode, int index);
//  ����һ������
void insertLiteral(ClauseNode* targetNode, int data);

/*2.��ʽ�ĺ�������*/
//  �½���ʽ������ṹ�������ر�ͷ�ڵ�
FormulaNode* createFormula();
//  ���ٹ�ʽ������Ϊһ����ʽ��Node
void destroyFormula(FormulaNode* targetNode);
//  �жϹ�ʽ���Ƿ����Ӿ�
int hasVoidClause(FormulaNode* targetNode);
//  ���ҹ�ʽ�еĵ��Ӿ䲢�����Ӿ�ڵ�ָ�룬��������ڷ���nullptr
ClauseNode* getUnitClause(FormulaNode* targetNode);
//  ɾ����ʽ�е��Ӿ�
int deleteClause(FormulaNode* header, FormulaNode* targetNode);
//  ��ʽ�в����Ӿ䲢����һ���µĹ�ʽ
#endif

