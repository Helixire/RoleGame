/*
** display_grid.c for display grid in /home/pinloc_a/rendu_mint/BocalEmblem/tool
** 
** Made by pinloche antoine
** Login   <pinloc_a@epitech.eu>
** 
** Started on  Sun May 17 19:26:52 2015 pinloche antoine
** Last update Sun May 17 20:15:04 2015 pinloche antoine
*/

#include <stdlib.h>
#include <unistd.h>
#include "tool.h"

static void	my_putnbr_blue(int nb)
{
  if (nb >= 10)
    {
      my_putnbr_blue(nb / 10);
      my_putnbr_blue(nb % 10);
    }
  else
    {
      my_putstr(BLUE);
      my_putchar(nb + '0');
      my_putstr(NORM);
    }
}

static void	my_putnbr_red(int nb)
{
  if (nb >= 10)
    {
      my_putnbr_red(nb / 10);
      my_putnbr_red(nb % 10);
    }
  else
    {
      my_putstr(RED);
      my_putchar(nb + '0');
      my_putstr(NORM);
    }
}

void		display_grid(int **grid, char *name, t_unit *list)
{
  int		x_g;
  int		y_g;
  t_unit	*tmp;

  y_g = 0;
  my_putstr(WHITE);
  my_putstr(BGGREEN);
  my_putname(name);
  while (grid[++y_g][1] != 1)
    {
      x_g = 0;
      while (grid[y_g][++x_g] != 1)
	{
	  if ((tmp = find_unit_at(list, x_g, y_g)) != NULL)
	    (tmp->id > 41) ? my_putnbr_red(tmp->id) : my_putnbr_blue(tmp->id);
	  else
	    {
	      (void)write(1, "0", 1);
	      my_putnbr(grid[y_g][x_g]);
	    }
	  (void)write(1, " ", 1);
	}
      my_putchar('\n');
    }
}
