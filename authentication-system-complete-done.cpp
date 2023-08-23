#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Body of class
class User
{
public:
	string name;
	string email;
	string password;
	bool isLoggedIn;
	static const string SECRET;
	int loginNumber;

	void signup(vector<User>& users);
	void login(const vector<User>& users);
	void getProfile(const vector<User>& users);
	void updateProfile(vector<User>& users);
	void deleteMyAccount(vector<User>& users);

};

//Signup function of class user
void User::signup(vector<User>& users)
{
	cout << "Registration Process" << endl;

	cout << "Enter the Name: ";
	//cin.ignore();
	getline(cin, name);

	cout << "Enter the Email: ";
	getline(cin, email);

	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].email == email)
		{
			cout << "The entered Email is already present. Please enter a valid Email: ";
			getline(cin, email);
			i = -1;
		}
	}

	cout << "Enter the Password: ";
	getline(cin, password);

	while (password.length() < 6)
	{
		cout << "Password must be of at least 6 characters: ";
		getline(cin, password);
	}

	string tempPassword = password;

	password = {};

	int j = 0;
	for (int i = 0; i < tempPassword.length() + SECRET.length() - 2; i += 2)
	{
		password += tempPassword[j];

		if (j < SECRET.length())
		{
			password += SECRET[j];
		}
		else
		{
			password += tempPassword[j + 1];
		}
		j++;
	}

	users.push_back(*this);
	cout << "Account created successfully!" << endl;
}

void User::login(const vector<User>& users)
{
	if (users.empty())
	{
		cout << "No account register yet" << endl;
		return;
	}

	cout << "Login Process" << endl;
	cout << "Enter the Email: ";
	getline(cin, email);

	cout << "Enter the Password: ";
	getline(cin, password);

	string tempPassword = password;

	password = {};

	int j = 0;
	for (int i = 0; i < tempPassword.length() + SECRET.length() - 2; i += 2)
	{
		password += tempPassword[j];

		if (j < SECRET.length())
		{
			password += SECRET[j];
		}
		else
		{
			password += tempPassword[j + 1];
		}
		j++;
	}

	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].email == email && users[i].password == password)
		{
			loginNumber = i;
			isLoggedIn = true;
			cout << "Login Successful" << endl;
			return;
		}
	}
	cout << "Invalid Credentials" << endl;
}

void User::getProfile(const vector<User>& users)
{
	if (isLoggedIn == true)
	{
		cout << "Name is: " << users[loginNumber].name << endl;
		cout << "Email is: " << users[loginNumber].email << endl;
	}
}

void User::updateProfile(vector<User>& users)
{
	if (isLoggedIn == true)
	{
		do {
			char choice;
			cout << "To change name press 'n', change email press 'e', change password press 'p', for exit press '#': ";
			cin >> choice;
			cin.ignore();

			if (choice == 'n' || choice == 'N')
			{
				cout << "Kindly enter the name you want to change to: ";
				getline(cin, name);
				users[loginNumber].name = name;
				cout << "Successfuly Changed" << endl;
				return;
			}

			if (choice == 'e' || choice == 'E')
			{
				cout << "Kindly enter the email you want to change to: ";
				getline(cin, email);
				for (int i = 0; i < users.size(); i++)
				{
					if (users[i].email == email)
					{
						cout << "The entered Email is already present. Please enter a valid Email: ";
						getline(cin, email);
						i = -1;
					}
				}
				users[loginNumber].email = email;
				cout << "Successfully Changed" << endl;
				return;
			}

			if (choice == 'p' || choice == 'P')
			{
				cout << "kindly entered the password you want to change to: ";
				getline(cin, password);

				string tempPassword = password;

				password = {};

				int j = 0;
				for (int i = 0; i < tempPassword.length() + SECRET.length() - 2; i += 2)
				{
					password += tempPassword[j];

					if (j < SECRET.length())
					{
						password += SECRET[j];
					}
					else
					{
						password += tempPassword[j + 1];
					}
					j++;
				}
				users[loginNumber].password = password;
				cout << "Successfuly Changed" << endl;
				return;
			}

			if (choice == '#')
			{
				return;
			}
			else
			{
				cout << "Invalid choice. Please select a valid option." << endl;
			}

		} while (true);
	}
}

void User::deleteMyAccount(vector<User>& users)
{
	do {
		char choice;
		cout << "Are you sure you want to delete your account (y / n): ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			users.erase(users.begin() + loginNumber);
			cout << "Account Successfully Deleted" << endl;
			isLoggedIn = false;
			return;
		}
		else if (choice == 'n' || choice == 'N')
		{
			return;
		}
		else
		{
			cout << "Invalid Operation" << endl;
		}
	} while (true);
}

const string User::SECRET = "secret";

int main()
{
	vector<User> users;

	int choice;

	while (true)
	{
		cout << "For Signup press 1, For Login press 2, For exit press 3: ";
		cin >> choice;
		cin.ignore();

		if (choice == 3)
		{
			break;
		}

		if (choice == 1)
		{
			User newUser;
			newUser.signup(users);
		}

		if (choice == 2)
		{
			User currentUser;
			currentUser.login(users);
			if (currentUser.isLoggedIn == true)
			{
				while (true)
				{
					cout << "For get profile press 1" << endl
						<< "For update profile press 2" << endl
						<< "For delete profile press 3" << endl
						<< "For logout press 4" << endl;
					cin >> choice;
					cin.ignore();

					if (choice == 1)
					{
						currentUser.getProfile(users);
						continue;
					}
					if (choice == 2)
					{
						currentUser.updateProfile(users);
						continue;
					}
					if (choice == 3)
					{
						currentUser.deleteMyAccount(users);
						break;
					}
					if (choice == 4)
					{
						cout << "Logout Successful" << endl;
						break;
					}
				}
				continue;
			}
		}

	}

	cout << "Thanks for using" << endl;

	return 0;
} 