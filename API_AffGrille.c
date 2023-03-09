#include "API_AffGrille.h"
#include<math.h>


void
SDL_PutPixel32 (SDL_Surface * surface, int x, int y, Uint32 pixel)
{
  Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * 4;
  *(Uint32 *) p = pixel;
}


void
HorizLine (SDL_Surface * surf, int x1, int y1, int x2, Uint32 couleur)  // a noter que Line gere ça aussi
{
  int i;
  for (i = x1; i <= x2; i++)
    SDL_PutPixel32 (surf, i, y1, couleur);
}


void
Disc (SDL_Surface * surf, int x1, int y1, int radius, Uint32 couleur)
{
  int x, y, d, stepd, max;
  y = radius;
  d = -radius;
  stepd = -1;
  max = (int) (radius / sqrt (2.0));
  for (x = 0; x <= max; x++)
  {
    stepd += 2;
    d += stepd;
    if (d >= 0)
    {
      y--;
      d -= (y << 1);            /* Must do this AFTER y-- */
    }
    HorizLine (surf, x1 - x, y1 + y, x1 + x, couleur);
    HorizLine (surf, x1 - x, y1 - y, x1 + x, couleur);
    HorizLine (surf, x1 - y, y1 + x, x1 + y, couleur);
    HorizLine (surf, x1 - y, y1 - x, x1 + y, couleur);
  }

}


void
AffGrille_init (Grille * G, AffGrille * AG)
{
  int i;
  unsigned int genecl = 10101;

  AG->G = G;

  // Affecte des couleurs au numero de 0 a nbcoul-1

  AG->T_coul = (Uint32 *) malloc (sizeof (Uint32) * G->nbcoul);

  for (i = 0; i < 32; i++)
  {                             // pour sauter les premieres couleurs un peu palotes
    genecl = genecl * (i + i + 1);
    genecl = (genecl ^ (0xffffff)) >> 2;
  }

  for (i = 0; i < G->nbcoul; i++)
  {
    genecl = genecl * (i + i + i + 1);
    genecl = (genecl ^ (0xffffff)) >> 2;
    AG->T_coul[i] = genecl;
  }


}


void
AffGrille_free (AffGrille * AG)
{
  free (AG->T_coul);
}


void
AffGrille_ouvre_fenetre (AffGrille * AG)
{
  int taille_pixel;
  Uint32 flags = SDL_HWSURFACE | SDL_HWACCEL | SDL_DOUBLEBUF;

  // Initialize SDL 2D display component.

  if (SDL_Init (SDL_INIT_VIDEO) != 0)
  {
    fprintf (stderr,
             "Erreur: ne peut pas initialiser le système graphique (\"%s\").\n",
             SDL_GetError ());
    return;
  }

  // Make sure that SDL_Quit is executed upon exit (especially
  // important if running in fullscreen display).

  atexit (SDL_Quit);

  // Find the screen height to decide the window size
  const SDL_VideoInfo *info = SDL_GetVideoInfo ();
  taille_pixel = info->current_h / 2;


  // Decide si la fenetre permet ou non un affiche des cases
  // Dans le cas contraire, une case sera representee par un seul pixel

  if ((taille_pixel * 1.0) / AG->G->n > 1)
  {
    AG->cas_aff = 0;
    AG->taille_case = taille_pixel / AG->G->n;
  }
  else
  {
    AG->cas_aff = 1;
    AG->modulo = AG->G->n / taille_pixel;
  }


  // Initialized windowed mode with given size and flags.

  SDL_SetVideoMode (AG->taille_case * AG->G->n, AG->taille_case * AG->G->m, 0,
                    flags);

  // Enable key repeat (i.e.: when a key is kept down, the keyboard
  // event is repeteadly triggered).

  SDL_EnableKeyRepeat (SDL_DEFAULT_REPEAT_INTERVAL / 4,
                       SDL_DEFAULT_REPEAT_DELAY / 12);

  SDL_WM_SetCaption ("Sorting Robot", 0);
}


void
AffGrille_ferme_fenetre ()
{
  SDL_Quit ();
}


void
AffGrille_redessine_case (AffGrille * AG, Grille * G, int i, int j)
{

  SDL_Surface *screen = SDL_GetVideoSurface ();

  if (AG->cas_aff == 0)
  {                             // Si affiche d une case possible

    if (G->T[i][j].fond != G->T[i][j].piece)
    {
      // Si la piece n est pas sur une case de meme couleur

      SDL_Rect rectangle = { j * AG->taille_case, i * AG->taille_case,
        AG->taille_case, AG->taille_case
      };
      SDL_FillRect (screen, &rectangle, AG->T_coul[G->T[i][j].fond]);


      if (G->T[i][j].piece != -1)       // Si absence de piece
        Disc (screen, (j + 0.5) * AG->taille_case,
              (i + 0.5) * AG->taille_case, 0.3 * AG->taille_case,
              AG->T_coul[G->T[i][j].piece]);
      else
        Disc (screen, (j + 0.5) * AG->taille_case,
              (i + 0.5) * AG->taille_case, 0.3 * AG->taille_case, 0);
    }
    else
    {                           // Si case noire
      SDL_Rect rectangle = { j * AG->taille_case, i * AG->taille_case,
        AG->taille_case, AG->taille_case
      };
      SDL_FillRect (screen, &rectangle, 0);
    }

    SDL_Rect robotext =
      { (j + 0.35) * AG->taille_case, (i + 0.35) * AG->taille_case,
      0.30 * AG->taille_case, 0.30 * AG->taille_case
    };
    SDL_Rect robot =
      { (j + 0.375) * AG->taille_case, (i + 0.375) * AG->taille_case,
      0.25 * AG->taille_case, 0.25 * AG->taille_case
    };

    if (G->T[i][j].robot >= -1) // Si robot present sur la case
      SDL_FillRect (screen, &robotext, 0xffffff);
    if (G->T[i][j].robot >= 0)  // Si robot porteur d une piece
      SDL_FillRect (screen, &robot, AG->T_coul[G->T[i][j].robot]);
    if (G->T[i][j].robot == -1) // Si pas de robot
      SDL_FillRect (screen, &robot, 0);


  }
  else
  {                             // Si affichage d une case impossible

    if ((i % AG->modulo == 0) && (j % AG->modulo == 0))
    {

      SDL_Rect rectangle = { j / AG->modulo, i / AG->modulo, 1, 1 };
      if (G->T[i][j].fond != G->T[i][j].piece)
        SDL_FillRect (screen, &rectangle, AG->T_coul[G->T[i][j].fond]);
      else
        SDL_FillRect (screen, &rectangle, 0);
    }
  }

}

void
AffGrille_reaffiche_Grille ()
{
  SDL_Surface *screen = SDL_GetVideoSurface ();
  screen = SDL_GetVideoSurface ();
  SDL_Flip (screen);
}
