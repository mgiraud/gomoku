CC = clang++
CFLAGS = -std=c++11 -Wextra -Wall -Werror -O3
IFLAGS = -I./includes -I ~/.brew/include -I./SFML/include
LFLAGS = -L ./SFML -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
SRC = main.cpp Board.cpp Solver.cpp Render.cpp Player.cpp Game.cpp AThreat.cpp

NAME = gomoku

OBJ = $(SRCS:.cpp=.o)

SRCS = $(addprefix srcs/, $(SRC))

all : $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
		$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean
	make all

.PHONY: clean fclean all re make_minilibx
