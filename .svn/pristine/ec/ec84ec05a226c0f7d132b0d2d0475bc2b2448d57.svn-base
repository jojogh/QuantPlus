# IPydra
# Template for ipython notebook config

c = get_config()
c.NotebookApp.ip = '*'
c.NotebookApp.enable_mathjax = True
c.NotebookApp.open_browser = False
c.NotebookApp.ipython_dir = u'{{ ip_dir }}'

c.IPKernelApp.pylab = 'inline'
c.NotebookManager.notebook_dir = u'{{ nb_dir }}'
c.NotebookApp.password = u'{{ hashed_password }}'

c.InteractiveShellApp.exec_lines = [
    'import numpy as np',
    'import scipy as sp',
    'import pandas as pd',
    'from CAL.PyCAL import *'
]