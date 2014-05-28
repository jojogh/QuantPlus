import site
site.addsitedir('/home/ubuntu/repos/ipydra')

from ipydra import db
from ipydra import models
from ipydra import create_app


def update_score(score):
    app = create_app()
    db.init_app(app)
    ctx = app.test_request_context()
    ctx.push()
    user = (models.User.query
        .filter(models.User.username == '{{ username }}')
    ).first()
    user.score = score
    db.session.merge(user)
    db.session.commit()
    ctx.pop()
