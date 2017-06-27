/**********************************************************
 Software developed by Senior Software Delevoper Nimalendiran Kailasanathan
 This software is released under MIT license.
****************************************************************/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "raspicam.h"


class EndiranCamera
{
public:
    static EndiranCamera* instance()
    {
        if (!s_instance)
            s_instance = new EndiranCamera();
        return s_instance;
    }


    bool open() {
        return thecamera->open();
    }


    int width() {
        return thecamera->getWidth();
    }

    int size() {
        return thecamera->getImageBufferSize();
    }

    int height() {
        return thecamera->getHeight();
    }

    void release() {
        thecamera->release();
    }

    unsigned char* getImage(bool isGrayImage, int width,int height) {

        int iso=800;

        if(isGrayImage){
            thecamera->setFormat(raspicam::RASPICAM_FORMAT_GRAY);
        }else{
            thecamera->setFormat(raspicam::RASPICAM_FORMAT_RGB);
        }

        thecamera->setWidth ( width );
        thecamera->setHeight ( height );




        thecamera->setBrightness ( 50 );
        thecamera->setRotation ( 0);

        thecamera->setISO ( 400 );

        thecamera->setSharpness ( 0 );

        thecamera->setContrast ( 0 );

        thecamera->setSaturation ( 0);

        thecamera->setExposure ( raspicam::RASPICAM_EXPOSURE_AUTO );
 thecamera->setVideoStabilization(true);





 thecamera->open();



        if ( !thecamera->open() ) {
            //  return -1;
        }

        unsigned char *data=new unsigned char[  thecamera->getImageBufferSize( )];

        thecamera->grab();
        thecamera->retrieve(data);


        return data;

    }


private:
    EndiranCamera() {
        thecamera = new raspicam::RaspiCam();
    }

    raspicam::RaspiCam* thecamera;

public:
    static EndiranCamera* s_instance;


};

