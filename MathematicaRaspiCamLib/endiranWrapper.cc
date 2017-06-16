/**********************************************************
 Software developed by Senior Software Delevoper Nimalendiran Kailasanathan
 This software is released under MIT license.
****************************************************************/

#include "endiranWrapper.h"
#include "raspicam.h"
#include <stdio.h>
#include <string.h>

EndiranCamera *EndiranCamera::s_instance = 0;
raspicam::RaspiCam* var = NULL;

extern "C" {

DLLEXPORT int open_wrapper(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    EndiranCamera* camera = EndiranCamera::instance();

    MArgument_setBoolean(Res,camera->open());

    return LIBRARY_NO_ERROR;

}


DLLEXPORT int release_wrapper(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    EndiranCamera* camera = EndiranCamera::instance();
    camera->release();

    MArgument_setBoolean(Res,true);

    return LIBRARY_NO_ERROR;

}

DLLEXPORT int getImage_wrapper(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res){

    EndiranCamera* camera = EndiranCamera::instance();

    const char *imageType;
    imageType = MArgument_getUTF8String(Args[0]);
    std::string imageTypeStr(imageType);

    int width =  MArgument_getInteger(Args[1]);
    int height = MArgument_getInteger(Args[2]);


    MImage image_out;

    WolframImageLibrary_Functions imgFuns = libData->imageLibraryFunctions;

    if (imageTypeStr == "Gray") {
        raw_t_ubit8 * raw_data = (raw_t_ubit8*)camera->getImage(true, width, height);

        imgFuns->MImage_new2D(camera->width(), camera->height(), 1,
                              MImage_Type_Bit8, MImage_CS_Gray, 1,
                              &image_out);

        memcpy(imgFuns->MImage_getByteData(image_out),
               raw_data,
               camera->width() * camera->height() * 1 * sizeof(raw_t_ubit8));

           delete[] raw_data;

       } else  {
           raw_t_ubit8 * raw_data = (raw_t_ubit8*)camera->getImage(false, width, height);

           imgFuns->MImage_new2D(camera->width(), camera->height(), 3,
                                 MImage_Type_Bit8, MImage_CS_RGB, 1,
                                 &image_out);

           memcpy(imgFuns->MImage_getByteData(image_out),
                  raw_data,
                  camera->width() * camera->height() * 3 * sizeof(raw_t_ubit8));

           delete[] raw_data;

       }


   MArgument_setMImage(Res,image_out);

   return LIBRARY_NO_ERROR;


}


}

