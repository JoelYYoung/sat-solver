// SATSolver.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "Global.h"

int main()
{
    cout << "Test structure:" << endl;
    FormulaNode* header = createFormula();
    FormulaNode* newNode = insertClause(header);
    insertLiteral(newNode, 1);
    FormulaNode* unitClause = getUnitClause(header);
    cout << "result1:" << unitClause->data.clauseData->next->literalData<<endl;
    FormulaNode* newheader = deepInsert(header, -1);
    ClauseNode* result = getLiteral(newheader->next->data.clauseData, 1);
    if (result != nullptr) cout << "Success" << endl;
    int result1 = deleteLiteral(newheader->next, 1);
    cout << "result2:" << result1<<endl;
    FormulaNode* newheader1 = deepInsert(newheader, 2);
    int result2 = hasVoidClause(newheader1);
    deleteClause(header, unitClause);
    cout << "firstClause:" << header->next->data.clauseData->next->literalData<<endl;
    cout << result2 << endl<<endl;
}