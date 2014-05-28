/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2013 Cheng Li, DataYes

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

/*! \file repochina.h
    \brief base class for China Shibor indexes
*/

#ifndef quanlib_repochina_hpp
#define quanlib_repochina_hpp

#include <ql/indexes/iborindex.hpp>

namespace QuantLib {

	class RepoChina : public IborIndex {
	public:
		RepoChina(
			const Period& tenor,
			const Handle<YieldTermStructure>& h =
			Handle<YieldTermStructure>());

		Date valueDate(const Date& fixingDate) const;
		Date maturityDate(const Date& valueDate) const;

		boost::shared_ptr<IborIndex> clone(
			const Handle<YieldTermStructure>& h) const;

		Calendar jointCalendar() const;

	private:
		Calendar financialCenterCalendar_;
		Calendar jointCalendar_;
	};
}

#endif