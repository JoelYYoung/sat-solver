﻿// SATSolver-V2.0.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Global.h"

int main()
{
    //cout << "Test Starting:"<<endl;
    //cout << "Create Formula." << endl;
    //int varnum = 3;
    //Variable* variableList = (Variable*)malloc(sizeof(Variable) * varnum);
    //ClauseNode* header = createFormula(variableList, varnum);
    //cout << "Formula Created." << endl;
    //cout << "Insert 3 Clauses." << endl;
    //ClauseNode* firstClause = insertClause(header);
    //ClauseNode* secondClause = insertClause(header);
    //ClauseNode* thirdClause = insertClause(header);
    //cout << "Clauses Inserted." << endl;
    //cout << "Insert Literals" << endl;
    //insertLiteral(firstClause, 1, variableList);
    //cout << "First Literal Inserted." << endl;
    //insertLiteral(firstClause, 2, variableList);
    //insertLiteral(secondClause, -1, variableList);
    //insertLiteral(secondClause, 3, variableList);
    //insertLiteral(thirdClause, -3, variableList);
    //insertLiteral(thirdClause, -2, variableList);
    //cout << "Literals Inserted." << endl;
    //cout << "Verifiy." << endl;
    //cout << "The firstClause has " << header->nextClause->num << " literals."<<endl;
    //cout << "Variable 2's second literal is " << variableList[1].firstLiteral->nextCounterpart->data << "."<<endl;


    ////正式开始进行文件读取操作
    //string filename = R"(my.cnf)";
    //int varnum = 0;
    //stack<ClauseNode*> unitClause;
    //Variable* variableList = nullptr;
    //ClauseNode* header = readCNFFile(varnum, filename, variableList, unitClause);
    //cout << "There are " << unitClause.size() << " unitclauses in the formula." << endl;
    //cout << "The first Literal is " << header->nextClause->data->nextLiteral->data <<" ."<< endl;
    ////文件读取测试完成

    //开始开始测试DPLL过程
    string filename = R"(board.cnf)";
    int varnum = 0, clausenum = 0;
    stack<ClauseNode*> unitClause;
    Variable* variableList = nullptr;
    ClauseNode* header = readCNFFile(varnum, clausenum,filename, variableList, unitClause);
    int* solution = (int*)malloc(sizeof(int) * varnum);
    int result;
    
    //计时功能
    LARGE_INTEGER t1, t2, tc;
    double time;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    //需计时的函数
    //result = DPLL(header, variableList, unitClause, solution, clausenum);
    result = DPLLIterate(header, variableList, unitClause, varnum, clausenum, solution);
    QueryPerformanceCounter(&t2);
    time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
    cout << "Result = " << result << endl;
    cout << "Time = " << time << endl;  //输出时间（单位：ｓ）
    int* board = (int*)malloc(sizeof(int) * 36);
    fillBoard(solution, board, 6);
    showBoard(board, 6);
    
    //测试Console的功能
    /*startProgram();*/

    /*int i[64];
    for (int j = 0; j < 64; j++) {
        i[j] = 0;
    }
    showBoard(i, 3);
    cout << getVarnumOfBoard(i, 8)<<endl;*/
    //int i[36] = {1,0,0,-1,0,0,0,0,-1,-1,0,1,0,-1,-1,0,0,1,0,0,0,0,0,0,-1,-1,0,1,0,0,0,1,0,0,-1,-1};
    /*int i[64];
    for (int j = 0; j < 64; j++) {
        i[j] = 0;
    }*/
    //board2CNFFile(i, 6);
    /*vector<vector<int>> ans;
    vector<int> temp;
    dfs(ans, temp, 1, 4, 3);
    cout << "Size of ans is:" << ans.size() << endl;
    cout << ans[0][0] << endl;
    cout << ans[0][1] << endl;*/
}
