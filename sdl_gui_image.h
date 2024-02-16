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
inline struct ImageAtlas
{
std::unordered_map<const char*, Image_Data*> data; 
~ImageAtlas()
{
    for(auto& el: data)delete el.second;
    data.clear();
}

}__img_atlas;
struct Tileset_Data
{
    float frameWidth;
    float frameHeight;
    float spacingX; 
    float spacingY; 
    size_t numObjects; 
};



inline void AddImage(const char* name, const char* path,const SDL_Color& transpColor)
{
    __img_atlas.data.insert({name,new Image_Data(path,transpColor)});
}
inline Image_Data* GetImage(const char* name)
{
    return __img_atlas.data.at(name);
}

struct Image
{
    Image_Data* data=nullptr; 
    int x=0;
    int y=0; 
    int width=0; 
    int height=0; 
    double angle=0; 
    SDL_Point center={0,0};
    SDL_RendererFlip flipMode=SDL_FLIP_NONE; 

    Image(){}
    Image(Image_Data* imgData):data(imgData)
    {}
    Image(Image_Data* imgData, int X, int Y, int Width, int Height):data(imgData),x(X),y(Y),width(Width),height(Height)
    {}
    Image(Image_Data* imgData, int X, int Y, int Width, int Height, double Angle, const SDL_Point& centerOfRotation):data(imgData),x(X),y(Y),width(Width),height(Height),angle(Angle),center(centerOfRotation)
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
    Image& SetAngle(double Angle)
    {
        angle=Angle;
        return *this; 
    }
    Image& Rotate(double deltaAngle)
    {
        angle+=deltaAngle;

        return *this; 
    }
    Image& SetFlipmode(const SDL_RendererFlip& Flipmode)
    {
        flipMode=Flipmode; 

        return *this; 
    }
    Image& SetCenter(const SDL_Point& Center)
    {
        center=Center; 

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
    double GetAngle()const
    {
        return angle; 
    }
    SDL_Point GetCenter()const
    {
        return center; 
    }

    Image& Draw()
    {
        const SDL_Rect srcRect{0,0,data->width,data->height};
        const SDL_Rect destRect{x,y,width,height};

        SDL_RenderCopyEx(__SG::renderer.obj,data->text,&srcRect,&destRect,angle,&center,flipMode);

        return *this;
    }


};
struct Tileset
{
    Tileset_Data* tilesetData=nullptr; 
    Image_Data* data=nullptr; 
    int x=0;
    int y=0; 
    int width=0; 
    int height=0; 
    double angle=0; 
    SDL_Point center={0,0};
    SDL_RendererFlip flipMode=SDL_FLIP_NONE; 

    Tileset(){}
    Tileset(Image_Data* imgData,Tileset_Data* TilesetData):data(imgData),tilesetData(TilesetData)
    {}
    Tileset(Image_Data* imgData,Tileset_Data* TilesetData, int X, int Y, int Width, int Height):data(imgData),tilesetData(TilesetData),x(X),y(Y),width(Width),height(Height)
    {}
    Tileset(Image_Data* imgData,Tileset_Data* TilesetData, int X, int Y, int Width, int Height, double Angle, const SDL_Point& centerOfRotation):data(imgData),tilesetData(TilesetData),x(X),y(Y),width(Width),height(Height),angle(Angle),center(centerOfRotation)
    {}


    Tileset& SetWidth(int Width)
    {
        width=Width; 
        return *this; 
    }
    Tileset& SetHeight(int Height)
    {
        height=Height; 
        return *this; 
    }
    Tileset& SetX(int X)
    {
        x=X; 
        return *this; 
    }
    Tileset& SetY(int Y)
    {
        y=Y; 
        return *this; 
    }
    Tileset& SetAngle(double Angle)
    {
        angle=Angle;
        return *this; 
    }
    Tileset& Rotate(double deltaAngle)
    {
        angle+=deltaAngle;

        return *this; 
    }
    Tileset& SetFlipmode(const SDL_RendererFlip& Flipmode)
    {
        flipMode=Flipmode; 

        return *this; 
    }
    Tileset& SetCenter(const SDL_Point& Center)
    {
        center=Center; 

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
    double GetAngle()const
    {
        return angle; 
    }
    SDL_Point GetCenter()const
    {
        return center; 
    }

    Tileset& Draw(size_t obj, size_t el)
    {
        const SDL_Rect srcRect{0,0,data->width,data->height};
        const SDL_Rect destRect{x,y,width,height};

        SDL_RenderCopyEx(__SG::renderer.obj,data->text,&srcRect,&destRect,angle,&center,flipMode);

        return *this;
    }


};





};



#endif