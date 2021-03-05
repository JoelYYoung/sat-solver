#include "Global.h"

int DPLL(ClauseNode* header, Variable*& variableList, stack<ClauseNode*>& clauseStack, int*& solution, int& existing) {
	cout << "Processing..." << endl;
	//cout << "sizeof clauseStack is " << clauseStack.size() << endl;
	//cout << "S existing = " << existing << endl;
	stack<ClauseNode*> deleteClause; //存储在DPLL过程中删除的子句的指针
	stack<LiteralNode*> deleteLiteral; //存储在DPLL过程中删除的文字的指针
	stack<ClauseNode*> copyStack{clauseStack};  //复制用于恢复
	stack<int> assignedVariable; //赋值变量
	int rawExisting = existing;
	//首先判断是否存在单子句
	while (!clauseStack.empty()) { //存在单子句
		ClauseNode* unitClause = clauseStack.top();
		clauseStack.pop();
		if (unitClause->flag == 0) continue;
		deleteClause.push(unitClause);
		unitClause->flag = 0; //删除单子句 
		existing--;
		int variableValue = getLiteralofUnit(unitClause);
		//cout << "delete clause " << variableValue << endl;
		int variableID = abs(variableValue);
		int variableIndex = variableID - 1;
		variableList[variableIndex].flag = 1; //赋值变量
		assignedVariable.push(variableIndex); //保存在本DPLL过程中赋值的变量，方便之后回退
		LiteralNode* literalPointer = variableList[variableIndex].firstLiteral;
		while (literalPointer) { //开始删除
			if (literalPointer->data == variableValue) { //相同，应该判断是否是这个子句，然后删除
				if (literalPointer->clause->flag == 0) { //如果文字所在的子句已经被删除了，直接进入下一个
					literalPointer = literalPointer->nextCounterpart;
					continue;
				}
				else { //没有被删除，那么就删除这个子句
					literalPointer->clause->flag = 0;
					//cout << "delete Clause" << endl;
					deleteClause.push(literalPointer->clause);
					existing--;
				}
			}
			else { //不同，应该直接删除文字，并且判断，添加到单子句栈中，如果是空子句，直接返回0
				//cout << "delete Literal " << literalPointer->data << endl;
				literalPointer->flag = 0; //文字不可能已经删除了，自己推理下
				deleteLiteral.push(literalPointer);
				int num = --(literalPointer->clause->num);
				if (literalPointer->clause->flag != 0) {
					if (num == 0) {
						//恢复原状再推出
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
							variableList[assignedVariable.top()].flag = 0;
							assignedVariable.pop();
						}
						clauseStack = copyStack;
						existing = rawExisting;

						//cout << "return 0" << endl;
						return 0; //出现空子句，unSAT
					}
					else if(num == 1) {
						clauseStack.push(literalPointer->clause);
					}
				}
			}
			literalPointer = literalPointer->nextCounterpart;
		}
	}
	//cout << "existing = " << existing << endl;
	if (existing > 0) {
		//通过variableList选择一个变元，然后把这个变元作为一个单独的子句添加到结构中，然后...
		int chosenIndex = 0, chosenPos, chosenNeg;
		while (variableList[chosenIndex].flag) chosenIndex++;
		chosenPos = chosenIndex + 1;
		chosenNeg = -chosenPos;

		ClauseNode* newNode = (ClauseNode*)malloc(sizeof(ClauseNode));
		LiteralNode* literalHeader = (LiteralNode*)malloc(sizeof(LiteralNode));
		LiteralNode* newLiteral = (LiteralNode*)malloc(sizeof(LiteralNode));
		newNode->data = literalHeader;
		newNode->nextClause = header->nextClause;
		newNode->flag = 1;
		clauseStack.push(newNode);//别急，马上删掉
		literalHeader->nextLiteral = newLiteral;
		newLiteral->data = chosenPos;
		header->nextClause = newNode;
		existing++;
		//cout << "pos trying: " << chosenPos << " ." << endl;
		int pos = DPLL(header, variableList, clauseStack, solution, existing); //正的尝试
		if (pos) {
			header->nextClause = newNode->nextClause;
			free(newNode);
			free(literalHeader);
			free(newLiteral);
			clauseStack.pop();
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
				variableList[assignedVariable.top()].flag = 0;
				assignedVariable.pop();
			}
			clauseStack = copyStack;
			existing = rawExisting;
			//cout << "pos return 1" << endl;
			return 1;
		}
		newLiteral->data = chosenNeg;
		//cout << "neg trying: " << chosenNeg << " ." << endl;
		int neg = DPLL(header, variableList, clauseStack, solution, existing);
		//回复原状
		header->nextClause = newNode->nextClause;
		free(newNode);
		free(literalHeader);
		free(newLiteral);
		clauseStack.pop();
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
			variableList[assignedVariable.top()].flag = 0;
			assignedVariable.pop();
		}
		clauseStack = copyStack;
		existing = rawExisting;

		//cout << "neg return " << neg << endl;
		return neg;
	}
	else {
		//首先把东西恢复到原来的样子
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
			variableList[assignedVariable.top()].flag = 0;
			assignedVariable.pop();
		}
		clauseStack = copyStack;
		existing = rawExisting;

		//cout << "return 1" << endl;
		return 1;
	}
}