// Online Quiz Platform.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
	int score;
public:
	quiz()
	{
		score = 0;
		cout << "score = " << score;
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
			cout << "thank you for your visit\n";
		else
			cout << "Wrong choice retry!! "; sleep_for(seconds(1)); system("cls"); goto start;

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

	bool check(string u)
	{
		int counter = 0;

		ifstream file(u+"txt");
		
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
			h:

				cout << "|\t\tenter G to continue to game\t\t|\n";
				cout << "|\t      enter B to return to main menu \t\t|\n";
				c = _getch();
			again:

				if (c == 'G' or c == 'g')
				{
					sleep_for(seconds(1));
					system("cls");
					game();
				h:

					cout << "|\t\tenter G to play again\t\t|\n";
					cout << "|\t      enter B to return to main menu \t\t|\n";
					c = _getch();
					
					if (c == 'G' or c == 'g' or c == 'B' or c == 'b')
						goto again;
					else
						cout << "try again .... "; goto h;
				}
				else if (c == 'B' or c == 'b')
				{
					sleep_for(seconds(1)); 
					system("cls"); 
					main_menu();
				}
				else
					cout << "Wrong key .... retry!!"; sleep_for(seconds(1)); goto h;
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

	void game()
	{
		for (int i = 0; i < 10; i++)
		{
			srand(time(0));
			float n1 = rand() % 100;
			float n2 = rand() % 100;
		again:
			int op = rand() % 10;


			switch (op)
			{
			case 1:
				cout << "\t" << n1 << endl << "  +\t" << n2 << endl << "\t-------------\n";
				answer(n1, n2, op);
				break;
			case 2:
				cout << "\t" << n1 << endl << "  -\t" << n2 << endl << "  -------------\n";			answer(n1, n2, op);
				answer(n1, n2, op);
				break;
			case 3:
				cout << "\t" << n1 << endl << "  x\t" << n2 << endl << "  -------------\n";
				answer(n1, n2, op);
				break;
			case 4:
				cout << "\t" << n1 << endl << "  /\t" << n2 << endl << "  -------------\n";
				answer(n1, n2, op);
				break;
			default:
				goto again;
			}
		}	

		cout << "\tyou scored " << score << "out of 10.\n";
	}

	void answer(float n1, float n2, int op)
	{
		double ans, check;
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
		case 4:
			check = n1 / n2;
			break;
		default:
			cout << "unable to find answer\n";
		}

		if (ans != check)
			cout << "Wrong answer !!! right answer is " << check << endl;
		else
			cout << "\tCongratulations!! your answer is correct\n"; score++;
	}
};

int main()
{
	quiz q;

	for (int i = 0; i < 57; i++)
	{
		cout << "-";
	}
	cout << endl;

	cout << "|\tWelcome to Universal Truth Quiz Platform.\t|\n";
	
	for (int i = 0; i < 57; i++)
	{
		cout << "-";
	}
	cout << endl;

	q.main_menu();

	for (int i = 0; i < 57; i++)
	{
		cout << "-";
	}
	cout << endl;

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
