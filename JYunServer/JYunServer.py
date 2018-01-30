#coding: utf-8
import json

from flask import Flask, request
import config
from logic.user.Head import Head

app = Flask(__name__)
app.config.from_object(config)

@app.route('/login/', methods=["POST"])
def login():
    """
    登录响应函数
    :return:
    """
    print(request.get_data())
    data = {
        "login_result":"True"
    }
    return json.dumps(data)

@app.route('/head/', methods=["GET", "POST"])
def head():
    """
    头像函数
    :return:
    """
    print(request.args)
    if request.method == "GET":
        Head.downloadHead(request.args.get("user"))
    elif request.method == "POST":
        Head.uploadHead(request.args.get("user"))

    return ""


if __name__ == '__main__':
    app.run(port=36951)
