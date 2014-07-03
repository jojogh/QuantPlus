import os
import subprocess
import shutil
import time
import hashlib
import random
import socket

from flask import Blueprint
from flask import redirect
from flask import render_template
from flask import request
from flask import flash
from flask import url_for

from flask.ext.wtf import Form
from wtforms import TextField, PasswordField, BooleanField
from wtforms import TextAreaField
from flask.ext.wtf.html5 import EmailField, URLField
from wtforms.validators import DataRequired, Email, Length, Regexp
from wtforms.validators import Optional, URL

from ipydra import db
from ipydra import models
from ipydra import DATA_DIR
from ipydra import BASE_URL
from ipydra import INITDATA_DIR

from IPython.utils.py3compat import cast_bytes, str_to_bytes
import pdb
#-----------------------------------------------------------------------------
# Globals
#-----------------------------------------------------------------------------

# Length of the salt in nr of hex chars, which implies salt_len * 4
# bits of randomness.
salt_len = 12
algorithm = 'sha1'

bp = Blueprint('login', __name__)

class SignUpForm(Form):
    """ A simple signup form for front end.
    """
    username = TextField(
        'Username', validators=[
            DataRequired(), Length(min=3, max=20),
            Regexp(r'([a-zA-Z_0-9])[\.$0]*')
        ], description='English Characters Only.',
    )
    email = EmailField(
        'Email', validators=[DataRequired(), Email()]
    )
    password = PasswordField(
        'Password', validators=[DataRequired()]
    )

    def validate_username(self, field):
        user = models.User.query.filter(models.User.username == field.data.lower()).first()
        if user:
            raise ValueError('This name has been registered.')

    def validate_email(self, field):
        user = models.User.query.filter(models.User.email == field.data.lower()).first()
        if user:
            raise ValueError('This name has been registered.')

class LoginForm(Form):
    """ A simple login form for front end.
    """
    username = TextField(
        'Username', validators=[
            DataRequired(), Length(min=3, max=20),
            Regexp(r'([a-zA-Z_0-9])[\.$0]*')
        ], description='English Characters Only.',
    )
    
    password = PasswordField(
        'Password', validators=[DataRequired()]
    )

    def validate_username(self, field):
        user = models.User.query.filter(models.User.username == field.data.lower()).first()
        if not user:
            raise ValueError('This user does not exist.')

@bp.route('/', methods=['GET', 'POST'])
def signup():
    form = SignUpForm(request.form,csrf_enabled=False)
    if request.method == 'POST':
        if form.validate():
            
            username = str(form.username.data)
            email = str(form.email.data)
            password = str(form.password.data)

            #curr user count
            curr_user_count = models.User.query.count()

            if curr_user_count >= 15:
                flash('Your company can only create 15 users, please contact us if you have any question')
                return render_template('index.html')

            # get the next server port
            port = 9499 + curr_user_count + 1
            #create passwd
            h = hashlib.new(algorithm)
            salt = ('%0' + str(salt_len) + 'x') % random.getrandbits(4 * salt_len)
            h.update(cast_bytes(password, 'utf-8') + str_to_bytes(salt, 'ascii'))
            hashed_password = ':'.join((algorithm, salt, h.hexdigest()))

            # create user
            user = models.User()
            user.username = username
            user.email = email
            user.password = hashed_password
            user.nbserver_port = port
            user = db.session.merge(user)
            db.session.commit()

            # create the user data directory hierarchy
            if not os.path.exists('{0}/{1}'.format(DATA_DIR, username)):
                create_user_dir(username, hashed_password)

            return redirect('/login')
        else:
            errorMsg = ''
            for key in form.errors:
                errorMsg=errorMsg+key+':'+form.errors[key][0]+'      '

            flash(errorMsg)
            return render_template('index.html')
        
    return render_template('index.html')

@bp.route('/login', methods=['GET', 'POST'])
def login():
    """ Login view which redirects the user to the spawned servers.
    """
    form = LoginForm(request.form,csrf_enabled=False)
    if request.method == 'POST':
        if form.validate():
            username = str(form.username.data)
            password = str(form.password.data)
            user = models.User.query.filter(models.User.username == username).first()
          
            if not passwd_check(user.password, password):
                flash('Wrong Password')
                return render_template('login.html')

            # spawn the notebook server if its not currently running
            if (not user.nbserver_pid or
                not os.path.exists('/proc/{0}'.format(user.nbserver_pid))):
                ip_dir = '{0}/{1}/.ipython'.format(DATA_DIR, username)
                user.nbserver_pid = run_server(ip_dir, user.nbserver_port)
                user = db.session.merge(user)
                db.session.commit()
                # sleep to let server start listening
                while not port_is_used(user.nbserver_port):
                    time.sleep(1)
            return redirect('{0}:{1}/login'.format(BASE_URL, user.nbserver_port), code=307)
        else:
            errorMsg = ''
            for key in form.errors:
                errorMsg=errorMsg+key+':'+form.errors[key][0]+'      '

            flash(errorMsg)
            return render_template('login.html')
    return render_template('login.html')

def run_server(ip_dir, port):
    """ Run a notebook server with a given ipython directory and port.
        Returns a PID.
    """
    #pdb.set_trace()
    pid = subprocess.Popen(['ipython',
                            'notebook',
                            '--profile=nbserver',
                            '--NotebookApp.port={0}'.format(port),
                            '--NotebookApp.ipython_dir={0}'.format(ip_dir)]).pid
    return pid

def create_user_dir(username, hashed_password):
    """ Create a new user's directory structure.
    """
    user_dir = '{0}/{1}'.format(DATA_DIR, username)
    ip_dir = '{0}/.ipython'.format(user_dir)
    conf_dir = '{0}/profile_nbserver'.format(ip_dir)
    nb_dir = '{0}/notebooks'.format(user_dir)

    os.makedirs(ip_dir)
    os.makedirs(conf_dir)

    # render config
    config = render_template('ipython_notebook_config.jinja.py',
                             username=username,
                             ip_dir=ip_dir,
                             nb_dir=nb_dir,
                             hashed_password=hashed_password)
    config_file = open('{0}/ipython_notebook_config.py'.format(conf_dir), 'w')
    config_file.write(config)
    config_file.close()

    # copy data files over
    if INITDATA_DIR:
        shutil.copytree(INITDATA_DIR, '{0}'.format(nb_dir))
    else:
        os.makedirs(nb_dir)

    # render update_score script
    script = render_template('update_score.jinja.py', username=username)
    script_file = open('{0}/update_score.py'.format(nb_dir), 'w')
    script_file.write(script)
    script_file.close()

def passwd_check(hashed_passphrase, passphrase):
    """Verify that a given passphrase matches its hashed version.

    Parameters
    ----------
    hashed_passphrase : str
        Hashed password, in the format returned by `passwd`.
    passphrase : str
        Passphrase to validate.

    Returns
    -------
    valid : bool
        True if the passphrase matches the hash.

    Examples
    --------
    >>> from IPython.lib.security import passwd_check
    >>> passwd_check('sha1:0e112c3ddfce:a68df677475c2b47b6e86d0467eec97ac5f4b85a',
    ...              'mypassword')
    True

    >>> passwd_check('sha1:0e112c3ddfce:a68df677475c2b47b6e86d0467eec97ac5f4b85a',
    ...              'anotherpassword')
    False
    """
    try:
        algorithm, salt, pw_digest = hashed_passphrase.split(':', 2)
    except (ValueError, TypeError):
        return False

    try:
        h = hashlib.new(algorithm)
    except ValueError:
        return False

    if len(pw_digest) == 0:
        return False

    h.update(cast_bytes(passphrase, 'utf-8') + cast_bytes(salt, 'ascii'))

    return h.hexdigest() == pw_digest

def port_is_used(port):
    '''
    @note: if the port is used, return True. otherwise return False.
    '''
    TIME_OUT = 2
    HOST = "127.0.0.1"
    inner_port = port

    sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sk.settimeout(TIME_OUT)
    try:
        sk.bind((HOST, inner_port))
        sk.close()
    except socket.error, e:
        if e.errno == 98 or e.errno == 13:
            return True
    return False