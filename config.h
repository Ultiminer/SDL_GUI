#ifndef CONFIG_H_
#define CONFIG_H_

#ifdef TEST_MODE 
#define RMV_OBJ() remove("../build/main.o")
#else 
#define RMV_OBJ()
#endif
#ifndef WINDOW_TITLE 
#define WINDOW_TITLE "SDL_GUI"
#endif
#ifndef WINDOW_WIDTH 
#define WINDOW_WIDTH 800
#endif
#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 600
#endif
#ifndef WINDOW_FLAGS
#define WINDOW_FLAGS SDL_WINDOW_SHOWN 
#endif
#ifndef RENDERER_FLAGS
#define RENDERER_FLAGS SDL_RENDERER_PRESENTVSYNC 
#endif


#endif