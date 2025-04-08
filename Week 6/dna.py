import csv
import sys

# T C A G

# Name     AGATC    AATG    TATC
# Alice      28      42      14
# Bob        17      22      19
# Charlie    36      18      25

# name,AGATC,AATG,TATC
# Alice,28,42,14
# Bob,17,22,19
# Charlie,36,18,25

#reader - sequence of lists
#DictReader - sequence of dictionaries
#sys.argv - 1 csv file 2 dna sequence
#f = open(filename) read using f.read

# int(string) string[i:j]

def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py file.csv file.txt")
        return

    # Read database file into a variable (csv file)
    rows = []
    with open(sys.argv[1]) as database:
        reader = csv.DictReader(database)
        for row in reader:
            rows.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequence:
        dna = sequence.read()

    # Find longest match of each STR in DNA sequence
    AGATC = longest_match(dna, "AGATC")
    AATG = longest_match(dna, "AATG")
    TATC = longest_match(dna, "TATC")

    # Check database for matching profiles
    match = 0

    for row in rows:
        if int(row["AGATC"]) == AGATC:
            if int(row["AATG"]) == AATG:
                if int(row["TATC"]) == TATC:
                    match = row["name"]
                    break

    # If matches print the match, if no matches print no match
    if match != 0:
        print(match)
    else:
        print("No match")

    return

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
