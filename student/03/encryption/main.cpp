#include <iostream>
#include <cctype>
using namespace std;

int main() {
    string salaus;
    cout << "Enter the encryption key: ";
    cin >> salaus;
    string::size_type apu = 0;
    apu = salaus.length();
    if (apu != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return 1;
    }
    for (int i = 0; i < 26; ++i) {
        if (islower(salaus[i])) {
        } else {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return 1;
        }
    }
    for ( char kirjain = 'a'; kirjain < 'z'; ++kirjain ) {
        apu = salaus.find(kirjain);
        if ( apu == string::npos ) {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return 1;
        }
    }
    string salatava;
    string aakkoset = "abcdefghijklmnopqrstuvwxyz";
    cout << "Enter the text to be encrypted: ";
    cin >> salatava;
    string::size_type pituus = 0;
    pituus = salatava.length();
    int pituusi = pituus;
    cout << "Encrypted text: ";
    for (int i = 0; ++i;) {
        char kirjain = salatava[i - 1];
        apu = aakkoset.find(kirjain);
        char numero = salaus[apu];
        cout << numero;
        if (i == pituusi) {
            break;
        }
    }
    return 0;
}
