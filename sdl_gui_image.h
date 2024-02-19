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




inline void AddImage(const char* name, const char* path,const SDL_Color& transpColor)
{
    __img_atlas.data.insert({name,new Image_Data(path,transpColor)});
}
inline Image_Data* GetImage(const char* name)
{
    return __img_atlas.data.at(name);
}

struct AnimationData{
    size_t iA; size_t jA; size_t iB; size_t jB; float frameW; float frameH; size_t numCols; size_t numRows; size_t FPS; 
    size_t ticks=0; float x; float y; 
};
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
    AnimationData animData={0};

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
    Image& Draw(size_t x, size_t y, size_t numCols, size_t numRows)
    {
        const float tWidth{data->width/numCols};
        const float tHeight{data->height/numRows};
        const SDL_Rect srcRect{x*tWidth,y*tHeight,tWidth,tHeight};
        const SDL_Rect destRect{x,y,width,height};

        SDL_RenderCopyEx(__SG::renderer.obj,data->text,&srcRect,&destRect,angle,&center,flipMode);

        return *this;
    }
    Image& SetupAnimation(size_t iA, size_t jA,size_t iB, size_t jB ,size_t numCols, size_t numRows, size_t FPS)
    {
        animData={iA,jA,iB,jB,(float)data->width/numCols,(float)data->height/ numRows,numCols,numRows,FPS};
        animData.x=iA*animData.frameW;
        animData.y=jA*animData.frameH;

        return *this;
    }
    Image& Animate()
    {  
        if(animData.ticks+1000/animData.FPS>SDL_GetTicks())return *this;

        if(animData.x+animData.frameW>animData.iB*animData.frameW && animData.y+animData.frameH>animData.jB*animData.frameH )
        {
            animData.x=animData.iA*animData.frameW;
            animData.y=animData.jA*animData.frameH;
            return *this;
        }

        if(animData.x<data->width-animData.frameW)
        animData.x+=animData.frameW;
        else 
        animData.y+=animData.frameH;

        animData.ticks=SDL_GetTicks();
        return *this;
    }
    
    Image& SetAnimationFrame(size_t i, size_t j)
    {
        animData.x=i*animData.frameW;
        animData.y=j*animData.frameH;

        return *this;
    }
    Image& AnimationDraw()
    {
        const SDL_Rect srcRect{animData.x,animData.y,animData.frameW,animData.frameH};
        const SDL_Rect destRect{x,y,width,height};

        SDL_RenderCopyEx(__SG::renderer.obj,data->text,&srcRect,&destRect,angle,&center,flipMode);

        return *this;
    }



};






};



#endif