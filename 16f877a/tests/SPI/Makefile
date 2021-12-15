proj = spi-test
CXX = xc8-cc -mcpu=16f877a

all: master slave

master: master.c ../../spi.h
	$(CXX) -o dist/$@ $@.c

slave: slave.c ../../spi.h
	$(CXX) -o dist/$@ $@.c

clean:
	rm -v dist/*

