#ifndef CONFIG_H_
#define CONFIG_H_
#include  <SDL.h>

#ifdef TEST_MODE 
#define RMV_OBJ() remove("../build/main.o")
#else 
#define RMV_OBJ()
#endif


#endif