# How to build the Raspberry Pi camera library for Wolfram Mathematica.

Clone the repository to your Raspberry Pi. Then, uncompress the files and compile:

mkdir build

cd build

cmake ../

make

sudo make install

sudo ldconfig

Check the install/lib folder for the mathematica camera lib file.

# How to load camera library in Wolfram Mathematica.
In order to laod the library in Mathematica execute the following commands in Mathematica (remember to replace the library URL):

raspiCamLib = FindLibrary["/home/pi/Documents/github/endiran-build/MathematicaRaspiCamLib/libraspicam.so.0.1.6"];

mathematicaCamLib = FindLibrary["/home/pi/Documents/github/endiran-build/MathematicaRaspiCamLib/libMathematicaRaspiCamLib.so"];

LibraryLoad[mathematicaCamLib]

capture = LibraryFunctionLoad[mathematicaCamLib, "getImage_wrapper", {{"UTF8String"}, {Integer}, {Integer}}, LibraryDataType[Image]];

Test the camera :

capture["RGB", 320, 160]
