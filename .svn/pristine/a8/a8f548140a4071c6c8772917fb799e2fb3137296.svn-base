/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2013 Klaus Spanderen

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

/*! \file observable.cpp
    \brief observer/observable pattern
*/

#include <ql/qldefines.hpp>

#ifndef QL_ENABLE_THREAD_SAFE_OBSERVER_PATTERN
#define QL_ENABLE_THREAD_SAFE_OBSERVER_PATTERN
#endif

#ifdef QL_ENABLE_THREAD_SAFE_OBSERVER_PATTERN

#include <ql/patterns/observable.hpp>
#include <boost/thread/locks.hpp>

#if defined(BOOST_MSVC)
	#pragma warning(disable: 4355)
#endif

namespace QuantLib {
	namespace {
		boost::mutex* observerListMutex(new boost::mutex);
		std::set<void*>* globalObserverList(new std::set<void*>);

		void addObserverToGlobalList(void* observer) {
			boost::lock_guard<boost::mutex> lock(*observerListMutex);
			globalObserverList->insert(observer);
		}

		void eraseIfObserver(void* ptr, std::size_t size) {
			boost::lock_guard<boost::mutex> lock(*observerListMutex);
			const std::set<void*>::iterator iter
				=  globalObserverList->lower_bound(ptr);

			if (iter != globalObserverList->end()) {
				char* p = static_cast<char*>(ptr);
				if ((p+size) >= *iter) {
					QuantLib::Observer* const observer
						= static_cast<QuantLib::Observer*>(*iter);

					observer->deactivate();
					globalObserverList->erase(*iter);
				}
			}
		}
	}

	class Observer::Proxy {
      public:
        Proxy(Observer* const observer)
        : active_(true),
          observer_(observer) {
        	addObserverToGlobalList(observer_);
        }
        void update() const {
            boost::lock_guard<boost::mutex> lock(mutex_);
            if(active_) {
                observer_->update();
            }
        }
        void deactivate() {
            boost::lock_guard<boost::mutex> lock(mutex_);
            active_ = false;
        }

        bool isActive() const {
            return active_;
        }
      private:
        bool active_;
        mutable boost::mutex mutex_;
        Observer* const observer_;
    };

    Observer::Observer() {}

    void Observer::deactivate() {
        boost::lock_guard<boost::mutex> lock(mutex_);
        if (proxy_) {
        	proxy_->deactivate();
        }
    }

    bool Observer::isActive() const {
    	if (proxy_) {
    		return proxy_->isActive();
    	}
    	return true;
    }

    std::pair<std::set<boost::shared_ptr<Observable> >::iterator, bool>
    Observer::registerWith(const boost::shared_ptr<Observable>& h) {
        boost::lock_guard<boost::mutex> lock(mutex_);
        if (!proxy_) {
        	proxy_.reset(new Proxy(this));
        }
        if (h) {
            h->registerObserver(proxy_);
            return observables_.insert(h);
        }
        return std::make_pair(observables_.end(), false);
    }


    Size Observer::unregisterWith(const boost::shared_ptr<Observable>& h) {
        boost::lock_guard<boost::mutex> lock(mutex_);
        if (h) {
        	QL_REQUIRE(proxy_, "unregister called without a proxy");

            h->unregisterObserver(proxy_);
        }

        return observables_.erase(h);
    }

    Observer::Observer(const Observer& o)
    : proxy_(new Proxy(this)) {
        {       
            boost::lock_guard<boost::mutex> lock(o.mutex_);
            observables_ = o.observables_;
        }
        for (iterator i=observables_.begin(); i!=observables_.end(); ++i)
            (*i)->registerObserver(proxy_);
    }

    Observer& Observer::operator=(const Observer& o) {
        boost::lock_guard<boost::mutex> lock(mutex_);
        if (!proxy_) {
        	proxy_.reset(new Proxy(this));
        }

        for (iterator i=observables_.begin(); i!=observables_.end(); ++i)
            (*i)->unregisterObserver(proxy_);

        {
            boost::lock_guard<boost::mutex> lock(o.mutex_);
            observables_ = o.observables_;
        }

        for (iterator i=observables_.begin(); i!=observables_.end(); ++i)
            (*i)->registerObserver(proxy_);
        return *this;
    }

    Observer::~Observer() {
    	eraseIfObserver(this, 0);

        for (iterator i=observables_.begin(); i!=observables_.end(); ++i)
            (*i)->unregisterObserver(proxy_);
    }


    void Observable::registerObserver(
        const boost::shared_ptr<Observer::Proxy>& observerProxy) {

        signal_type::slot_type slot(&Observer::Proxy::update,
                                    observerProxy.get());
        sig_.connect(slot.track(observerProxy));
    }

    void Observable::unregisterObserver(
        const boost::shared_ptr<Observer::Proxy>& observerProxy) {

        sig_.disconnect(boost::bind(&Observer::Proxy::update,
                        observerProxy.get()));
    }

    void Observable::notifyObservers() {
        sig_();
    }
}

namespace boost {
    void sp_scalar_constructor_hook( void * px, std::size_t size, void * pn ) {
    }

    void sp_scalar_destructor_hook( void * px, std::size_t size, void * pn ){
    	QuantLib::eraseIfObserver(px, size);
    }
}
#endif

