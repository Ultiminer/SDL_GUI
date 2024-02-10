#define TEST_MODE


#include <iostream>
#include "sdl_gui_wrapper.h"
#include "sdl_gui_image.h"



int main()
{
    RMV_OBJ();
    SG::AddImage("test","test.bmp",{255,255,255,255});
    SG::Image img=SG::GetImage("test");
    img.SetWidth(100).SetHeight(100).SetX(100).SetY(100);

    SG_Start(true);
    SG_UseColor(255,255,255,255);
    img.Draw();

    SG_End();

    return 0; 
}