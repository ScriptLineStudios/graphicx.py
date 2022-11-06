from flask import Flask, render_template
import graphicx

canvas = graphicx.Surface((600, 600))
app = Flask(__name__)

@app.route("/")
def home():
    return render_template("home.html", buffer=canvas)

if __name__ == "__main__":
    app.run(debug=True)