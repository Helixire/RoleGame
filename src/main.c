/*
** main.c for emblem in /home/helixire/rendu/BocalEmblem/II : Path of Radiance
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Sun May 17 16:40:55 2015 Blank Pierre
** Last update Sun May 17 16:40:55 2015 Blank Pierre
*/

#include <stdlib.h>
#include "game.h"

int		main(int ac, char **av)
{
  int		**grid;
  t_unit	*unit;
  int		i;
  int		win;

  win = 0;
  if (ac == 1)
    return (my_error(GE));
  i = 0;
  while (i != -1 && ++i < ac)
    {
      grid = NULL;
      unit = NULL;
      my_putstr("--");
      my_putstr(av[i]);
      my_putstr("--\n");
      if (init(av[i], &grid, &unit) != 1)
	{
	  display_grid(grid, av[i], unit);
	  init_turn(unit, NULL);
	  win = loop(av[i], grid, &unit);
	}
      clean_unit(unit);
      free_grid(grid);
      my_putstr("--end--\n");
    }
  return (win);
}
