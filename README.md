# CS50 Problem Sets
This repository contains a set of problems of each week of the 2025 CS50 Harvard program.

Those problems are related to each week content and made for training coding.

Program content:
  - Week 0 - Scratch
  - Week 1 - C
  - Week 2 - Arrays
  - Week 3 - Algorithms
  - Week 4 - Memory
  - Week 5 - Data Structures
  - Week 6 - Python
  - Artificial Intelligence
  - Week 7 - SQL
  - Week 8 - HTML, CSS and JavaScript
  - Week 9 - Flask
  - Week 10 - Cybersecutiry (2024) and The End (2025)

### Week 1 - Credit
The purpose is to write a program that prompts the user for a credit card number and then reports whether it is a valid American Express, MasterCard, or Visa card number, per the definitions of each’s format herein.

Also, before that, there was another problem to be resolved for those who were not so comfortable programming, I solved it as well. However, as it was too simple (code a program that gives the minimum amount of coins to give as a change of a <$1 buy) I chose not to put in here.

### Week 2 - Scrabble
Now time we had to write a program about the Scrabble game.

For those that are unfamiliar with Scrabble (as I was), it is a game that gives a certain score for each player's words based on the values of each letter.
The program should do exactly what the game is all about by typing the player's words, and then prompt who won or if it was a tie.

### Week 2 - Caesar
This time the program should enable you to encrypt messages using Caesar’s cipher (a cypher based on a key and each letter has a value, by adding the key value to each letter). 

At the time the user executes the program, they should decide, by providing a command-line argument, what the key should be in the secret message they’ll provide at runtime.

### Week 2 - Substitution
Now we have to encrypt messages again, but now, we provide a command-line argument that will be the entire key.

By providing, for exemple, the key = YTNSHKVEFXRBAUQZCLWDMIPGJO, the message is encripted following the sequence, where:
- A = Y
- B = T
- C = C
...

### Week 3 - Plurality
On this exercise we need to create a program simulating an election.

Based on a certain set of candidates, the votes should be computaded each time the candidate`s name is tiped.
The candidate with most votes win.

### Week 3 - Runoff
Now, continuing with elections, now all voters can rank their prefereces over each candidate.

For exemple, if the candidates are: Alice, Bob and Charlie, the voter could rank them like:
1 - Alice
2 - Bob
3 - Charlie

That way, they can express who they would prefer. This should help in case that a tie happens, as we can exclude the least voted and see who is prefered over who from the least voted electors.

### Week 3 - Tideman
Again, there`s also some problems with runoff. For instance, it can happen that Alice loose agains Bob in an runoff election, but seeing the votes, she might won if the competition was a head to head.

Considering those votes:

Vote 1:    Vote 2:    Vote 3:    Vote 4:    Vote 5:    Vote 6:    Vote 7:    Vote 8:    Vote 9:

Alice      Alice      Bob        Bob        Bob        Charlie    Charlie    Charlie    Charlie

Charlie    Charlie    Alice      Alice      Alice      Alice      Alice      Alice      Bob

Bob        Bob        Charlie    Charlie    Charlie    Bob        Bob        Bob        Alice


In an Plurality or Runoff vote system, Charlie would be the winner. But, if we analyse it, Alice would win if it was head to head.

Plurality: Alice - 2, Bob - 3, Charlie - 4

Runoff: Charlie would win as he would be the second most voted

Head to head: Alice > Charlie - 5, Alice > Bob: 5, Bob > Alice: 4, Bob > Charlie: 3, Charlie > Alice: 4, Charlie > Bob: 6

The Tideman algorith takes the head to head competition and consider the winner of it as the true winner (Condorcet Winner).

### Week 4 - Volume
Week 4 was focused on handling files, pointers and dynamic memory allocation.

Here is a algorithm to increase or decrease a WAV file`s volume, simple as that.

### Week 4 - Filter
Now images! This basically adds filters to BMP images using command line arguments.

### Week 4 - Recover
Lastly, using JPEG images. This algorithm recovers lost images that may be excluded, as removing files always leaves traces.

### Week 5 - Inheritance
This week was focused on data structures and this exercise simulates a blood type inheritance. 

That is done by passing a number of generations on a family that should be simulated, in a way that the first generation blood type alleles would be randomly generated and all subsequent member's alleles would be calculated based on that ones.

### Week 5 - Speller
The second exercise from week 5 was way more focused on data structures. For instance, I had to create a hash function to work in a hash table of words, which would be used as a dictionary to verify if all words in a text are spelled correctly.

The goal was to make a hash function as fast as possible, without copying it from any other source, in another words, I should create it.

After that, we would compare our hash function to CS50's staffs' own.

### Week 6 - Training Python
This week was focused on learning Python, so most of the exercises were the similar to the ones in C, but as expected, in Python.

### Week 6 - DNA
On DNA I had to create a program that would read a dna sequence and see if it matches to the dna of someone in a database, looking for the same amount of STRs

### Artificial Intelligence Week
This week was a event focused more on explaining how an AI works, in a language understandable even to non tech area people. So, no exercises this time.

### Following weeks are being made...
