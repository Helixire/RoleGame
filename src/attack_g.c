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
  if (atk->atk != 0 && atk != def && atk->faction != def->faction &&
      (((ABS(atk->pos.x - def->pos.x)) <= g_type[atk->type].range && (ABS(atk->pos.y - def->pos.y)) == 0) ||
       ((ABS(atk->pos.y - def->pos.y)) <= g_type[atk->type].range && (ABS(atk->pos.x - def->pos.x)) == 0)))
    return (1);
  return (0);
}

void		attack_g(t_unit *atk, t_unit *def, t_unit **list)
{
  SDL_Rect	pos;
  int		damage;
  char		buf[11];
  SDL_Color	color;

  color.r = 250;
  color.g = 0;
  color.b = 0;
  if (is_in(def->type, g_type[atk->type].counter) == 1)
    damage = -15;
  else
    damage = -5;
  atk->move = 0;
  atk->atk = 0;
  def->hp += damage;
  int_to_str(damage, buf);
  TTF_SizeText(g_font, buf, &damage, NULL);
  pos.x = def->pos.x * TSIZE - TSIZE / 2 - damage / 2;
  pos.y = def->pos.y * TSIZE - TSIZE - 16;
  print_str(img[0], buf, color, &pos);
  SDL_Flip(img[0]);
  FMOD_System_Update(g_m);
  FMOD_System_PlaySound(g_m, sound[atk->type], NULL, 0, NULL);
  SDL_Delay(500);
  if (def->hp <= 0)
    {
      rm_unit(list, def);
      FMOD_System_Update(g_m);
      FMOD_System_PlaySound(g_m, sound[3], NULL, 0, NULL);
    }
}
