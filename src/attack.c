/*
** attack.c for attack in /home/pinloc_a/rendu_mint/BocalEmblem/tool
** 
** Made by pinloche antoine
** Login   <pinloc_a@epitech.eu>
** 
** Started on  Sat May 16 18:32:16 2015 pinloche antoine
** Last update Sun May 17 20:11:15 2015 pinloche antoine
*/

#include <stdlib.h>
#include "game.h"

static int	same_team(int att, int def)
{
  if (((def >= 11 && def <= 40) &&
       (att >= 41 && att <= 70)) ||
      ((def >= 41 && def <= 70) &&
       (att >= 11 && att <= 40)))
    return (1);
  else
    return (0);
}

static int	verif_pos(int x_attacker, int y_attacker, int x_def, int y_def)
{
  if (((x_attacker == x_def) && (y_attacker - y_def == -1)) ||
      ((x_attacker == x_def) && (y_attacker - y_def == 1)) ||
      ((y_attacker == y_attacker) && ((x_attacker - x_def) == 1)) ||
      ((y_attacker == y_attacker) && ((x_attacker - x_def) == -1)))
    return (0);
  else
    return (1);
}

static int	fight_engage(t_unit *defender, t_unit *attacker)
{
  attacker->move = 0;
  if ((attacker->id >= 11 && attacker->id <= 20)
      || (attacker->id >= 41 && attacker->id <= 50))
    return (archer_attack(defender));
  else if ((attacker->id >= 21 && attacker->id <= 30)
	   || (attacker->id >= 51 && attacker->id <= 60))
    return (soldier_attack(defender));
  else
    return (knight_attack(defender));
}

int			attack(int **grid, t_unit **list, int attack, int def)
{
  t_unit		*attacker;
  t_unit		*defender;
  int			damage;

  (void)grid;
  if (attack < 10 || def < 10 ||
      (attacker = find_unit(*list, attack)) == NULL ||
      (defender = find_unit(*list, def)) == NULL)
    return (my_error(GE));
  if (same_team(attack, def) == 0)
    return (my_error(ST));
  if (verif_pos(attacker->x, attacker->y, defender->x, defender->y) == 1)
    return (my_error(GE));
  damage = fight_engage(defender, attacker);
  if (life_unit(defender, attack, damage) == 1)
    dead_unit(list, def);
  return (1);
}
