#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Functions prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman(int letters, int words, int senteces);

int main(void) {
    string text = get_string("Text: "); // Gets the text
    int letters = count_letters(text), words = count_words(text), sentences = count_sentences(text); // Gets the amount of letters, words and sentences
    int grade = coleman(letters, words, sentences); // Calculate the grade

    // Program output
    if (grade < 1) {
        printf("Before Grade 1\n");
    } else if (grade >= 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text) {
    int count = 0;

    // Run through the array and count every letter
    for (int i = 0, lenght = strlen(text); i < lenght; i++) {
        if (isalpha(text[i])) {
            count++;
        }
    }

    return count;
}

int count_words(string text) {
    int count = 0;

    // Run through the array and count every word
    for (int i = 0, lenght = strlen(text); i < lenght; i++) {
        if(isspace(text[i])) {
            count++;
        }
    }

    return count + 1; // Return +1 because the last word is not computed due to not having an empty space after it.
}

int count_sentences(string text) {
    int count = 0;

    // Run through the array and count every sentence
    for (int i = 0, lenght = strlen(text); i < lenght; i++) {
        if(text[i] == '.' || text[i] == '!' || text[i] == '?') {
            count++;
        }
    }

    return count;
}

int coleman(int letters, int words, int sentences) {
    float L = ((float)letters / words) * 100; // Average of letters per 100 words
    float S = ((float)sentences / words) * 100; // Average of sentences per 100 words

    return round(0.0588 * L - 0.296 * S - 15.8); // Coleman formula to get the text grade
}
