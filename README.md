# Image Viewer
A basic fast image viewer for Linux for everyday use.
It tries to mimic usability of default image viewer of Windows 7.
 
![application screenshot](https://github.com/aldn/ImageViewer/raw/master/Doc/app_screenshot.png "Application Screenshot")

## Features
* walk through directory of image files
* view animated GIFs
* zoom 1:1, zoom to fit toggleable, arbitrary zoom
* basic editing such as rotation
* slideshow
* fullscreen mode


## Dependencies
Qt 5

## Building
##### 1. Clone
```shell
git clone https://github.com/aldn/ImageViewer.git
```
##### 2. Generate Makefile
```shell
cd ImageViewer
mkdir Build
cd Build
qmake ..
```
##### 3. Build
```shell
make
```

## Running
##### Usage
```shell
./ImageViewer [IMAGE_FILE]
```

##### Note

It tries to use icons from the current icon theme. Most of the time Qt should properly detect platform icon theme. However if running outside of desktop environment session (such as Gnome, KDE or XFCE), environment variable XDG_CURRENT_DESKTOP should be set manually, otherwise most of the icons might be missing.
E.g. put something like this to startup script:
```shell
export XDG_CURRENT_DESKTOP=gnome
```
To use selected Gnome icon theme.
