/*
** list.c for emblem in /home/helixire/rendu/PSU_2014_42sh
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Sat May 16 15:23:27 2015 Blank Pierre
** Last update Sat May 16 15:23:27 2015 Blank Pierre
*/

#include <stdlib.h>
#include "my_error.h"
#include "tool.h"

int		add_unit(t_unit **list, const int id, const int x, const int y)
{
  t_unit	*ret;
  t_unit	*tmp;

  if ((ret = malloc(sizeof(*ret))) == NULL)
    return (1);
  ret->id = id;
  ret->pv = 30;
  ret->x = x;
  ret->y = y;
  ret->next = NULL;
  if (*list == NULL)
    *list = ret;
  else
    {
      tmp = *list;
      while (tmp->next != NULL)
	{
	  if (tmp->id == id)
	    {
	      free(ret);
	      return (2);
	    }
	  tmp = tmp->next;
	}
      tmp->next = ret;
    }
  return (0);
}

t_unit		*find_unit(t_unit *list, const int nb)
{
  t_unit	*tmp;

  tmp = list;
  while (tmp != NULL && tmp->id != nb)
    tmp = tmp->next;
  return (tmp);
}

void		rm_unit(t_unit **list, const int nb)
{
  t_unit	*tmp;
  t_unit	*i;

  i = *list;
  while (i != NULL && i->id != nb)
    {
      tmp = i;
      i = i->next;
    }
  if (i != NULL)
    {
      if (i == *list)
	*list = (*list)->next;
      else
	tmp->next = i->next;
      free(i);
    }
}

void		clean_unit(t_unit *list)
{
  t_unit	*tmp;
  t_unit	*tmp2;

  tmp = list;
  while (tmp != NULL)
    {
      tmp2 = tmp;
      tmp = tmp->next;
      free(tmp2);
    }
}
