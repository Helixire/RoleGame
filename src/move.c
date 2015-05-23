/*
** move.c for emblem in /home/helixire/rendu/BocalEmblem/I : The Sacred Stones
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Sun May 17 22:20:02 2015 Blank Pierre
** Last update Sun May 17 22:20:02 2015 Blank Pierre
*/

#include <stdlib.h>
#include "game.h"

int		move(int **tab, char *str, int id, t_unit *list)
{
  int		x;
  int		y;
  t_unit	*unit;

  if ((unit = find_unit(list, id)) == NULL)
    return (my_error(UNF));
  if (unit->move == 0)
    return (my_error(UAM));
  x = 0;
  y = 0;
  if (my_strcmp(str, LEFT) == 0)
    x -=1;
  else if (my_strcmp(str, RIGHT) == 0)
    x += 1;
  else if (my_strcmp(str, TOP) == 0)
    y -= 1;
  else if (my_strcmp(str, BOTTOM) == 0)
    y += 1;
  else
    return(my_error(WD));
  if (tab[unit->y + y][unit->x + x] != 1 &&
      find_unit_at(list, unit->x + x, unit->y + y) == NULL)
    {
      unit->move -= 1;
      unit->y += y;
      unit->x += x;
    }
  else
    return (my_error(NA));
  return (1);
}
