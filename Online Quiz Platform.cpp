// Online Quiz Platform.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <fstream>
#include <string>
// #include <cstring>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace chrono;
using namespace this_thread;

class quiz
{
	int score;
public:
	quiz()
	{
		score = 0;
		cout << "score = " << score;
	}

	bool check(string u)
	{
		int counter = 0;

		ifstream file(u+".txt");
		
		if (file.is_open())
			return true;
		else
			return false;

		file.close();
	}

	void signup()
	{
		string fname, lname, user, pass, pass2;

		cout << "\t\t first name : ";
		cin >> fname;
		cout << "\t\t  last name : ";
		cin >> lname;
		cout << "\t\t   username : ";
		cin >> user;

		if (check(user))
		{
			cout << "\t\t user already exits\n";
		}
		else
		{
			ofstream file;
			file.open(user + ".txt");

			if (file.is_open())
			{
				cout << "\t\t   password : ";
				cin >> pass;
			here:
				cout << "\t\tconfirm password : ";
				cin >> pass2;

				if (pass == pass2)
				{
					file << user << endl;
					file << pass << endl;
					file << fname << endl;
					file << lname << endl;

					cout << "\n\t\taccount added successfully\n";
					cout << "\n\t\tlogin to continue to game\n";
					sleep_for(seconds(1));
					system("cls");

					main_menu();
				}
				else
				{
					cout << "\tpasswords doesn't match\n";
					goto here;
				}
			}
		}
	}

	void login()
	{
		char c, s;
		string user, pass, line;
		vector<string> st;

	there:
		cout << "\t\tusername : ";
		cin >> user;

		ifstream file;
		file.open(user+".txt");
		if (file.is_open())
		{
			here:
			cout << "\t\tpassword : ";
			cin >> pass;

			int i = 0;
			while (!file.eof())
			{
				getline(file, line);
				st.push_back(line);
			}

			if (pass == st[1])
			{
				cout << "\n\tWelcome " << st[2] << " " << st[3] << endl << endl;
			hr:

				cout << "\n|\t\tenter G to continue to game\t\t|\n";
				cout << "|\t     enter L to check the leaderboard\t\t|\n";
				cout << "|\t      enter B to return to main menu \t\t|\n";
				c = _getch();
			again:

				if (c == 'G' or c == 'g')
				{
					sleep_for(seconds(1));
					system("cls");
					game();
					leaderboard(user);
				h:
					for (int i = 0; i < 57; i++)
					{
						cout << "-";
					}
					cout << endl;

					cout << "|\t\tenter G to play again\t\t|\n";
					cout << "|\t      enter B to return to main menu \t\t|\n";
					c = _getch();
					
					if (c == 'G' or c == 'g' or c == 'B' or c == 'b')
						goto again;
					else
						cout << "try again .... "; goto h;
				}
				else if (c == 'L' or c == 'l')
				{
					sleep_for(seconds(1));
					system("cls");
					leaderboard_display(user);
				h2:
					for (int i = 0; i < 57; i++)
					{
						cout << "-";
					}
					cout << endl;

					cout << "|\t\tenter G to play again\t\t|\n";
					cout << "|\t      enter B to return to main menu \t\t|\n";
					c = _getch();

					if (c == 'G' or c == 'g' or c == 'B' or c == 'b')
						goto again;
					else
						cout << "try again .... "; goto h2;
				}
				else if (c == 'B' or c == 'b')
				{
					sleep_for(seconds(1)); 
					system("cls"); 
					main_menu();
				}
				else
					cout << "Wrong key .... retry!!"; sleep_for(seconds(1)); goto hr;
			}
			else
			{
				cout << "\twrong password ..... retry!!\n"; 
				goto here;
			}
		}
		else
		{
			cout << "no record found.\n";
			goto there;
		}
	}

	void answer(float n1, float n2, int op)
	{
		double ans, check = 0;
		cin >> ans;

		switch (op)
		{
		case 1:
			check = n1 + n2;
			break;
		case 2:
			check = n1 - n2;
			break;
		case 3:
			check = n1 * n2;
			break;
		case 0:
			check = n1 / n2;
			break;
		default:
			cout << "unable to find answer\n";
		}

		if (ans != check)
			cout << "Wrong answer !!! right answer is " << check << endl;
		else
		{
			cout << "\tCongratulations!! your answer is correct\n";
			score++;

			cout << "test: " << score << endl;
		}
	}

	void game()
	{
		for (int i = 0; i < 10; i++)
		{
			srand(time(0));
			float n1 = rand() % 100;
			float n2 = rand() % 100;
		again:
			int op = rand() % 4;
			cout << "op: " << op << endl;

			switch (op)
			{
			case 1:
				cout << "\t" << n1 << endl << "  +\t" << n2 << endl << "\t-------------\n";
				answer(n1, n2, op);
				break;
			case 2:
				cout << "\t" << n1 << endl << "  -\t" << n2 << endl << "  -------------\n";
				answer(n1, n2, op);
				break;
			case 3:
				cout << "\t" << n1 << endl << "  x\t" << n2 << endl << "  -------------\n";
				answer(n1, n2, op);
				break;
			case 0:
				cout << "\t" << n1 << endl << "  /\t" << n2 << endl << "  -------------\n";
				answer(n1, n2, op);
				break;

			default:
				goto again;
			}
		}	

		cout << "\tyou scored " << score << "out of 10.\n";
		sleep_for(seconds(2));
	}

	void user_menu()
	{
		char ch;

		cout << "|\t\t    enter S to signup \t\t\t|\n";
		cout << "|\t\tenter G to contine as guest \t\t|\n";
		cout << "|\t      enter B to return to main menu \t\t|\n";

		for (int i = 0; i < 57; i++)
		{
			cout << "-";
		}
		cout << endl;

		ch = _getch();

		if (ch == 's' or ch == 'S')
		{
			signup();
		}
		else if (ch == 'g' or ch == 'G')
		{
			game();
		}
		else if (ch == 'b' or ch == 'B')
		{
			system("cls");
			main_menu();
		}
	}

	void main_menu()
	{
		char choice;

	start:
		for (int i = 0; i < 57; i++)
		{
			cout << "-";
		}
		cout << endl;

		cout << "|\t\t  press N for new user  \t\t|\n";
		cout << "|\t\t   press L for login    \t\t|\n";
		cout << "|\t\t    press E to exit \t\t\t|\n";

		for (int i = 0; i < 57; i++)
		{
			cout << "-";
		}
		cout << endl;

		choice = _getch();

		if (choice == 'N' or choice == 'n')
			user_menu();
		else if (choice == 'l' or choice == 'L')
			login();
		else if (choice == 'e' or choice == 'E')
		{
			cout << "thank you for your visit\n";
			exit(1);
		}
		else
			cout << "Wrong choice retry!! "; sleep_for(seconds(1)); system("cls"); goto start;

	}


	void leaderboard(string user)
	{
		string line;
		vector<pair<string, int>> leaderboard;

		ifstream file;
		file.open("leaderboard.txt");

		if (file.is_open())
		{
			while (!file.eof())
			{
				getline(file, line);
				size_t index = line.find(':');
				if (index != string::npos)
				{
					string name = line.substr(0, index);
					int scr = stoi(line.substr(index + 1));

					leaderboard.push_back({ name,scr });
				}
			}

			file.close();
		}

		leaderboard.push_back({ user,score });

		sort(leaderboard.begin(), leaderboard.end(),
			[](const pair<string, int>& a, const pair<string, int>& b) {
				return a.second > b.second;
			});

		ofstream outFile("leaderboard.txt");
		for (const auto& entry : leaderboard)
		{
			outFile << entry.first << ':' << entry.second << endl;
		}

	}

	void leaderboard_display(string user)
	{
		string line;
		vector<pair<string, int>> leaderboard;
		int i = 1;

		ifstream file;
		file.open("leaderboard.txt");

		if (file.is_open())
		{
			cout << "Leaderboard:\n";
			while (!file.eof())
			{
				getline(file, line);
				size_t index = line.find(':');
				if (index != string::npos)
				{
					string name = line.substr(0, index);
					int scr = stoi(line.substr(index + 1));

					cout << i << ".\t";
					cout << name << " : " << scr << endl;
				}
			}

			file.close();
		}
	}
};

void drawHorizontal()
{
	for (int i = 0; i < 57; i++)
	{
		cout << "-";
	}
	cout << endl;
}

int main()
{
	quiz q;

	drawHorizontal();

	cout << "|\tWelcome to Universal Truth Quiz Platform.\t|\n";
	
	q.main_menu();

	drawHorizontal();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
