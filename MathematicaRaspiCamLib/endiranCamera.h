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
        thecamera->setISO(iso);
        thecamera->setBrightness(50);

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

