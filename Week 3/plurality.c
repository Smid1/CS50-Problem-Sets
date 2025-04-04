#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool vote(string name);
void print_winner(void);

typedef struct {
    string name;
    int votes;
} candidate;

const int MAX = 9;
candidate candidates[MAX];
int quantCand;

int main(int argc, string argv[]) {
    quantCand = argc - 1;

    if (quantCand < 2) {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    } else if (quantCand > MAX) {
        printf("Max of candidates is %i", MAX);
    }

    for (int i = 0; i < quantCand; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voters = 0;

    do {
        voters = get_int("Number of voters: ");
        if (voters < 2) {
            printf("It is necessary at least 2 voters.\n");
        }
    } while (voters < 2);


    string voting;
    for (int i = 0; i < voters; i++) {
        voting = get_string("Vote: ");
        if (!vote(voting)) {
            printf("Invalid vote.\n");
        } 
    }

    print_winner();
}

bool vote(string name) {
    for (int i = 0; i < quantCand; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

void print_winner(void) {
    int highestNumber = 0;

    for (int i = 0; i < quantCand; i++) {
        if (candidates[i].votes > highestNumber) {
            highestNumber = candidates[i].votes;
        }
    }

    for (int i = 0; i < quantCand; i++) {
        if (candidates[i].votes == highestNumber) {
            printf("%s\n", candidates[i].name);
        }
    }
}
