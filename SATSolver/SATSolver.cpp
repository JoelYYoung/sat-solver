// SATSolver.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "Global.h"

int main()
{
    string filename = R"(problem1-20.cnf)";
    int varnum = 0;
    /*
    FormulaNode* header = createFormula();
    FormulaNode* newNode = insertClause(header);
    insertLiteral(newNode, 1);
    insertLiteral(newNode, 2);
    insertLiteral(newNode, 3);
    deleteLiteral(newNode, 2);
    cout << "The next Literal is: " << newNode->data.clauseData->next->literalData<<endl;*/
    //cout << "First Clause:" << header->next->data.clauseData->next->next->literalData << endl;
    FormulaNode* header = readCNFFile(varnum, filename);
    /*FormulaNode* unitClause = getUnitClause(header);
    if (unitClause != nullptr) {
        cout << unitClause->data.clauseData->next->literalData << endl;
    }
    else {
        cout << "is not Nullptr" << endl;
    }*/
    int result = DPLL(header);
    cout << "result is :" << result<<endl;
}