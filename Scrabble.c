#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Array with each letter points
const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int word_score(string word);

int main(void) {
    string word1 = get_string("Player 1: "), word2 = get_string("Player 2: "); // Gets each player`s words
    int score1 = word_score(word1), score2 = word_score(word2); // Gets each player`s score

    // Verify who won
    if (score1 > score2) {
        printf("Player 1 wins!");
    } else if (score2 > score1){
        printf("Player 2 wins!");
    } else {
        printf("Tie!");
    }
}

// Function to calculate each player`s score
int word_score(string word) {
    int score = 0;

    for (int i = 0, lenght = strlen(word); i < lenght; i++) {
        if (isupper(word[i])) {
            score += POINTS[word[i] - 'A'];
        } else if (islower(word[i])) {
            score += POINTS[word[i] - 'a'];
        }
    }

    return score;
}
