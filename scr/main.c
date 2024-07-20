#include "game.c"
#include "menu.c"

int main(void) {
  init();

  enum State game_state = GAME;

  while (true) {
    switch (game_state) {
    case MENU:
      menu(&game_state);
      break;
    case GAME:
      game(&game_state);
      break;
    case OVER:
      break;
    }
  }

  quit();
}
