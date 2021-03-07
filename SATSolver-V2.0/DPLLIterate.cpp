#include "Global.h"

// ����һ����������װ��DPLL���̵ĵ���ʵ�֣����õݹ飩
int DPLLIterate(ClauseNode* header, Variable*& variableList, stack<ClauseNode*>& unitClauseStack, int varnum, int clausenum, int* solution) {
	stack<int> existingStack; //״̬ջ������ջʱ����
	stack<stack<ClauseNode*>> deleteClauseStack; //���Ǵ洢ջ��ջ
	stack<stack<ClauseNode*>> unitClauseStackStack; //�洢��unitClauseSatck֮ǰ��ջ��״̬ջ
	stack<stack<LiteralNode*>> deleteLiteralStack; //�洢������ڵ㴦ɾ�������ֵ�ջ��ջ�����ܴ��������Ҫ�����ڴ�Ĳ�ε�����
	stack<stack<int>> assignedVariableStack; //����ɲ���֮���ٸ���
	stack<int> recursionStack; //��¼�����ͻ��ݵĽ���
	int existing = clausenum; //������ɾ��֮ǰ��existing������
	back:while (true) { //������һ��ѭ����˵
		//���Ȳ��ϵ�ɾ�����Ӿ䣬�϶���Ҫ�õ��Ǹ����Ӿ��ջ��
		stack<ClauseNode*> deleteClause;
		stack<LiteralNode*> deleteLiteral;
		stack<int> assignedVariable; //�Ѿ���ֵ�ı���
		while (!unitClauseStack.empty()) {
			//������ĵ��Ӿ�����Ǽ���ģ�Ҳ���������ѭ��֮ǰ���е�
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
			variableList[variableIndex].flag = 1; //��ֵ����
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
						if (num == 0) { //˵������ڵ㲻���ߣ�Ӧ�û���
							variableValue = recursionStack.top();
							if (variableValue > 0) { //��������ģ���ôֱ���Լ���ջ��Ȼ��ָ����е�֮ǰ��״̬��Ȼ�󸺵���ջ
								//�����˽ڵ�
								recursionStack.pop();
								existing = existingStack.top();
								// existingStack.pop();  ��������Ӧ�õ����ģ��������ں��渺����ջ��Ҫ�룬����û�䣬���ԾͲ�����
								unitClauseStack = stack<ClauseNode*>{ unitClauseStackStack.top() };  //ע������Ӧ�������
								// unitClauseStackStack.pop(); ͬ��
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
									variableList[assignedVariable.top()].flag = 0; //��ʾû�и�ֵ
									assignedVariable.pop();
								}

								//������ջ���ڵ�Ͳ��ø�����
								//cout << "Getting into " << -variableValue << endl;
								recursionStack.push(-variableValue);
								header->nextClause->data->nextLiteral->data = -variableValue;
								unitClauseStack.push(header->nextClause);
							}
							else {
								// ���θ��ĳ�ջ���һָ�ԭ״���ڵ�Ҫɾ��
								recursionStack.pop();
								existing = existingStack.top()-1;  // -1�Ǳ�Ҫ�ģ���Ϊ֮ǰ+1ʡ��
								existingStack.pop(); 
								unitClauseStackStack.top().pop();  //pop()�Ǳ�Ҫ��
								unitClauseStack = stack<ClauseNode*>{ unitClauseStackStack.top() };  //ע������Ӧ�������
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
									variableList[assignedVariable.top()].flag = 0; //��ʾû�и�ֵ
									assignedVariable.pop();
								}

								ClauseNode* tmp = header->nextClause;
								header->nextClause = tmp->nextClause;
								free(tmp->data->nextLiteral);
								free(tmp->data);
								free(tmp);

								while ((!recursionStack.empty())&&recursionStack.top() < 0) { //ɾ��ջ�����еĸ�
									//cout << "Jumping out of " << recursionStack.top() << endl;
									recursionStack.pop();
									existing = existingStack.top() - 1;  //��Ҫ��
									existingStack.pop();
									unitClauseStackStack.top().pop();  //��Ҫ��
									unitClauseStack = stack<ClauseNode*>{ unitClauseStackStack.top() };  //ע������Ӧ�������
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
										variableList[assignedVariable.top()].flag = 0; //��ʾû�и�ֵ
										assignedVariable.pop();
									}
									assignedVariableStack.pop();

									ClauseNode* tmp = header->nextClause;
									header->nextClause = tmp->nextClause;
									free(tmp->data->nextLiteral);
									free(tmp->data);
									free(tmp);
								}

								if (recursionStack.empty()) return 0; //˵������������
								//��������Ǹ����ģ�Ȼ��������������һ��
								variableValue = recursionStack.top();
								//cout << "Jumping out of " << variableValue << endl;
								recursionStack.pop();
								existing = existingStack.top();
								// existingStack.pop();  ��������Ӧ�õ����ģ��������ں��渺����ջ��Ҫ�룬����û�䣬���ԾͲ�����
								unitClauseStack = stack<ClauseNode*>{ unitClauseStackStack.top() };  //ע������Ӧ�������
								// unitClauseStackStack.pop(); ͬ��
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
									variableList[assignedVariable.top()].flag = 0; //��ʾû�и�ֵ
									assignedVariable.pop();
								}
								assignedVariableStack.pop();
								//������ջ���ڵ�Ͳ��ø�����
								//cout << "Getting into " << -variableValue << endl;
								recursionStack.push(-variableValue);
								header->nextClause->data->nextLiteral->data = -variableValue;
								unitClauseStack.push(header->nextClause);
							}
							goto back;
						}
						else if (num == 1) { //��Ҫ����µĵ��Ӿ��ȥ��
							unitClauseStack.push(literalPointer->clause);
						}
					}
				}
				literalPointer = literalPointer->nextCounterpart;
			}
		}
		//Ȼ��Ҫ������ĵĶ���
		deleteClauseStack.push(stack<ClauseNode*>{deleteClause});
		deleteLiteralStack.push(stack<LiteralNode*>{deleteLiteral});
		assignedVariableStack.push(stack<int>{assignedVariable});

		//���Ϊ���ˣ���ΪSAT��ֱ�ӷŻ�
		if (existing == 0) return 1;

		//˵�������У�Ȼ�����ѡ��һ����Ԫ�����ȥ��
		int chosenIndex = 0, chosenPos, chosenNeg;
		while (variableList[chosenIndex].flag) chosenIndex++;
		chosenPos = chosenIndex + 1;
		ClauseNode* newNode = (ClauseNode*)malloc(sizeof(ClauseNode));
		LiteralNode* literalHeader = (LiteralNode*)malloc(sizeof(LiteralNode));
		LiteralNode* newLiteral = (LiteralNode*)malloc(sizeof(LiteralNode));
		newNode->data = literalHeader;
		newNode->nextClause = header->nextClause;
		newNode->flag = 1;
		unitClauseStack.push(newNode);//�𼱣�����ɾ��
		literalHeader->nextLiteral = newLiteral;
		newLiteral->data = chosenPos;
		header->nextClause = newNode;
		recursionStack.push(chosenPos);
		existing++;
		//cout << "Getting into " << chosenPos << endl;
		unitClauseStackStack.push(stack<ClauseNode*>{unitClauseStack}); //�������޸ĺ���Ҫ�Ȱ�״̬����
		existingStack.push(existing);
	}
};