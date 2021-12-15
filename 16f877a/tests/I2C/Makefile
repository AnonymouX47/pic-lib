proj = i2c-test
CXX = xc8-cc -mcpu=16f877a

all: master slave

master: master.c ../../i2c.h
	$(CXX) -o dist/$@ $@.c

slave: slave.c ../../i2c.h
	$(CXX) -o dist/$@ $@.c

clean:
	rm -v dist/*

