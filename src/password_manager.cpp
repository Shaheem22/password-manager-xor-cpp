#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// XOR-based encryption
string simpleEncrypt(const string &data, const string &key) {
    string encrypted = data;
    for (size_t i = 0; i < data.size(); i++) {
        encrypted[i] ^= key[i % key.size()];
    }
    return encrypted;
}

// XOR-based decryption
string simpleDecrypt(const string &encrypted, const string &key) {
    return simpleEncrypt(encrypted, key);
}

// Convert string to hex 
string toHex(const string &data) {
    stringstream hexStream;
    for (unsigned char c : data) {
        hexStream << hex << setw(2) << setfill('0') << (int)c;
    }
    return hexStream.str();
}

// Convert hex to string  
string fromHex(const string &hexData) {
    string result;
    for (size_t i = 0; i < hexData.length(); i += 2) {
        string byte = hexData.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
        result.push_back(chr);
    }
    return result;
}

// Password generator
string generatePassword(int length, bool useSpecialChars) {
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string numbers = "0123456789";
    const string specialChars = "!@#$%^&*()-_+=<>?/";

    string pool = letters + numbers;
    if (useSpecialChars) pool += specialChars;

    string password;
    srand(time(nullptr)); // Seed randomness

    for (int i = 0; i < length; i++) {
        password += pool[rand() % pool.size()];
    }

    return password;
}

int main() {
    string masterKey;
    cout << "Set your master key: ";
    cin >> masterKey;

    while (true) {
        cout << "\nMenu:\n1. Store Password\n2. Retrieve Password\n3. Generate Password\n4. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string site, password;
            cout << "Enter site/app name: ";
            cin >> site;
            cout << "Enter password: ";
            cin >> password;

            ofstream file("passwords.txt", ios::app);
            if (!file) {
                cerr << "Error opening file for writing!" << endl;
                continue;
            }

            string encrypted = simpleEncrypt(password, masterKey);
            string encoded = toHex(encrypted);
            file << site << " " << encoded << endl;
            file.close();
            cout << "Password stored for site: " << site << endl;

        } else if (choice == 2) {
            string site, line, storedPassword;
            cout << "Enter site/app name to retrieve: ";
            cin >> site;

            ifstream file("passwords.txt");
            if (!file) {
                cerr << "Error opening file for reading!" << endl;
                continue;
            }

            bool found = false;
            while (getline(file, line)) {
                istringstream iss(line);
                string storedSite, encodedPassword;
                iss >> storedSite >> encodedPassword;

                if (storedSite == site) {
                    found = true;
                    string encrypted = fromHex(encodedPassword);
                    storedPassword = simpleDecrypt(encrypted, masterKey);
                    break;
                }
            }
            file.close();

            if (found) {
                cout << "Password for " << site << ": " << storedPassword << endl;
            } else {
                cout << "No password found for the site/app!" << endl;
            }

        } else if (choice == 3) {
            int length;
            char specialCharChoice;
            cout << "Enter desired password length: ";
            cin >> length;
            cout << "Include special characters? (y/n): ";
            cin >> specialCharChoice;

            bool useSpecialChars = (specialCharChoice == 'y');
            string generatedPassword = generatePassword(length, useSpecialChars);
            cout << "Generated password: " << generatedPassword << endl;

        } else if (choice == 4) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
