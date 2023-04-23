CXXFLAGS = --std=c++11 -I./
CXX = clang++

test : matInverse.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

run : test
	./test

clean :
	rm -rf *.o test
