CXX = g++
CXXFLAGS = -std=c++17 -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++17 -Ih -pthread
OBJECTS = ./obj/program.o ./obj/main.o ./obj/program_unittest.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/program.o: ./cpp/program.cpp
	$(CXX) $(CXXFLAGS) ./cpp/program.cpp -o ./obj/program.o
./obj/program_unittest.o: ./cpp/program_unittest.cpp
	$(CXX) $(CXXFLAGS) ./cpp/program_unittest.cpp -o ./obj/program_unittest.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
