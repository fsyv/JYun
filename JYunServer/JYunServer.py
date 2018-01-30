#coding: utf-8
import json

from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy

import config
from logic.user.Head import Head

app = Flask(__name__)
app.config.from_object(config)
db = SQLAlchemy(app)

class TableUserPass(db.Model):
    """
    用户名密码表
    """
    __tablename__ = "TABLE_USER_PASS"
    username = db.Column(db.String(16), primary_key=True, nullable=False)
    userpass = db.Column(db.String(32), nullable=False)

db.create_all()

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

@app.route('/register/', methods=["GET", "POST"])
def register():
    """
    注册
    :return:
    """
    if request.method == "GET":
        print(request.args)
        data = {
            "username_state": "False"
        }
        return json.dumps(data)
    elif request.method == "POST":
        print(request.get_data())
        data = {
            "register_result": "True"
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
    app.run(host="0.0.0.0", port=36951)
