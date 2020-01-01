CXX=g++
CFLAGS+=-Wall

wlc_c: wlc_c.cpp
	$(CXX) $(CFLAGS) -o wlc_c wlc_c.cpp

clean:
	rm wlc_c
