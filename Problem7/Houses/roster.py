from cs50 import SQL
from sys import argv, exit
import csv

# check command-line arguments
if len(argv) != 2:
    print("Usage: python roster.py house")
    exit(1)

# set up a database connection
db = SQL("sqlite:///students.db")

# query database for all students in house
student = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

# print out each student's full name and birth year
for column in student:
    if column['middle'] == None:
        print("%s %s, born %d" % (column['first'], column['last'], column['birth']))
    else:
        print("%s %s %s, born %d" % (column['first'], column['middle'], column['last'], column['birth']))
