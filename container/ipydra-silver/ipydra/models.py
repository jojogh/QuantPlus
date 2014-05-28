from ipydra import db

class User(db.Model):

    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True)
    email = db.Column(db.String(80), unique=True)
    password = db.Column(db.String(80))
    nbserver_port = db.Column(db.Integer, unique=True)
    nbserver_pid = db.Column(db.Integer, unique=True)
    score = db.Column(db.Float)
