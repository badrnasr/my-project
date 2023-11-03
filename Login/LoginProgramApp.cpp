// Program:     TextEditorApp.cpp
// Purpose:     Login App
//              take from user the data

/* Authors:     Tawfik Mohamed Khalil        id->20211024
                Badr Nasr Al-Din Al-Badri    id->20210086
                Yousef Abdallah Ahmed        id->20211117
                
*/
// Date:     27 April 2022
// Version: 1.0

#include "LoginProgramFun.h"
#include "LoginProgramFun.cpp"

int main(){
    string choice;
    // let the user to choose from choices
    cout << "Press (1) to Register\nPress(2) to Login\nPress(3) to change your old password : " ;
    cin >> choice   ;
    if (choice == "1")
    {
        registeration();
    }
    if (choice == "2")
    {
        login();
    }
    if (choice == "3")
    {
        change_password();
    }

    return 0;

}
