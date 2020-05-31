from sys import argv, exit
import csv


def main():
    if len(argv) != 3:
        print("Usage: python dna_str.py data.csv sequence.txt")
        exit(1)

    csv_file = open(argv[1], "r")
    txt_file = open(argv[2], "r")

    dna_str = txt_file.read()

    count = [0, 0, 0, 0, 0, 0, 0, 0]
    count[0] = get_max("AGATC", dna_str)
    count[1] = get_max("TTTTTTCT", dna_str)
    count[2] = get_max("AATG", dna_str)
    count[3] = get_max("TCTAG", dna_str)
    count[4] = get_max("GATA", dna_str)
    count[5] = get_max("TATC", dna_str)
    count[6] = get_max("GAAA", dna_str)
    count[7] = get_max("TCTG", dna_str)

    smallList = [str(count[0]), str(count[2]), str(count[5])]
    largeList = [str(count[0]), str(count[1]), str(count[2]), str(count[3]),
                 str(count[4]), str(count[5]), str(count[6]), str(count[7])]

    reader = csv.reader(csv_file)
    for row in reader:
        if row[1:] == smallList:
            print(row[0])
            exit(0)
        if row[1:] == largeList:
            print(row[0])
            exit(0)
    print("No match")


def get_max(nucleotid, dna_string):

    repeat = dna_string.count(nucleotid)
    if repeat == 0:
        max_repeat = 0
    else:
        for max_repeat in range(repeat, 0, -1):
            if nucleotid * max_repeat in dna_string:
                break
    return max_repeat


main()
