#ifndef PASS_H
#define PASS_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Account{
    string _company;
    string _username;
    string _password;

    Account( string company, string username, string password);
    

};


struct User{
    
    string _username;
    string _password;
    vector<Account> _accounts;



    
    User();// resets everything to blank
    User( string username, string password, vector<Account> accounts);
    User(string usernme, string password);
    
    string getUsername();
    string getPassword();

    void addPasswords(string company, string username, string password);
    vector <Account> loadPasswords(string user);
    bool loadUsers(string filename);
    void showInfo(User user);
    void changePassword();

};

class allAccounts{

    private:
    vector<User> _users;



    public:


};





#endif