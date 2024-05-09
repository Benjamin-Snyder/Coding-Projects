#include <iostream>
using namespace std;

char shiftChar(char letter, int shift_value) {
    char shifted_letter;
    
    if (shift_value > 25) { // adjusting to make sure the shift value stays in range
        shift_value = shift_value % 26;
    } else if (shift_value < -25) {
        shift_value = (shift_value % 26) + 26;
    }

    shifted_letter = letter + shift_value;

   if (letter >= 'a' && letter <= 'z') { // wrap around
        shifted_letter = 'a' + ((letter - 'a' + shift_value) + 26) % 26;
    } else if (letter >= 'A' && letter <= 'Z') {
        shifted_letter = 'A' + ((letter - 'A' + shift_value) + 26) % 26;
    } else {
        shifted_letter = letter; 
    }

    return shifted_letter;
} 


int getDoubleKeyShiftValue(string key1, string key2){ // method 2
    int shift_distance = 0;
   

   int length;

   if(key1.length() < key2.length()){ // picking the length for encryption so it runs long enough
        length = key2.length();
    }
    else {
        length = key1.length(); 
    } 
   
    for (int i=0; i < length; ++i ){ // if there are any matching letters, increase shift value
        for (int j = 0; j < length; ++j){
            if(key1[i] == key2[j]){
            ++shift_distance;
          
            }
        }
        }
    

   
    return shift_distance % 26 ;
}


string getLayer1MessageEncryption(string message, int method_choice, string key1, string key2){
   
    string encrypted_message;
    

    switch(method_choice){

        case 1: //shift by 13
        char letter;
        int shift_value;
        
        
            for (int i=0; i < message.length(); ++i){ // shifting each letter
                letter = message[i];
                shift_value=13;
                message[i] = shiftChar(letter, shift_value);
            
                encrypted_message = message;
            }

            break;
        case 2: //method 2
        
        shift_value = getDoubleKeyShiftValue(key1, key2);
        
            for (int i =0; i < message.length(); ++i){ // making sure each letter is alphabetical
                
                if (message[i] < 'A' || (message[i] > 'Z' && message[i]< 'a') || message[i]> 'z'){
                    message[i] = message[i];
                }
                else{
                message[i] = shiftChar(message[i], shift_value);
                  


                }
                encrypted_message = message;
            }
            break;
        default:
            encrypted_message = message;

    }
        

    return encrypted_message;
}


string getLayer1MessageDecryption(string encrypted_message, int method_choice, string key1, string key2){
   
    string decrypted_message;
    

    switch(method_choice){

        case 1: //shift by -13 decryption
        char letter;
        int shift_value;
        
        
            for (int i=0; i < encrypted_message.length(); ++i){
                letter = encrypted_message[i];
                shift_value=-13;
                encrypted_message[i] = shiftChar(letter, shift_value);
            
                decrypted_message = encrypted_message;
            }

            break;
        case 2: //method 2 decryption
       
        shift_value = getDoubleKeyShiftValue(key1, key2)* -1;
        
            for (int i =0; i < encrypted_message.length(); ++i){
                
                if (encrypted_message[i] < 'A' || (encrypted_message[i] > 'Z' && encrypted_message[i]< 'a') || encrypted_message[i]> 'z'){
                    encrypted_message[i] = encrypted_message[i];
                }
                else{
                encrypted_message[i] = shiftChar(encrypted_message[i], shift_value);
                  


                }
                decrypted_message = encrypted_message;
            }
            break;
        default:
            decrypted_message = encrypted_message;

    }
        

    return decrypted_message;
}

string getLayer2MessageEncryption(string message, string key_phrase){
    string key;
    string encrypted_message;
    

    int keyPhraseLength = key_phrase.length()-1;
    if (key_phrase == ""){ //returns message if key_phrase is blank
        return message;
    }
    for (int i=0; i< keyPhraseLength; i++){ 
        if(i==0){ //creating the first letter of the key from the first part of key_phrase
            if ((key_phrase[i] >='A'&& key_phrase[i]<='Z') || (key_phrase[i] >= 'a' && key_phrase[i]<= 'z')){
                key += key_phrase[i];
            }
            else{
                return message;
            }
        }
        if (key_phrase[i] == ' '){ // creating the other parts of key by detecting the start of a new word, via a space
            if ((key_phrase[i+1] >='A'&& key_phrase[i+1]<='Z') || (key_phrase[i+1] >= 'a' && key_phrase[i+1]<= 'z')){
                key += key_phrase[i+1];
            }
            else{
                return message;
            }
        }
    }
    
    for (int i =0; i < key.length(); i++){ // converts the key to uppercase
        if(key[i]>='a' && key[i] <= 'z'){
            key[i] -=32;
        }
    }

    
    int j=0;

    for (int i=0; i < message.length(); i++){
        if (!(j<key.length())){ //makes sure the key repeats for the entirety of the message
            j=0;
        }
        
        int shift_value = key[j] -65;
        message[i] = shiftChar(message[i], shift_value);
        if ((message[i]>= 'A'&& message[i]<= 'Z')||(message[i]>='a' && message[i]<= 'z')){ // makes sure to only alter alphabetical letters
            j++;
        }
    }
    encrypted_message = message;
    return encrypted_message;
}

string getLayer2MessageDecryption(string encrypted_message, string key_phrase){
        /*
        
        This code is the exact same as layer 2 encryption,
        only dfference is the shift_value is turned negative
        
        
        */
        
        string key;

    int keyPhraseLength = key_phrase.length()-1;
    if (key_phrase == ""){ //returns message if key_phrase is blank
        return encrypted_message;
    }
    for (int i=0; i< keyPhraseLength; i++){ 
        if(i==0){ //creating the first letter of the key from the first part of key_phrase
            if ((key_phrase[i] >='A'&& key_phrase[i]<='Z') || (key_phrase[i] >= 'a' && key_phrase[i]<= 'z')){
                key += key_phrase[i];
            }
            else{
                return encrypted_message;
            }
        }
        if (key_phrase[i] == ' '){ // creating the other parts of key by detecting the start of a new word, via a space
            if ((key_phrase[i+1] >='A'&& key_phrase[i+1]<='Z') || (key_phrase[i+1] >= 'a' && key_phrase[i+1]<= 'z')){
                key += key_phrase[i+1];
            }
            else{
                return encrypted_message;
            }
        }
    }
    
    for (int i =0; i < key.length(); i++){ // converts the key to uppercase
        if(key[i]>='a' && key[i] <= 'z'){
            key[i] -=32;
        }
    }

    
    int j=0;

    for (int i=0; i < encrypted_message.length(); i++){
        if (!(j<key.length())){ //makes sure the key repeats for the entirety of the message
            j=0;
        }
        int shift_value = key[j] -65;
        shift_value *= -1; // make the shift value negative so it decrypts
        encrypted_message[i] = shiftChar(encrypted_message[i], shift_value);
        if ((encrypted_message[i]>= 'A'&& encrypted_message[i]<= 'Z')||(encrypted_message[i]>='a' && encrypted_message[i]<= 'z')){ // makes sure to only alter alphabetical letters
            j++;
        }
    }
    string decrypted_message;
    decrypted_message = encrypted_message;
    return decrypted_message;
}

string getChainEncryption(string message, int method_choice, string key1, string key2, string key_phrase) {
    string encrypted_message;
    
    if(message == ""|| method_choice < 1|| method_choice >2|| key1== ""|| key2== "" || key_phrase ==""){
        return message;
    }
    if ((key_phrase[0] <65) || (key_phrase[0] >90 && key_phrase[0] < 97) || (key_phrase[0] > 122)){
        return message;
    }
    
    string message1 = getLayer1MessageEncryption(message, method_choice, key1, key2); // encrypt with Layer 1

    encrypted_message = getLayer2MessageEncryption(message1, key_phrase); // encrypt again with Layer 2

    return encrypted_message;
}

string getChainDecryption (string encrypted_message, int method_choice, string key1, string key2, string key_phrase){
     string decrypted_message;
    
    if(encrypted_message == ""|| method_choice < 1|| method_choice >2|| key1== ""|| key2== "" || key_phrase ==""){
        return encrypted_message;
    }
    if ((key_phrase[0] <65) || (key_phrase[0] >90 && key_phrase[0] < 97) || (key_phrase[0] > 122)){
        return encrypted_message;
    }

    string message2 = getLayer1MessageDecryption(encrypted_message, method_choice, key1, key2); //decrypt with Layer 1

    decrypted_message = getLayer2MessageDecryption(message2, key_phrase); // decrypt again with Layer 2

    return decrypted_message;
}

void displayMenu(){
    cout << "Please input 1-7 followed by enter to navigate the menu:" << endl;
    cout << "1. Set Encryption Key 1" << endl;
    cout << "2. Set Encryption Key 2" << endl;
    cout << "3. Set Key Phrase" << endl;
    cout << "4. Select Encryption Method" << endl;
    cout << "5. Encrypt Message" << endl;
    cout << "6. Decrypt Message" << endl;
    cout << "7. Exit Program" << endl;

    
}
void displayEType(){
    cout << "Please input 1-3 to decide encryption technique." << endl;
    cout << "1. Layer 1 Message Encryption" << endl;
    cout << "2. Layer 2 Message Encryption" << endl;
    cout << "3. Chain Encryption" << endl;


}
void display13Encrypt(){
    cout << "Please input 1-2 to decide Layer-1 encryption technique." << endl;
    cout << "1. Shift by 13" << endl;
    cout << "2. Shift by mixed keys" << endl;
    
    
}

int main(){
    string message, men, meth,machine_encrypted_message, encrypted_message, key1, key2, key_phrase, method, decrypted_message;
    int menuSelect;
    int method_choice =0;
    int Etype = 0;
    
    do{
    displayMenu();
    getline(cin,men);
        while(men != "1" && men != "2" && men != "3" && men != "4" && men != "5" && men != "6" && men != "7"){ // validate input
            cout << "Invalid input" << endl;
            displayMenu();
            getline(cin,men);
            menuSelect =0;
        }
    
            menuSelect = stoi(men);
        

        if (menuSelect < 1 || menuSelect > 7){
            cout << "Invalid input" << endl;
            menuSelect = 0;
        }
        else{
    
    switch(menuSelect){
        
        case 1: // set encryption key 1
            cout << "Enter First key:" << endl;
            getline(cin, key1);
            while (key1 == ""){ // validate key1
                cout << "Invalid key" << endl;
                cout << "Enter First key:" << endl;
                getline(cin, key1);
            }
            
            cout << "Successfully set first encryption key to " << key1 << endl;
            
            

        break;
        case 2: // set encryption key 2
            cout << "Enter Second key:" << endl;
            getline(cin,key2);
            
            while (key2 == ""){ // validate key 2
                cout << "Invalid key" << endl;
                cout << "Enter Second key:" << endl;
                getline(cin,key2);
            }
            
            cout << "Successfully set second encryption key to " << key2 << endl;
            
            
        break;
        case 3: // set key phrase
            cout << "Enter keyphrase:" << endl;
            getline(cin, key_phrase);
            
            for (int i =0 ; i<key_phrase.length(); i++){ // validate key phrase
                while (key_phrase[i]<32 || (key_phrase[i]< 'A' && key_phrase[i] >32)|| (key_phrase[i]>'Z' && key_phrase[i]<'a') || key_phrase[i] > 'z'){
                    cout << "Invalid keyphrase" << endl;
                    cout << "Enter keyphrase:" << endl;
                    getline(cin, key_phrase);
                }

            }
            
            while (key_phrase == ""){ // if key phrase if invalid
                cout << "Invalid keyphrase" << endl;
                cout << "Enter keyphrase:" << endl;
                getline(cin, key_phrase);
            }
            cout << "Successfully set encryption keyphrase to " << key_phrase << endl;
            

        break;
        case 4: //select encryption method
        
             displayEType();
            getline(cin, method);
            while (method != "1" && method != "2" && method != "3"){ // validate encryption method
                cout << "Invalid encryption choice" << endl;
                displayEType();
            getline(cin, method);
            }
            Etype = stoi(method);
            
            
            
                switch(Etype){
                    case 1: // Layer 1
                        cout << "Successfully set encryption type to " << Etype << endl;
                        display13Encrypt();
                        getline(cin,meth);
                        
                        while (meth != "1" && meth != "2"){
                             cout << "Invalid encryption choice" << endl;
                            display13Encrypt();
                            getline(cin,meth);
                
                        }
                        method_choice = stoi(meth);
                        

                    break;
                    case 2: // Layer 2
                        cout << "Successfully set encryption type to " << Etype << endl;
                        
                    break;
                    case 3: // Chain
                        cout << "Successfully set encryption type to " << Etype << endl;
                        display13Encrypt();
                        getline(cin,meth);
                        
                        while (meth != "1" && meth != "2"){
                            cout << "Invalid encryption choice" << endl;
                            display13Encrypt();
                            getline(cin,meth);
                            
                        }
                       method_choice = stoi(meth);

                    break;
                        default: // invalid selection
                        cout << "Invalid encryption choice" << endl;
                        displayEType();
                        

                }

        break;
        case 5: // encrypt message
            if(key1=="" || key2=="" ||key_phrase=="" || (Etype != 1 && Etype != 2 && Etype !=3)){
                cout << "You cannot do this until you set both keys, keyphrase and choose an encryption method" << endl;
               
            }
            else{
            cout << "Enter your message to encrypt:" << endl;
            getline(cin, message);
                if (Etype == 1){
                    machine_encrypted_message = getLayer1MessageEncryption(message, method_choice, key1, key2);
                }
                else if( Etype ==2){
                    machine_encrypted_message= getLayer2MessageEncryption(message,key_phrase);
                }
                else {
                    machine_encrypted_message = getChainEncryption(message, method_choice, key1, key2, key_phrase);
                }
                cout << machine_encrypted_message << endl;
            

        break;
        case 6: // decrypt message
        if(key1=="" || key2=="" ||key_phrase=="" || (Etype != 1 && Etype != 2 && Etype !=3)){
                cout << "You cannot do this until you set both keys, keyphrase and choose an encryption method" << endl;
               
            }
        else{
            cout << "Enter your message to decrypt:" << endl;
            getline(cin, encrypted_message);
            if (Etype == 1){
                decrypted_message = getLayer1MessageDecryption(encrypted_message, method_choice, key1, key2);
            }
            else if( Etype ==2){
                decrypted_message= getLayer2MessageDecryption(encrypted_message, key_phrase);
            }
            else {
                decrypted_message = getChainDecryption(encrypted_message,method_choice, key1, key2, key_phrase);
            }
            cout << decrypted_message << endl;
            
        }

        break;
        case 7: // exit program
            cout << "Goodbye." <<endl;
            

        break;

        default: // invalid input
            cout << "Invalid Input" << endl;
            menuSelect = 0;
    }
    }
        }
     } while(menuSelect != 7);
   
   return 0;


}