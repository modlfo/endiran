/**********************************************************
 Software developed by Senior Software Delevoper Nimalendiran Kailasanathan
 This software is released under MIT license.
****************************************************************/

#ifndef __ENDIRANWRAPPER_H
#define __ENDIRANWRAPPER_H

#include "WolframLibrary.h"
#include "WolframImageLibrary.h"
#include "endiranCamera.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RaspiCam RaspiCam;

DLLEXPORT int open_wrapper(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT int getImage_wrapper(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT int release_wrapper(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);



#ifdef __cplusplus
}
#endif
#endif
