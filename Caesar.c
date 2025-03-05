#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions prototypes
bool onlydigits(string s);
char rotate(char c, int key);

int main(int argc, string argv[]) {
    // verify if the code`s execution is right
    if (argc != 2 || !onlydigits(argv[1])) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string text = get_string("Plaintext:  ");
    char ciphertext[strlen(text)];
    int key = atoi(argv[1]); // Converts the key to int

    for (int i = 0, lenght = strlen(text); i < lenght; i++) {
        ciphertext[i] = rotate(text[i], key);
    }

    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

// Function to verify if the argument has only digits
bool onlydigits(string s) {
    for (int i = 0, lenght = strlen(s); i < lenght; i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

// Function that changes the letter based on the key
char rotate(char c, int key) {
    if (isalpha(c)) {
        if (isupper(c)) {
            return (char)(((c - 'A' + key) % 26) + 'A'); // It takes the character and subtracts it by the "A" ASCII table value, then it sums it to the key and takes the module by 26, therefore getting it`s position, then, adds "A" ASCII table value again, so it gets its true ASCII value 
        } else {
            return (char)(((c - 'a' + key) % 26) + 'a'); // Does exactly the same as the prior one, but with lowercase letters
        }
    } else {
        return c;
    }
}
