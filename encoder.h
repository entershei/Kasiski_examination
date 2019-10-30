#ifndef KASISKI_EXAMINATION_ENCODER_H
#define KASISKI_EXAMINATION_ENCODER_H

#include <utility>

using namespace std;

struct Encoder {

    Encoder(string key) : key(move(key)) {};

    string encode(const string &message) {
        string encrypted_message(message.size(), ' ');
        for (int i = 0; i < message.size(); ++i) {
            encrypted_message[i] = (message[i] + key[i % key.size()]) % 26 + 'A';
        }

        return encrypted_message;
    }

private:
    // key = [A..Z]+
    string key;
};

#endif //KASISKI_EXAMINATION_ENCODER_H
