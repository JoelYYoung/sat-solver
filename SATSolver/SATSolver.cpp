// SATSolver.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "Global.h"

int main()
{
    cout << "Test structure:" << endl;
    FormulaNode* header = createFormula();
    FormulaNode* newNode = insertClause(header);
    insertLiteral(newNode, 1);
    FormulaNode* unitClause = getUnitClause(header);
    cout << "result:" << unitClause->data.clauseData->next->literalData;
}