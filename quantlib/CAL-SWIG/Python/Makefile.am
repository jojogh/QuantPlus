
CLEANFILES = CAL/CAL_wrap.cpp CAL/CAL.py .build-stamp

BUILT_SOURCES = CAL/CAL_wrap.cpp CAL/CAL.py

if HAVE_PYTHON
if BUILD_PYTHON

all-local: .build-stamp

.build-stamp: CAL/CAL_wrap.cpp CAL/CAL.py
	CXXFLAGS="$(CXXFLAGS) $(CXXWARNINGFLAGS)" $(PYTHON) setup.py build
	touch .build-stamp

check-local: .build-stamp
	$(PYTHON) setup.py test

install-exec-local: .build-stamp
	$(PYTHON) setup.py install

clean-local:
	rm -rf build

endif
endif

CAL/CAL_wrap.cpp CAL/CAL.py: ../SWIG/*.i
	$(SWIG) -python -c++ -modern -outdir CAL \
            -o CAL/CAL_wrap.cpp ../SWIG/CAL.i

dist-hook:
	mkdir -p $(distdir)/examples
	cp ./examples/*.py $(distdir)/examples
	mkdir -p $(distdir)/test
	cp ./test/*.py $(distdir)/test

EXTRA_DIST = README.txt setup.py CAL/__init__.py $(BUILT_SOURCES)

