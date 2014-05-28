#coding=utf-8

import re

pat1 = re.compile('([^=]+=)?\s*(import|from|eval|exec|open|write)(\s+|\()+')
pat2 = re.compile('([^=]+=)?\s*(import|from|eval|exec|open|write)$')
# pat2 = re.compile('([^=]*=?)\s*(open|write)\s*')


def command_safe(command):
    return not any(elem.match(command) for elem in [pat1, pat2])


testcase = {
 'open = test': True,
 'evala(1)': True,
 'exec1 = test': True,
 'f= 1open("af","w+")': True,
 'f= open1("af","w+")': True,
 'open = open': False,

  'open= open("af","w+")': False,
 'import os': False,
 ' import os ': False,
 'from os import path ': False,
 'f= import': False,
 'f= import ': False,
 'import os ': False,
 ' import os ': False,
 '''
import os''': False,
 'f=open("af","w+")': False,
 ' f=open("af","w+")': False,
 'f = open("af","w+")': False,
 
 'open("af"), "w+"': False,
 'f=open': False,
 ' f = open ': False,
 'f= open': False,
 'f= open , write': False,
 'f= eval(': False,
'f= eval ': False,
'f= eval': False
}

if __name__ == '__main__':
    print all([command_safe(tc) == res for tc, res in testcase.iteritems()])
    print [tc for tc, res in testcase.iteritems() if not command_safe(tc) == res]


