// SATSolver.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "Global.h"

int main()
{
    string filename = R"(sat-20.cnf)";
    int varnum = 0;
    FormulaNode* header = readCNFFile(varnum, filename);
    time_t first, second;
    first = time(NULL);
    int* solution = (int*)malloc(sizeof(int) * varnum);
    int result = DPLL(header, solution);
    second = time(NULL);
    cout << "result is :" << result<<endl;
    cout << "time:" << difftime(second, first);
    for (int i = 0; i < varnum; i++) {
        cout << solution[i] << ' ';
    }
}