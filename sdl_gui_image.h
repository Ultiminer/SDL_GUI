#ifndef SDL_GUI_IMAGE_H_
#define SDL_GUI_IMAGE_H_

#include "sdl_gui_wrapper.h"
#include <unordered_map>



namespace SG{
struct Image_Data
{
    SDL_Texture* text; 
    int width; 
    int height; 
    Image_Data(const char* path,const SDL_Color& transpColor)
    {
        SDL_Surface* tempSurface= SDL_LoadBMP(path);
        uint32_t color_key=SDL_MapRGBA(tempSurface->format,transpColor.r,transpColor.g,transpColor.b,transpColor.a);
        SDL_SetColorKey(tempSurface,SDL_TRUE,color_key);
        text=SDL_CreateTextureFromSurface(__SG::renderer.obj,tempSurface);
        SDL_QueryTexture(text,NULL,NULL,&width,&height);
        SDL_FreeSurface(tempSurface);
    }
    ~Image_Data()
    {
        SDL_DestroyTexture(text);
    }
};
inline std::unordered_map<const char*, Image_Data>__img_atlas;
inline void AddImage(const char* name, const char* path,const SDL_Color& transpColor)
{
    __img_atlas.insert({name,Image_Data(path,transpColor)});
}
inline Image_Data GetImage(const char* name)
{
    return __img_atlas.at(name);
}

class Image
{
    Image_Data data; 
    int width=0; 
    int height=0; 
    int x=0;
    int y=0; 
    Image(const Image_Data& imgData):data(imgData)
    {}
    Image(const Image_Data& imgData, int X, int Y, int Width, int Height):data(imgData),x(X),y(Y),width(Width),height(Height)
    {}
   
    Image& SetWidth(int Width)
    {
        width=Width; 
        return *this; 
    }
    Image& SetHeight(int Height)
    {
        height=Height; 
        return *this; 
    }
    Image& SetX(int X)
    {
        x=X; 
        return *this; 
    }
    Image& SetY(int Y)
    {
        y=Y; 
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
};



};



#endif