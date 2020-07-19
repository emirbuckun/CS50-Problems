import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import credit
import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


# Main page
@app.route("/")
@login_required
def index():
    sum_of_shares_price = 0
    # Get data from accounts table
    rows = db.execute("""SELECT symbol, SUM(shares) FROM accounts
                            JOIN users ON id == user_id
                            WHERE user_id == :user_id
                            AND symbol != "CASH"
                            GROUP BY symbol
                            HAVING SUM(shares) > 0""", user_id = session["user_id"])

    # Get info from lookup function which is in helpers.py
    for row in rows:
        quoted = lookup(row["symbol"])
        price = quoted["price"]
        total_price = float(quoted["price"]) * float(row["SUM(shares)"])
        row["name"] = quoted["name"]
        row["price"] = quoted["price"]
        row["total_price"] = round(total_price)
        sum_of_shares_price += total_price

    # Get user's total cash from users table
    funds = db.execute("SELECT cash FROM users WHERE id == :user_id", user_id = session["user_id"])
    cash = round(funds[0]["cash"])

    total_value = round(cash + sum_of_shares_price)
    return render_template("index.html", rows = rows, cash = cash, total_value = total_value)


# Change user's password
@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changepassword():
    if request.method == "GET":
        return render_template("changepassword.html")
    else:
        old_password = request.form.get("old_password")
        if not old_password:
            return apology("You must provide the old password.")

        rows = db.execute("SELECT hash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # Ensure that old password is true
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], old_password):
            return apology("Invalid password")

        new_password = request.form.get("new_password")
        if not new_password:
            return apology("Please provide a new password.")

        confirm_password = request.form.get("confirm_password")
        if new_password != confirm_password:
            return apology("The password do not match.")

        # Update the user's new password in users table
        password_hash = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash = :password_hash WHERE id = :user_id", user_id=session["user_id"], password_hash = password_hash)

        flash("Password Changed")
        return redirect("/")

    return apology("Change Password is not working.")


# Add cash from credit card
@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    if request.method == "GET":
        return render_template("addcash.html")
    else:
        credit_card_number = int(request.form.get("number"))
        amount = float(request.form.get("amount"))

        # Check for valid or invalid credit card number
        is_valid = credit.luhn(credit_card_number)
        if not is_valid:
            return apology("Invalid Credit Card.")

        # Get user current cash amount
        funds = db.execute("SELECT cash FROM users WHERE id == :user_id", user_id = session["user_id"])
        cash = float(funds[0]["cash"])

        # Add cash to current cash of the user
        cash = cash + amount

        # Update the user's cash amount in users table
        db.execute("UPDATE users SET cash = :cash WHERE id == :user_id", cash = cash, user_id = session["user_id"])

        # Get current time information
        date_time = datetime.datetime.now()
        date_time = date_time.strftime("%Y-%m-%d %H:%M:%S")

        # Insert the money transaction to accounts table
        db.execute("""INSERT INTO accounts (user_id, symbol, date_time, total_price)
                        VALUES (:user_id, :symbol, :date_time, :total_price)""",
                        user_id = session["user_id"], symbol = "CASH",
                        date_time = date_time, total_price = amount)

        flash("Cash Added.")
        return redirect("/")

    return apology("Add Cash is not working.")


# Buy products by giving the symbol name
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        quoted = lookup(symbol)
        if not quoted:
            return apology("Invalid Symbol.")
        if not shares:
            return apology("Share must be minimum 1.")

        funds = db.execute("SELECT cash FROM users WHERE id == :user_id", user_id = session["user_id"])
        total_price = float(quoted["price"])*float(shares)
        cash = float(funds[0]["cash"])

        # Check for there are enough money to buy or not
        if total_price > cash:
            return apology("Can't Afford.")

        cash = cash - total_price
        db.execute("UPDATE users SET cash = :cash WHERE id == :user_id", cash = cash, user_id = session["user_id"])

        date_time = datetime.datetime.now()
        date_time = date_time.strftime("%Y-%m-%d %H:%M:%S")

        db.execute("INSERT INTO accounts VALUES (:user_id, :symbol, :shares, :date_time, :price, :total_price)",
                    user_id = session["user_id"], symbol = symbol,
                    shares = shares, date_time = date_time,
                    price = quoted["price"], total_price = total_price)

        flash("Bought.")
        return redirect("/")

    return apology("Buy is not working.")


# Show history of things done
@app.route("/history")
@login_required
def history():
    # Get all data from accounts table
    rows = db.execute("""SELECT * FROM accounts
                            JOIN users ON id == user_id
                            WHERE user_id == :user_id""", user_id = session["user_id"])

    return render_template("history.html", rows = rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


# Quote for a product with symbol
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")

    else:
        symbol = request.form.get("symbol")
        quoted = lookup(symbol)
        if not quoted:
            return apology("Invalid Symbol")
        return render_template("quoted.html", name=quoted["name"], symbol=quoted["symbol"], price=quoted["price"])

    return apology("Quote is not working.")


# Register to the application
@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else :
        username = request.form.get("username")
        if not username:
            return apology("You must provide a username.")
        username_check = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(username_check) != 0:
            return apology("This username is already taken.")

        password = request.form.get("password")
        if not password:
            return apology("You must provide a password.")

        confirmation = request.form.get("confirmation")
        if not confirmation or password != confirmation:
            return apology("You must provide a confirmation password.")
        if password != confirmation:
            return apology("The password do not match.")

        # Hash the given password for security
        hash = generate_password_hash(password)

        # Insert the hashed password to users table
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=hash)

        user = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        session["user_id"] = user[0]["id"]

        flash("Registered")
        return redirect("/")

    return apology("Register is not working.")


# Sell any product you own
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        # Get all products owned by the user
        rows = db.execute("""SELECT symbol FROM accounts
                                JOIN users ON id == user_id
                                WHERE user_id == :user_id
                                AND symbol != "CASH"
                                GROUP BY symbol
                                HAVING SUM(shares) > 0""", user_id = session["user_id"])

        return render_template("sell.html", rows = rows)
    else:
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        quoted = lookup(symbol)
        if not quoted:
            return apology("Invalid Symbol.")
        if not shares:
            return apology("You must sell minimum 1 share.")

        # Get users symbol input and learn the total shares of the product
        rows = db.execute("""SELECT SUM(shares) FROM accounts
                                JOIN users ON id == user_id
                                WHERE user_id == :user_id
                                AND symbol == :symbol
                                GROUP BY symbol""", user_id = session["user_id"], symbol = symbol)

        current_shares = float(rows[0]["SUM(shares)"])
        shares = float(shares)

        # Check if there are enough products
        if shares > current_shares:
            return apology("You don't have so much shares.")

        total_sell_price = float(quoted["price"]) * float(shares)

        funds = db.execute("SELECT cash FROM users WHERE id == :user_id", user_id = session["user_id"])
        cash = float(funds[0]["cash"])

        cash = cash + total_sell_price
        db.execute("UPDATE users SET cash = :cash WHERE id == :user_id", cash = cash, user_id = session["user_id"])

        date_time = datetime.datetime.now()
        date_time = date_time.strftime("%Y-%m-%d %H:%M:%S")

        db.execute("INSERT INTO accounts VALUES (:user_id, :symbol, :shares, :date_time, :unit_price, :total_price)",
                    user_id = session["user_id"], symbol = symbol,
                    shares = -shares, date_time = date_time,
                    unit_price = -float(quoted["price"]), total_price = -total_sell_price)

        flash("Sold.")
        return redirect("/")

    return apology("Sell is not working.")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)