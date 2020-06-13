from cs50 import SQL
from sys import argv, exit
import csv

# check command-line arguments
if len(argv) != 2:
    print("Usage: python import.py filename.csv")
    exit(1)

# open csv file given by command-line argument
csvFile = open(argv[1], "r")
reader = csv.reader(csvFile)

# set up a database connection
db = SQL("sqlite:///students.db")

# insert each student into the students table of students.db
for row in reader:
    if len(row[0].split()) == 2:
        firstLast = row[0].split()
        firstName = firstLast[0]
        lastName = firstLast[1]
        home = row[1]
        year = row[2]
        db.execute("INSERT INTO students (first , last, house, birth) VALUES (?, ?, ?, ?)", firstName, lastName, home, year)

    elif len(row[0].split()) == 3:
        firstMidLast = row[0].split()
        firstName = firstMidLast[0]
        middleName = firstMidLast[1]
        lastname = firstMidLast[2]
        home = row[1]
        year = row[2]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                   firstName, middleName, lastname, home, year)
