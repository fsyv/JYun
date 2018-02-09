#coding: utf-8
import json

import sys

import os
from flask import Flask, request, redirect, url_for, send_from_directory
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

class TableUserHead(db.Model):
    """
    用户名头像表
    """
    __tablename__ = "TABLE_USER_HEAD"
    username = db.Column(db.String(16), primary_key=True, nullable=False)
    head_md5 = db.Column(db.String(32), nullable=False)

class TableFileCount(db.Model):
    """
    文件引用表
    """
    __tablename__ = "TABLE_FILE_COUNT"
    file_md5 = db.Column(db.String(32), primary_key=True, nullable=False)
    file_count = db.Column(db.INT, nullable=False)

db.create_all()

@app.route('/login/', methods=["POST"])
def login():
    """
    登录响应函数
    :return:
    """
    user_data = json.loads(request.get_data())
    username = user_data["username"]
    userpass = user_data["userpass"]
    userlist = TableUserPass.query.filter(TableUserPass.username == username).all()

    data = {}

    if userlist:
        user = userlist[0]
        if user.userpass == userpass:
            data["login_result"] = "True"
        else:
            data["login_result"] = "False"
            data["login_error"] = "密码错误"
        pass
    else:
        data["login_result"] = "False"
        data["login_error"] = "账号不存在"

    return json.dumps(data)

@app.route('/register/', methods=["GET", "POST"])
def register():
    """
    注册
    :return:
    """
    if request.method == "GET":
        username = request.args.get("username")
        userlist = TableUserPass.query.filter(TableUserPass.username == username).all()
        if userlist:
            return json.dumps({"username_state": "True"})
        else:
            return json.dumps({"username_state": "False"})
    elif request.method == "POST":
        user_data = json.loads(request.get_data())
        user = TableUserPass(username=user_data["username"], userpass=user_data["userpass"])
        db.session.add(user)
        db.session.commit()
        os.mkdir("/home/fsyv/user/" + user_data["username"])
        return json.dumps({"register_result": "True"})

@app.route('/head/', methods=["GET", "POST"])
def head():
    """
    头像函数
    :return:
    """
    if request.method == "GET":
        username = request.args.get("username")
        head_md5 = redirect(url_for("head_md5") + "?username=%s" % (username))
        print(head_md5)
        print(url_for("file", filename=head_md5, _method="GET"))
        return redirect(url_for("file", filename = head_md5, _method="GET"))
    elif request.method == "POST":
        Head.uploadHead(request.args.get("user"))

    return ""

@app.route('/head/md5/')
def head_md5():
    """
    头像函数
    :return:
    """
    username = request.args.get("username")
    user = TableUserHead.query.filter(TableUserHead.username == username)[0]
    return user.head_md5

@app.route('/modify/', methods=["POST"])
def modify():
    """
    修改密码
    :return:
    """
    print(request.data)

    return ""

@app.route('/file/<filename>', methods=["GET", "POST"])
def file(filename):
    """
    文件上传下载
    :return:
    """
    if request.method == "GET":
        filepath = os.path.join(os.path.expanduser("~"), 'file')
        return send_from_directory(filepath, filename, as_attachment=True)
    elif request.method == "POST":
        filepath = os.path.join(os.path.expanduser("~"), 'file')
        file = request.files["file"]
        file.save(os.path.join(filepath, filename))
    return ""

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=36951)
