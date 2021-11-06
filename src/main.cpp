
#include <SDL.h>
#include <libtcod.h>

#include <cstdlib>

int main(int argc, char** argv) {
  TCOD_ContextParams params{};
  params.tcod_version = TCOD_COMPILEDVERSION;
  params.argc = argc;
  params.argv = argv;
  params.vsync = 1;
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.window_title = "Template Rouguelite";

  tcod::ConsolePtr console = tcod::new_console(80, 50);
  params.columns = console->w;
  params.rows = console->h;

  tcod::ContextPtr context = tcod::new_context(params);


//Player:
int playerX = 40;
int playerY = 25;
std::string playerChar = "@";





  // Game loop.
  while (true) {
    // Rendering.
    TCOD_console_clear(console.get());
    //tcod::print(*console, 0, 0, "Hello World", &TCOD_white, nullptr, TCOD_BKGND_SET, TCOD_LEFT);
    tcod::print(*console, playerX, playerY, playerChar, &TCOD_white, nullptr, TCOD_BKGND_SET, TCOD_LEFT);
    context->present(*console);

    // Handle input.
    SDL_Event event;
    SDL_WaitEvent(nullptr);
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
            case SDLK_RIGHT:
              playerX++;
              break;

            case SDLK_LEFT:
              playerX--;
              break;

            case SDLK_UP:
              playerY--;
              break;

            case SDLK_DOWN:
              playerY++;
              break;


            default:
              break;
          }


          break;
        case SDL_QUIT:
          std::exit(EXIT_SUCCESS);
          break;
      }
    }
  }
  return 0;
}
