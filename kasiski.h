#ifndef KASISKI_EXAMINATION_KASISKI_H
#define KASISKI_EXAMINATION_KASISKI_H

#include <map>
#include <vector>

struct kasiski {
    explicit kasiski(string encrypted_message) : encrypted_message(std::move(encrypted_message)) {
        count_key_length();
    };

    int get_key_length() {
        return key_length;
    }
private:
    void count_key_length() {
        map<string, vector<int>> suffixes;

        for (int i = 0; i < encrypted_message.size() - 8; ++i) {
            string suffix;

            for (int j = 0; j < 8; ++j) {
                suffix += encrypted_message[i + j];
            }

            suffixes[suffix].push_back(i);
        }

        vector<int> dividers;
        for (auto trigram : suffixes) {
            for (int i = 0; i < trigram.second.size(); ++i) {
                for (int j = i + 1; j < trigram.second.size(); ++j) {
                    size_t pos_i = trigram.second[i];
                    size_t pos_j = trigram.second[j];
                    if (pos_j - pos_i > 2) {
                        dividers.push_back(pos_j - pos_i);
                    }
                }
            }
        }

        if (dividers.size() < 2) {
            key_length = -1;
            return;
        }

        int gcd = find_gcd(dividers[0], dividers[1]);
        for (int i = 2; i < dividers.size(); ++i) {
            gcd = find_gcd(gcd, dividers[i]);
        }

        key_length = gcd;
    }

    int find_gcd(int a, int b) {
        return b ? find_gcd(b, a % b) : a;
    }

    string encrypted_message;
    int key_length = -1;
};

#endif //KASISKI_EXAMINATION_KASISKI_H
