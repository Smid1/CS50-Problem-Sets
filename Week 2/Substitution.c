#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int verifykey(string key);
char substitution(char c, string key);

int main(int argc, string argv[]) {
    if (argc != 2) { // Verify if it has only 1 argument (the first is the program`s name)
        printf("Usage: ./substitution key\n"); 
        return 1;
    } else if (strlen(argv[1]) != 26) { // Verify if it`s 26 characters long
        printf("Key must contain 26 characters.\n");
        return 1;
    } else {
        if (verifykey(argv[1]) == 1)
            return 1;
    }

    string key = argv[1];
    string text = get_string("Plaintext: ");
    char ciphertext[26];
    int letterValues[26];

    for (int i = 0; i < 26; i++) {
        ciphertext[i] = substitution(text[i], key);
    }

    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}


int verifykey(string key) {
    for (int i = 0; i < 26; i++) {
        if (isdigit(key[i]) || ispunct(key[i])) { // Verify if it has only letters
            printf("Key must only contain alhphabetic characters.\n");
            return 1;
        } else {
            for (int j = 0; j < 26; j++) { // O(n^2) run to verify if it has repeated characters
                if (i != j && key[i] == key[j]) {
                    printf("Key must not contain repeated characters\n");
                    return 1;
                }
            }
        }
    }

    return 0;
}

char substitution(char c, string key) {
    if (!isalpha(c)) {
        return c;
    } else if (isupper(c)){
        return toupper(key[c - 'A']); // Gets the letter that is in the character alphabet position and send`s it uppercase
    } else {
        return tolower(key[c - 'a']); // Does the same, but lowercase
    }
}

