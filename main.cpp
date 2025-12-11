// Modules
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <openssl/sha.h>
using namespace std;


// Variables
char outputBuffer[64];
int choose;
int result;
string name, password;


// Create User
int new_user(string name, string password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
    FILE* dosya=fopen("account.txt", "a");

    fprintf(dosya, "%s:%s\n", name.c_str(), outputBuffer);
    fclose(dosya);

    return 1;
}

// Login User
int login_user(string name, string password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;

    FILE* dosya = fopen("account.txt", "r");
    if (dosya == nullptr) {
        printf("Dosya açılamadı!\n");
        return 0;
    }

    char satir[256];
    while (fgets(satir, sizeof(satir), dosya)) {
        string satirStr(satir);
        size_t ayirici = satirStr.find(':');
        if (ayirici != string::npos) {
            string dosyaName = satirStr.substr(0, ayirici);
            string dosyaPassword = satirStr.substr(ayirici + 1);
            dosyaPassword.erase(remove(dosyaPassword.begin(), dosyaPassword.end(), '\n'), dosyaPassword.end());

            if (dosyaName == name && dosyaPassword == outputBuffer) {
                fclose(dosya);
                return 1;
            }
        }
    }

    fclose(dosya);
    return 0;
}



// Main Code
int main() {
    system("CLS");
    cout << "0. Register\n1. Login\n\n>>> ";
    cin >> choose;

    system("CLS");
    cout << "Username >> ";
    cin >> name;

    system("CLS");
    cout << "Password >> ";
    cin >> password;
    system("CLS");

    switch (choose){
        case 0:

            result=new_user(name, password);

            if (result) {
                cout << "Registiration Successful!" << endl;
            } else {
                cout << "Something Went Wrong!" << endl;
            };

            break;

        case 1:
            
            result=login_user(name, password);
            
            if (result) {
                cout << "Login Successful!" << endl;
            } else {
                cout << "Login Unsuccessful!" << endl;
            }

            break;
        
        default:
            break;
    }
}