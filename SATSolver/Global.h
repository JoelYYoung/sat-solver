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
//  �½��Ӿ䣨����ṹ�������ر�ͷ��� pass
ClauseNode* createClause();
//  �����Ӿ䣬����Ϊ�Ӿ��ͷ�ڵ�ָ�� pass
void destroyClause(ClauseNode* targetNode);
//  ���ݱ�Ԫ��Ų������֣�indexΪ��Ҫ���ҵı�� pass
ClauseNode* getLiteral(ClauseNode* targetNode, int index);
//  ���ݱ�Ԫ���ɾ������ pass
int deleteLiteral(FormulaNode* targetNode, int index);  //����FormulaNode����Ϊ��Ҫ�������������
//  ����һ������ pass
void insertLiteral(FormulaNode* targetNode, int data);  //����FormulaNode����Ϊ��Ҫ�������������

/*2.��ʽ�ĺ�������*/
//  �½���ʽ������ṹ�������ر�ͷ�ڵ� pass
FormulaNode* createFormula(); 
//  ���ٹ�ʽ������Ϊһ����ʽ��Node pass��������Ҫ�ã�
void destroyFormula(FormulaNode* targetNode);
//  �жϹ�ʽ���Ƿ����Ӿ� pass
int hasVoidClause(FormulaNode* targetNode); 
//  ���ҹ�ʽ�еĵ��Ӿ䲢�����Ӿ�ڵ�ָ�룬��������ڷ���nullptr pass
FormulaNode* getUnitClause(FormulaNode* targetNode);
//  ɾ����ʽ�е��Ӿ� pass
int deleteClause(FormulaNode* header, FormulaNode* targetNode);
//  ��ʽ�в����Ӿ� pass
FormulaNode* insertClause(FormulaNode* header);
//  ��ʽ�в����Ӿ䲢����һ���µĹ�ʽ pass
FormulaNode* deepInsert(FormulaNode* header, int data);
#endif

