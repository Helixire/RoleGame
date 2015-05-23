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

TOOL	= tool/list.c \
	  tool/list2.c \
	  tool/str.c \
	  tool/str2.c \
	  tool/str3.c \
	  tool/get_next_line.c \
	  tool/parser.c

SRC	= src/main.c \
	  src/init.c \
	  src/loop.c \
	  src/move.c \
	  src/display_grid.c \
	  src/attack.c \
	  src/attack_unit.c \
	  $(TOOL)

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
