#pragma once
#include"solitaire.h"
#include<map>
#include<string>
#include<queue>
static const int numarray[7][7] = {
		0, 0, 1, 2, 3, 0, 0,
		0, 0, 4, 5, 6, 0, 0,
		7, 8, 9, 10,11,12,13,
		14,15,16,17,18,19,20,
		21,22,23,24,25,26,27,
		0, 0, 28,29,30,0, 0,
		0, 0, 31,32,33,0, 0
};
static const int renumarray_x[34] = {
	-1,
	0,0,0,
	1,1,1,
	2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,
	5,5,5,
	6,6,6
};
static const int renumarray_y[34] = {
	-1,2,3,4,
	2,3,4,
	0,1,2,3,4,5,6,
	0,1,2,3,4,5,6,
	0,1,2,3,4,5,6,
	2,3,4,
	2,3,4
};
struct Bidirectional_BFS{
	long long origin_state;
	long long destin_state;
	static const int dividing = 13;//С�ڸ���ʱ�������ӣ���������ո�
	static constexpr int dy[4] = { 0,0,-1,1 };//��������
	static constexpr int dx[4] = { 1,-1,0,0 };//��������
	static constexpr char direction[4] = { 'd','u','l','r'};
	
	map<long long, string>state_map;//01~33,string��ʽΪ01u02d21l22r�Դ˱�ʾ·��
	map<long long, string>backmap;
	//һ�β�������һ��ԭλ�ú�һ�������ʾ
	//������ĳ��״̬�Ĳ����ַ���һ����ͬ,������Ϊһ����map�в����ٵĽ����ǲ������

	//�ɽ�һ��map<long long,long long>���ɼ�¼����ĳ״̬�ķ�����
	Bidirectional_BFS(long long origin, long long destin):origin_state(origin),destin_state(destin)
	{
		state_map[origin] = "";
		backmap[destin] = "";
	}
	bool solve();//˫������
	string two_string(int num) {
		string s = "";
		int temp = num % 10;
		num /= 10;
		s += num % 10+'0';
		s += temp + '0';
		return s;
	}
	void route_print();
};