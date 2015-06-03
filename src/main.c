/*
** main.c for emblem in /home/helixire/rendu/BocalEmblem/II : Path of Radiance
** 
** Made by Blank Pierre
** Login   <blank_p@epitech.net>
** 
** Started on  Sun May 17 16:40:55 2015 Blank Pierre
** Last update Sun May 17 16:40:55 2015 Blank Pierre
*/

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "game.h"

static int	start_maps(char **av)
{
  int		**grid;
  t_unit	*unit;
  int		i;
  int		win;

  win = 0;
  if (av[0] == NULL)
    return (my_error(NF));
  i = -1;
  while (av[++i])
    {
      grid = NULL;
      unit = NULL;
      my_putstr("--");
      my_putstr(av[i]);
      my_putstr("--\n");
      if (init(av[i], &grid, &unit) != 1)
	{
	  init_turn(unit, NULL);
	  win = loop_g(grid, &unit);
	}
      clean_unit(unit);
      free_grid(grid);
      my_putstr(END);
    }
  return (win);
}

int	main(int ac, char **av)
{
  int		ret;

  FMOD_System_Create(&g_m);                             /* load sound card */
  FMOD_System_Init(g_m, 2, FMOD_INIT_NORMAL, NULL);     /* allow sound usage */
  if (SDL_Init(SDL_INIT_VIDEO) == -1 ||                 /* INIT SDL */
      (img[0] = SDL_SetVideoMode(SIZEX * TSIZE, SIZEY * TSIZE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL ||  /* Create Screen */
      (img[1] = IMG_Load("data/tiles.bmp")) == NULL ||  /* Load map img */
      (img[3] = IMG_Load("data/cursor.bmp")) == NULL || /* cursor       */
      (img[2] = IMG_Load("data/unit.bmp")) == NULL ||   /* and unit     */
      (img[4] = IMG_Load("data/selected.bmp")) == NULL ||
      (img[5] = IMG_Load("data/move.bmp")) == NULL ||
      TTF_Init() != 0)
    return (my_error(SDL_GetError()));
  FMOD_System_CreateSound(g_m, "data/sound/arrow.wav", FMOD_CREATESAMPLE, 0, &sound[0]);
  FMOD_System_CreateSound(g_m, "data/sound/sword.wav", FMOD_CREATESAMPLE, 0, &sound[1]);
  FMOD_System_CreateSound(g_m, "data/sound/lance.wav", FMOD_CREATESAMPLE, 0, &sound[2]);
  FMOD_System_CreateSound(g_m, "data/sound/died.wav", FMOD_CREATESAMPLE, 0, &sound[3]);
  FMOD_System_CreateStream(g_m, "data/sound/bg.mp3", FMOD_2D | FMOD_CREATESTREAM, 0, &sound[4]);
  FMOD_Sound_SetLoopCount(sound[4], -1);
  FMOD_System_PlaySound(g_m, sound[4], NULL, 0, NULL);
  SDL_WM_SetCaption("RoleGame", NULL); /* Change window name */
  g_font = TTF_OpenFont("data/font/Lobster-Regular.ttf", 16);
  g_turn = 0;
  g_sel = NULL;
  SDL_EnableKeyRepeat(200, 100);                        /* key repeat */
  ret = start_maps(av + 1);
  ac = 5;
  while (--ac > 0)
    SDL_FreeSurface(img[ac]);
  ac = 5;
  while (--ac >= 0)
    FMOD_Sound_Release(sound[ac]);
  TTF_CloseFont(g_font);
  FMOD_System_Close(g_m);
  FMOD_System_Release(g_m);
  TTF_Quit();
  SDL_Quit(); /* i think you can guess it */
  return (ret);
}
