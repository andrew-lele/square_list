CXX = g++
CXXFLAGS = -g


p2grade01.cpp: Int341.o SqList.o 
	$(CXX) $(CXXFLAGS) Int341.o SqList.o p2grade01.cpp -o 1g
	
Int341.o: Int341.h Int341.cpp
	$(CXX) $(CXXFLAGS) -c Int341.cpp

SqList.o: SqList.h SqList.cpp
	$(CXX) $(CXXFLAGS) -c SqList.cpp

clean:
	rm *.o
	rm *~

run:
	./proj2
