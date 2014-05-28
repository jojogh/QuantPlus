
CLEANFILES = CAL_wrap.cpp libCALJNI.@JNILIB_EXTENSION@ CAL.jar

BUILT_SOURCES = CAL_wrap.cpp CAL_wrap.h

EXAMPLES = DiscreteHedging EquityOptions FRA UnaryFunctions

if HAVE_JAVA
if BUILD_JAVA

examples/%.class: examples/%.java CAL.jar
	$(JAVAC) -source 1.5 -cp CAL.jar examples/$*.java

.PHONY: $(EXAMPLES)

all-local: libCALJNI.@JNILIB_EXTENSION@ CAL.jar

CAL_wrap.o: CAL_wrap.cpp CAL_wrap.h
	g++ -c CAL_wrap.cpp -fno-strict-aliasing -fPIC $(CXXFLAGS) @JDK_INCLUDE@ @JDK_SYSTEM_INCLUDE@ `quantlib-config --cflags` -o CAL_wrap.o

libCALJNI.@JNILIB_EXTENSION@: CAL_wrap.o
	g++ @SHARED_LIB@ CAL_wrap.o -o libCALJNI.@JNILIB_EXTENSION@ `quantlib-config --libs`

CAL.jar: CAL_wrap.cpp org/CAL/*.java
	mkdir -p bin
	find org/CAL -name '*.java' | xargs $(JAVAC) -d bin
	$(JAR) cf CAL.jar -C bin org

install-exec-local:
	cp -p libCALJNI.@JNILIB_EXTENSION@ $(DESTDIR)/$(libdir)/libCALJNI.@JNILIB_EXTENSION@
	cp -p CAL.jar $(DESTDIR)/$(libdir)/CAL.jar

check-local: $(EXAMPLES)

$(EXAMPLES): $(EXAMPLES:%=examples/%.class)
	LD_LIBRARY_PATH=. $(JAVA) -cp ".:CAL.jar" examples.$@

endif
endif


CAL_wrap.cpp: ../SWIG/*.i
	mkdir -p org/CAL
	$(SWIG) -java -c++ -outdir org/CAL \
            -package org.CAL -o CAL_wrap.cpp ../SWIG/CAL.i

dist-hook:
	mkdir -p $(distdir)/org/CAL
	cp ./org/CAL/*.java $(distdir)/org/CAL
	touch $(distdir)/CAL_wrap.cpp
	touch $(distdir)/CAL_wrap.h
	mkdir -p $(distdir)/examples
	cp ./examples/*.java $(distdir)/examples

clean-local:
	rm -rf org 
	rm -f examples/*.class
	rm -f CAL_wrap.o
	rm -rf bin

EXTRA_DIST = README.txt $(BUILT_SOURCES)

