The project is for Vimba camera, such as GT-2000, and acquiring and showing images with OpenCV and c++11 multithread.

## Install Vimba2.0

1. Follow the document named *Vimba Manual.pdf page 27th* in Document Dir to install Vimba.

2. Use **sudo -E ./VimbaViewer** to check your camera name, usually prefix with *DEV_XXXXXX*.

3. Remenber the above camera names <camera_name>. They are not changed for each camera.

## Compile and use the driver

1. Enter the DriverOpenCV dir, modify CMakeLists.txt to fit your library or header file path.

```
mkdir build
cd build
cmake ..
make
```

2. Enter build dir, use the command to start and acquire images.

```
./AsynchronousGrabConsole <camera_name> <camera_name> ....
./AsynchronousGrabConsole DEV_000F3102767B DEV_000F3102EF34 //Start two cameras called DEV_000F3102767B and DEV_000F3102EF34
```

## This is the easiest driver and welcome you to add other function.

TODO: add function about setting parameters for camera.

*If you have any problems, just issue them. I would reply you as soon as possible.*
