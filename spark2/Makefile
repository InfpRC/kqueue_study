CXX = g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

TARGET = tcp_server

SRCS = main.cpp TcpServer.cpp

HEADERS = TcpServer.h

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
