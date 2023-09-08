#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User;

vector<User> users;
const string SECRET = "secret";

class User
{
protected:
	string name;
	string username;
	string password;
	bool isLogin = false;

	friend string encryptedPassword(const User& user, string password);

public:

	void signupProfile(string name, string username, string password)
	{
		cout << "Signup process" << endl;
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].username == username)
			{
				cout << "Username already exists. Enter the username again: ";
				cin >> username;
				i = -1;
			}
		}

		this->name = name;
		this->username = username;
		this->password = encryptedPassword(*this, password);

		users.push_back(*this);

		cout << "You register successfully" << endl;
	}

	bool loginProfile(string username, string password)
	{
		if (users.empty())
		{
			cout << "No user register yet" << endl;
			return false;
		}

		cout << "Login Process" << endl;
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].username == username && users[i].password == encryptedPassword(*this, password))
			{
				*this = users[i];
				this->isLogin = true;
				cout << "Login successfully" << endl;
				return true;
			}
		}
		cout << "Invalid credentials" << endl;
		return false;
	}

	void getProfileInfo()
	{
		if (this->isLogin == true)
		{
			cout << "Name is: " << name << endl;
			cout << "Username is: " << username << endl;
		}
	}

	void updateProfile(const string& fieldToUpdate, string change)
	{
		if (this->isLogin == true)
		{
			cout << "Enter the password to change: ";
			cin >> password;

			if (this->password != encryptedPassword(*this, password))
			{
				cout << "Incorrect password" << endl;
				return;
			}

			if (fieldToUpdate == "name")
			{
				this->name = change;
			}
			else if (fieldToUpdate == "username")
			{
				this->username = change;
			}
			else
			{
				this->password = change;
			}

			cout << "Changes made successfully" << endl;
		}
	}

	void logoutProfile()
	{
		if (this->isLogin == true)
		{
			this->isLogin = false;
			cout << "Logout successfully" << endl;
		}
	}

	void deleteProfile()
	{
		if (this->isLogin == true)
		{
			int i;
			for (i = 0; i < users.size(); i++)
			{
				if (users[i].username == this->username)
					break;
			}

			cout << "Enter the password to delete your account: ";
			cin >> password;

			if (users[i].password == encryptedPassword(*this, password))
			{
				users.erase(users.begin() + i);
				cout << "Account deleted successfully" << endl;
				return;
			}

			cout << "Sorry incorrect password we cannot delete this account" << endl;
		}
	}
};

//Encrypted Password
string encryptedPassword(const User& user, string password)
{
	string tempPassword = SECRET + password;
	int first = 0, last = tempPassword.length();

	while (first < last)
	{
		password += tempPassword[first];
		password += tempPassword[last];
		first++; last--;
	}
	return password;
}


int main()
{
	cout << "Welcome to User Profile Management System" << endl;
	cout << "=================================================================" << endl;

	int choice;
	string name, username, password;

	while (true)
	{
		cout << "Menu" << endl;
		cout << "Press 1 for signup: " << endl
			<< "Press 2 for login: " << endl
			<< "Press 3 for Exit: " << endl;

		cin >> choice;

		if (choice == 1)
		{
			cout << "Enter your name: ";
			cin.ignore();
			getline(cin, name);

			cout << "Enter a username: ";
			cin >> username;

			cout << "Enter a strong password: ";
			cin >> password;

			User currentUser;
			currentUser.signupProfile(name, username, password);
		}

		else if (choice == 2)
		{
			cout << "Enter your username: ";
			cin >> username;

			cout << "Enter your password: ";
			cin >> password;

			bool logedIn = false;
			User loginUser;
			logedIn = loginUser.loginProfile(username, password);

			if (logedIn == true)
			{
				while (true)
				{
					cout << "User Menu" << endl
						<< "Press 1 for View profile" << endl
						<< "Press 2 for Update profile" << endl
						<< "Press 3 for logout profile" << endl
						<< "Press 4 for delete profile" << endl
						<< "Press 5 for return to main menu" << endl;
					cin >> choice;
					if (choice == 1)
					{
						loginUser.getProfileInfo();
					}
					else if (choice == 2)
					{
						string fieldToUpdate, change;
						cout << "Enter the field to update (name , username, password): ";
						cin >> fieldToUpdate;

						cout << "Enter the change:";
						cin >> change;

						if (fieldToUpdate == "name" || fieldToUpdate == "username" || fieldToUpdate == "password")
						{
							loginUser.updateProfile(fieldToUpdate, change);
							continue;
						}
						else
						{
							cout << "You enter invalid field" << endl;
							break;
						}
					}
					else if (choice == 3)
					{
						loginUser.logoutProfile();
						logedIn = false;
						break;
					}
					else if (choice == 4)
					{
						loginUser.deleteProfile();
						logedIn = false;
						break;
					}
					else if (choice == 5)
					{
						logedIn == false;
						break;
					}
					else
					{
						cout << "Invalid choice" << endl;
						continue;
					}
				}
			}
		}

		else if (choice == 3)
		{
			cout << "Thank you for using" << endl;
			return 0;
		}

		else
		{
			cout << "Invalid Operation" << endl;
		}
	}

	return 0;
}