##
## Makefile for emblem in /home/helixire/rendu/BocalEmblem/II : Path of Radiance
## 
## Made by Blank Pierre
## Login   <blank_p@epitech.net>
## 
## Started on  Sun May 17 18:06:26 2015 Blank Pierre
## Last update Sun May 17 18:06:26 2015 Blank Pierre
##

CC	= gcc

RM	= rm -f

NAME	= Game

CFLAGS	+= -W -Wall -ansi -pedantic
CFLAGS	+= -I./include

LDFLAGS	= -lSDL -lSDL_image -lSDL_ttf -L/usr/local/bin -lfmod

TOOL	= tool/list.c \
	  tool/str.c \
	  tool/str2.c \
	  tool/str3.c \
	  tool/str4.c \
	  tool/get_next_line.c \
	  tool/parser.c \
	  tool/my_sdl.c

SRC	= src/main.c \
	  src/init.c \
	  src/loop_g.c \
	  src/init_turn.c \
	  src/attack_g.c \
	  src/find_path.c \
	  src/global.c \
	  $(TOOL)

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
