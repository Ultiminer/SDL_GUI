#ifndef SDL_GUI_SHAPE_COLLISION_H_
#define SDL_GUI_SHAPE_COLLISION_H_
#include "sdl_gui_wrapper.h"

namespace SG{

constexpr bool Collide(const SDL_Point& p, const SDL_Rect& rect )noexcept
{
    return (p.x>rect.x)&&(p.y>rect.y)&&(rect.x+rect.w>p.x)&&(rect.y+rect.h>p.y);
}
constexpr bool Collide(const SDL_Rect& A, const SDL_Rect& B )noexcept
{
    return (A.x+A.w>B.x)&&(A.y+A.h>B.y)&&(B.x+B.w>A.x)&&(B.y+B.h>A.y);
}







}


#endif