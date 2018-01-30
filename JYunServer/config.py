#coding: utf-8

# dialect+driver://username:password@host:port/database?charset:utf8
DIALECT = 'mysql'
DRIVER = 'pymysql'
USERNAME = 'root'
PASSWORD = 'root'
HOST = '127.0.0.1'
PORT = '3306'
DATABASE = 'JYUN_DATABASE'

SQLALCHEMY_DATABASE_URI = "{}+{}://{}:{}@{}:{}/{}?charset:utf8".format(
DIALECT, DRIVER, USERNAME, PASSWORD, HOST, PORT, DATABASE
)

SQLALCHEMY_TRACK_MODIFICATIONS=False

DEBUG=True