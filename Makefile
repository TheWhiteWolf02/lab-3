all: fputs_test

fputs_test: fputs_test.o tools.o stats.o
	g++ fputs_test.o tools.o stats.o -o $@ -lm
	
fputs_test.o: fputs_test.cpp tools.h tests.h
	g++ -c fputs_test.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp
	
stats.o: stats.cpp stats.h tests.h
	g++ -c stats.cpp
	
clean:
	rm -f *.o fputs_test test_.txt
	
