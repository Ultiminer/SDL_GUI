#ifndef SDL_GUI_BUTTON_H_
#define SDL_GUI_BUTTON_H_

#include "sdl_gui_wrapper.h"
#include "sdl_gui_image.h"
#include "sdl_gui_shape_collision.h"


namespace SG{

struct Button
{
    int x=0; 
    int y=0;    
    int width=0;
    int height=0; 
    Image_Data* defDisplay=nullptr;
    Image_Data* onDisplay=nullptr;
    Image_Data* clickDisplay=nullptr;
    Image img;

    Button(int X, int Y, int Width, int Height):x(X),y(Y),width(Width),height(Height)
    {
        
    }
    Button(int X, int Y, int Width, int Height, Image_Data* DefDisplay ):x(X),y(Y),width(Width),height(Height),defDisplay(DefDisplay)
    {}
    Button(int X, int Y, int Width, int Height, Image_Data* DefDisplay, Image_Data* OnDisplay):x(X),y(Y),width(Width),height(Height),defDisplay(DefDisplay), onDisplay(OnDisplay)
    {}
    Button(int X, int Y, int Width, int Height, Image_Data* DefDisplay, Image_Data* OnDisplay, Image_Data* ClickDisplay):x(X),y(Y),width(Width),height(Height),defDisplay(DefDisplay), onDisplay(OnDisplay),clickDisplay(ClickDisplay)
    {}
    Button& SetX(int X)
    {
        x=X;
        return *this;
    }
    Button& SetY(int Y)
    {
        y=Y;
        return *this;
    }
    Button& SetWidth(int Width)
    {
        width=Width;
        return *this;
    }
    Button& SetHeight(int Height)
    {
        height=Height;
        return *this;
    }

    int GetX()const
    {
        return x;
    }
    int GetY()const
    {
        return y;
    }
    int GetWidth()const
    {
        return width;
    }
    int GetHeight()const
    {
        return height;
    }
    SDL_Rect GetRect()const
    {
        return {x,y,width,height};
    }

    bool IsHover()
    {
        return SG::Collide(__SG::mouse.GetP(),{x,y,width,height}); 
    }
    bool OnClick()
    {
        return __SG::mouse.IsLeft(); 
    }

    Button& Draw()
    {
        img.width=width; 
        img.height=height; 
        img.x=x; 
        img.y=y; 

        if(IsHover())
        {
            img.data=onDisplay;
            if(OnClick())img.data=clickDisplay;
            img.Draw(); 
            return *this; 
        }

        img.data=defDisplay; 
        img.Draw(); 

        
        return *this;
    }
};




};


#endif