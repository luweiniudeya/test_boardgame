#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
struct OriginState {

	/*���״̬ing ����Stateû�����壬ֻ��֪�����̲��ܽ�ѹ*/
	/*******  	ʵ�����ݳ�Ա	*******/
	long long state;											//������01ѹ����ֻѹ������ڵĸ��ӣ�������33����state�Ķ�����λ��ΧΪ0~32����33��


	/*******  	��̬���ݳ�Ա	*******/
	static const int board_maxlength = 10;						//10*10���������


	/*******  	ʵ��������Ա	*******/
	OriginState():state(0) {}
	OriginState(long long state):state(state){}
	OriginState(char array[10][10]){ this->state = OriginState::array_to_state_unsecure(array); }
	OriginState(char array[10][10],int up,int down,int left,int right){}
	int get_chessnum() const;//��ñ�״̬��������


	/*******  	��̬������Ա�����ߺ�����	*******/

	static void array_print(char array[board_maxlength][board_maxlength]);
	static long long string_to_state(string);
	static string array_to_string(char[board_maxlength][board_maxlength]);
	static long long array_to_state_unsecure(char[board_maxlength][board_maxlength]);
	static long long array_to_state_efficient(char array[10][10], int up, int down, int left, int right);
};
struct State :public OriginState{

	/*���״̬ing ����Stateû�����壬ֻ��֪�����̲��ܽ�ѹ*/
	/*******  	ʵ�����ݳ�Ա	*******/
	string route;

	/*******  	ʵ��������Ա	*******/
	State() :OriginState(), route("") {}
	State(long long state) :OriginState(state), route("") {}
	State(long long state, string s) :OriginState(state), route(s) {}
	State(char array[10][10]) :OriginState(array),route("") {}
	State(char array[10][10], string s) :OriginState(array),route(s) {}

};
struct ConState :public State {
	int step;//���ﵱǰ״̬�Ĳ���(������Ϊһ��)
	ConState() :State(),step(0) {}
	ConState(long long state):State(state),step(0){}
	ConState(char array[State::board_maxlength][State::board_maxlength], int step) :State(array), step(step) {}
	ConState(char array[State::board_maxlength][State::board_maxlength]) :State(array), step(0) {}
	ConState(char array[State::board_maxlength][State::board_maxlength],string s,int step):State(array,s),step(step){}
};