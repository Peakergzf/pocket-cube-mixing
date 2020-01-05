cube2: cube2.cpp
	g++ -std=c++11 -Wall -I ./alglib -o sol cube2.cpp alglib.a
# https://stackoverflow.com/questions/51855264/undefined-symbols-for-architecture-x86-64-alglibspline2dcalcalglibspline2

cube: cube.cpp
	g++ -std=c++11 -Wall -I ./eigen -o sol cube.cpp 

run:
	./sol

clean:
	/bin/rm -f sol