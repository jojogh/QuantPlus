"""
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
 Copyright (C) 2009 Joseph Malicki

 This file is part of CAL, a free-software/open-source library
 for financial quantitative analysts and developers - http://CAL.org/

 CAL is free software: you can redistribute it and/or modify it
 under the terms of the CAL license.  You should have received a
 copy of the license along with this program; if not, please email
 <CAL-dev@lists.sf.net>. The license is also available online at
 <http://CAL.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
"""

import sys
import unittest

from date import DateTest
from instruments import InstrumentTest
from marketelements import MarketElementTest
from integrals import IntegralTest
from solvers1d import Solver1DTest
from termstructures import TermStructureTest
from bonds import FixedRateBondTest
from ratehelpers import FixedRateBondHelperTest
from cms import CmsTest
from assetswap import AssetSwapTest

def test():
    import CAL
    print('testing CAL ' +  CAL.__version__)

    suite = unittest.TestSuite()

    suite.addTest(DateTest())
    suite.addTest(unittest.makeSuite(InstrumentTest,'test'))
    suite.addTest(unittest.makeSuite(MarketElementTest,'test'))
    suite.addTest(unittest.makeSuite(IntegralTest,'test'))
    suite.addTest(Solver1DTest())
    suite.addTest(unittest.makeSuite(TermStructureTest,'test'))
    suite.addTest(unittest.makeSuite(FixedRateBondTest, 'test'))
    suite.addTest(unittest.makeSuite(FixedRateBondHelperTest, 'test'))
    suite.addTest(unittest.makeSuite(CmsTest, 'test'))
    suite.addTest(unittest.makeSuite(AssetSwapTest, 'test'))

    result = unittest.TextTestRunner(verbosity=2).run(suite)

    if not result.wasSuccessful:
        sys.exit(1)

if __name__ == '__main__':
    test()
