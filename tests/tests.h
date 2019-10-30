#ifndef KASISKI_EXAMINATION_TESTS_H
#define KASISKI_EXAMINATION_TESTS_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <set>
#include "../encoder.h"
#include "../kasiski.h"

using namespace std;

void test(const string &key, const string &in, const string &out) {
    ifstream fin;
    fin.open(in);

    ofstream fout;
    fout.open(out);

    Encoder encoder(key);

    string message;
    string s;
    while(fin >> s) {
        message += s;
    }

    string encrypted_message = encoder.encode(message);
    kasiski kasiski(encrypted_message);

    fout << "------------------------------\n";
    fout << "Key = " << key << endl;
    //fout << "Message:\n" << message << endl;
    //fout << "Encrypted message:\n" << encrypted_message << endl;
    fout << "Calculated length of key = " << kasiski.get_key_length() << endl;
    fout << ((kasiski.get_key_length() == key.size()) ? "SUCCESS" : "FAILED") << endl << endl;
    fout << "==============================\n\n\n";
}

string gen_key(size_t n) {
    set<int> used;
    string key(n, ' ');

    for (int i = 0; i < n; ++i) {
        while (true) {
            int cur = rand() % 26;

            if (used.count(cur) == 0) {
                used.insert(cur);
                key[i] = 'A' + cur;
                break;
            }
        }
    }

    return key;
}

void tests() {
    for (size_t i = 1; i < 10; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            string key = gen_key(i);

            string fout = "test-";
            fout += char('0' + i);
            fout += '-';
            fout += char('0' + j);

            test(key, "Harry_Potter", fout);
        }
    }

    for (size_t i = 10; i < 15; ++i) {
        string key = gen_key(i);

        string fout = "test2-1";
        fout += char('0' + i - 10);

        test(key, "HPMOR", fout);
    }
}

#endif //KASISKI_EXAMINATION_TESTS_H
