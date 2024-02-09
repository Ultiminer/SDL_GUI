#ifndef SDL_GUI_WRAPPER_H_
#define SDL_GUI_WRAPPER_H_
#include <SDL.h>
#include "config.h"
#define SDL_main WinMain

void inline __SDL_GUI_INIT()noexcept
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

}
void inline __SDL_GUI_Close()noexcept
{
    SDL_Quit();
}
namespace __SG{
inline struct Window{
SDL_Window* obj; 


Window()
{
    obj=SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_FLAGS);
}
~Window()
{
    SDL_DestroyWindow(obj);
}
}window=Window(); 


inline struct Renderer{
SDL_Renderer* obj; 


Renderer()
{
    obj=SDL_CreateRenderer(window.obj,-1,RENDERER_FLAGS);
}
~Renderer()
{
    SDL_DestroyRenderer(obj);
}
}renderer=Renderer(); 

inline struct Event{
SDL_Event* obj; 


Event()
{
    obj=new SDL_Event();
}
~Event()
{
    delete obj;
}
}event=Event(); 




}


#define SG_Start(condition) __SDL_GUI_INIT(); while(__SG::event.obj->type!=SDL_QUIT&&((condition)==true)){SDL_RenderClear(__SG::renderer.obj);
#define SG_End() SDL_RenderPresent(__SG::renderer.obj);SDL_PollEvent(__SG::event.obj);} __SDL_GUI_Close();
#define SG_UseColor(r,g,b,a) SDL_SetRenderDrawColor(__SG::renderer.obj,(r),(g),(b),(a));



#endif