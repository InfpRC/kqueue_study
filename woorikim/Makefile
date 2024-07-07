CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SOURCES = Socket.cpp Server.cpp Client.cpp EventManager.cpp main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

NAME = mul_server

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re