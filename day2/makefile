srcs	= $(wildcard *.cpp)

make:
	g++ -Wall -std=c++11 main.cpp
	./a.out
	rm -f ./a.out

%.o: %.cpp
		$(CC) -MMD -MP $(CFLAGS) -c $< -o $@