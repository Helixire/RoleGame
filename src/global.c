/*
** global.c for game in /home/helixire/rendu/RoleGame
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Tue May 26 22:52:18 2015 Blank Pierre
** Last update Tue May 26 22:52:18 2015 Blank Pierre
*/

#include "game.h"

int		g_xd;
int		g_yd;
TTF_Font	*g_font;
SDL_Surface	*img[6];
int		g_turn;
t_unit		*g_sel;
FMOD_SYSTEM	*g_m;
FMOD_SOUND	*sound[5];
const t_type	g_type[] =
  {{"archer", 30, 4, 2, {2, -1}, {2, 3, 8, 9, 10, 11, 12, 13, 14, 16, -1}},
   {"soldier", 30, 3, 1, {0, -1}, {2, 3, 8, 9, 10, 11, 12, 13, 14, 16, -1}},
   {"knight", 30, 2, 1, {1, -1}, {2, 3, 8, 9, 10, 11, 12, 13, 14, 16, -1}}};
