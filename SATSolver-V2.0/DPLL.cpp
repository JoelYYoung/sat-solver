#include "Global.h"

int DPLL(ClauseNode* header, Variable*& variableList, stack<ClauseNode*>& clauseStack, int*& solution, int& existing) {
	cout << "Processing..." << endl;
	//cout << "sizeof clauseStack is " << clauseStack.size() << endl;
	//cout << "S existing = " << existing << endl;
	stack<ClauseNode*> deleteClause; //�洢��DPLL������ɾ�����Ӿ��ָ��
	stack<LiteralNode*> deleteLiteral; //�洢��DPLL������ɾ�������ֵ�ָ��
	stack<ClauseNode*> copyStack{clauseStack};  //�������ڻָ�
	stack<int> assignedVariable; //��ֵ����
	int rawExisting = existing;
	//�����ж��Ƿ���ڵ��Ӿ�
	while (!clauseStack.empty()) { //���ڵ��Ӿ�
		ClauseNode* unitClause = clauseStack.top();
		clauseStack.pop();
		if (unitClause->flag == 0) continue;
		deleteClause.push(unitClause);
		unitClause->flag = 0; //ɾ�����Ӿ� 
		existing--;
		int variableValue = getLiteralofUnit(unitClause);
		//cout << "delete clause " << variableValue << endl;
		int variableID = abs(variableValue);
		int variableIndex = variableID - 1;
		variableList[variableIndex].flag = 1; //��ֵ����
		assignedVariable.push(variableIndex); //�����ڱ�DPLL�����и�ֵ�ı���������֮�����
		LiteralNode* literalPointer = variableList[variableIndex].firstLiteral;
		while (literalPointer) { //��ʼɾ��
			if (literalPointer->data == variableValue) { //��ͬ��Ӧ���ж��Ƿ�������Ӿ䣬Ȼ��ɾ��
				if (literalPointer->clause->flag == 0) { //����������ڵ��Ӿ��Ѿ���ɾ���ˣ�ֱ�ӽ�����һ��
					literalPointer = literalPointer->nextCounterpart;
					continue;
				}
				else { //û�б�ɾ������ô��ɾ������Ӿ�
					literalPointer->clause->flag = 0;
					//cout << "delete Clause" << endl;
					deleteClause.push(literalPointer->clause);
					existing--;
				}
			}
			else { //��ͬ��Ӧ��ֱ��ɾ�����֣������жϣ���ӵ����Ӿ�ջ�У�����ǿ��Ӿ䣬ֱ�ӷ���0
				//cout << "delete Literal " << literalPointer->data << endl;
				literalPointer->flag = 0; //���ֲ������Ѿ�ɾ���ˣ��Լ�������
				deleteLiteral.push(literalPointer);
				int num = --(literalPointer->clause->num);
				if (literalPointer->clause->flag != 0) {
					if (num == 0) {
						//�ָ�ԭ״���Ƴ�
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
						return 0; //���ֿ��Ӿ䣬unSAT
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
		//ͨ��variableListѡ��һ����Ԫ��Ȼ��������Ԫ��Ϊһ���������Ӿ���ӵ��ṹ�У�Ȼ��...
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
		clauseStack.push(newNode);//�𼱣�����ɾ��
		literalHeader->nextLiteral = newLiteral;
		newLiteral->data = chosenPos;
		header->nextClause = newNode;
		existing++;
		//cout << "pos trying: " << chosenPos << " ." << endl;
		int pos = DPLL(header, variableList, clauseStack, solution, existing); //���ĳ���
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
		//�ظ�ԭ״
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
		//���ȰѶ����ָ���ԭ��������
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