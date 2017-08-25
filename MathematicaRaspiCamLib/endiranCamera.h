/**********************************************************
 Software developed by Senior Software Delevoper Nimalendiran Kailasanathan
 This software is released under MIT license.
****************************************************************/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "raspicam.h"
#include <stdio.h>
#include <unistd.h>




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


        if(isGrayImage){
            if(raspicam::RASPICAM_FORMAT_GRAY != thecamera->getFormat()){
                thecamera->release();
                thecamera->setFormat(raspicam::RASPICAM_FORMAT_GRAY);
                init = false;
            }
        }else{
            if(raspicam::RASPICAM_FORMAT_RGB != thecamera->getFormat()){
                thecamera->release();
                thecamera->setFormat(raspicam::RASPICAM_FORMAT_RGB);
                init = false;

            }
        }


        if(thecamera->getWidth() != width && thecamera->getHeight()!=height){
            thecamera->release();
            thecamera->setWidth ( width );
            thecamera->setHeight ( height );
            init = false;
        }





        thecamera->setBrightness ( 50 );
        thecamera->setRotation ( 0);

        thecamera->setISO ( 400 );

        thecamera->setSharpness ( 0 );

        thecamera->setContrast ( 0 );

        thecamera->setSaturation ( 0);

        thecamera->setExposure ( raspicam::RASPICAM_EXPOSURE_AUTO );
        thecamera->setVideoStabilization(true);

        thecamera->setAWB(raspicam::RASPICAM_AWB_AUTO);




        thecamera->open();



        if ( !thecamera->open() ) {
            //  return -1;
        }


        unsigned char *data=new unsigned char[  thecamera->getImageBufferSize( )];

        if(!init){
         //When a taking a picture using Mathematica, the first pictur becomes dark.
         // Therefore a sleep is added, when taking the first picture.
            thecamera->grab();
            usleep( 300000 );
            init = true;

        }

        thecamera->grab();
        thecamera->retrieve(data);

        return data;

    }


private:
    EndiranCamera() {
        thecamera = new raspicam::RaspiCam();
        init=false;
    }

    raspicam::RaspiCam* thecamera;


public:
    static EndiranCamera* s_instance;
    bool init;


};
