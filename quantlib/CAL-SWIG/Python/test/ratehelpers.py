"""
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

import CAL
import unittest

class FixedRateBondHelperTest(unittest.TestCase):
    def setUp(self):
        self.settlement_days = 3
        self.face_amount = 100.0
        self.redemption = 100.0
        self.quote_handle = CAL.QuoteHandle(CAL.SimpleQuote(100.0))

        self.issue_date = CAL.Date(2,1,2008)
        self.maturity_date = CAL.Date(2,1,2018)
        self.calendar = CAL.UnitedStates(CAL.UnitedStates.GovernmentBond)
        self.day_counter = CAL.ActualActual(CAL.ActualActual.Bond)
        self.sched = CAL.Schedule(self.issue_date, self.maturity_date,
                                       CAL.Period(CAL.Semiannual), self.calendar,
                                       CAL.Unadjusted, CAL.Unadjusted,
                                       CAL.DateGeneration.Backward, False)
        self.coupons = [0.05]

        self.bond_helper = CAL.FixedRateBondHelper(self.quote_handle, self.settlement_days,
                                                        self.face_amount, self.sched, self.coupons,
                                                        self.day_counter, CAL.Following,
                                                        self.redemption, self.issue_date)
    def testBond(self):
        """ Testing FixedRateBondHelper bond() method. """
        bond = self.bond_helper.bond()
        self.assertEqual(bond.issueDate(), self.issue_date)
        self.assertEqual(bond.nextCouponRate(), self.coupons[0])

if __name__ == '__main__':
    print('testing CAL ' + CAL.__version__)
    suite = unittest.TestSuite()
    suite.addTest(unittest.makeSuite(FixedRateBondHelperTest,'test'))
    unittest.TextTestRunner(verbosity=2).run(suite)
