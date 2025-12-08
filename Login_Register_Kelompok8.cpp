#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct  User
{
    string username;
    string password;
    string forgotpassword;
    string usernameInput;
    string passwordInput;
    char choice;
    
};

void pauseProgram()
{
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

bool usernameExists(const string &username) {
    ifstream file("user_data.txt");
    string fileUsername, filePassword;

    while (getline(file, fileUsername) && getline(file, filePassword)) {
        if (fileUsername == username) {
            return true; 
        }
    }
    return false; 
}

void registerUser(User &user)
{
    cout << "\n====Register====\n";

    cin.ignore();
    bool valid = false;

    while (!valid)  
    {
        cout << "Enter username: ";
        getline(cin, user.username);

        if (usernameExists(user.username))
        {
            cout << "Username already exists! Please choose another one.\n";
        }
        else
        {
            valid = true;
        }
    }

    do {
        cout << "Enter 10 character password: \n";
        cin >> user.password;

        if (user.password.length() != 10)
            cout << "Password must be exactly 10 characters!\n";

    } while (user.password.length() != 10);

    cout << "\n=== Registration Complete ===\n";
    cout << "Saved Username : " << user.username << "\n";
    cout << "  ✓ Password : ";
    
    for (int i = 0; i < user.password.length(); i++)
        cout << "*";
    
    cout << "\n\n";
}



void savedata(User &user)
{
    ofstream file("user_data.txt", ios::app);
    if (file.is_open())
    {
        file << user.username << "\n";
        file << user.password << "\n";
        file.close();
        cout << "User data saved successfully.\n";
    }
    else
    {
        cout << "Error saving user data.\n";
    }
}

void forgotPassword(User &user)
{
    cout << "\n====Forgot Password====\n";

    ifstream inFile("user_data.txt");
    if (!inFile.is_open()) {
        cout << "Error loading data.\n";
        return;
    }

    string fileUsername, filePassword;
    string newContent = "";
    string oldPassword = "";
    bool userFound = false;
    while (getline(inFile, fileUsername) && getline(inFile, filePassword)) {
        if (fileUsername == user.usernameInput) {
            oldPassword = filePassword;  
            userFound = true;
        }
    }
    inFile.close();

    if (!userFound) {
        cout << "Username not found!\n";
        return;
    }
    do {
        cout << "Enter NEW 10 character password (must be different from old one): \n";
        cin >> user.forgotpassword;

        if (user.forgotpassword.length() != 10)
            cout << "Password must be exactly 10 characters!\n";
        else if (user.forgotpassword == oldPassword)
            cout << "New password cannot be the SAME as old password!\n";

    } while (user.forgotpassword.length() != 10 || user.forgotpassword == oldPassword);

    ifstream fileRead("user_data.txt");
    newContent = "";
    while (getline(fileRead, fileUsername) && getline(fileRead, filePassword)) {
        if (fileUsername == user.usernameInput)
            newContent += fileUsername + "\n" + user.forgotpassword + "\n";
        else
            newContent += fileUsername + "\n" + filePassword + "\n";
    }
    fileRead.close();

    ofstream fileWrite("user_data.txt");
    fileWrite << newContent;
    fileWrite.close();

    cout << "Password reset successful! Your new password is: " << user.forgotpassword << "\n";
}


void loginUser(User &user)
{
    cout << "\n====Login====\n";
    ifstream file("user_data.txt");
    if (!file.is_open())
    {
        cout << "Error loading user data. Please register first.\n";
        return;
    }

    cout << "Enter username: ";
    cin.ignore();
    getline(cin, user.usernameInput);
    cout << "Enter password: ";
    getline(cin, user.passwordInput);

    string fileUsername, filePassword;
    bool found = false;

    while (getline(file, fileUsername) && getline(file, filePassword))
    {
        if (user.usernameInput == fileUsername && user.passwordInput == filePassword)
        {
            found = true;
            break;
        }
    }
    file.close();

    if (found)
    {
        cout << "Login successful! Welcome, " << user.usernameInput << ".\n";
    }
    else
    {
        cout << "Login failed! Invalid username or password.\n";
        cout << "Forgot password? (Y/n): ";
        cin >> user.choice;
        if (user.choice == 'Y' || user.choice == 'y')
        {
            forgotPassword(user);
            savedata(user);
        }
    }
}

void displayMainMenu() {
    cout << "\n";
    cout << "  +========================================+\n";
    cout << "  |        LOGIN &REGISTER SYSTEM          |\n";
    cout << "  |               WELCOME!                 |\n";
    cout << "  +========================================+\n\n";
    
    cout << "  [*] MAIN MENU\n";
    cout << "  \n";
    cout << "      [1] Register New Account\n";
    cout << "      [2] Login\n";
    cout << "      [3] Exit\n\n";
    cout << "  Choose an option (1-3): ";
}

int main()
{
    User user;
    int choice;

   do
   {
    displayMainMenu();
    cin >> choice;

    if (choice == 1)
    {
        registerUser(user);
        savedata(user);
        pauseProgram();
    }
    else if (choice == 2)
    {
        loginUser(user);
        pauseProgram();
    }
    else if (choice == 3)
    {
        cout << "Exiting program... Goodbye!\n";
    }
    else
    {
        cout << "Invalid choice! Please choose again.\n";
    }
}
   while (choice != 3);
    return 0;
}