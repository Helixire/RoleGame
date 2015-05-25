/*
** init_turn.c for game in /home/helixire/rendu/RoleGame/dev
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Mon May 25 01:56:47 2015 Blank Pierre
** Last update Mon May 25 01:56:47 2015 Blank Pierre
*/

#include "game.h"

void		init_turn(t_unit *list, int *turn)
{
  t_unit	*i;
  int		type;

  if (turn != NULL)
    {
      if (*turn == 0)
	{
	  my_putstr(RT);
	  *turn = 1;
	}
      else
	{
	  my_putstr(BT);
	  *turn = 0;
	}
    }
  i = list;
  while (i != NULL)
    {
      type = (i->id > 40) ? (i->id - 40) / 10 : i->id / 10 - 1;
      i->move = 4 - type;
      i = i->next;
    }
  g_sel = NULL;
}
