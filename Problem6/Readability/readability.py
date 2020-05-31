letters = 0
words = 0
sentences = 0
text = input("Text: ")
for i in range(len(text)):
    if ((text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z')):
        letters += 1
    elif text[i] == " ":
        words += 1
    elif (text[i] == '.' or text[i] == '?' or text[i] == '!'):
        sentences += 1
    
L = letters * 100 / (words + 1)
S = sentences * 100 / (words + 1)
index = 0.0588 * L - 0.296 * S - 15.8

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
