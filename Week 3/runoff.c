#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int MAX_CANDIDATES = 9;
const int MAX_VOTERS = 100;

typedef struct {
    string name;
    int votes;
    bool eliminated;
} candidate;

bool vote (int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);


candidate candidates[MAX_CANDIDATES];
int preferences[MAX_VOTERS][MAX_CANDIDATES];

int candidatesNumber, votersNumber, necessaryVotes;

int main(int argc, string argv[]) {
    if (argc < 3 || argc > 10) {
        printf("Usage: ./runoff candidate1 candidate2... (up to %i)\n", MAX_CANDIDATES);
        return 1;
    }

    candidatesNumber = argc - 1;

    do {
        votersNumber = get_int("Number of voters: ");

        if (votersNumber < 2 || votersNumber > MAX_VOTERS)
            printf("The number of voters must be between 2 and %i.\n", MAX_VOTERS);
    } while (votersNumber < 2 || votersNumber > MAX_VOTERS);

    for (int i = 0; i < candidatesNumber; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    string voteName;
    for (int i = 0; i < votersNumber; i++) {
        for (int j = 0; j < candidatesNumber; j++) {
            voteName = get_string("Rank %i: ", j + 1);
            if(!vote(i, j, voteName)) {
                printf("Invalid vote.\n");
                return 1;
            }
        }

        printf("\n");
    }

    necessaryVotes = (votersNumber / 2) + 1;

    do {
        tabulate();

        if (print_winner()) {
            break;
        }

        if (is_tie(find_min())) {
            break;
        }

        eliminate(find_min());
    } while (true);

    return 0;
}

bool vote(int voter, int rank, string name) {
    for (int i = 0; i < candidatesNumber; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

void tabulate(void) {
    for (int i = 0; i < votersNumber; i++) {
        for (int j = 0; j < candidatesNumber; j++) {
            if (!candidates[preferences[i][j]].eliminated) {
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }

    }
}

bool print_winner(void) {
    for (int i = 0; i < candidatesNumber; i++) {
        if (candidates[i].votes >= necessaryVotes) {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

int find_min(void) {
    int min;

    for (int i = 1; i < candidatesNumber; i++) {
        if (candidates[i].votes < min && !candidates[i].eliminated) {
            min = candidates[i].votes;
        }
    }

    return min;
}

bool is_tie(int min) {
    for (int i = 0; i < candidatesNumber; i++) {
        if (candidates[i].votes != min && !candidates[i].eliminated) {
            return false;
        }
    }

    printf("Tie.\n");
    return true;
}

void eliminate(int min) {
    for (int i = 0; i < candidatesNumber; i++) {
        if (candidates[i].votes == min) {
            candidates[i].eliminated = true;
        }
    }
}
