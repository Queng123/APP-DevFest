LIB_THREAD	=	-lpthread

LIB_RAYLIB	=	-lraylib -ldl

LIB_PIGPIO	=	-lpigpio

INCLUDE		=	-I src/network/client/ -I src/network/ -I src/display -I src/io/ -I src/

MAIN		=	Main.cpp

NAME		=	pi-display

C++			=	g++

compile: $(NAME)

$(NAME):
	$(C++) $(MAIN) $(INCLUDE) $(LIB_THREAD) $(LIB_RAYLIB) $(LIB_PIGPIO) $(CXXFLAGS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: clean compile
