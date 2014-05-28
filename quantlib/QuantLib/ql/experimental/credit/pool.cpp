/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2008 Roland Lichters

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

#include <ql/experimental/credit/pool.hpp>

using namespace std;

namespace QuantLib {

    Pool::Pool() {
        clear();
    }

    Size Pool::size() const {
        return names_.size();
    }

    void Pool::clear() {
        data_.clear();
        time_.clear();
        names_.clear();
    }

    bool Pool::has(const std::string& name) const {
        return data_.find(name) != data_.end();
    }

    void Pool::add (const std::string& name, const Issuer& issuer) {
        if (!has(name)) {
            data_[name] = issuer;
            time_[name] = 0.0;
            names_.push_back(name);
        }
    }

    const Issuer& Pool::get (const std::string& name) const {
        QL_REQUIRE(has(name), name + " not found");
        return data_.find(name)->second;
    }

    Real Pool::getTime (const std::string& name) const {
        QL_REQUIRE(has(name), name + " not found");
        return time_.find(name)->second;
    }

	Date Pool::getDate (const std::string& name) const {
		QL_REQUIRE(has(name), name + " not found");
		return date_.find(name)->second;
	}

    void Pool::setTime(const std::string& name, Real time, const DayCounter& dc, Date refDate) {
		//if(refDate == Date())
		//	refDate = Settings::instance().evaluationDate();
        time_[name] = time;
		Real oneDayTimeFrac = dc.yearFraction(refDate, refDate + 1*Days);
		date_[name] = refDate + int(time/oneDayTimeFrac)*Days;
    }

	Date Pool::getDate(Real time, const DayCounter& dc, Date refDate) {
		//if(refDate == Date())
		//	refDate = Settings::instance().evaluationDate();
		Real oneDayTimeFrac = dc.yearFraction(refDate, refDate + 1*Days);
		return refDate + int(time/oneDayTimeFrac)*Days;
	}

    const std::vector<std::string>& Pool::names() const {
        return names_;
    }
}

