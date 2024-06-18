#include <iostream>
#include <fstream>
#include <vector>
#include "Pass.h"

using namespace std;



Account::Account(string company, string username, string password ){
    _company = company;
    _username=username;
    _password = password;
}

User::User(){
    _username = "";
    _password= "";
    _accounts.clear();
}
User::User(string username, string password, vector<Account> accounts){
    _username = username;
    _password = password;
    _accounts = accounts;
}
User::User(string username, string password){
    _username = username;
    _password = password;
}
string User:: getUsername(){
    return _username;
}
string User:: getPassword(){
    return _password;
}



bool isUsernameTaken(string username){
    ifstream usernameFile( "usernames.txt");
    string line;
    

    while(getline(usernameFile, line)){
        size_t pos = line.find('|');
        
        if(pos != string::npos){
            string existingUsername = line.substr(0,pos);
            if(existingUsername == username){
            return true;
            }
        }
        
    }
    return false;

}

bool userExists(string username, vector <User> users){
    ifstream usernameFile("usernames.txt");
    
    for (int i=0; i < users.size(); i++){
        if (username == users[i].getUsername()){
            return true;
        }

    }
    return false;
}

bool passExists(string username, string password, vector <User> users){
    ifstream usernameFile("usernames.txt");

    for (int i =0; i < users.size() ; i++){
        if ((username == users[i].getUsername()) && (password == users[i].getPassword())){
            return true;
        }
    }
    return false;
}

vector<User> loadUsers(string filename){
    ifstream usersFile ("usernames.txt");
    string line;
    vector <User> users;

    

    while(getline(usersFile, line)){
    
        if(line.empty()){ //skip empty lines
            continue;
        }

        size_t delim1 = line.find('|');
        

        string username = line.substr(0, delim1);
        string password = line.substr(delim1+1);


        //debugger
        /*if(username != ""){
            cout << username << endl;
        }
        else{
            cout <<"No username found" << endl;
        }*/


        users.push_back(User(username, password));

    
    }

    vector<User> _accounts_;

    for( int i =0; i < users.size(); i ++){
        _accounts_.push_back(users[i]);
    }

    

    return _accounts_;
    //return true;
}

vector <Account> loadPasswords(string user){
    string fileName= user + ".txt";
    ifstream file(fileName);
    vector<Account> userAccounts;

    string line;
    while(getline(file, line)){
       
        if (line.empty()){// skip empty lines
            continue;
        }

        size_t delimiter1=line.find('|');
        size_t delimiter2= line.find('|',delimiter1 + 1);

        string company = line.substr(0, delimiter1);
        string username = line.substr(delimiter1 + 1, delimiter2 - delimiter1 - 1);
        string password = line.substr(delimiter2 + 1);

        userAccounts.push_back(Account(company, username, password));

        //debuggers
        /*
        cout << "Company: " << company << endl;
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        
        cout << "----------------------------------"<< endl;
                        for (int i =0; i< userAccounts.size(); i++){
                            cout << "Company: "<< userAccounts[i]._company << endl;
                            cout << "Username: " << userAccounts[i]._username << endl;
                            cout << "Password: " << userAccounts[i]._password << endl;
                            cout <<"----------------------------------" << endl;
                        }
        */
        
    }

    return userAccounts;

}





void User::addPasswords( string company, string username, string password){
    string fileName= this->getUsername() + ".txt"; // "this->" accesses the member function within the same class
    ofstream file;
    file.open(fileName, ios::app);

    file << endl <<company << "|" << username << "|" << password << endl;
    cout << "Account successfully added!" << endl;


}




User Signin(vector <User> people){
    ofstream userFile;

    cout << "Please enter your username:" << endl;
    string user;
    cin>> user;

    bool doesUserExist = false;
    doesUserExist = userExists(user, people);

    while(!doesUserExist){
        cout << "Your user does not exist. Please enter correct username:" << endl;
        cin>> user;

        doesUserExist = false;
        doesUserExist = userExists(user, people);
    }


    cout << "Please enter your password:" << endl;
    string pass;
    cin >> pass;

    bool passCorrect = false;
    passCorrect = passExists(user, pass, people);

    while(!passCorrect){
        cout << "Incorrect password. Please try again:" << endl;
        cin >> pass;

        passCorrect = false;
        passCorrect = passExists(user, pass, people);
    }
    
    cout << "Successfully signed in!" << endl;

    User currentUser = User(user,pass);
    return currentUser;
}

void SignUp(){
    
    ofstream usernameFile;
    usernameFile.open("usernames.txt", ios::app);

    cout << "Please create a username:" << endl;
    string newname;
    cin >> newname;// create username        
    
    

    
    bool usernameTaken = false;
    if (newname == "usernames"){ // validate username
        usernameTaken = true;
    }
    usernameTaken = isUsernameTaken(newname);

    while (usernameTaken){
        cout << "Username is already in use. Please create a new username: " << endl;
        cin >> newname;

        usernameTaken = false;
        if (newname == "usernames"){
            usernameTaken = true;
        }
        
        usernameTaken = isUsernameTaken(newname);
    }
    
    
    cout << "Please create a password." << endl;
    string password;
    cin >> password;

            // creates the file (account)
            usernameFile << newname << "|" << password<< endl; 
            string filename = newname + ".txt";
            ofstream outputFile(filename);
            if ( outputFile.is_open()){
                cout << "You have successfully made an account!" << endl;
            }
    
    User(newname, password );// create the object

    
    

        

    

    


}




int main(){
    vector<User> allAccounts = loadUsers("usernames.txt");
    


    string _choice;

    while (true){


    

    cout << "(1). Login" << endl;
    cout << "(2). Sign Up" << endl;
    cout << "(3). Exit" << endl;
    getline(cin,_choice);
    int choice = stoi(_choice);

    User user;
    
    string company,username,password;
    //string signInChoice;
    vector<Account> userAccounts;
    
    int _signInChoice;
    switch(choice){
        case 1://sign in
            user = Signin(allAccounts);
            userAccounts = loadPasswords(user.getUsername());
            

            while(true){

            
            
            cout << "What would you like to do:" << endl;
            cout<< "(1). View passwords" << endl;
            cout << "(2). Add password" << endl;
            cout << "(3). Exit" << endl;
            cin >> _signInChoice;
            //getline(cin,signInChoice);
            //_signInChoice = stoi(signInChoice);
                
                switch(_signInChoice){
                    
                    case 1:// view passwords
                        
                        cout << "----------------------------------"<< endl;
                        for (int i =0; i< userAccounts.size(); i++){
                            cout << "Company: "<< userAccounts[i]._company << endl;
                            cout << "Username: " << userAccounts[i]._username << endl;
                            cout << "Password: " << userAccounts[i]._password << endl;
                            cout <<"----------------------------------" << endl;
                        }
                        
                        

                    break;
                    case 2:// add password
                        cout << "Enter company:" << endl;
                        cin >> company;
                        cout << "Enter your username:" << endl;
                        cin >> username;
                        cout << "Enter your password:" << endl;
                        cin >> password;


                        user.addPasswords(company, username, password);

                    break;
                    case 3:// exit
                        return 0;
                    break;
                    default:
                    cout << "Invalid choice. Please choose a valid option" << endl;
        
                    
                }   
    }
                             
        break;
        case 2:// sign up
            SignUp();
        break;
        case 3: //exit
            return 0;
        break;
        default:
            cout << "Invalid choice. Please choose a valid option" << endl;
    }
    
  
    
    }


    return 0;
}



/* CREATE A FILE 
string name = "test";
    name += ".txt";
    ofstream outputFile(name); // creates a file
*/
    

   

