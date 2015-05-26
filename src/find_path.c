/*
** find_path.c for game in /home/helixire/rendu/RoleGame
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Mon May 25 20:14:16 2015 Blank Pierre
** Last update Mon May 25 20:14:16 2015 Blank Pierre
*/

#include "game.h"

void		clean_node(t_node **node)
{
  t_node	*i;
  t_node	*tmp;

  i = *node;
  while (i != NULL)
    {
      tmp = i;
      i = i->next;
      free(tmp);
    }
  *node = NULL;
}

static int	add_node(SDL_Rect *pos, int dist, t_node **list)
{
  t_node	*res;

  if ((res = malloc(sizeof(*res))) == NULL)
    return (my_error(EM));
  res->pos.x = pos->x;
  res->pos.y = pos->y;
  res->dist = dist;
  res->open = 1;
  res->next = *list;
  *list = res;
  return (0);
}

static t_node	*find_next(t_node *list, int dist)
{
  t_node	*i;

  i = list;
  while (i != NULL)
    {
      if (i->open == 1 && i->dist == dist)
	return (i);
      i = i->next;
    }
  return (i);
}

t_node		*node_at(t_node *list, SDL_Rect *pos)
{
  t_node	*i;

  i = list;
  while (i != NULL)
    {
      if (i->pos.x == pos->x && i->pos.y == pos->y)
	return (i);
      i = i->next;
    }
  return (NULL);
}

int		find_path(t_unit *unit, int **grid, t_node **res, t_unit *list)
{
  int		cd;
  SDL_Rect	p;
  t_node	*tmp;
  t_unit	*t;

  if (*res != NULL)
    clean_node(res);
  p.x = unit->pos.x;
  p.y = unit->pos.y;
  if (add_node(&p, 0, res) == 1)
    return (1);
  cd = -1;
  while (++cd < unit->move)
    {
      while ((tmp = find_next(*res, cd)) != NULL)
	{
	  tmp->open = 0;
	  p.h = 0;
	  while (p.h <= 6)
	    {
	      p.x = tmp->pos.x;
	      p.y = tmp->pos.y;
	      if (p.h < 3)
		p.x += p.h - 1;
	      else
		p.y += p.h - 5;
	      if (is_in(grid[p.y][p.x], ilegal) == 0 &&
		  node_at(*res, &p) == NULL &&
		  ((t = find_unit_at(list, p.x, p.y)) == NULL ||
		   t->faction == unit->faction))
		add_node(&p, tmp->dist + 1, res);
	      p.h += 2;
	    }
	}
    }
  return (0);
}
