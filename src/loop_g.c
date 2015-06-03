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
#include <SDL/SDL_image.h>

static void	print_map(int **grid, const int xd, const int yd)
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
	  pos.x = (x - 1 - xd) * TSIZE;
	  pos.y = (y - 1 - yd) * TSIZE;
	  size.x = (grid[y][x] - 1) * TSIZE;
	  SDL_BlitSurface(img[1], &size, img[0], &pos);
	}
    }
}

static void	update(int **grid, t_unit *i, SDL_Rect *cursor, t_node *res)
{
  SDL_Rect	pos;
  SDL_Rect	size;
  static int	xd;
  static int	yd;
  int		gridx;
  int		gridy;

  gridx = 1;
  while (grid[1][gridx] != 0)
    gridx += 1;
  gridy = 1;
  while (grid[gridy][1] != 0)
    gridy += 1;
  while (cursor->x - xd > SIZEX - 4 && cursor->x + 4 < gridx)
    xd += 1;
  while (cursor->x - xd < 4 && cursor->x - 3 > 0)
    xd -= 1;
  while (cursor->y - yd > SIZEY - 4 && cursor->y + 4 < gridy)
    yd += 1;
  while (cursor->y - yd < 4 && cursor->y - 3 > 0)
    yd -= 1;
  size.h = TSIZE;
  size.w = TSIZE;
  SDL_FillRect(img[0], NULL, 0);
  print_map(grid, xd, yd);
  while (res != NULL)
    {
      pos.x = (res->pos.x - xd) * TSIZE - TSIZE;
      pos.y = (res->pos.y - yd) * TSIZE - TSIZE;
      SDL_BlitSurface(img[5], NULL, img[0], &pos);
      res = res->next;
    }
  while (i != NULL)
    {
      pos.x = (i->pos.x - 1 - xd) * TSIZE;
      pos.y = (i->pos.y - 1 - yd) * TSIZE;
      size.x = (i->atk == 0) ? TSIZE * 2 : (i->faction == 1) ? TSIZE : 0;
      size.y = i->type * TSIZE;
      SDL_BlitSurface(img[2], &size, img[0], &pos);
      i = i->next;
    }
  pos.x = (cursor->x - xd) * TSIZE - TSIZE;
  pos.y = (cursor->y - yd) * TSIZE - TSIZE;
  SDL_BlitSurface(img[3], NULL, img[0], &pos);
  if (g_sel != NULL)
    {
      pos.x = (g_sel->pos.x - xd) * TSIZE - TSIZE;
      pos.y = (g_sel->pos.y - yd) * TSIZE - TSIZE;
      SDL_BlitSurface(img[4], NULL, img[0], &pos);
    }
  SDL_Flip(img[0]);
}

static void	space_key(SDL_Rect *cursor, int **grid,
			  t_unit **list, t_node **path)
{
  t_unit	*tmp;
  char		ttmp[300];
  t_node	*node;

  tmp = find_unit_at(*list, cursor->x, cursor->y);
  if (g_sel == NULL)
    {
      if ((g_sel = tmp) != NULL && g_sel->move != 0 && g_sel->faction == g_turn)
	find_path(g_sel, grid, path, *list);
    }
  else
    {
      if (tmp != NULL)
	{
	  if (can_attack(g_sel, tmp) == 1)
	    attack_g(g_sel, tmp, list);
	}
      else if ((node = node_at(*path, cursor)) != NULL)
	{
	  g_sel->pos.x = cursor->x;
	  g_sel->pos.y = cursor->y;
	  g_sel->move -= node->dist;
	}
      g_sel = NULL;
    }
  sprintf(ttmp, "\rselected : ");
  if (g_sel)
    sprintf(ttmp + 12, "%s has %d hp and %d movement", g_type[g_sel->type].name, g_sel->hp, g_sel->move);
  else
    {
      sprintf(ttmp + 12, "pos: %d %d                                        ", cursor->x, cursor->y);
      clean_node(path);
    }
  my_putstr(ttmp);
}

static int	key_event(SDL_Event *event, SDL_Rect *cursor,
			  int **grid, t_unit **list, t_node **path)
{
  if (event->key.keysym.sym == SDLK_ESCAPE)
    return (1);
  else if (event->key.keysym.sym == SDLK_DOWN &&
	   grid[cursor->y + 1][1] != 0)
    cursor->y += 1;
  else if (event->key.keysym.sym == SDLK_UP &&
	   cursor->y != 1)
    cursor->y -= 1;
  else if (event->key.keysym.sym == SDLK_RIGHT &&
	   grid[1][cursor->x + 1] != 0)
    cursor->x += 1;
  else if (event->key.keysym.sym == SDLK_LEFT &&
	   cursor->x != 1)
    cursor->x -= 1;
  else if (event->key.keysym.sym == SDLK_SPACE)
    space_key(cursor, grid, list, path);
  else if (event->key.keysym.sym == SDLK_p)
    init_turn(*list, &g_turn);
  return (0);
}

int		loop_g(int **grid, t_unit **list)
{
  int		state;
  SDL_Event	event;
  SDL_Rect	cursor;
  t_node	*path;

  path = NULL;
  cursor.x = 1;
  cursor.y = 1;
  update(grid, *list, &cursor, path);
  state = 1;
  while (state)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	state = 0;
      else if (event.type == SDL_KEYDOWN)
	if (key_event(&event, &cursor, grid, list, &path) != 0)
	  state = 0;
      update(grid, *list, &cursor, path);
    }
  return (0);
}
