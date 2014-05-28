/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Aurelien Chanudet
 Copyright (C) 2013 Cheng Li

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

#ifdef HAVE_CONFIG_H
#include <qlo/config.hpp>
#endif

#include <qlo/shortratemodels.hpp>

#include <ql/models/shortrate/onefactormodels/vasicek.hpp>
#include <ql/models/shortrate/onefactormodels/hullwhite.hpp>
#include <ql/models/shortrate/onefactormodels/blackkarasinski.hpp>
#include <ql/models/shortrate/onefactormodels/coxingersollross.hpp>
#include <ql/models/shortrate/onefactormodels/extendedcoxingersollross.hpp>
#include <ql/experimental/shortrate/generalizedhullwhite.hpp>

namespace QuantLibAddin {

    Vasicek::Vasicek(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                     QuantLib::Real a,
                     QuantLib::Real b,
                     QuantLib::Real lambda,
                     QuantLib::Real sigma,
                     bool permanent) : AffineModel(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::AffineModel>(new
            QuantLib::Vasicek(a, b, lambda, sigma));
    }

    HullWhite::HullWhite(
                const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
                QuantLib::Real a,
                QuantLib::Real sigma,
                bool permanent) : AffineModel(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::AffineModel>(new
            QuantLib::HullWhite(hYTS, a, sigma));
    }

	GeneralizedHullWhite::GeneralizedHullWhite(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
		QuantLib::Real a,
		QuantLib::Real sigma,
		bool permanent) : AffineModel(properties, permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::AffineModel>(new
			QuantLib::GeneralizedHullWhite(hYTS, a, sigma));
	}

	CIR::CIR(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		QuantLib::Rate r0,
		QuantLib::Real theta,
		QuantLib::Real k,
		QuantLib::Real sigma,
		bool permanent) : AffineModel(properties, permanent) 
	{
		libraryObject_ = boost::shared_ptr<QuantLib::AffineModel>(new
			QuantLib::CoxIngersollRoss(r0, theta, k, sigma));
	}

	ExtendedCIR::ExtendedCIR(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& termStructure,
		QuantLib::Real theta,
		QuantLib::Real k,
		QuantLib::Real sigma,
		QuantLib::Real x0,
		bool permanent) : AffineModel(properties, permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::AffineModel>(new
			QuantLib::ExtendedCoxIngersollRoss(termStructure, theta, k, sigma, x0));
	}

	VasicekShortRate::VasicekShortRate(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		QuantLib::Real a,
		QuantLib::Real b,
		QuantLib::Real lambda,
		QuantLib::Real sigma,
		bool permanent) : ShortRateModel(properties, permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::ShortRateModel>(new
			QuantLib::Vasicek(a, b, lambda, sigma));
	}

	HullWhiteShortRate::HullWhiteShortRate(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
		QuantLib::Real a,
		QuantLib::Real sigma,
		bool permanent) : ShortRateModel(properties, permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::ShortRateModel>(new
			QuantLib::HullWhite(hYTS, a, sigma));
	}

	GeneralizedHullWhiteShortRate::GeneralizedHullWhiteShortRate(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
		QuantLib::Real a,
		QuantLib::Real sigma,
		bool permanent) : ShortRateModel(properties, permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::ShortRateModel>(new
			QuantLib::GeneralizedHullWhite(hYTS, a, sigma));
	}

	BlackKarasinski::BlackKarasinski(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
		QuantLib::Real a,
		QuantLib::Real sigma,
		bool permanent) : ShortRateModel(properties, permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::ShortRateModel>(new
			QuantLib::BlackKarasinski(hYTS, a, sigma));
	}

	CIRShortRate::CIRShortRate(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		QuantLib::Rate r0,
		QuantLib::Real theta,
		QuantLib::Real k,
		QuantLib::Real sigma,
		bool permanent) : ShortRateModel(properties, permanent) 
	{
		libraryObject_ = boost::shared_ptr<QuantLib::ShortRateModel>(new
			QuantLib::CoxIngersollRoss(r0, theta, k, sigma));
	}

	ExtendedCIRShortRate::ExtendedCIRShortRate(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>& termStructure,
		QuantLib::Real theta,
		QuantLib::Real k,
		QuantLib::Real sigma,
		QuantLib::Real x0,
		bool permanent) : ShortRateModel(properties, permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::ShortRateModel>(new
			QuantLib::ExtendedCoxIngersollRoss(termStructure, theta, k, sigma, x0));
	}

}

