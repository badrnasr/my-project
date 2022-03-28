#include <iostream>
using namespace std;

int main()
{
    char ch[6][6];
    ch[0][0]='-';
    cout<<"Please choose the operation: \n"<<"1- encrypt a message. \n"<<"2- decipher a message. \n";
    int choice;cin>>choice;
    cout<<"Enter the key Values:";
    for (int i=1;i<6;i++){
        char tmp;cin>>tmp;
        ch[0][i]=tmp;
        ch[i][0]=tmp;
    }
    char start='a';
    for(int i=1;i<6;i++){
        for(int j=1;j<6;j++){
            if(start=='j')start++;
            ch[i][j]=start;
            start++;
        }
    }
    switch (choice){
    case 1:
        {
            cout<<"Enter the message: ";
            string message;
            cin.ignore();
            getline(cin,message);
            string cipherText="";
            for(int i=0;i<message.length();i++){
                int flag=0;
                if(message[i]==' ')cipherText+=' ';
                for(int j=1;j<6;j++){
                    for(int k=1;k<6;k++) {
                        if (message[i] == ch[j][k] || (message[i]=='j' && ch[j][k]=='i')) {
                            cipherText += ch[j][0];
                            cipherText += ch[0][k];
                            flag=1;
                            break;
                        }
                    }
                    if (flag==1)break;
                }
            }
            cout<<"Cipher Text: "<<cipherText<<endl;
            break;
        }
    case 2:
        {
            cout<<"Enter the Cipher Text: ";
            string cipherText;
            cin.ignore();
            getline(cin,cipherText);
            string message;
            for(int i=0;i<cipherText.length();i+=2){
                if(cipherText[i]==' '){
                        message+=' ';
                        i--;
                        continue;
                }
                for(int j=1;j<6;j++){
                    if(cipherText[i]==ch[j][0]) {
                        for (int k = 1; k < 6; k++) {
                            if(cipherText[i+1]==ch[0][k]){
                                message+=ch[j][k];
                            }
                        }
                    }
                }
            }
            cout<<"Plain Text: "<<message<<endl;
            break;
        }
    default:
        break;
    }
    return 0;
}