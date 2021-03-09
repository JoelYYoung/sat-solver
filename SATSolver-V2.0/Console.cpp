#include "Global.h"

void screen_0();
void screen_1_1();
void screen_1_2();
void screen_1_3();
void screen_1_4();
void screen_1_5(int result, float time, int verify);
void verify(ClauseNode* header, int clausenum);

//Console交互函数，负责程序于客户的交互
void startProgram() {
	int varnum = 0, clausenum = 0;
	stack<ClauseNode*> unitClause;
	Variable* variableList = nullptr;
	ClauseNode* header;

	int choice1;
	do {
		system("cls");
		screen_0();
		cin >> choice1;
		switch (choice1) {
		case 1: { //SAT solver
			int choice2;
			system("cls");
			screen_1_1();
			cin >> choice2;
			switch (choice2) {
			case 1: { //load file
				string filename;
				screen_1_2();
				cin >> filename;
				header = readCNFFile(varnum, clausenum, filename, variableList, unitClause); //读取文件
				int choice3;
				do {
					system("cls");
					screen_1_3();
					cin >> choice3;
					switch (choice3) {
					case 1: { //reload file
						screen_1_2();
						cin >> filename;
						header = readCNFFile(varnum, clausenum, filename, variableList, unitClause);
						break;
					}
					case 2: { //verify
						verify(header, clausenum);
						break;
					}
					case 3: { //solve cnf

						break;
					}
					default: //back
						break;
					}
				} while (choice3);
				break;
			}
			default: //default
				break;
			}
		case 2: { //soduku

			break;
		}
		default:
			break;
		}
		}
	} while (choice1);
}

void screen_0() {  //欢迎界面
	cout << "*********************************************" << endl;
	cout << "                   Welcome" << endl;
	cout << "          Please choose SAT or Soduku" << endl;
	cout << "                 1.SAT Problem" << endl;
	cout << "                 2.Soduku Game" << endl;
	cout << "                 0.Exit Program" << endl;
	cout << "*********************************************" << endl;
	cout << "Your choice: ";
}

void screen_1_1() {  //加载文件或者返回 
	cout << "*********************************************" << endl;
	cout << "                  1.Load file" << endl;
	cout << "                  2.Back" << endl;
	cout << "*********************************************" << endl;
	cout << "Your choice: ";
}

void screen_1_2() {  //输入文件名
	cout << "Please input file name:";
}

void screen_1_3() {  //选择对已加载的CNF文件的操作
	cout << "*********************************************" << endl;
	cout << "                 1.Reload file" << endl;
	cout << "                 2.Verify" << endl;
	cout << "                 3.Solve SAT" << endl;
	cout << "                 0.Back" << endl;
	cout << "*********************************************" << endl;
	cout << "Your choice: ";
}

void screen_1_4() {
	cout << "*********************************************" << endl;
	cout << "              Choose an algorithm:" << endl;
	cout << "                1.SATSolver-V1.0" << endl;
	cout << "                2.SATSolver-V2.0" << endl;
	cout << "                3.SATSolver-Iterate" << endl;
	cout << "*********************************************" << endl;
	cout << "Your choice: ";
}

void screen_1_5(int result, float time, int verify){
	cout << "Result: " << result << endl;
	cout << "Time consumption: " << time << endl;
	cout << "Verify: " << verify << endl;
}

void verify(ClauseNode* header, int clausenum) {
	if (header == nullptr) {
		cout << "Haven't read file." << endl;
		getchar();
		getchar();
		return;
	}
	int verifynum;
	cout << "Please input number of lines to show: ";
	cin >> verifynum;
	verifyFormula(header, clausenum, verifynum);
	getchar();
	getchar();
}