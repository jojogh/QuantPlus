/*
 Copyright (C) 2014 Cheng Li

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef quantlib_sensitivityanalysis_i
#define quantlib_sensitivityanalysis_i

%include types.i
%include vectors.i
%include marketelements.i
%include instruments.i

%{
using QuantLib::aggregateNPV;
using QuantLib::bucketAnalysis;
using QuantLib::SensitivityAnalysis;
using QuantLib::OneSide;
using QuantLib::Centered;
%}

enum SensitivityAnalysis {
        OneSide = 0,
        Centered = 1
};


#if defined(SWIGMZSCHEME) || defined(SWIGGUILE)
%rename("aggregate-npv")         aggregateNPV;
#endif

Real aggregateNPV(const std::vector<boost::shared_ptr<QuantLib::Instrument> >& instruments,
                          const std::vector<Real>& quantities) {
						  return aggregateNPV(instruments, quantities);
}


#if defined(SWIGMZSCHEME) || defined(SWIGGUILE)
%rename("bucket-analysis")         bucketAnalysis;
#endif

std::pair<std::vector<Real>, std::vector<Real> >
bucketAnalysis(const std::vector<Handle<Quote> >& quotes,
                   const std::vector<boost::shared_ptr<Instrument> >& instruments,
                   const std::vector<Real>& quantities,
                   Real shift = 0.0001,
                   SensitivityAnalysis type = Centered) {
            return bucketAnalysis(quotes, instruments, quantities, shift, type);
				   }

#endif