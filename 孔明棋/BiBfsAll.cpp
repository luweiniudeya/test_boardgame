#include"Boardgame_simple.h"

void Boardgame_central::LeastStepsSlove_BiBfsAll()
{
	priority_queue<State,vector<State>,Statecmp>forward;//�ֱ�洢Ŀ���������뷴��ڵ�
	priority_queue<State,vector<State>,Statecmp>backward;//Ŀ�������Ӹ���Ϊ1+n)/2
	BiBfsAll_sub(forward, backward);
	vector<State>tempward;
	//��forward,��backward������ɽ�
	//forward��backward����state��������
	while (!(forward.empty()) && (!backward.empty()))
	{
		if (forward.top().state < backward.top().state)
		{
			//forward����Ҫ����
			long long temp = forward.top().state;
			while (!forward.empty() && forward.top().state == temp)
				forward.pop();
		}
		else if (forward.top().state > backward.top().state)
		{
			//backward����Ҫ����
			long long temp = backward.top().state;
			while (!backward.empty() && backward.top().state == temp)
				backward.pop();
		}
		else {
			//��� ��ϴ�
			//��forwardͷ�������������ȵ�backward��ϴ�
			long long temp = backward.top().state;
			while (!backward.empty() && backward.top().state == temp)
			{
				tempward.push_back(backward.top());
				backward.pop();
			}
			
			temp = forward.top().state;
			while (!forward.empty() && forward.top().state == temp)
			{
				//������ƴ����������
				string s = forward.top().route;
				string temps = s;
				forward.pop();
				for (int i = 0; i < tempward.size(); i++)
				{
					temps = s;
					string tempstring = tempward[i].route;
					for (int i = tempstring.size() - 3; i >= 0; i -= 3)
						temps += tempstring.substr(i, 3);
					//����ϲ���s�Ĳ���
					int steps = Boardgame_simple::get_routesteps(temps);
					if (steps < this->step_min)
					{
						this->anwser_central.clear();
						this->step_min = steps;
						this->anwser_central.push_back(temps);
					}
					else if (steps == this->step_min)
						this->anwser_central.push_back(temps);
				}
				
			}//forward.front
			tempward.clear();
		}//else
	}//while
}
void Boardgame_central::BiBfsAll_sub(priority_queue<State,vector<State>,Statecmp>&forward,priority_queue<State, vector<State>, Statecmp>&backward)
{
	//'d','u','l','r'
	//��չ����
	int polarity_forward_chess[4] = { 0,2,1,3 };//������չ����  ��������
	int polarity_forward_space[4] = { 1,3,0,2 };
	//����bfs�ļ��Խ������ܷ����������ֽ�
	int polarity_backward_chess[4] = { 3,1,2,0 };
	int polarity_backward_space[4] = { 2,0,3,1 };
	//�ó����ۣ�����Ĳ��ܴ����ԣ�������Լ���
	// ���ַ�����1.˫�����򲻴����ԣ��ܱ��������ѵ���Ŀ���վ֣����������Ե���״̬���ǳ���
	//			2.������������ԣ����������������վ֣���������ʣ1���ĺ͸���ʣ���վ֣�
	//�ֵ���
	// A44=24
	//      step  solution
	//0123	 7		6
	//0132	�޽�
	//0213   7		6
	//0231   7      3
	//0312  �޽�
	//0321	�޽�
	//1023	 7		6
	//1032	 10     111
	//1203	 7		6
	//1230	 7		6
	//1302	 10		111
	//1320	 10		111
	//2013   8		11
	//2031	 8		8
	//2103	 6		5
	//2130	 6		5
	//2301	 8		8
	//2310	 6		5
	//3012	 8		74
	//3021	 8		74
	//3102	 �޽�
	//3120	 �޽�
	//3201	 8		74
	//3210  �޽�
	//ȥ�������Խ�Ϊ6 5

	//for (int i = 0; i < 4; i++)
	//{
	//	polarity_forward_chess[i] = i;
	//	polarity_forward_space[i] = i;
	//	polarity_backward_chess[i] = i;
	//	polarity_backward_space[i] = i;
	//}
	queue<State>upward;
	upward.push(State(this->origin_state));
	int destinlayer = (upward.front().get_chessnum() + State(this->destin_state).get_chessnum()) / 2;
	char array[10][10];
	map<long long, bool> equalmap;
	memcpy(array, this->chessboard, sizeof(this->chessboard));
	
	while (!upward.empty())
	{
		State temps = upward.front();
		int chessnum = temps.get_chessnum();//ʹ��State��װ��getchessnumЧ�ʸ���
		if (chessnum <= destinlayer)
			break;
		upward.pop();
		equalmap.clear();//��չ��������
		//��temps������չ��Ҫע����չ�ļ���
		this->state_to_array_unsecure(array, temps.state);
		
		if (chessnum > this->method_dividing)
		{//�����ո�
			for (int k = 0; k < 4; k++)
				for (int i = up; i <= down; i++)
					for (int j = left; j <= right; j++)
						if (array[i][j] == 0)
						{
							int x1 = i + dx[polarity_forward_space[k]], x2 = i + dx[polarity_forward_space[k]] * 2;
							int y1 = j + dy[polarity_forward_space[k]], y2 = j + dy[polarity_forward_space[k]] * 2;
							if (x1 >= up && x1 <= down &&
								x2 >= up && x2 <= down &&
								y1 >= left && y1 <= right &&
								y2 >= left && y2 <= right)
								if (array[x1][y1] == 1 && array[x2][y2] == 1)
								{
									array[i][j] = 1;
									array[x1][y1] = 0;
									array[x2][y2] = 0;

									State nexts(array, temps.route + this->num_to_string(x2, y2) + char((polarity_forward_space[k] ^ 1) + '0'));
									//�˲�if��ÿ����չʱ�ļ��Ա�֤���²Ᵽ֤ÿ����չ�ļ��ԣ����ܱ�֤·�����������ϵļ���
									//������ô���ݲ�������
									if (!this->isrepeated_state(nexts, equalmap))//��equalmap��û��nexts�����е�Ч״̬
									{
										equalmap[nexts.state] = 1;
										upward.push(nexts);
									}

									array[i][j] = 0;
									array[x1][y1] = 1;
									array[x2][y2] = 1;
								}
						}
		}
		else {
			//�������� forward
			for (int k = 0; k < 4; k++)
				for (int i = up; i <= down; i++)
					for (int j = left; j <= right; j++)
						if (array[i][j] == 1)

						{
							int x1 = i + dx[polarity_forward_chess[k]], x2 = i + dx[polarity_forward_chess[k]] * 2;
							int y1 = j + dy[polarity_forward_chess[k]], y2 = j + dy[polarity_forward_chess[k]] * 2;
							if (x1 >= up && x1 <= down &&
								x2 >= up && x2 <= down &&
								y1 >= left && y1 <= right &&
								y2 >= left && y2 <= right)
								if (array[x1][y1] == 1 && array[x2][y2] == 0)
								{
									array[i][j] = 0;
									array[x1][y1] = 0;
									array[x2][y2] = 1;

									State nexts(array, temps.route + this->num_to_string(i, j) + char(polarity_forward_chess[k] + '0'));
									if (!this->isrepeated_state(nexts, equalmap))//��equalmap��û��nexts�����е�Ч״̬
									{
										equalmap[nexts.state] = 1;
										upward.push(nexts);
									}


									array[i][j] = 1;
									array[x1][y1] = 1;
									array[x2][y2] = 0;
								}
						}
		}

	}//������չ��Ŀ���
	while (!upward.empty())
	{
		forward.push(upward.front());
		upward.pop();
	}

	upward.push(State(this->destin_state));
	while (!upward.empty())
	{
		State temps = upward.front();
		int chessnum = temps.get_chessnum();//ʹ��State��װ��getchessnumЧ�ʸ���
		if (chessnum >= destinlayer)
			break;
		upward.pop();
		//equalmap.clear();
		//��temps������չ��Ҫע����չ�ļ���
		this->state_to_array_unsecure(array, temps.state);

		if (chessnum > this->method_dividing)
		{//�����ո�
			for (int k = 0; k < 4; k++)
				for (int i = up; i <= down; i++)
					for (int j = left; j <= right; j++)
						if (array[i][j] == 0)

						{
							int x1 = i + dx[polarity_backward_space[k]], x2 = i + dx[polarity_backward_space[k]] * 2;
							int y1 = j + dy[polarity_backward_space[k]], y2 = j + dy[polarity_backward_space[k]] * 2;
							if (x1 >= up && x1 <= down &&
								x2 >= up && x2 <= down &&
								y1 >= left && y1 <= right &&
								y2 >= left && y2 <= right)
								if (array[x1][y1] == 0 && array[x2][y2] == 1)
								{
									array[i][j] = 1;
									array[x1][y1] = 1;
									array[x2][y2] = 0;

									State nexts(array, temps.route + this->num_to_string(i, j) + char(polarity_backward_space[k] + '0'));
									//if (!this->isrepeated_state(nexts, equalmap))//��equalmap��û��nexts�����е�Ч״̬
									//{
									//	equalmap[nexts.state] = 1;
									//	upward.push(nexts);
									//}
									/*else
										upward.push(nexts);*/

									upward.push(nexts);
									array[i][j] = 0;
									array[x1][y1] = 0;
									array[x2][y2] = 1;
								}
						}
		}
		else {
			//�������� forward
			for (int k = 0; k < 4; k++)
				for (int i = up; i <= down; i++)
					for (int j = left; j <= right; j++)
						if (array[i][j] == 1)

						{
							int x1 = i + dx[polarity_backward_chess[k]], x2 = i + dx[polarity_backward_chess[k]] * 2;
							int y1 = j + dy[polarity_backward_chess[k]], y2 = j + dy[polarity_backward_chess[k]] * 2;
							if (x1 >= up && x1 <= down &&
								x2 >= up && x2 <= down &&
								y1 >= left && y1 <= right &&
								y2 >= left && y2 <= right)
								if (array[x1][y1] == 0 && array[x2][y2] == 0)
								{
									array[i][j] = 0;
									array[x1][y1] = 1;
									array[x2][y2] = 1;

									State nexts(array, temps.route + this->num_to_string(x2, y2) + char(polarity_backward_chess[k] ^ 1 + '0'));
									//if (!this->isrepeated_state(nexts, equalmap))//��equalmap��û��nexts�����е�Ч״̬
									//{
									//	equalmap[nexts.state] = 1;
									//	upward.push(nexts);
									//}
									/*else
										upward.push(nexts);*/
									upward.push(nexts);
									array[i][j] = 1;
									array[x1][y1] = 0;
									array[x2][y2] = 0;
								}
						}
		}
		
	}//����
	while (!upward.empty())
	{
		backward.push(upward.front());
		/*cout << "��������:" << endl;
		cout << upward.front().state << endl;
		this->print_chessboard(upward.front().state);*/
		upward.pop();
	}
}