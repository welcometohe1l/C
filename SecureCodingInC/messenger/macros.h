#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>

#ifndef __FUNCTION_NAME__
    #ifdef WIN32   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__  
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__ 
    #endif
#endif
#define error_message(x) fprintf(stderr, "%s: " #x, __FUNCTION_NAME__)

#endif // MACROS_H
