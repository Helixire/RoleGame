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
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "game.h"

static int	start_maps(char **av, SDL_Surface *img[])
{
  int		**grid;
  t_unit	*unit;
  int		i;
  int		win;

  win = 0;
  if (av[0] == NULL)
    return (my_error(NF));
  i = -1;
  while (av[++i])
    {
      grid = NULL;
      unit = NULL;
      my_putstr("--");
      my_putstr(av[i]);
      my_putstr("--\n");
      if (init(av[i], &grid, &unit) != 1)
	{
	  init_turn(unit, NULL);
	  if (!GRAPH)
	    display_grid(grid, av[i], unit);
	  win = (GRAPH) ? loop_g(img, grid, &unit) : loop(av[i], grid, &unit);
	}
      clean_unit(unit);
      free_grid(grid);
      my_putstr("--end--\n");
    }
  return (win);
}

  int	main(int ac, char **av)
  {
    SDL_Surface	*img[4];
    int		ret;

    (void)ac;
    if (GRAPH)
      {
	if (SDL_Init(SDL_INIT_VIDEO) == -1 || /* INIT SDL */
	    (img[0] = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL ||  /* Create Screen */
	    (img[1] = IMG_Load("data/tiles.bmp")) == NULL ||  /* Load map img */
	    (img[3] = IMG_Load("data/cursor.bmp")) == NULL || /* cursor       */
	    (img[2] = IMG_Load("data/unit.bmp")) == NULL)     /* and unit     */
	  return (my_error(SDL_GetError()));
	SDL_WM_SetCaption("RoleGame", NULL); /* Change window name */
      }
    ret = start_maps(av + 1, img);
    if (GRAPH)
      {
	SDL_FreeSurface(img[1]);
	SDL_FreeSurface(img[2]);
	SDL_FreeSurface(img[3]);
	SDL_Quit(); /* i think you can guess it */
      }
    return (ret);
  }
