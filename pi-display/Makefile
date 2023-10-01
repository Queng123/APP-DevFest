LIB_THREAD	=	-lpthread

LIB_RAYLIB	=	-lraylib -ldl

INCLUDE		=	-I src/network/client/ -I src/network/ -I src/display -I src/

MAIN		=	main.cpp

NAME		=	pi-display

SRC			=	src/display/GameDatasDisplay.cpp

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++17

OBJ			=	$(SRC:.cpp=.o)

C++			=	g++

%.o: %.cpp
	$(C++) $(INCLUDE) $(CXXFLAGS) -c $< -o $@

compile: $(NAME)

$(NAME): $(OBJ)
	$(C++) $(MAIN) $(OBJ) $(INCLUDE) $(LIB_THREAD) $(LIB_RAYLIB) $(CXXFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean compile
