from cs50 import get_string
import re

text = get_string("Text: ")

words = text.split()
word_count = len(words)

letters = re.findall(r'[a-zA-Z]', text)
letter_count = len(letters)

sentences = re.findall(r'[.!?]', text)
sentence_count = len(sentences)

L = (letter_count / word_count) * 100
S = (sentence_count / word_count) * 100

x = round(0.0588 * L - 0.296 * S - 15.8)

if x < 1:
    print("Before Grade 1")
elif x >= 16:
    print("Grade 16+")
else:
    print(f"Grade {x}")
