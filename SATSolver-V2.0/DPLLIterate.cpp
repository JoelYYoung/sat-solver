#include "Global.h"

// 定义一个函数，封装了DPLL过程的迭代实现（不用递归）
int DPLLIterate(ClauseNode* header, Variable*& variableList, stack<ClauseNode*>& unitClauseStack, int varnum, int clausenum, int* solution) {
	stack<int> existingStack; //状态栈，在入栈时更新
	stack<stack<ClauseNode*>> deleteClauseStack; //这是存储栈的栈
	stack<stack<ClauseNode*>> unitClauseStackStack; //存储了unitClauseSatck之前的栈，状态栈
	stack<stack<LiteralNode*>> deleteLiteralStack; //存储了这个节点处删除的文字的栈的栈，可能待会儿还需要考虑内存的层次的问题
	stack<stack<int>> assignedVariableStack; //在完成操作之后再更新
	stack<int> recursionStack; //记录搜索和回溯的进度
	int existing = clausenum; //代表在删除之前的existing的数量
	back:while (true) { //反正先一个循环再说
		//首先不断的删除单子句，肯定是要用到那个单子句的栈了
		stack<ClauseNode*> deleteClause;
		stack<LiteralNode*> deleteLiteral;
		stack<int> assignedVariable; //已经赋值的变量
		while (!unitClauseStack.empty()) {
			//这里面的单子句可能是加入的，也可能是这个循环之前就有的
			ClauseNode* unitClause = unitClauseStack.top();
			unitClauseStack.pop();
			if (unitClause->flag == 0) continue;
			unitClause->flag = 0;
			deleteClause.push(unitClause);
			existing--;
			int variableValue = getLiteralofUnit(unitClause);
			int variableID = abs(variableValue);
			int variableIndex = variableID - 1;
			assignedVariable.push(variableIndex);
			variableList[variableIndex].flag = 1; //赋值变量
			LiteralNode* literalPointer = variableList[variableIndex].firstLiteral;
			while (literalPointer) {
				if (literalPointer->data == variableValue) {
					if (literalPointer->clause->flag == 0) {
						literalPointer = literalPointer->nextCounterpart;
						continue;
					}
					else {
						literalPointer->clause->flag = 0;
						deleteClause.push(literalPointer->clause);
						existing--;
					}
				}
				else {
					literalPointer->flag = 0;
					deleteLiteral.push(literalPointer);
					int num = --(literalPointer->clause->num);
					if (literalPointer->clause->flag == 1) {
						if (num == 0) { //说明这个节点不能走，应该回溯
							variableValue = recursionStack.top();
							if (variableValue > 0) { //如果是正的，那么直接自己退栈，然后恢复所有到之前的状态，然后负的入栈
								//别忘了节点
								recursionStack.pop();
								existing = existingStack.top();
								// existingStack.pop();  本来这里应该弹出的，但是由于后面负的入栈又要入，而且没变，所以就不变了
								unitClauseStack = stack<ClauseNode*>{ unitClauseStackStack.top() };  //注意这里应该是深拷贝
								// unitClauseStackStack.pop(); 同上
								while (!deleteClause.empty()) {
									deleteClause.top()->flag = 1;
									deleteClause.pop();
								}
								while (!deleteLiteral.empty()) {
									deleteLiteral.top()->flag = 1;
									deleteLiteral.top()->clause->num++;
									deleteLiteral.pop();
								}
								while (!assignedVariable.empty()) {
									variableList[assignedVariable.top()].flag = 0; //表示没有赋值
									assignedVariable.pop();
								}

								//负的入栈，节点就不用更改了
								//cout << "Getting into " << -variableValue << endl;
								recursionStack.push(-variableValue);
								header->nextClause->data->nextLiteral->data = -variableValue;
								unitClauseStack.push(header->nextClause);
							}
							else {
								// 本次负的出栈并且恢复原状，节点要删除
								recursionStack.pop();
								existing = existingStack.top()-1;  // -1是必要的，因为之前+1省事
								existingStack.pop(); 
								unitClauseStackStack.top().pop();  //pop()是必要的
								unitClauseStack = stack<ClauseNode*>{ unitClauseStackStack.top() };  //注意这里应该是深拷贝
								unitClauseStackStack.pop();
								while (!deleteClause.empty()) {
									deleteClause.top()->flag = 1;
									deleteClause.pop();
								}
								while (!deleteLiteral.empty()) {
									deleteLiteral.top()->flag = 1;
									deleteLiteral.top()->clause->num++;
									deleteLiteral.pop();
								}
								while (!assignedVariable.empty()) {
									variableList[assignedVariable.top()].flag = 0; //表示没有赋值
									assignedVariable.pop();
								}

								ClauseNode* tmp = header->nextClause;
								header->nextClause = tmp->nextClause;
								free(tmp->data->nextLiteral);
								free(tmp->data);
								free(tmp);

								while ((!recursionStack.empty())&&recursionStack.top() < 0) { //删除栈中所有的负
									//cout << "Jumping out of " << recursionStack.top() << endl;
									recursionStack.pop();
									existing = existingStack.top() - 1;  //必要的
									existingStack.pop();
									unitClauseStackStack.top().pop();  //必要的
									unitClauseStack = stack<ClauseNode*>{ unitClauseStackStack.top() };  //注意这里应该是深拷贝
									unitClauseStackStack.pop();
									deleteClause = deleteClauseStack.top();
									while (!deleteClause.empty()) {
										deleteClause.top()->flag = 1;
										deleteClause.pop();
									}
									deleteClauseStack.pop();
									deleteLiteral = deleteLiteralStack.top();
									while (!deleteLiteral.empty()) {
										deleteLiteral.top()->flag = 1;
										deleteLiteral.top()->clause->num++;
										deleteLiteral.pop();
									}
									deleteLiteralStack.pop();
									assignedVariable = assignedVariableStack.top();
									while (!assignedVariable.empty()) {
										variableList[assignedVariable.top()].flag = 0; //表示没有赋值
										assignedVariable.pop();
									}
									assignedVariableStack.pop();

									ClauseNode* tmp = header->nextClause;
									header->nextClause = tmp->nextClause;
									free(tmp->data->nextLiteral);
									free(tmp->data);
									free(tmp);
								}

								if (recursionStack.empty()) return 0; //说明不可满足了
								//否则这个是个正的，然后按照正的流程走一遍
								variableValue = recursionStack.top();
								//cout << "Jumping out of " << variableValue << endl;
								recursionStack.pop();
								existing = existingStack.top();
								// existingStack.pop();  本来这里应该弹出的，但是由于后面负的入栈又要入，而且没变，所以就不变了
								unitClauseStack = stack<ClauseNode*>{ unitClauseStackStack.top() };  //注意这里应该是深拷贝
								// unitClauseStackStack.pop(); 同上
								deleteClause = deleteClauseStack.top();
								while (!deleteClause.empty()) {
									deleteClause.top()->flag = 1;
									deleteClause.pop();
								}
								deleteClauseStack.pop();
								deleteLiteral = deleteLiteralStack.top();
								while (!deleteLiteral.empty()) {
									deleteLiteral.top()->flag = 1;
									deleteLiteral.top()->clause->num++;
									deleteLiteral.pop();
								}
								deleteLiteralStack.pop();
								assignedVariable = assignedVariableStack.top();
								while (!assignedVariable.empty()) {
									variableList[assignedVariable.top()].flag = 0; //表示没有赋值
									assignedVariable.pop();
								}
								assignedVariableStack.pop();
								//负的入栈，节点就不用更改了
								//cout << "Getting into " << -variableValue << endl;
								recursionStack.push(-variableValue);
								header->nextClause->data->nextLiteral->data = -variableValue;
								unitClauseStack.push(header->nextClause);
							}
							goto back;
						}
						else if (num == 1) { //需要添加新的单子句进去了
							unitClauseStack.push(literalPointer->clause);
						}
					}
				}
				literalPointer = literalPointer->nextCounterpart;
			}
		}
		//然后要保存更改的东西
		deleteClauseStack.push(stack<ClauseNode*>{deleteClause});
		deleteLiteralStack.push(stack<LiteralNode*>{deleteLiteral});
		assignedVariableStack.push(stack<int>{assignedVariable});

		//如果为空了，则为SAT，直接放回
		if (existing == 0) return 1;

		//说明还不行，然后随机选择一个变元加入进去，
		int chosenIndex = 0, chosenPos, chosenNeg;
		while (variableList[chosenIndex].flag) chosenIndex++;
		chosenPos = chosenIndex + 1;
		ClauseNode* newNode = (ClauseNode*)malloc(sizeof(ClauseNode));
		LiteralNode* literalHeader = (LiteralNode*)malloc(sizeof(LiteralNode));
		LiteralNode* newLiteral = (LiteralNode*)malloc(sizeof(LiteralNode));
		newNode->data = literalHeader;
		newNode->nextClause = header->nextClause;
		newNode->flag = 1;
		unitClauseStack.push(newNode);//别急，马上删掉
		literalHeader->nextLiteral = newLiteral;
		newLiteral->data = chosenPos;
		header->nextClause = newNode;
		recursionStack.push(chosenPos);
		existing++;
		//cout << "Getting into " << chosenPos << endl;
		unitClauseStackStack.push(stack<ClauseNode*>{unitClauseStack}); //在所有修改后，需要先把状态保存
		existingStack.push(existing);
	}
};