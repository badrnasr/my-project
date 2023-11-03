#ifndef LOGIN_H
#define LOGIN_H
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
// ________________________________________________________
// stract of data
struct data{
    string username;
    string password;
    string email;
    string phone;
    string password2;
};
// _________________________________________________________
// Variable
data user;
// _________________________________________________________
// Functions
string cypher (string w);
string HiddenPassword(string pass);
string StrengthOfPassword();
string RepeatThePassword(string pass1, string pass2);
void registeration();
bool check_compatibility(string old_cyphered , string email);
void change_password();
void password_and_email();
void login ();
// ________________________________________________________
#endif