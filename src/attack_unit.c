/*
** attack_unit.c for attack unit in /home/pinloc_a/rendu_mint/BocalEmblem/tool
** 
** Made by pinloche antoine
** Login   <pinloc_a@epitech.eu>
** 
** Started on  Sat May 16 19:46:25 2015 pinloche antoine
** Last update Sun May 17 20:11:24 2015 pinloche antoine
*/

#include "tool.h"

int		archer_attack(t_unit *defender)
{
  if ((defender->id >= 31 && defender->id <= 40) ||
      (defender->id >= 61 && defender->id <= 70))
    {
      defender->pv -= 15;
      return (15);
    }
  else
    {
      defender->pv -= 5;
      return (5);
    }
}

int		soldier_attack(t_unit *defender)
{
  if ((defender->id >= 11 && defender->id <= 20) ||
      (defender->id >= 41 && defender->id <= 50))
    {
      defender->pv -= 15;
      return (15);
    }
  else
    {
      defender->pv -= 5;
      return (5);
    }
}

int		knight_attack(t_unit *defender)
{
  if ((defender->id >= 21 && defender->id <= 30) ||
      (defender->id >= 51 && defender->id <= 60))
    {
      defender->pv -= 15;
      return (15);
    }
  else
    {
      defender->pv -= 5;
      return (5);
    }
}

void		dead_unit(t_unit **list, int def)
{
  rm_unit(list, def);
  my_putstr(" [The unit ");
  my_putnbr(def);
  my_putstr(SLAIN);
}

int		life_unit(t_unit *defender, int att, int damage)
{
  my_putnbr(att);
  my_putstr(ATTACK);
  my_putnbr(damage);
  my_putchar(' ');
  my_putnbr(defender->id);
  my_putchar('.');
  my_putnbr(defender->id);
  my_putstr(" has ");
  my_putnbr(defender->pv);
  my_putstr(HP);
  if (defender->pv <= 0)
    return (1);
  else
    {
      my_putchar('\n');
      return (0);
    }
}
