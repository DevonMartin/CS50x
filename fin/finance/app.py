import os

from collections import deque
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    id = session["user_id"]
    rows = db.execute("SELECT * FROM holdings WHERE id = ? ORDER BY symbol", id)
    for row in rows:
        quote = lookup(row["symbol"])
        row["name"] = quote["name"]
        row["price"] = quote["price"]
        row["total"] = usd(row["price"] * row["shares"])
        row["price"] = usd(row["price"])
    return render_template("index.html", rows=rows)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Get money of user from db
    id = session["user_id"]
    rows = db.execute("SELECT cash FROM users WHERE id = ?", id)
    money = rows[0]["cash"]


    if request.method == "POST":
        # Check all possible issues
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please input a stock symbol", 403)
        quote = lookup(symbol)
        if not quote:
            return apology("Stock Symbol Not Found", 403)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Invalid number of stocks to purchase")
        if shares < 0:
            return apology("Must input a positive number of shares")
        price = float(quote["price"])
        symbol = quote["symbol"]
        cost = shares * price
        if cost > money:
            return apology("You can't afford that!")

        # Passing all checks, execute buy
        else:
            # Update money
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?;", cost, id)
            # Add transaction
            db.execute("INSERT INTO transactions (id, action, shares, symbol, price) VALUES(?, 'buy', ?, ?, ?);", id, shares, symbol, price)
            # Update user's holdings
            db.execute("INSERT INTO holdings (id, shares, symbol) VALUES(?, ?, ?) ON CONFLICT(id, symbol) DO UPDATE SET shares = shares + ?;", id, shares, symbol, shares)

            if shares > 1:
                shareString = "shares"
            else:
                shareString = "share"
            success = "Congratulations! You've purchased " + str(shares) + " " + shareString + " of " + symbol + " for " + usd(cost) + "."
            rows = db.execute("SELECT cash FROM users WHERE id = ?", id)
            # Update money after purchase
            money = rows[0]["cash"]
            return render_template("buy.html", success = success, money = usd(money))
        
    else:
        return render_template("buy.html", money = usd(money))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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


quotes = deque()
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("Stock Symbol Not Found", 403)

        global quotes
        quotes.appendleft(quote)
        return render_template("quoted.html", quotes=quotes)
    else:
        quotes.clear()
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted twice
        elif not request.form.get("password") and not request.form.get("confirmation"):
            return apology("must provide password both times", 403)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username LIKE ?", request.form.get("username"))

        # Ensure username isn't in use
        if len(rows) != 0:
            return apology("username already in use", 403)

        # Add user to database
        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
