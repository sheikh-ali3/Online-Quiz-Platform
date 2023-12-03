#include"Header.h"

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


void style()
{
	for (int i = 0; i < 57; i++)
	{
		cout << "-";
	}
	cout << endl;
}

quiz::quiz()
{
	score = 0;
	count = 0;
}

bool quiz::check(string u)
{
	int counter = 0;

	ifstream file(u + ".txt");

	if (file.is_open())
		return true;
	else
		return false;

	file.close();
}

void quiz::signup()
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

void quiz::login()
{
	char c, s;
	string user, pass, line;
	vector<string> st;

there:
	cout << "|\t\tusername : ";
	cin >> user;

	ifstream file;
	file.open(user + ".txt");
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
			cout << "\n|\t\tWelcome back " << st[2] << " " << st[3] << "\t\t|\n" << endl;
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
				game_menu();
				leaderboard_update(user);
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
					cout << "|\t\ttry again .... \t\t|\n"; goto h;
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
				cout << "|\tWrong key .... retry!!"; sleep_for(seconds(1)); goto hr;
		}
		else
		{
			cout << "\twrong password ..... retry!!\n";
			goto here;
		}
	}
	else
	{
		cout << "|\t\t no record found...retry \t\t|\n";
		goto there;
	}
}

void quiz::answer(float n1, float n2, int op)
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
		cout << "|\t\tunable to find answer\t\t|\n";
	}

	if (ans != check)
		cout << "|\tWrong answer !!! right answer is " << check << "\t|\n";
	else
	{
		cout << "|\tCongratulations!! your answer is correct\t|\n";
		score++;

		cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
	}
}

void quiz::questions(float n1, float n2, int o)
{
	if (count == 9)
		return;

	srand(time(0));
	float num1 = rand() % 100;
	float num2 = rand() % 100;

	int max = 4, min = 1;
again:
	int op = rand() % (max - min + 1);
	//cout << "op: " << op << endl;

	switch (op)
	{
	case 1:
		cout << "|\t Question no. " << count + 1 << ": \t\t\t\t|\n";
		cout << "|\t\t\t\t" << n1 << "\t\t\t|\n" << "|\t\t\t  +\t" << n2 << "\t\t\t|\n" << "|\t\t\t---------------\t\t\t|\n\t\t\t\t";
		answer(n1, n2, op);
		break;
	case 2:
		cout << "|\t Question no. " << count + 1 << ": \t\t\t\t|\n";
		cout << "|\t\t\t\t" << n1 << "\t\t\t|\n" << "|\t\t\t  -\t" << n2 << "\t\t\t|\n" << "|\t\t\t---------------\t\t\t|\n\t\t\t\t";
		answer(n1, n2, op);
		break;
	case 3:
		cout << "|\t Question no. " << count + 1 << ": \t\t\t\t|\n";
		cout << "|\t\t\t\t" << n1 << "\t\t\t|\n" << "|\t\t\t  x\t" << n2 << "\t\t\t|\n" << "|\t\t\t---------------\t\t\t|\n\t\t\t\t";
		answer(n1, n2, op);
		break;
	case 0:
		cout << "|\t Question no. " << count + 1 << ": \t\t\t\t|\n";
		cout << "|\t\t\t\t" << n1 << "\t\t\t|\n" << "|\t\t\t  /\t" << n2 << "\t\t\t|\n" << "|\t\t\t---------------\t\t\t|\n\t\t\t\t";
		answer(n1, n2, op);
		break;
	default:
		goto again;
	}

	count++;
	style();
	questions(num1, num2, op);
}

void quiz::math()
{
	srand(time(0));
	float n1 = rand() % 100;
	float n2 = rand() % 100;

	int max = 4, min = 1;
	int op = rand() % (max - min + 1);
	questions(n1, n2, op);

	cout << "\tyou scored " << score << "out of 10.\n";
	sleep_for(seconds(3));
}

void quiz::user_menu()
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
		game_menu();
	}
	else if (ch == 'b' or ch == 'B')
	{
		system("cls");
		main_menu();
	}
}

void quiz::main_menu()
{
	char choice;

start:
	style();

	cout << "|\t\t  press N for new user  \t\t|\n";
	cout << "|\t\t   press L for login    \t\t|\n";
	cout << "|\t\t    press E to exit \t\t\t|\n";

	style();

	choice = _getch();

	if (choice == 'N' or choice == 'n')
		user_menu();
	else if (choice == 'l' or choice == 'L')
		login();
	else if (choice == 'e' or choice == 'E')
	{
		cout << "|\t\tthank you for your visit\t\t|\n";
		cout << "|\t press any key to close this window\t\t|\n";
		style();
		exit(1);
	}
	else
		cout << "Wrong choice retry!! "; sleep_for(seconds(1)); system("cls"); goto start;

}

void quiz::leaderboard_update(string user)
{
	string line;

	ifstream file;
	file.open("leaderboard.txt");

	leaderboard l;
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
				l.add(name, scr);
			}
		}

		file.close();
	}

	l.add(user, score);

	l.sort();

	ofstream outFile("leaderboard.txt");
}

void quiz::leaderboard_display(string user)
{
	string line;
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

void quiz::game_menu()
{
	char choice;

	here:
	system("cls");
	style();
	cout << "|\t\tChoose the subject of quiz \t\t|\n";
	style();
	cout << "|\t\tPress 1 for basic DSA in C++\t\t|\n";
	cout << "|\t\tPress 2 for basic OOP in C++\t\t|\n";
	cout << "|\t\tPress 3 for basic PF  in C++\t\t|\n";
	cout << "|\t\tPress 4 for basic mathematics\t\t|\n";
	style();

	choice=_getch();

	switch (choice)
	{
	case '1':
		system("cls");
		cout << "|\tproceeding to DSA questions choose\t\t|\n|\t\t the right answer from below options\t|\n";
		style();
		DSA();
		break;

	case '2':
		system("cls");
		cout << "|\tproceeding to OOP questions choose\t\t|\n|\t\t the right answer from below options\t|\n";
		style();
		OOP();
		break;

	case '3':
		system("cls");
		cout << "|\tproceeding to PF questions choose\t\t|\n|\t\t the right answer from below options\t|\n";
		style(); 
		PF();
		break;

	case '4':
		system("cls");
		cout << "|\tproceeding to mathematics questions \t\t|\n|\t\t enter correct answer for below sums\t|\n";
		style(); 
		math();
		break;

	default:
		cout << "|\t Invalid input ..... retry!!\t\t|\n";
		sleep_for(seconds(1));
		goto here;
	}
}

void quiz::DSA()
{

}

void quiz::OOP()
{
	int counter = 1;
	char option;

	for (int i = 0; i < 10; i++)
	{
	hre:
		srand(time(0));
		int min = 1, max = 40;
		int op = rand() % (max - min + 1);

		op = 13;
		switch (op)
		{
		case 1:
			cout << "|\t Question no. " << counter << "\t\t\t\t\t|\n";
			cout << "|  What is the fundamental principle of OOP that states |\n|\t \"a class can inherit the characteristics\t|\n|\t (properties and behaviors) of another class\"?  | \n";
			cout << "|\t\t A) Abstraction\t\t\t\t|\n";
			cout << "|\t\t B) Inheritance\t\t\t\t|\n";
			cout << "|\t\t C) Encapsulation\t\t\t|\n";
			cout << "|\t\t D) Polymorphism\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'b' or option == 'B')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 2:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which keyword is used to define a child class that\t|\n|\t inherits from a parent class in C++? \t\t| \n";
			cout << "|\t\t A) using \t\t\t\t|\n";
			cout << "|\t\t B) extends \t\t\t\t|\n";
			cout << "|\t\t C) inherit \t\t\t\t|\n";
			cout << "|\t\t D) class \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 3:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "|\t In OOP, what does \"Encapsulation\" refer to?\t|\n";
			cout << "|\t A) Hiding implementation details and \t\t|\n|\t\t exposing only necessary features\t|\n";
			cout << "|\t B) Inheriting properties from a parent class\t|\n";
			cout << "|\t C) Creating multiple instances of a class\t|\n";
			cout << "|\t D) Overloading operators in a class\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 4:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which access specifier allows class members to be\t|\n|\t accessed by any function in the same program?  |\n";
			cout << "|\t\t A) public \t\t\t\t|\n";
			cout << "|\t\t B) private \t\t\t\t|\n";
			cout << "|\t\t C) protected \t\t\t\t|\n";
			cout << "|\t\t D) friend \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 5:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What does the term \"Polymorphism\" mean in OOP? \t| \n";
			cout << "|\t A) Ability to access different classes members |\n";
			cout << "|\t B) Ability of a function to perform different  |\n|\t tasks based on the object it is called on \t|\n";
			cout << "|\t C) Ability to create multiple objects of class |\n";
			cout << "|\t D) Ability to inherit properties from multiple |\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 6:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which keyword in C++ is used to create an alias \t|\n|\t\t for a data type?\t\t\t| \n";
			cout << "|\t\t\t A) typedef \t\t\t|\n";
			cout << "|\t\t\t B) typename \t\t\t|\n";
			cout << "|\t\t\t C) using \t\t\t|\n";
			cout << "|\t\t\t D) define \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 7:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| In OOP, what is the concept of \"Overloading\" in C++?\t| \n";
			cout << "|\t A) Creating multiple functions with the same\t|\n|\t\t name but different parameters \t\t|\n";
			cout << "|\t B) Inheriting properties from a parent class\t|\n";
			cout << "|\t C) Defining a function within another function |\n";
			cout << "|\t D) Providing multiple access levels for class  |\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 8:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which OOP concept emphasizes that objects created from|\n| class can be treated as instances of their superclass?| \n";
			cout << "|\t\t A) Encapsulation \t\t\t|\n";
			cout << "|\t\t B) Inheritance \t\t\t|\n";
			cout << "|\t\t C) Polymorphism \t\t\t|\n";
			cout << "|\t\t D) Abstraction \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 9:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| In C++, what is the purpose of the \"virtual\" keyword\t|\n|\t\t  in a base class function?\t\t| \n";
			cout << "|\t A) It prevents the function from being\t\t|\n|\t\t inherited by derived classes\t\t|\n";
			cout << "|\t B) It ensures the function is called first\t|\n|\t\t in the program\t\t\t\t|\n";
			cout << "|\t C) It allows derived classes to override\t|\n|\t\t the function\t\t\t\t|\n";
			cout << "|\t D) It restricts the function's access to\t|\n|\t\t the base class only\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 10:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which feature of OOP allows a class to have multiple  |\n| methods with the same name but different parameters?  | \n";
			cout << "|\t\t A) Inheritance \t\t\t|\n";
			cout << "|\t\t B) Encapsulation \t\t\t|\n";
			cout << "|\t\t C) Polymorphism \t\t\t|\n";
			cout << "|\t\t D) Abstraction \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 11:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which access specifier in C++ restricts access to\t|\n|\t class members only within the same class? \t| \n";
			cout << "|\t\t\t A) public \t\t\t|\n";
			cout << "|\t\t\t B) private \t\t\t|\n";
			cout << "|\t\t\t C) protected \t\t\t|\n";
			cout << "|\t\t\t D) friend \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 12:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the term used for a function defined\t\t|\n|\t inside a class in C++?\t\t\t\t| \n";
			cout << "|\t\t\t A) Method \t\t\t|\n";
			cout << "|\t\t\t B) Procedure \t\t\t|\n";
			cout << "|\t\t\t C) Member function \t\t|\n";
			cout << "|\t\t\t D) Subroutine \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 13:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which OOP concept involves bundling data and methods  |\n|\tthat work on the data into a single unit?\t| \n";
			cout << "|\t\t A) Abstraction \t\t\t|\n";
			cout << "|\t\t B) Inheritance \t\t\t|\n";
			cout << "|\t\t C) Encapsulation \t\t\t|\n";
			cout << "|\t\t D) Polymorphism \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 14:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| what is the function of the \"switch\" statement? \t| \n";
			cout << "|\t A) To execute a block of code repeatedly \t|\n";
			cout << "|\t B) To compare multiple conditions and execute\t|\n|\t\t the appropriate block of code \t\t|\n";
			cout << "|\t C) To terminate the program \t\t\t|\n";
			cout << "|\t D) To declare variables \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 15:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which data type in C++ is used to store characters? \t| \n";
			cout << "|\t\t A) char \t\t\t\t|\n";
			cout << "|\t\t B) string \t\t\t\t|\n";
			cout << "|\t\t C) float \t\t\t\t|\n";
			cout << "|\t\t D) double \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 16:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the purpose of the \"continue\" statement\t|\n|\t\t in a loop in C++?\t\t\t| \n";
			cout << "|\t A) Terminate the loop \t\t\t\t|\n";
			cout << "|\t B) Skip the remaining code in the loop\t\t|\n|\t\t and move to the next iteration \t|\n";
			cout << "|\t C) Exit the entire program \t\t\t|\n";
			cout << "|\t D) Restart the loop from the beginning \t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 17:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the syntax for a single-line comment in C++?\t| \n";
			cout << "|\t\t A) // comment \t\t\t\t|\n";
			cout << "|\t\t B) /* comment */ \t\t\t|\n";
			cout << "|\t\t C) # comment # \t\t\t|\n";
			cout << "|\t\t D) ' comment ' \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 18:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the purpose of the \"cin.ignore()\" function?\t| \n";
			cout << "|\t A) Ignore any input given by the user \t\t|\n";
			cout << "|\t B) Ignore a specific character from the\t|\n|\t\t input buffer \t\t\t\t|\n";
			cout << "|\t C) Ignore all errors in the input stream \t|\n";
			cout << "|\t D) Ignore whitespace characters in the\t\t|\n|\t\t input stream \t\t\t\t|\n\t\tanswer: ";
			cin >> option;

			if (option == 'D' or option == 'd')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is D \t\t|\n";
				counter++;
			}
			style();
			break;

		case 19:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the function of the \"do - while\" loop in C++?\t| \n";
			cout << "|\t A) Execute the code block based on a condition |\n";
			cout << "|\t B) Execute the code block at least once\t|\n|\t\t before checking the condition \t\t|\n";
			cout << "|\t C) Execute the code block for a specific\t|\n|\t\t number of times \t\t\t|\n";
			cout << "|\t D) Execute the code block if the condition\t|\n|\t\t is true \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 20:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which operator in C++ is used to compare two values\t|\n|\t\t and check for equality?\t\t| \n";
			cout << "|\t\t\t A) = \t\t\t\t|\n";
			cout << "|\t\t\t B) == \t\t\t\t|\n";
			cout << "|\t\t\t C) != \t\t\t\t|\n";
			cout << "|\t\t\t D) <= \t\t\t\t|\n\t\tAnswer: ";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 21:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the purpose of the \"endl\" manipulator? \t| \n";
			cout << "|  A) Move to the next line and flush the output buffer |\n";
			cout << "|\t B) Print the end of a line character \t\t|\n";
			cout << "|\t C) Terminate the program \t\t\t|\n";
			cout << "|\t D) Clear the console screen \t\t\t|\n\t\t Answer: ";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 22:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which keyword is used to exit a loop prematurely?\t| \n";
			cout << "|\t\t A) end \t\t\t\t|\n";
			cout << "|\t\t B) stop \t\t\t\t|\n";
			cout << "|\t\t C) break \t\t\t\t|\n";
			cout << "|\t\t D) terminate \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 23:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the role of the \"default\" case in\t\t|\n|\t\t \"switch\" statement in C++?\t\t| \n";
			cout << "|\t A) It defines the default value for a variable |\n";
			cout << "|\t B) It executes when none of the other case\t|\n|\t\t values match the switch expression \t|\n";
			cout << "|\t C) It indicates the end of switch statement\t|\n";
			cout << "|\t D) It terminates the program \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 24:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which operator is used to perform pointer arithmetic? | \n";
			cout << "|\t\t\t A) + \t\t\t\t|\n";
			cout << "|\t\t\t B) / \t\t\t\t|\n";
			cout << "|\t\t\t C) * \t\t\t\t|\n";
			cout << "|\t\t\t D) $ \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 25:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 26:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 27:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			break;

		case 28:
			cout << "|\t\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 29:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 30:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 31:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 32:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 33:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 34:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 35:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 36:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 37:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 38:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 39:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 40:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		default:
			cout << "inavalid option\t";
			goto hre;
		}
	}

	cout << "|\t\tyou scored " << score << " out of 10.\t\t\t|\n";
	style();
	sleep_for(seconds(1));
}

void quiz::PF()
{
	int counter = 1;
	char option;

	for (int i = 0; i < 10; i++)
	{
		hre:
		srand(time(0));
		int min = 1, max = 40;
		int op = rand() % (max - min + 1);

		switch (op)
		{
		case 1:
			cout << "|\t Question no. " << counter << "\t\t\t\t\t|\n";
			cout << "| What is the purpose of the \"cout\" object in C++ ? \t| \n";
			cout << "|\t A) Input data from the user\t\t\t|\n";
			cout << "|\t B) Print data to the console\t\t\t|\n";
			cout << "|\t C) Read data from a file\t\t\t|\n";
			cout << "|\t D) Perform arithmetic operations\t\t|\n\t\t";
			cin >> option;

			if (option == 'b' or option == 'B')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 2:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which data type in C++ is use to store integer value? | \n";
			cout << "|\t\t A) int \t\t\t\t|\n";
			cout << "|\t\t B) float \t\t\t\t|\n";
			cout << "|\t\t C) char \t\t\t\t|\n";
			cout << "|\t\t D) double \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 3:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which loop structure in C++ executes the code block\t|\n|\t at least once before checking the condition? \t| \n";
			cout << "|\t A) for loop \t\t\t\t\t|\n";
			cout << "|\t B) while loop \t\t\t\t\t|\n";
			cout << "|\t C) do-while loop \t\t\t\t|\n";
			cout << "|\t D) if-else loop \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'c' or option == 'C')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 4:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What does the \"break\" statement do in a loop in C++?\t| \n";
			cout << "| A) Terminates the loop and transfers control to\t|\n|\t\t the next iteration \t\t\t|\n";
			cout << "| B) Skips the current iteration and continues with the |\n|\t\t next iteration \t\t\t|\n";
			cout << "| C) Exits the entire program \t\t\t\t|\n";
			cout << "| D) Executes the code block repeatedly \t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 5:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t\t\t|\n";
			cout << "|\t\t B) / \t\t\t\t\t|\n";
			cout << "|\t\t C) * \t\t\t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 6:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the purpose of the \"cin\" object in C++?\t| \n";
			cout << "|\t A) Print data to the console \t\t\t|\n";
			cout << "|\t B) Read data from a file \t\t\t|\n";
			cout << "|\t C) Input data from the user \t\t\t|\n";
			cout << "|\t D) Perform arithmetic operations \t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 7:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which operator in C++ is used to access the value\t|\n|\t stored at a memory address?\t\t\t| \n";
			cout << "|\t\t\t A) * \t\t\t\t|\n";
			cout << "|\t\t\t B) & \t\t\t\t|\n";
			cout << "|\t\t\t C) -> \t\t\t\t|\n";
			cout << "|\t\t\t D) $ \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'c' or option == 'C')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 8:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the purpose of the \"++\" operator in C++?\t| \n";
			cout << "|\t A) Decrement a value by 1 \t\t\t|\n";
			cout << "|\t B) Add 1 to a value \t\t\t\t|\n";
			cout << "|\t C) Multiply a value by 2 \t\t\t|\n";
			cout << "|\t D) Divide a value by 2 \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 9:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which C++ keyword is used to declare a constant?\t| \n";
			cout << "|\t\t A) var \t\t\t\t|\n";
			cout << "|\t\t B) const \t\t\t\t|\n";
			cout << "|\t\t C) constant \t\t\t\t|\n";
			cout << "|\t\t D) static \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 10:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What does the \"else\" statement represent in an\t|\n|\t\t if-else construct in C++?\t\t| \n";
			cout << "|\t A) It indicates the end of the if block \t|\n";
			cout << "|\t B) It specifies the condition for the if block |\n";
			cout << "|\t C) It contains the code to be executed if\t|\n|\t\t the condition is false \t\t|\n";
			cout << "|\t D) It defines the variable to be used in \t|\n|\t\t the if block \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 11:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the purpose of the \"sizeof\" operator in C++?\t| \n";
			cout << "|\t A) Returns the size of a variable in bytes \t|\n";
			cout << "|\t B) Performs addition on two variables \t\t|\n";
			cout << "|\t C) Checks if two variables are of the same type|\n";
			cout << "|\t D) Converts variables to a specific size \t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 12:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which type of control structure allows a program\t|\n|\t\t to choose between two or more paths?\t| \n";
			cout << "|\t\t\t A) Sequence \t\t\t|\n";
			cout << "|\t\t\t B) Iteration \t\t\t|\n";
			cout << "|\t\t\t C) Selection \t\t\t|\n";
			cout << "|\t\t\t D) Looping \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 13:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What does the \" || \" operator represent in C++? \t| \n";
			cout << "|\t\t A) Logical OR \t\t\t\t|\n";
			cout << "|\t\t B) Bitwise OR \t\t\t\t|\n";
			cout << "|\t\t C) Assignment \t\t\t\t|\n";
			cout << "|\t\t D) Exclusive OR \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 14:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| what is the function of the \"switch\" statement? \t| \n";
			cout << "|\t A) To execute a block of code repeatedly \t|\n";
			cout << "|\t B) To compare multiple conditions and execute\t|\n|\t\t the appropriate block of code \t\t|\n";
			cout << "|\t C) To terminate the program \t\t\t|\n";
			cout << "|\t D) To declare variables \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 15:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which data type in C++ is used to store characters? \t| \n";
			cout << "|\t\t A) char \t\t\t\t|\n";
			cout << "|\t\t B) string \t\t\t\t|\n";
			cout << "|\t\t C) float \t\t\t\t|\n";
			cout << "|\t\t D) double \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 16:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the purpose of the \"continue\" statement\t|\n|\t\t in a loop in C++?\t\t\t| \n";
			cout << "|\t A) Terminate the loop \t\t\t\t|\n";
			cout << "|\t B) Skip the remaining code in the loop\t\t|\n|\t\t and move to the next iteration \t|\n";
			cout << "|\t C) Exit the entire program \t\t\t|\n";
			cout << "|\t D) Restart the loop from the beginning \t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 17:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the syntax for a single-line comment in C++?\t| \n";
			cout << "|\t\t A) // comment \t\t\t\t|\n";
			cout << "|\t\t B) /* comment */ \t\t\t|\n";
			cout << "|\t\t C) # comment # \t\t\t|\n";
			cout << "|\t\t D) ' comment ' \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 18:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the purpose of the \"cin.ignore()\" function?\t| \n";
			cout << "|\t A) Ignore any input given by the user \t\t|\n";
			cout << "|\t B) Ignore a specific character from the\t|\n|\t\t input buffer \t\t\t\t|\n";
			cout << "|\t C) Ignore all errors in the input stream \t|\n";
			cout << "|\t D) Ignore whitespace characters in the\t\t|\n|\t\t input stream \t\t\t\t|\n\t\tanswer: ";
			cin >> option;

			if (option == 'D' or option == 'd')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is D \t\t|\n";
				counter++;
			}
			style();
			break;

		case 19:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the function of the \"do - while\" loop in C++?\t| \n";
			cout << "|\t A) Execute the code block based on a condition |\n";
			cout << "|\t B) Execute the code block at least once\t|\n|\t\t before checking the condition \t\t|\n";
			cout << "|\t C) Execute the code block for a specific\t|\n|\t\t number of times \t\t\t|\n";
			cout << "|\t D) Execute the code block if the condition\t|\n|\t\t is true \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 20:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which operator in C++ is used to compare two values\t|\n|\t\t and check for equality?\t\t| \n";
			cout << "|\t\t\t A) = \t\t\t\t|\n";
			cout << "|\t\t\t B) == \t\t\t\t|\n";
			cout << "|\t\t\t C) != \t\t\t\t|\n";
			cout << "|\t\t\t D) <= \t\t\t\t|\n\t\tAnswer: ";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 21:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the purpose of the \"endl\" manipulator? \t| \n";
			cout << "|  A) Move to the next line and flush the output buffer |\n";
			cout << "|\t B) Print the end of a line character \t\t|\n";
			cout << "|\t C) Terminate the program \t\t\t|\n";
			cout << "|\t D) Clear the console screen \t\t\t|\n\t\t Answer: ";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 22:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which keyword is used to exit a loop prematurely?\t| \n";
			cout << "|\t\t A) end \t\t\t\t|\n";
			cout << "|\t\t B) stop \t\t\t\t|\n";
			cout << "|\t\t C) break \t\t\t\t|\n";
			cout << "|\t\t D) terminate \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is C \t\t|\n";
				counter++;
			}
			style();
			break;

		case 23:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the role of the \"default\" case in\t\t|\n|\t\t \"switch\" statement in C++?\t\t| \n";
			cout << "|\t A) It defines the default value for a variable |\n";
			cout << "|\t B) It executes when none of the other case\t|\n|\t\t values match the switch expression \t|\n";
			cout << "|\t C) It indicates the end of switch statement\t|\n";
			cout << "|\t D) It terminates the program \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'B' or option == 'b')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is B \t\t|\n";
				counter++;
			}
			style();
			break;

		case 24:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| Which operator is used to perform pointer arithmetic? | \n";
			cout << "|\t\t\t A) + \t\t\t\t|\n";
			cout << "|\t\t\t B) / \t\t\t\t|\n";
			cout << "|\t\t\t C) * \t\t\t\t|\n";
			cout << "|\t\t\t D) $ \t\t\t\t|\n\t\t";
			cin >> option;

			if (option == 'C' or option == 'c')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 25:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 26:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 27:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			break;

		case 28:
			cout << "|\t\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 29:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 30:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 31:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 32:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 33:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 34:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 35:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 36:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 37:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 38:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 39:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		case 40:
			cout << "|\t\t Question no. " << counter << "\t\t\t\t|\n";
			cout << "| What is the operator used for the modulus operation in C++? \t| \n";
			cout << "|\t\t A) % \t\t\t|\n";
			cout << "|\t\t B) / \t\t\t|\n";
			cout << "|\t\t C) * \t\t\t|\n";
			cout << "|\t\t D) $ \t\t\t|\n\t\t";
			cin >> option;

			if (option == 'A' or option == 'a')
			{
				counter++;
				cout << "|\tCongratulations!! your answer is correct\t|\n";
				score++;
				cout << "|\t\tyour points are updated to " << score << "\t\t|\n";
			}
			else
			{
				cout << "|\tWrong choice !!! right option is A \t\t|\n";
				counter++;
			}
			style();
			break;

		default:
			cout << "inavalid option\t";
			goto hre;
		}
	}

	cout << "|\t\tyou scored " << score << " out of 10.\t\t\t|\n";
	style();
	sleep_for(seconds(1));
}

leaderboard::leaderboard()
{
	head = NULL;
}

bool leaderboard::isEmpty()
{
	if (head == NULL)
		return true;
	else
		return false;
}

void leaderboard::add(string n, int s)
{
	if (isEmpty())
	{
		head = new node(n, s, NULL);
	}
	else
	{
		node* p = new node(n, s, head);
		head = p;
	}
}

void leaderboard::sort()
{
	if (isEmpty())
	{
		cout << "linklist is empty......\n";
	}
	else
	{
		node* current = head;
		node* keyAd = current;
		while (current->get_next() != NULL)
		{
			int key = keyAd->get_score();
			if (key > current->get_score())
			{
				node* temp = head;
				head = current;
				current->set_next(temp);
				keyAd = keyAd->get_next();
			}
			current = current->get_next();
		}
	}
}