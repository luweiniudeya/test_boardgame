#pragma once
#include"solitaire.h"
struct Boardgame_simple {

	//����������ֵ�dfs��

	/*ʵ�����ݳ�Ա*/
	long long origin_state;//��ʼ���
	char chessboard[State::board_maxlength][State::board_maxlength];

	int up;//�߽�
	int down;
	int left;
	int right;
	int method_dividing;//�����ո���������Ӳ���ѡ��ķֽ��ߣ�Ĭ��ֵȡ�����һ��
	string anwser_simple;//һ����
	int chessnum_min;//�����������ʣ�¼���
	int squarenum;//��������

	/*��̬���ݳ�Ա*/
	static constexpr int dy[4] = { 0,0,-1,1 };
	static constexpr int dx[4] = { 1,-1,0,0 };//�������� k����0,1,2,3 ȡ������Ϊk^1
	static constexpr char direction[4] = { 'd','u','l','r' };




	/*ʵ��������Ա*/
	Boardgame_simple(string s);//��������ε�* o .��, ��0��Ϊ���б��
	long long array_to_state(char array[State::board_maxlength][State::board_maxlength]);//simple���ṩ�ĸ���Ч��ת������
	void print_chessboard(char[State::board_maxlength][State::board_maxlength]);
	void print_chessboard();
	void print_simplecase();
	void OnlyOneLeft();//dfs�������ӽ�ʣһ���Ľ�
	void print_OnlyOneLeft();
	void print_route() { print_route(this->anwser_simple); }
	void print_route(string);
	void print_route_continuous(string);
	bool dfs(char[State::board_maxlength][State::board_maxlength],int,string);
	int get_chessnum(char s[State::board_maxlength][State::board_maxlength]);
	string route_transfer_string() { return route_transfer_string(this->anwser_simple); }
	string route_transfer_string(string ans) {
		for (int i = 0; i <= ans.size() - 3; i += 3)
			ans[i + 2] = direction[ans[i + 2] - '0'];
		return ans;
	}
	void state_to_array_unsecure(char[State::board_maxlength][State::board_maxlength],long long state);//�ڳ�ʼ��ֵĻ����Ͻ�ѹ�����ѹ
	long long construct_final_state()//��֤�����ĶԳƸ��������������ѹ���룬����ͨ�������һ���Ϸ���������
	{
		long long ans = 1;
		//long long ans = 1 << (this->squarenum / 2);//Ӧ�ò��ᳬ32
		for (int i = 0; i < this->squarenum / 2; i++)
			ans *= 2;
		return ans;
	}
	long long mirror_level(char array[State::board_maxlength][State::board_maxlength]);//��������������������¾��� �����ؾ�����״̬��
	long long mirror_vertical(char s[State::board_maxlength][State::board_maxlength]);//Ҫע�⣬�������ֻ����Ч����
	
	static string read_string();
	
	static string num_to_string(int i, int j)
	{
		//�������� �������� 00~99
		int num = i * 10 + j;
		string ans = "";
		int temp = num % 10;
		num /= 10;
		ans += num % 10 + '0';
		ans += temp + '0';
		return ans;
	}
};

struct Boardgame_central :public Boardgame_simple {
	
	//����������ٲ��������н�(������ʼ����ֹ״̬)
	//Ҫ���������ĶԳƣ�Ŀ��������ĶԳƣ���Ҫ��������Ч������һ�������Σ���Ҫ���������ʮ�˲��Ľ�
	/*ʵ�����ݳ�Ա*/
	long long destin_state;
	int step_min;
	vector<string> anwser_central;
	

	/*ʵ��������Ա*/
	Boardgame_central(string s) :Boardgame_simple(s) {
		step_min = this->chessnum_min;
		destin_state = this->construct_final_state();//�վ����������ĺ������ɽ�ʣ���ĵ�ѹ����
	}
	Boardgame_central(string s,int step) :Boardgame_simple(s) {
		step_min = step;
		destin_state = this->construct_final_state();
	}
	Boardgame_central(string s,long long final_state) :Boardgame_simple(s),destin_state(final_state) {
		step_min = this->chessnum_min;
	}
	void print_centralcase();
	void LeastStepsSolve();
	void LeastStepsSolve_less_memory();
	void LeastStepsSolve_more_less_memory();
	void OnlyOneLeft();//ʹ��˫��bfs���������ĶԳ���֣����͸���OnlyOneLeftһ��������

	void LSS_less_memory_bfs(queue<ConState>& before, queue<ConState>& after, map<long long, int>& visited);
	void print_LeastStepsSolve();
	long long turn_unsecure(char array[State::board_maxlength][State::board_maxlength]);//�������������left~right up~down�е���Ч����������ת��������ѹ����
	bool isrepeated_state(ConState& state, map<long long, int>&);
	bool isrepeated_state(OriginState& st, map<long long, string>& visited);
};
