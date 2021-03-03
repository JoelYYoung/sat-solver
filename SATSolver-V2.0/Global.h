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
	int flag; //ָʾ�Ӿ��Ƿ��Ѿ���ɾ��
	struct ClauseNode* nextClause;

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
	int num; //�洢���ֱ������ڶ��ٸ��Ӿ���
}Variable;
