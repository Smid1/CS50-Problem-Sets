#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int MAX_CANDIDATES = 9;

typedef struct {
    int winner;
    int loser;
} pair;

int candidate_count;
int pair_count;

string candidates[MAX_CANDIDATES];
pair pairs[(MAX_CANDIDATES * (MAX_CANDIDATES - 1)) /2];
int preferences[MAX_CANDIDATES][MAX_CANDIDATES];
bool locked[MAX_CANDIDATES][MAX_CANDIDATES];

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs();
void sort_pairs();
void lock_pairs();
void print_winner();

int main(int argc, string argv[]) {
    if (argc < 3 || argc > MAX_CANDIDATES + 1) {
        printf("Usage: ./tideman candidate1 candidate2... (up to %i)\n", MAX_CANDIDATES);
        return 1;
    }

    candidate_count = argc - 1;
    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
    }

    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            locked[i][j] = false;
        }
    }

    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            preferences[i][j] = 0;
        }
    }

    int voters_count = get_int("Number of Voters: ");

    for (int i = 0; i < voters_count; i++) {
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++) {
            string vote_name = get_string("Rank %i: ", j + 1);

            if (!vote(j, vote_name, ranks)) {
                printf("Invalid vote.\n");
                return 2;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}

bool vote(int rank, string name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i], name) == 0) {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

void record_preferences(int ranks[]) {
    for (int i = 0; i < candidate_count - 1; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
}

void add_pairs() {
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                pair_count++;
            } else if (preferences[i][j] < preferences[j][i]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;

                pair_count++;
            }
        }
    }
}

void sort_pairs() {
    for (int i = 0; i < pair_count; i++) {
        for (int j = i + 1; j < pair_count; j++) {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser]) {
                pair aux = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = aux;
            }
        }
    }
}

void lock_pairs() {
    bool isPointed = false;

    for (int i = 0; i < pair_count; i++) {
        isPointed = false;

        for (int j = 0; j < pair_count; j++) {
            if (locked[j][pairs[i].winner]) {
                isPointed = true;
                break;
            }
        }

        if (isPointed == false) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

void print_winner() {
    bool isWinner = true;

    for (int i = 0; i < candidate_count; i++) {
        isWinner = true;

        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                isWinner = false;
                break;
            }
        }

        if (isWinner) {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
