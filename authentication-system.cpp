#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


class User
{
public:
	string name;
	string email;
	string password;

	int login = -1;

	void signupAccount(vector<User>& users)
	{
		cout << "Registration Process:" << endl;

		cout << "Enter the name: ";
		cin.ignore();
		getline(cin, name);

		cout << "Enter the email: ";
		getline(cin, email);

		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].email == email)
			{
				cout << "The entered email is already present. Please enter a valid email: ";
				getline(cin, email);
				i = -1;
			}
		}

		cout << "Enter the password: ";
		getline(cin, password);

		users.push_back(*this);
	}

	void loginAccount(const vector<User>& users)
	{
		cout << "Login Process" << endl;
		cout << "Enter the email: ";
		getline(cin, email);

		cout << "Enter the password: ";
		getline(cin, password);

		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].email == email && users[i].password == password)
			{
				cout << "Login successful" << endl;
				cout << "User Name is: " << users[i].name << endl
					<< "Email is: " << users[i].email << endl
					<< "Password is: " << users[i].password << endl;

				login = i;
				return;
			}
		}
		cout << "Login failed. Invalid email or password." << endl;
	}

	void editAccount(vector<User>& users)
	{
		char choice;

		cout << "For changing Name press: n" << endl
			<< "For changing Email press: e" << endl
			<< "For changing Password press: p" << endl;

		cin >> choice;
		cin.ignore();

		if (choice == 'n')
		{
			string tempName;
			cout << "Enter the Name you want to change: ";
			getline(cin, tempName);
			users[login].name = tempName;
			cout << "Your new user name is: " << users[login].name << endl;
			cout << "Successful Change" << endl;
		}

		if (choice == 'e')
		{
			string tempEmail;
			cout << "Enter the Email you want to change: ";
			getline(cin, tempEmail);
			users[login].email = tempEmail;
			cout << "Your new email is: " << users[login].email << endl;
			cout << "Successful Change" << endl;
		}

		if (choice == 'p')
		{
			string tempPassword;
			cout << "Enter the Password you want to change: ";
			getline(cin, tempPassword);
			users[login].password = tempPassword;
			cout << "Your new password is: " << users[login].password << endl;
			cout << "Successful Change" << endl;
		}
	}

	void deleteAccount(vector<User>& users)
	{
		users.erase(users.begin() + login);
		cout << "Account successfully deleted" << endl;
	}
};



int main() {
	vector<User> users;

	User currentUser;

	do
	{
		cout << "For Sign Up Press 1" << endl;
		cout << "For Login Press 2" << endl;
		cout << "For Exit Press 3" << endl;
		cout << "Enter your choice: ";

		int choice;
		cin >> choice;
		cin.ignore();

		if (choice == 1)
		{
			currentUser.signupAccount(users);
			continue;
		}
		else if (choice == 2)
		{
			currentUser.loginAccount(users);
			do {
				int innerChoice;
				cout << "For edit account press 1" << endl;
				cout << "For delete account press 2" << endl;
				cout << "For logout press 3" << endl;
				cin >> innerChoice;
				if (innerChoice == 1)
				{
					currentUser.editAccount(users);
					continue;
				}
				else if (innerChoice == 2)
				{
					currentUser.deleteAccount(users);
					continue;
				}
				else
				{
					char exit;
					cout << "Do you want to logout(y / n)";
					cin >> exit;

					if (exit == 'y' || exit == 'Y')
					{
						break;
					}
					else
					{
						continue;
					}
				}
			} while (true);
		}
		else
		{
			return 0;
			currentUser.login = -1;
		}
	} while (true);

	return 0;
}