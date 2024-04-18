#include"solitaire.h"
State::State(char s[7][7]) {
	//����ά����ѹ��Ϊ���״̬����ά����Ҫ���Ľ�Ϊ-1��
	long long temp = 0;
	for (int i = 6; i >= 0; i--)
		for (int j = 6; j >= 0; j--)
		{
			if (s[i][j] == -1)
				continue;
			temp *= 2;
			temp += s[i][j];
		}
	this->state = temp;
}
void State::transfer_to_array(char s[7][7]) {
	//�����״̬��ѹΪ��ά����
	State::array_init(s);
	long long temp = this->state;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (s[i][j] == -1)
				continue;
			s[i][j] = temp % 2;
			temp /= 2;
		}
	}
}
void State::array_init(char s[7][7]) {
	//�ྲ̬�������������ĽǵķǷ�������-1���
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			s[i][j] = -1;
			s[i + 5][j] = -1;
			s[i][j + 5] = -1;
			s[i + 5][j + 5] = -1;
		}
}
long long State::string_to_state(string s)
{
	if (s.size() != 33)
		return State::state_final;
	long long ans = 0;
	for (int i = 32; i >=0 ; i--)
	{
		ans *= 2;
		ans += s[i] - '0';
	}
	return ans;
}
void State::print() {
	char s[7][7];
	this->transfer_to_array(s);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (s[i][j] == -1)
				cout << "2 ";
			else if (s[i][j] == 0)
				cout << "0 ";
			else if (s[i][j] == 1)
				cout << "1 ";
		}
		cout << endl;
	}
}
void State::array_print(char s[7][7])
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (s[i][j] == -1)
				cout << "2 ";
			else if (s[i][j] == 0)
				cout << "0 ";
			else if (s[i][j] == 1)
				cout << "1 ";
		}
		cout << endl;
	}
}