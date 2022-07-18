# TODO
from sys import exit

text = input("Text: ")
words = 0
letters = 0
sentences = 0

words = len(text.split())
for char in text:
    if char.isalpha():
        letters += 1
    if char == "." or char == "!" or char == "?":
        sentences += 1

L = letters / words * 100
S = sentences / words * 100
grade = round(0.0588 * L - 0.296 * S - 15.8)

if grade < 1:
    print("Before Grade 1")
    exit(0)

if grade > 15:
    print("Grade 16+")
    exit(0)
print("Grade {}".format(grade))
exit(0)