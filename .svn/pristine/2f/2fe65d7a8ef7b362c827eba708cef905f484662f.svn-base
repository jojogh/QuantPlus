import ConfigParser
import os

from flask import Flask
from flask.ext.sqlalchemy import SQLAlchemy

db = SQLAlchemy()

# configuration
config = ConfigParser.SafeConfigParser()
# set some defautl values for the config
# there is probably a better way to do this...
config.add_section('ipydra')
config.set('ipydra', 'DB_URI', 'sqlite:///ipydra.db')
config.set('ipydra', 'BASE_URL', 'http://localhost')
config.set('ipydra', 'DATA_DIR', '~/.ipydra')
config.set('ipydra', 'INITDATA_DIR', '')
# load configuration file
config.read('ipydra.cfg')
DB_URI = os.path.expanduser(config.get('ipydra', 'DB_URI'))
BASE_URL = os.path.expanduser(config.get('ipydra', 'BASE_URL'))
DATA_DIR = os.path.expanduser(config.get('ipydra', 'DATA_DIR'))
INITDATA_DIR = os.path.expanduser(config.get('ipydra', 'INITDATA_DIR'))

def create_app():
    """ Creates and returns a flask app instance instance.
    """
    app = Flask(__name__)
    app.secret_key = 'why would I tell you my secret key?'
    app.debug = True
    app.config['SQLALCHEMY_DATABASE_URI'] = DB_URI
    db.init_app(app)

    from login import bp as bp_login
    app.register_blueprint(bp_login)

    from admin import bp as bp_admin
    app.register_blueprint(bp_admin, url_prefix='/admin')

    return app
