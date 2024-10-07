from flask import Flask,render_template

app = Flask(__name__)

@app.route("/show/info")
def index():
    return render_template("index.html")
#默认去同级目录下的templates目录下寻找文件
if __name__ == '__main__':
    app.run(debug=True)