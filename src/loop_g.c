/*
** loop_graph.c for game in /home/helixire/rendu/RoleGame/dev
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Mon May 25 00:03:22 2015 Blank Pierre
** Last update Mon May 25 00:03:22 2015 Blank Pierre
*/

#include "game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void	print_map(SDL_Surface *img[], int **grid)
{
  int		x;
  int		y;
  SDL_Rect	pos;
  SDL_Rect	size;

  size.y = 0;
  size.w = TSIZE;
  size.h = TSIZE;
  y = 0;
  while (grid[++y][1] != 0)
    {
      x = 0;
      while (grid[y][++x] != 0)
	{
	  pos.x = (x - 1) * TSIZE;
	  pos.y = (y - 1) * TSIZE;
	  size.x = (grid[y][x] - 1) * TSIZE;
	  SDL_BlitSurface(img[1], &size, img[0], &pos);
	}
    }
}

static void	update(SDL_Surface *img[], int **grid,
		       t_unit **list, SDL_Rect *cursor)
{
  t_unit	*i;
  SDL_Rect	pos;
  SDL_Rect	size;

  size.h = TSIZE;
  size.w = TSIZE;
  SDL_FillRect(img[0], NULL, 0);
  print_map(img, grid);
  i = *list;
  while (i != NULL)
    {
      pos.x = (i->x - 1) * TSIZE;
      pos.y = (i->y - 1) * TSIZE;
      size.x = (i->id > 40) ? TSIZE : 0;
      size.y = (i->id > 40) ? (i->id - 40) / 10 : i->id / 10 - 1;
      size.y *= TSIZE;
      SDL_BlitSurface(img[2], &size, img[0], &pos);
      i = i->next;
    }
  SDL_BlitSurface(img[3], NULL, img[0], cursor);
  SDL_Flip(img[0]);
}

int		loop_g(SDL_Surface *img[], int **grid, t_unit **list)
{
  int		state;
  SDL_Event	event;
  SDL_Rect	cursor;

  cursor.x = 0;
  cursor.y = 0;
  update(img, grid, list, &cursor);
  state = 1;
  while (state)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	state = 0;
      else if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    state = 0;
	  else if (event.key.keysym.sym == SDLK_DOWN &&
		   grid[cursor.y / TSIZE + 2][1] != 0)
	    cursor.y += TSIZE;
	  else if (event.key.keysym.sym == SDLK_UP &&
		   cursor.y != 0)
	    cursor.y -= TSIZE;
	  else if (event.key.keysym.sym == SDLK_RIGHT &&
		   grid[1][cursor.x / TSIZE + 2] != 0)
	    cursor.x += TSIZE;
	  else if (event.key.keysym.sym == SDLK_LEFT &&
		   cursor.x != 0)
	    cursor.x -= TSIZE;
	}
      update(img, grid, list, &cursor);
    }
  return (0);
}
