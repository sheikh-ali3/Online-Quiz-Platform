// Online Quiz Platform.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <fstream>
#include <string>
using namespace std;

class quiz
{
public:
	bool check(string u)
	{
		int counter = 0;

		ifstream file(filename.c_str());
		
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
				cout << "\t\tconfirm password : ";
				cin >> pass2;

				if (pass == pass2)
				{
					file << user << endl;
					file << pass << endl;
					file << fname << endl;
					file << lname << endl;
				}
			}
		}
	}

	void login()
	{
		string user, pass;
		cout << "  username : ";
		cin >> user;

		ifstream file;
		file.open(user+".txt");
		if (file.is_open())
		{
			cout << "  password : ";
			cin >> pass;
		}
		else
		{
			cout << "no record found.\n";
		}
	}
};

int main()
{
	char choice,ch;

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

	here:
	cout << "|\t\t  press N for new user  \t\t|\n";
	cout << "|\t\t   press L for login    \t\t|\n";
	cout << "|\t\t    press E to exit \t\t\t|\n"; 

	for (int i = 0; i < 57; i++)
	{
		cout << "-";
	}
	cout << endl;

	choice = _getch();
	
	quiz q;

	if (choice == 'n' or choice == 'N')
	{
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
			q.signup();
		}
		else if (ch == 'g' or ch == 'G')
		{

		}
		else if (ch == 'b' or ch == 'B')
		{
			system("cls");
			goto here;
		}
	}
	else if (choice == 'l' or choice == 'L')
	{
		string user, pass;

		cout << "|\t\t username : ";
		getline(cin, user);

		ifstream f;
		f.open(user + ".txt");

		if (f.is_open())
		{
			cout << "|\t\t password : ";
			getline(cin, pass);
		}
	}
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
