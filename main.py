from flask import Flask, render_template, request
from ctypes import *

# cc -fPIC -shared -o libC.so main.c

so_file = "D:/Travail/P24/NF06A/Projet_Bank/libC.so"

lib = CDLL(so_file)

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        if request.form["user_type"] == "customer":
            customers = lib.loadC()
            return lib.test(customers)
        else:
            return "advisor"
    else:
        return "<p>There is nothing to see here!</p>"


if __name__ == '__main__':
    app.run(debug=True)
