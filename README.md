# Multithreaded Canny Edge Detection

Opens image files and performs canny edge detection on them. Uses multithreading to improve performance.

Contains a variety of interfaces and implementations for use with normal image processing and concurrent image processing.

## Install

```bash
bash install.sh path/to/folder
```

This will create the directory if it does not exist as well as `lib` and `include` directories.

## Demo

### To run demo:

1. `make demo`
2. `./demo.exe [inputfile]`

The ``demo`` directory has multiple files demonstrating how to use:
* `CannyEdgeDetect` (demo.cpp)
* `CompositeFilter` (demo.cpp)
* Implement your own `Filter` (sample_filter.h)
* Implement your own `ThreadedFilter` (sample_threaded_filter.h)

## Shared Library (.so)

### To compile shared library:
1. `make imageio`

`libimageio.so` will be located in the lib folder.

To use it:

```bash
g++ -Wl,-rpath,lib [other compilation args...] -Llib -limageio 
```

This assumes that libimageio.so is located in the lib folder. Do note that library flags must come last.

## Run main executable

### To run:

1. `make canny`
2. `./image_processor [inputs] [filter-type: canny-edge-detect, gaussian, ...] [outputs]`
