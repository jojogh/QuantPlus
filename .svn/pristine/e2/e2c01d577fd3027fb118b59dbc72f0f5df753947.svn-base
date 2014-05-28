from flask import Blueprint
from flask import render_template

from ipydra import models
from ipydra import BASE_URL

bp = Blueprint('admin', __name__)

@bp.route('/secret')
def listing():
    return render_template('admin.jinja.html',
                           BASE_URL=BASE_URL,
                           users=models.User.query.all())
