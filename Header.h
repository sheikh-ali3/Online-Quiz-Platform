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
	void leaderboard_update(string user);
	void leaderboard_display(string user);
	void game_menu();
	void math();
	void DSA();
	void OOP();
	void PF();

public:
	quiz();
	void main_menu();
};

class node
{
	string name;
	int score;
	node* next;

public:
	node(string n = " ", int s = 0, node* nx = NULL)
	{
		name = n;
		score = s;
		next = nx;
	}

	void set_name(string n)
	{
		name = n;
	}

	string get_name()
	{
		return name;
	}

	void set_score(int s)
	{
		score = s;
	}

	int get_score()
	{
		return score;
	}

	void set_next(node* n)
	{
		next = n;
	}

	node* get_next()
	{
		return next;
	}
};

class leaderboard
{
	node* head;
	
public:
	leaderboard();
	void sort();
	bool isEmpty();
	void add(string n, int s);
};