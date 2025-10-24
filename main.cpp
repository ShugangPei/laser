#include "ModelProcessor.h"
#include <iostream>

#include <sstream>

#define LAYER_HEIGHT 0.1f
#define y_direction { 0.0f, 0.0f,1.0f }

int main() {
    MultiSTLManager manager;


//激光不旋转

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);





    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, -75, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 0.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, -66, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 0.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, -57, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 0.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, -48, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 0.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, -39, 0, 1.0f, 550.0f, 300.0f, 0.1f, 90.0f, 0.0f, 0, 240.0f, 600.0f);






    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -47, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -38, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -29, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -20, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", -11, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);





   

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, -26, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f , 0.0f, 90.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, -17, 0, 1.0f, 550.0f, 300.0f, 0.1f, 0.0f, 90.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, -8, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, 1, 0, 1.0f, 550.0f, 300.0f, 0.1f, 45.0f, 45.0f, 0, 240.0f, 600.0f);

    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 2, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 11, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 20, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 29, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
    //manager.addModel("C:\\Users\\90819\\Desktop\\777.stl", "1", 38, 10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 60.0f, 30.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -28.25, -18, 0.1, 1.0f, 550.0f, 225.0f, 0.1f, 23.0f, 67.0f, 1, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -28.25, -18, 0.0, 1.0f, 550.0f, 250.0f, 0.1f, 23.0f, 67.0f, 1, 240.0f, 600.0f);
//
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -25, -28, 0,1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -14, -28, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -3, -28, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 8, -28, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 19, -28, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//
manager.addModel(
    "C:\\Users\\90819\\Desktop\\zft.stl", "1",
    0, 0, 0,
    1.0f, 550.0f, 300.0f,
    0.1f, 23.0f, 0.0f,
    0, 240.0f, 600.0f,
    true,      // 棋盘格
    5.0f,      // 岛宽（mm）
	0.0f,      // 岛重叠：两个岛块在边界处有多少重合宽度（mm）
	0.0f       // 偶数/奇数岛扫描偏移:奇偶岛里的扫描线是否错位以及错多少
);

//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -25, -17, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -14, -17, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -3, -17, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 8, -17, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 19, -17, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -25, -6, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -14, -6, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -3, -6, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 8, -6, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 19, -6, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);

//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -25, 5, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -14, 5, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -3, 5, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 8, 5, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 19, 5, 0, 1.0f, 400.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);


//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 40, -27, 0,1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 51, -27, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 62, -27, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 73, -27, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 84, -27, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 40, -16, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 51, -16, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 62, -16, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 73, -16, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 84, -16, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 40, -5, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 51, -5, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 62, -5, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 73, -5, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 84, -5, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 40, 6, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 51, 6, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 62, 6, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 73, 6, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 84, 6, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 40, 17, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 51, 17, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 62, 17, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 73, 17, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 84, 17, 0, 1.0f, 500.0f, 500.0f, 0.1f, 0.0f, 67.0f, 0, 240.0f, 600.0f);
//
//
//

////manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -19, 12, 0, 1.0f, 700.0f, 350.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", -8, 12, 0, 1.0f, 700.0f, 350.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 3, 12, 0, 1.0f, 700.0f, 350.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
//manager.addModel("C:\\Users\\90819\\Desktop\\chilun.stl", "1", 14, 12, 0, 1.0f, 900.0f, 350.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);



   //manager.addModel("C:\\Users\\90819\\Desktop\\1010.stl", "1",-8.7, -23, 0, 1.0f, 550.0f, 300.0f, 0.1f,23.0f, 67.0f, 0, 240.0f, 600.0f);
   //manager.addModel("C:\\Users\\90819\\Desktop\\1010.stl", "1", -8.7, -10, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
   //manager.addModel("C:\\Users\\90819\\Desktop\\1010.stl", "1", -8.7, 3, 0, 1.0f, 640.0f, 400.0f, 0.1f, 120.0f, 120.0f, 0, 240.0f, 600.0f);

   //manager.addModel("C:\\Users\\90819\\Desktop\\12-12-12.stl", "1", -32.5, -53, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);

   //manager.addModel("C:\\Users\\90819\\Desktop\\12-12-12.stl", "1", -32.5, -53, 0, 1.0f, 550.0f, 300.0f, 0.1f, 23.0f, 67.0f, 0, 240.0f, 600.0f);
 
  

    std::vector<std::string> modelCommandFiles;
    std::vector<MultiSTLManager::ModelInfo> modelInfos;

    // 调整模型位置
    manager.adjustModelPosition(0, 0, 0, 0);

    float layerHeight = LAYER_HEIGHT;
    float directionVector[3] = y_direction;

    // 处理每个模型
    for (size_t i = 0; i < manager.getModelCount(); ++i) {
        std::ostringstream commandFileName;
        commandFileName << "C:\\output\\model_" << i << "_commands.txt";
        modelCommandFiles.push_back(commandFileName.str());
        modelInfos.push_back(manager.getModelInfo(i));
        ModelProcessor::processModel(manager, i, layerHeight, directionVector);
    }

    // 生成组合的命令文件，传递模型信息
    ModelProcessor::generateCombinedCommands(modelCommandFiles, "C:\\output\\combined_commands.txt", modelInfos);

    std::cout << "所有模型处理完成。请检查输出文件。" << std::endl;

    return 0;
}


