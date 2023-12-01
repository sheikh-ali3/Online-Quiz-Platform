#include"Header.h"

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
	cout << "score = " << score;
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
	cout << "\t\tusername : ";
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

	count++;

	questions(num1, num2, op);
}

void quiz::game()
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
		game();
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
		cout << "thank you for your visit\n";
		exit(1);
	}
	else
		cout << "Wrong choice retry!! "; sleep_for(seconds(1)); system("cls"); goto start;

}

void quiz::leaderboard(string user)
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

void quiz::leaderboard_display(string user)
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


