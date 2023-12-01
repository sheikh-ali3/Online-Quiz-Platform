#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace chrono;
using namespace this_thread;

class quiz
{
	int score, count;
	void questions(float n1, float n2, int o);
	bool check(string u);
	void signup();
	void login();
	void answer(float n1, float n2, int op);
	void user_menu();
	void leaderboard(string user);
	void leaderboard_display(string user);

public:
	quiz();
	void game();
	void main_menu();
	
};