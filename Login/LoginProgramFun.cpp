#include<iostream>
#include<istream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<regex>
#include<iomanip>
#include<map>
using namespace std;

struct members{
    string username;
    string password;
    string email;
    string phone;
    string password2;
};
// To cypher the password

members man;

string cypher (string w)
{
    // loop on every char and replace it with the Previouschar
    for (int i =0; i < w.length(); i++)
    {
        w[i]++;
    }
    return w;

}
// ____________________________________________________________________________________________________________________________________
// To view the password as star(*)
string HiddenPassword(string pass){
    char ch;
    ch=getch();
    bool Valid=true;
    while(Valid){
        // To remove a char press Backspace
        if(ch==8 && pass.length()!=0){
                cout<<"\b \b";
                pass.pop_back();
                ch=getch();
        }
        // if user want to stop press Enter
        else if(ch==13){
            Valid=false;
            break;
        }
        // print * when the user enter an char 
        // and save it in pass
        else{
            if(ch!=13){
                cout<<"*";
                pass+=ch;
                ch=getch();
            }
        }
    }
    return pass;
    
}
// ______________________________________________________________________________________________________________________________________
string StrengthOfPassword(){
    string pass;
    int strength=0,b=0;
    bool IsValid=true;
    while(IsValid){
        cout<<"Please Enter a strong password & more than 8 char : ";
        pass=HiddenPassword(pass);
        // check the pass is more than 8 or not 
        if(pass.length()>=8){
            // loop on the pass to check the strenght
            if(regex_search(pass,regex("[A-Z]+")))
                strength+=10;

            if(regex_search(pass,regex("[a-z]+")))
                strength+=10;

            if(regex_search(pass,regex("[0-9]+")))
                strength+=10;

            if(regex_search(pass,regex("[~`""!@#$%^&*()-_+={}[]|;:<>,./?/*]+")))
                strength+=10;

            IsValid=false;
        }
        else{
            cout<<"\nplease enter a password more than 8 char \n";
        }
    }
    // print to user if his password strong or not
    if(strength>=30){
        cout<<"\nYour password is very strong\n";
        return pass;
    }
    // if not repeat it a one more strong
    else{
        cout<<"\nYour password is weak\n";
        StrengthOfPassword();
    }
}
// _______________________________________________________________________________________________________________________________________
string RepeatThePassword(string pass1, string pass2){

    bool iscorrect=true;

    while(iscorrect){
        // get the password from the user then repeat it
        pass1 = StrengthOfPassword();
        cout<<"\nPlease repeat the password :\n";
        pass2=HiddenPassword(pass2);
        // if true print The password are identical
        if(pass1==pass2){
            cout<<"\nThe password are identical\n";
            iscorrect=false;
            return pass1;

        }
        // If not repeat it again 
        else{
            cout<<"The password are not identical\nplease enter the password again\n";
        }
    }

}
// ____________________________________________________________________________________________________________________________________
void registeration()
{

    string se, su, sp, sph;
    cout<<"Enter the following informations.\n";
    user:
    //checking availability:
    cout<<"Username: "; cin>>man.username;
    ifstream searchu("Database.txt");
    while(searchu>>su)
    {
        if(su==man.username)
        {
            cout<<"This username is already taken, try again.\n";
            goto user;
        }
    }
    searchu.close();
    //checking the username:
    regex correct_user("[-]*[a-zA-Z]+[-]*[a-zA-Z]+[-]*");
    regex_match(man.username,correct_user);
    if (regex_match(man.username,correct_user) != true)
    {
        cout<<"Error, the username is incorrect, try again.\n";
        cout<<"(NOTE: the username must be started by alphabet character and doesn't contain spaces.\n";
        goto user;
    }

    pass:
    //checking availability:
    // print at the rules of the password can be input
    cout << "Rules of strong password should user enter\n"
            "\n"
            "    At least 8 characters (required for your Muhlenberg password)—the more characters, the better\n"
            "    A mixture of both uppercase and lowercase letters\n"
            "    A mixture of letters and numbers \n"
            "    Inclusion of at least one special character, e.g., ! @ # ? ]\n";
    // get the password and store it in the struct
    man.password = RepeatThePassword(man.password , man.password2);

    ifstream searchp("Database.txt");
    while(searchp>>sp)
    {
        if(sp==man.password)
        {
            cout<<"This password is already taken, try again.\n";
            goto pass;
        }
    }

    searchp.close();

    emailaddress:
    //checking availability:
    cout<<"Email: ";
    cin>>man.email;
    ifstream searche("Database.txt");
    // chech if the email is not used or not
    while(searche>>se)
    {
        if(se==man.email)
        {
            cout<<"This email is already taken, try again."<<endl;
            goto emailaddress;
        }
    }
    searche.close();
    //checking the email (format)
    regex correct_email("[a-z|A-Z|0-9|.]+\\@[gmail|yahoo]+\\.com");
    regex_match(man.email,correct_email);
    // check if the email's format is not correct
    if (regex_match(man.email,correct_email) != true)
    {
        cout<<"Error, the email is incorrect, try again.\n";
        cout<<"(NOTE: the formula of the email --> [a-zA-z0-9.]+[@gmail|@yahoo].com)\n";
        goto emailaddress;
    }

    phone:
    cout<<"Phone number: "; cin>>man.phone;
    //checking availability:
    ifstream searchph("Database.txt");
    while(searchph>>sph)
    {
        if(sph==man.phone)
        {
            cout<<"This phone number is already taken, try again.\n";
            goto phone;
        }
    }
    searchph.close();
    //checking the number(format)
    regex correct_num("01[0-2|5]\\d{8}");
    regex_match(man.phone,correct_num);
    // check if the number's format is not correct
    if (regex_match(man.phone,correct_num) != true)
    {
        cout<<"\nError, the number is incorrect, try again.\n";
        cout<<"\n(NOTE: the number must start by '010' or '011' or '012' or '015' and the number must be 11 number.\n";
        goto phone;
    }
    // cypher the password
    string cyphered_password = cypher(man.password);
    ofstream reg("Database.txt",ios::app);
    reg<<man.username<< endl<<cyphered_password<< endl<<man.email<< endl<<man.phone<< endl<<"______________________"<<endl;

    cout<<"\nRegistration sucessful\n\n";


}
// ______________________________________________________________________________________________________________________________________
bool check_compatibility(string old_cyphered , string email)
{
    bool iscompatible;
    string search;
    ifstream text_file("Database.txt");
    string all_text;
    // read the text_file
    while(text_file >> search)
    {
        if (all_text == old_cyphered)
        {
            string savedpass = old_cyphered;
        }

        if(all_text == email)
        {
            string savedemail = email;
        }
        all_text +=search;
    }
    int begin = all_text.find(old_cyphered);
    int end = old_cyphered.length();
    int emailplace = all_text.find (email);
    if (begin+end == emailplace)
    {
        iscompatible = true;
        return iscompatible;
    }
    else{

        iscompatible = false;
        return iscompatible;}

}
// _______________________________________________________________________________________________________________________________________
void change_password()
{
    bool ispass , isemail;
    string old_password , email , new_password , new_password1 , sph ,se , search ,words, old_cyphered , new_cyphered;
    ifstream searche("Database.txt");
    ifstream searchph("Database.txt");
    ifstream searchcheck("Database.txt");
    fstream text_file("Database.txt");

    //infinite loop until the password change is valid
    while (true){
        // gat the email
        cout << "To change your password please enter : \n \n";
        cout << "Your email : \n ";
        cin >> email;
        // get the password
        cout << "Old Password : \n ";
        cin >> old_password;
        cout << "Rules of strong password should user enter\n"
                "\n"
                "    At least 8 characters (required for your Muhlenberg password)—the more characters, the better\n"
                "    A mixture of both uppercase and lowercase letters\n"
                "    A mixture of letters and numbers \n"
                "    Inclusion of at least one special character, e.g., ! @ # ? ]\n";
        // cypehr the password
        old_cyphered = cypher(old_password);
        new_cyphered = cypher (RepeatThePassword(man.password , man.password2));

        //compare new password with the re-written new password
        int temp3 = new_password.compare(new_password1);
        //check if the user is registered from before
        while (!searchph.eof()) {
            searchph >> sph;

            if (sph == old_cyphered) {
                ispass = true;
            }
        }

        while (!searche.eof())
        {
            searche >> se;

            if (se == email)
            {
                isemail = true;

            }

        }
        string temp;
        string all_text = "";
        int counter =0;
        while(text_file >> search)
        {
            all_text +=search + "\n";
        }

        if (check_compatibility( old_cyphered,email) == true)
        {
        int begin = all_text.find(old_cyphered);
        int end = old_cyphered.length();
        all_text.erase(begin,end);
        all_text.insert(begin , new_cyphered);
        std::fstream text_file;
        text_file.open("Database.txt", std::ofstream::out | std::ofstream::trunc);
        text_file << all_text;

        // tell the user if the password or not
        if ((temp3) == 0 && isemail == true && ispass == true && old_cyphered !=new_cyphered)
        {
            cout << "Password successfuly changed! \n";
            break;
        }
        else{
            cout << "Can't re-new the password! \n";
            cout << "Please make sure that the old password and email are correct, and that the re-newed password is typed the same twice!";
            break;
        }


    }


    }
}

// ________________________________________________________________________________________________________________________________________
void password_and_email()
{
    string password_match = man.password;
    string email_match = man.email;
    int counter=0;
    ifstream searche("Database.txt");
    ifstream searchph("Database.txt");

//infinite loop until login is in success
    while (true){
        string cyphered;
        string email;
        string password = "";
        // get email from user
        cout << "Please enter your ID and password : ";
        cout << "\n \n Email : ";
        cin >> email;
        // get password from user
        cout << "\n \n Password : ";
        password=HiddenPassword(password);
        cyphered = cypher(password);
        string sph , se ;
        bool ispass , isemail;
        //repeats the error of logging in maximum 3 times , then bans user
        if (counter < 3) {



            while (!searchph.eof()) {
                searchph >> sph;

                if (sph == cyphered) {
                    ispass = true;
                }
            }
            while (!searche.eof())
            {
                    searche >> se;
                    if (se == email) {
                        isemail = true;

                }
            }


        }
        // check if the login is vailed
        if (isemail == true && ispass == true && check_compatibility(cyphered ,email) == true)
        {
            cout << "\nSuccessful login , welcome!";
            break;
        }
        else {

                cout << "\nFailed login. Try again.\n";
                counter += 1;


            }

        if (counter == 3) {
            cout << "\nYou've attempted logging in 3 times! , you are now banned from this program.";
            break;

        }}
    searche.close();
    searchph.close();
    }



void login ()
{
  password_and_email();
}
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
