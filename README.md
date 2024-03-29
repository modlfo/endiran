# Endiran

### An autonomous robot based in the Raspberry Pi

#### Author: Nimalendiran Kailasanatham

## Introduction

In the near future we will see autonomous cars on the roads. Actually we already have cars with autonomous capabilities such as parallel parking functions and systems that keep the car within the marked driving lanes etc. Many car manufactures, are investing in autonomous cars as it is going to be the future.

So how does a car drive by itself? As an electrical engineer specializing in automation and robot technology this topic has always been of great interest to me, and it has helped me lay the foundation for the whole mental process required for advanced system development. The answer to the question is to be found in machine learning and artificial intelligence.

During my childhood, I was always interested in building robots. After taking an online Stanford University machine learning course, I decided to build my own autonomous robot.

At the outset of such a project, there are a number of important considerations to bear in mind. First and foremost there are the economic considerations, where the cost of the final product must be competitive. Furthermore, my goal was to keep the building and programming of the robot as user - friendly and simple as possible. This would entail minimizing the number of lines of code, so you would not be required to have an engineering background or have taken a course in machine learning and artificial Intelligence to be able to use the robot.

So how can I make a simple and cheap autonomous robot without needing to spend unnecessary money on software? 

Special thanks to my good friend and colleague Leonardo Ruiz Laguna for the implementation help.


## Hardware and Software

The approximate cost of the parts necessary to buils Endiran is $200.

1. Raspberry Pi™ 3 Model B 1GB Project Board, running Raspberry Raspbian - estimated price $35.
2. 8MP Raspberry Pi™ Camera Module - $25
3. Arduino Mega Development Board - $45.99
4. Dagu Rover 5 Tracked Chassis with four Encoders - $60
5. Rover 5 Motor Driver Board - $22

You can use any motor or even a RC car together with the above mentioned hardware. Please note, the reason for using an 
Arduino is that Endiran has four encoders and ultra-sonic sensors (available for new features in the future), and therefore 
more inputs are needed compared to just using the Raspberry Pi. 

The brain of Endiran is developed in Wolfram Mathematica, which is included on every Raspberry Pi. The programing language also includes a host of powerful free tools for image processing and analysis as 
well as a wide range of integrated machine learning capabilities. Furthermore, this powerful tool spares the effort of writing 
advanced machine learning algorithms, as the algorithms are already built into the programing language.

The Arduino is programmed using Vult. Vult is a simple open source programming language that makes easy to write signal processing code (like control systems) and generates efficient c++ code that can be run in an Arduino. The language is developed by my good friend and colleague Dr. Leonardo Ruiz Laguna. You can find more about the language on: https://modlfo.github.io/vult.

This repository contains all the code of Endiran clasified in the following directories:

1. [Arduino](https://github.com/modlfo/endiran/tree/master/Arduino): The control program running in the Arduino Mega.
2. [MachineLearning](https://github.com/modlfo/endiran/tree/master/MachineLearning): The Mathematica code to control, and train the robot.
3. [MathematicaRaspiCamLib](https://github.com/modlfo/endiran/tree/master/MathematicaRaspiCamLib): Mathematica bindings for the [RaspiCamLib](https://github.com/cedricve/raspicam.git) used to control the camera.

The following diagram shows how the different components are conencted:


![Endiran Hardware Connections Diagram](https://github.com/modlfo/endiran/blob/master/Wiki/Images/Endiran_Connection_Diagram.png?raw=true)


## Endiran?

Constructing  a  robot  is  not  just  about  soldering  and  programming.  Nowadays,  you  have  to  come  up  with  a  suitable  name  as well. So the inescapable question posed itself: "What should I call my self-driving robot?”

While tediously 3D-printing parts for my robot, an idea struck my mind - much like Newton's apple dropping down right smack
in  the  middle  of  his  brilliant  head.  Pondering  why  my  parents  named  me  "Nimalendiran"  -  and  trust  me!  this  is  not  the  first time  I  have  thought  about  it,  since  almost  everyone  I  know  have  asked  me  the  same  question  -  a  plausible  answer  finally presented itself. According to the foremost authority on the subject - my parents - "Nimal" is the "real" name, and "endiran" is merely an extension, an "add-on" if you like. But why endiran?

Finally I got it! In Tamil "Endiran" means "Robot". It seems like my parents knew right from their first peek into my cradle that I was destined to become an engineer within the field of robotics. Like Einstein's E=MC^2, I have reduced my insight to a simple equation:

Nimal + Robot = Nimalendiran

Well back to what the name for the robot should be: Destiny has spoken...

Say hello to Endiran :)

![Endiran](https://github.com/modlfo/endiran/blob/master/Wiki/Images/endiranFrontView.JPG?raw=true)
![Endiran](https://github.com/modlfo/endiran/blob/master/Wiki/Images/endiranSideView.JPG?raw=true)
 
