#coding: utf-8
import json

from flask import Flask, request
import config

app = Flask(__name__)
app.config.from_object(config)

@app.route('/login', methods=["POST"])
def login():
    print(request.get_data())
    data = {
        "login_result":"True"
    }
    return json.dumps(data)


if __name__ == '__main__':
    app.run(port=36951)
