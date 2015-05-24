/*
** game.h for game in /home/helixire/rendu/RoleGame
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Sat May 23 01:55:02 2015 Blank Pierre
** Last update Sat May 23 01:55:02 2015 Blank Pierre
*/

#ifndef _GAME_H_
# define _GAME_H_

# include <SDL/SDL.h>
# include "tool.h"
# include "my_error.h"

# define TSIZE	32
# define GRAPH	1

# define EXIT	"exit"
# define MAP	"map"
# define STRAT	"strategic"

# define TOP	"top"
# define BOTTOM	"bottom"
# define RIGHT	"right"
# define LEFT	"left"

# define NT	"This is not your turn.\n"
# define ST	"Can’t attack a unit from the same side sir.\n"

# define BT	BLUE "Blue Turn\n" NORM
# define RT	RED "Red Turn\n" NORM

typedef struct	s_action
{
  char		*key;
  int		(*act)();
}		t_action;

int		init(char *file, int ***grid, t_unit **unit);
int		attack(int **grid, t_unit **list, int attack, int def);
int		archer_attack(t_unit *defender);
int		soldier_attack(t_unit *defender);
int		knight_attack(t_unit *defender);
void		dead_unit(t_unit **list, int def);
int		life_unit(t_unit *defender, int att, int damage);
void		display_grid(int **grid, char *name, t_unit *list);
int		move(int **tab, char *str, int unit, t_unit *list);
int		loop(char *name, int **grid, t_unit **list);
void		init_turn(t_unit *list, int *turn);
int		loop_g(SDL_Surface *img[], int **grid, t_unit **list);

#endif /* !_GAME_H_ */