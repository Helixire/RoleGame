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

static void	print_map(int **grid)
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

static void	update(int **grid, t_unit **list, SDL_Rect *cursor)
{
  t_unit	*i;
  SDL_Rect	pos;
  SDL_Rect	size;

  size.h = TSIZE;
  size.w = TSIZE;
  SDL_FillRect(img[0], NULL, 0);
  print_map(grid);
  i = *list;
  while (i != NULL)
    {
      pos.x = (i->x - 1) * TSIZE;
      pos.y = (i->y - 1) * TSIZE;
      size.x = (i->move == 0) ? TSIZE * 2 : (i->id > 40) ? TSIZE : 0;
      size.y = (i->id > 40) ? (i->id - 40) / 10 : i->id / 10 - 1;
      size.y *= TSIZE;
      SDL_BlitSurface(img[2], &size, img[0], &pos);
      i = i->next;
    }
  pos.x = cursor->x * TSIZE;
  pos.y = cursor->y * TSIZE;
  SDL_BlitSurface(img[3], NULL, img[0], &pos);
  if (g_sel != NULL)
    {
      pos.x = g_sel->x * TSIZE - TSIZE;
      pos.y = g_sel->y * TSIZE - TSIZE;
      SDL_BlitSurface(img[4], NULL, img[0], &pos);
    }
  SDL_Flip(img[0]);
}

static void	space_key(SDL_Rect *cursor, int **grid, t_unit **list)
{
  t_unit	*tmp;

  if (g_sel == NULL)
    {
      g_sel = find_unit_at(*list, cursor->x + 1, cursor->y + 1);
    }
  else
    {
      tmp = find_unit_at(*list, cursor->x + 1, cursor->y + 1);
      if (tmp != NULL && g_sel->move != 0 && ((g_sel->id > 40 && g_turn == 1) ||
					      (g_sel->id < 41 && g_turn == 0)))
	{
	  if (can_attack(g_sel, tmp) == 1)
	    attack_g(g_sel, tmp, list);
	}
      g_sel = NULL;
    }
  printf("selected :");
  if (g_sel)
    printf("%d has %d hp and %d movement\n", g_sel->id, g_sel->pv, g_sel->move);
  else
    printf("NONE\n");
}

static int	key_event(SDL_Event *event, SDL_Rect *cursor,
			  int **grid, t_unit **list)
{
  if (event->key.keysym.sym == SDLK_ESCAPE)
    return (1);
  else if (event->key.keysym.sym == SDLK_DOWN &&
	   grid[cursor->y + 2][1] != 0)
    cursor->y += 1;
  else if (event->key.keysym.sym == SDLK_UP &&
	   cursor->y != 0)
    cursor->y -= 1;
  else if (event->key.keysym.sym == SDLK_RIGHT &&
	   grid[1][cursor->x + 2] != 0)
    cursor->x += 1;
  else if (event->key.keysym.sym == SDLK_LEFT &&
	   cursor->x != 0)
    cursor->x -= 1;
  else if (event->key.keysym.sym == SDLK_SPACE)
    space_key(cursor, grid, list);
  else if (event->key.keysym.sym == SDLK_p)
    init_turn(*list, &g_turn);
  return (0);
}

int		loop_g(int **grid, t_unit **list)
{
  int		state;
  SDL_Event	event;
  SDL_Rect	cursor;

  cursor.x = 0;
  cursor.y = 0;
  update(grid, list, &cursor);
  state = 1;
  while (state)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	state = 0;
      else if (event.type == SDL_KEYDOWN)
	if (key_event(&event, &cursor, grid, list) != 0)
	  state = 0;
      update(grid, list, &cursor);
    }
  return (0);
}
