/*
** list2.c for game in /home/helixire/rendu/RoleGame
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Sat May 23 02:09:08 2015 Blank Pierre
** Last update Sat May 23 02:09:08 2015 Blank Pierre
*/

#include "tool.h"

/*
** Will return the unit at the position given by x and y
** if no unit was found there return NULL
*/

#include <stdlib.h>
#include "tool.h"

t_unit		*find_unit_at(t_unit *list, const int x, const int y)
{
  t_unit	*i;

  i = list;
  while (i != NULL)
    {
      if (i->x == x && i->y == y)
	return (i);
      i = i->next;
    }
  return (NULL);
}
