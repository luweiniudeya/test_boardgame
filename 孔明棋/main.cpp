#include"solitaire.h"
#include"Boardgame_simple.h"
void test()
{
	Boardgame_central centralcase(Boardgame_simple::read_string());
	
	centralcase.print_chessboard();
	char array[10][10];
	memcpy(array, centralcase.chessboard, sizeof(centralcase.chessboard));
	centralcase.state_to_array_unsecure(array, centralcase.origin_state);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (array[i][j] == -1)
				cout << ". ";
			else if (array[i][j] == 0)
				cout << "o ";
			else cout <<"* ";
		}
		cout << endl;
	}
	cout << "��ʼ" <<  endl;
	centralcase.print_chessboard(array);
	centralcase.turn_unsecure(array);
	centralcase.print_chessboard(array);
	centralcase.turn_unsecure(array);
	centralcase.print_chessboard(array);
	centralcase.turn_unsecure(array);
	centralcase.print_chessboard(array);
	centralcase.turn_unsecure(array);
	centralcase.print_chessboard(array);

	centralcase.mirror_level(array);
	centralcase.print_chessboard(array);

	centralcase.turn_unsecure(array);
	centralcase.print_chessboard(array);
	centralcase.turn_unsecure(array);
	centralcase.print_chessboard(array);
	centralcase.turn_unsecure(array);
	centralcase.print_chessboard(array);
	
}
int main()
{
	/*string s=Boardgame_simple::read_string();
	cout << s;*/

	//string s = "..***...0..***...0*******.0***o***.0*******.0..***...0..***...0........";
	//Boardgame_simple case2(s);
	//case2.print_simplecase();




	/*char array[10][10];
	
	centralcase2.print_centralcase();
	centralcase2.LeastStepsSolve();
	centralcase2.print_LeastStepsSolve();
	memcpy(array, centralcase2.chessboard, sizeof(centralcase2.chessboard));
	centralcase2.turn_unsecure(array);
	centralcase2.print_chessboard(array);

	centralcase2.turn_unsecure(array);
	centralcase2.print_chessboard(array);

	centralcase2.turn_unsecure(array);
	centralcase2.print_chessboard(array);*/
	
	
	/*
	Boardgame_central centralcase2(Boardgame_simple::read_string());
	centralcase2.print_centralcase();

	cout << "��ת��Ч����" << endl;

	map<long long, bool>testmap;
	State s1(centralcase2.origin_state);
	centralcase2.isrepeated_state(s1, testmap);
	return 0;*/

	int op = 1;
	while (op)
	{
		cout << "1.simple���dfs(���֧��10*10),��������ʣ���һ����" << endl << "2.central���bfs����̲��������н�(���8*8)" << endl << "3.central less memory��2���ڴ��Ż����" << endl;
		cout << "4.central more less memory,3�����Ż����" << endl;
		cout << "5.central_BFS����������ʣ���һ����" << endl;
		cout << "6.central_BycicleBFS,˫��bfs������һ����Ž⣨���ģ���8*8�������ĶԳ���־���)" << endl;
		cout << "7.central_dfs ��ȥ�ص�dfs����һ����" << endl;
		cout << "8.central_BiBfsAll �Ż���Ч״̬��˫��bfs��ⲽ�����ٵ����н�" << endl;
		cout << "9.Astar" << endl;
		cout << "-1.BFSͳ���ɴ���ֻ��������״̬���������ٸ�״̬" << endl;
		cout << "-2.test()" << endl;
		scanf("%d", &op);
		switch (op) {

		case 0:
			break;
		case 1: {
			Boardgame_simple simplecase1(Boardgame_simple::read_string());
			simplecase1.print_simplecase();
			simplecase1.OnlyOneLeft();
			simplecase1.print_OnlyOneLeft();
			break;
		}
		case 2: {
			Boardgame_central centralcase2(Boardgame_simple::read_string());
			centralcase2.print_centralcase();
			centralcase2.LeastStepsSolve();
			centralcase2.print_LeastStepsSolve();
			break;
		}
		case 3: {
			Boardgame_central centralcase3(Boardgame_simple::read_string());
			centralcase3.print_centralcase();
			centralcase3.LeastStepsSolve_less_memory();
			centralcase3.print_LeastStepsSolve();
			break;
		}
		case 4: {
			Boardgame_central centralcase4(Boardgame_simple::read_string());
			centralcase4.print_centralcase();
			centralcase4.LeastStepsSolve_more_less_memory();
			centralcase4.print_LeastStepsSolve();
			break;
		}
		case 5: {
			Boardgame_central centralcase5(Boardgame_simple::read_string());
			centralcase5.print_simplecase();
			centralcase5.OnlyOneLeft();
			centralcase5.print_OnlyOneLeft();
			break;
		}
		case 6: {
			Boardgame_central centralcase6(Boardgame_simple::read_string());
			centralcase6.print_simplecase();
			centralcase6.OnlyOneLeft_BycicleBFS();
			centralcase6.print_OnlyOneLeft();
			break;
		}
		case 7: {
			Boardgame_central centralcase7(Boardgame_simple::read_string());
			//cout << sizeof(centralcase7.chessboard) << endl;
			centralcase7.print_simplecase();
			centralcase7.OnlyOneLeft_deequal();
			centralcase7.print_OnlyOneLeft();
			break;
		}
		case 8: {
			Boardgame_central centralcase8(Boardgame_simple::read_string());
			
			/*for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
					cout << int(centralcase8.chessboard[i][j]) << " ";
				cout << endl;
			}*/
			centralcase8.print_centralcase();
			centralcase8.LeastStepsSlove_BiBfsAll();
			centralcase8.print_LeastStepsSolve();
			break;
		}
		case 9: {
			Boardgame_central centralcase4(Boardgame_simple::read_string());
			centralcase4.print_centralcase();
			centralcase4.LeastStepsSolve_Astar();
			centralcase4.print_LeastStepsSolve();
			break;
		}
		case -1: {
			Boardgame_central centralcase8(Boardgame_simple::read_string());
			//cout << sizeof(centralcase7.chessboard) << endl;
			centralcase8.print_simplecase();
			centralcase8.print_statenum();
			break;
		}
		case -2: {
			test();
			break;
		}
		}//switch
		system("pause");
		system("cls");
	}//while
	return 0;
}