LIB_THREAD	=	-lpthread

LIB_RAYLIB	=	-lraylib -ldl

INCLUDE		=	-I src/network/client/ -I src/network/ -I src/display -I src/

MAIN		=	main.cpp

NAME		=	pi-display

C++			=	g++

compile: $(NAME)

$(NAME):
	$(C++) $(MAIN) $(INCLUDE) $(LIB_THREAD) $(LIB_RAYLIB) $(CXXFLAGS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: clean compile
