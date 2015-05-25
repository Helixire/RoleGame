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
#include <SDL/SDL_ttf.h>
#include "game.h"

TTF_Font	*g_font;
SDL_Surface	*img[5];
int		g_turn;
t_unit		*g_sel;

static int	start_maps(char **av)
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
	  win = (GRAPH) ? loop_g(grid, &unit) : loop(av[i], grid, &unit);
	}
      clean_unit(unit);
      free_grid(grid);
      my_putstr("--end--\n");
    }
  return (win);
}

int	main(int ac, char **av)
{
  int		ret;

  if (GRAPH)
    {
      if (SDL_Init(SDL_INIT_VIDEO) == -1 || /* INIT SDL */
	  (img[0] = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL ||  /* Create Screen */
	  (img[1] = IMG_Load("data/tiles.bmp")) == NULL ||  /* Load map img */
	  (img[3] = IMG_Load("data/cursor.bmp")) == NULL || /* cursor       */
	  (img[2] = IMG_Load("data/unit.bmp")) == NULL ||   /* and unit     */
	  (img[4] = IMG_Load("data/selected.bmp")) == NULL ||
	  TTF_Init() != 0)
	return (my_error(SDL_GetError()));
      SDL_WM_SetCaption("RoleGame", NULL); /* Change window name */
      g_font = TTF_OpenFont("data/font/Lobster-Regular.ttf", 16);
    }
  g_turn = 0;
  g_sel = NULL;
  ret = start_maps(av + 1);
  if (GRAPH)
    {
      ac = 5;
      while (--ac > 0)
	SDL_FreeSurface(img[ac]);
      TTF_CloseFont(g_font);
      TTF_Quit();
      SDL_Quit(); /* i think you can guess it */
    }
  return (ret);
}
