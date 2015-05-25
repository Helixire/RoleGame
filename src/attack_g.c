/*
** attack_g.c for game in /home/helixire/rendu/RoleGame/dev
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Mon May 25 02:32:15 2015 Blank Pierre
** Last update Mon May 25 02:32:15 2015 Blank Pierre
*/

#include "game.h"

int	can_attack(t_unit *atk, t_unit *def)
{
  if (def != NULL && atk != def &&
      atk->id + def->id >= 52 && atk->id + def->id <= 110 &&
      (((ABS(atk->x - def->x)) <= atk->range && (ABS(atk->y - def->y)) == 0) ||
       ((ABS(atk->y - def->y)) <= atk->range && (ABS(atk->x - def->x)) == 0)))
    return (1);
  return (0);
}

void		attack_g(t_unit *atk, t_unit *def, t_unit **list)
{
  SDL_Rect	pos;
  int		ta;
  int		td;
  int		damage;
  char		buf[11];
  SDL_Color	color;

  color.r = 250;
  color.g = 10;
  color.b = 10;
  ta = (atk->id > 40) ? (atk->id - 40) / 10 : atk->id / 10 - 1;
  td = (def->id > 40) ? (def->id - 40) / 10 : def->id / 10 - 1;
  if ((ta == 0 && td == 2) || (ta == 1 && td == 0) || (ta == 2 && td == 1))
    damage = -15;
  else
    damage = -5;
  atk->move = 0;
  def->pv += damage;
  int_to_str(damage, buf);
  TTF_SizeText(g_font, buf, &ta, NULL);
  pos.x = def->x * TSIZE - TSIZE / 2 - ta / 2;
  pos.y = def->y * TSIZE - TSIZE - 16;
  print_str(img[0], buf, color, &pos);
  SDL_Flip(img[0]);
  SDL_Delay(500);
  if (def->pv <= 0)
    rm_unit(list, def->id);
}
