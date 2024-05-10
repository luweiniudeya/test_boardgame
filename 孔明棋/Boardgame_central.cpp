#include"Boardgame_simple.h"
#include<queue>
bool Boardgame_central::isrepeated_state(OriginState& st, map<long long, bool>& visited)
{
	//��Ӧ�İ���״̬��δ�ڱ��г���
	long long tempstate;
	char array[10][10];
	memcpy(array, this->chessboard, sizeof(chessboard));
	this->state_to_array_unsecure(array, st.state);
	/*cout << "��ʼ" << endl;
	this->print_chessboard(array);*/

	//cout << "new" << endl;
	if (visited.count(st.state))
		return 1;
	for (int i = 0; i < 3; i++)
	{
		tempstate = this->turn_unsecure(array);
		/*cout << "��ת" << endl;
		this->print_chessboard(tempstate);*/
		if (visited.count(tempstate))
			return 1;
	}

	//��ת������ת
	tempstate = this->mirror_level(array);
	//cout << "��ת" << endl;
	//this->print_chessboard(tempstate);
	if (visited.count(tempstate))
		return 1;

	for (int i = 0; i < 3; i++)
	{
		tempstate = this->turn_unsecure(array);
		//cout << "��ת" << endl;
		//this->print_chessboard(tempstate);
		if (visited.count(tempstate))
			return 1;
	}

	return 0;
}
bool Boardgame_central::isrepeated_state(ConState& st,map<long long,int>&visited)
{
	//��Ӧ�İ���״̬��δ�ڱ��г��֣���st�Ĳ��������г��ֹ���״̬�Ĳ�����С����ڣ��򷵻�0
	int equalmin = 0x3f3f3f3f;
	long long tempstate;
	char array[10][10];
	memcpy(array, this->chessboard, sizeof(chessboard));
	this->state_to_array_unsecure(array,st.state);

	if (visited.count(st.state))
		equalmin = visited[st.state];
	for (int i = 0; i < 3; i++)
	{
		tempstate = this->turn_unsecure(array);
		if (visited.count(tempstate))
			equalmin = min(equalmin, visited[tempstate]);
	}

	//��ת������ת
	tempstate = this->mirror_level(array);
	if (visited.count(tempstate))
		equalmin = min(equalmin, visited[tempstate]);

	for (int i = 0; i < 3; i++)
	{
		tempstate = this->turn_unsecure(array);
		if (visited.count(tempstate))
			equalmin = min(equalmin, visited[tempstate]);
	}

	return !(equalmin == 0x3f3f3f3f || st.step <= equalmin );//�Ƿ�Ҫ��һ
}
bool Boardgame_central::isrepeated_state(OriginState& st, map<long long, string>& visited)
{
	//��Ӧ�İ���״̬��δ�ڱ��г���
	long long tempstate;
	char array[10][10];
	memcpy(array, this->chessboard, sizeof(chessboard));
	this->state_to_array_unsecure(array, st.state);

	if (visited.count(st.state))
		return 1;
	for (int i = 0; i < 3; i++)
	{
		tempstate = this->turn_unsecure(array);
		if (visited.count(tempstate))
			return 1;
	}

	//��ת������ת
	tempstate = this->mirror_level(array);
	if (visited.count(tempstate))
		return 1;

	for (int i = 0; i < 3; i++)
	{
		tempstate = this->turn_unsecure(array);
		if (visited.count(tempstate))
			return 1;
	}

	return 0;
}
long long Boardgame_central::turn_unsecure(char array[State::board_maxlength][State::board_maxlength])
//�������������left~right up~down�е���Ч����������ת��������ѹ����
//Ӳ��Ҫ����Ч������һ��������(��ż���ɣ�
{
	int originx, originy, newx, newy, temp;
	char originnum;
	int x_boundary, y_boundary;
	int width = this->down - this->up + 1;
	x_boundary = (width / 2) - 1 + up;
	y_boundary = (width / 2) + left;
	if (width % 2 == 0)
		y_boundary--;

	for(int i=up;i<=x_boundary;i++)
		for (int j = left; j <= y_boundary; j++)
		{
			originx = i;
			originy = j;
			newx = originx;
			newy = originy;
			originnum = array[originx][originy];
			for (int k = 0; k < 3; k++)
			{
				temp = newx - up + left;
				newx = width - newy + left + up - 1;
				newy = temp;
				array[originx][originy] = array[newx][newy];
				originx = newx;
				originy = newy;
			}
			array[originx][originy] = originnum;
		}
	return this->array_to_state(array);
}
void Boardgame_central::print_centralcase()
{
	char array[10][10];
	memcpy(array, this->chessboard, sizeof(this->chessboard));
	cout << "��Ѱ������̽�:" << endl;
	cout << "ԭʼ���:" << endl;
	this->print_chessboard();
	this->state_to_array_unsecure(array, this->destin_state);
	cout << "Ŀ�����:" << endl;
	this->print_chessboard(array);
}
void Boardgame_central::print_LeastStepsSolve()
{
	if (this->step_min >= get_chessnum(this->chessboard))
	{
		cout << "�޽�" << endl;
		return;
	}

	cout << "��̲�����" << this->step_min << endl;
	cout << "�������" << anwser_central.size() << endl;
	for (int i = 0; i < this->anwser_central.size(); i++)
		cout << anwser_central[i] << endl;
	for (int i = 0; i < this->anwser_central.size(); i++)
		cout << this->route_transfer_string(anwser_central[i]) << endl;

	system("pause");
	for (int i = 0; i < this->anwser_central.size(); i++)
	{
		cout << "�ⷨ" << i + 1 << endl;
		this->print_route_continuous(anwser_central[i]);
	}
}
