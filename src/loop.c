/*
** loop.c for Emblem in /home/helixire/rendu/BocalEmblem/II : Path of Radiance
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Sun May 17 15:02:50 2015 Blank Pierre
** Last update Sun May 17 15:02:50 2015 Blank Pierre
*/

#include <stdlib.h>
#include "game.h"

static int	check_turn(t_unit *list, int *turn)
{
  int		nb;
  t_unit	*i;

  i = list;
  nb = 0;
  while (i != NULL)
    {
      if ((*turn == 0 && i->id < 41) || (*turn == 1 && i->id > 40))
	{
	  nb += 1;
	  if (i->move != 0)
	    return (0);
	}
      i = i->next;
    }
  if (nb == 0)
    return (1);
  init_turn(list, turn);
  return (0);
}

static int	parse_l(char *tmp, int **grid, t_unit **list, int turn)
{
  char		**tab;
  int		i;
  int		perso;

  if ((tab = parse(tmp, " \t")) == NULL)
    return (0);
  if (tab[0] == NULL)
    return (1);
  i = 0;
  while (tab[i])
    i += 1;
  if ((perso = my_getnbr(tab[0])) < 11)
    return (free_tab(tab) + my_error(GE));
  if ((perso > 40 && turn == 0) ||
     (perso < 41 && turn == 1))
    return (free_tab(tab) + my_error(NT));
  if (i > 3 && my_strcmp(tab[1], "move") == 0 && my_strcmp(tab[2], "to") == 0)
    return (move(grid, tab[3], perso, *list) + free_tab(tab));
  if (i > 2 && my_strcmp(tab[1], "attack") == 0)
    return (attack(grid, list, perso, my_getnbr(tab[2])) + free_tab(tab));
  free_tab(tab);
  return (0);
}

int		loop(char *name, int **grid, t_unit **list)
{
  int		turn;
  char		*tmp;

  turn = 0;
  while (turn < 2)
    {
      my_putstr(":>");
      if ((tmp = get_next_line(0)) != NULL && tmp[0] != 0)
	{
	  if (my_strcmp(tmp, EXIT) == 0)
	    turn = 2;
	  else if (my_strcmp(tmp, MAP) == 0)
	    display_grid(grid, name, *list);
	  else if (my_strcmp(tmp, "pass") == 0)
	    init_turn(*list, &turn);
	  else if (parse_l(tmp, grid, list, turn) == 0)
	    my_putstr(CNF);
	  if (check_turn(*list, &turn) == 1)
	    turn += 2;
	}
      else if (tmp == NULL)
	return (1);
      if (tmp != NULL)
	free(tmp);
    }
  return (turn - 1);
}
