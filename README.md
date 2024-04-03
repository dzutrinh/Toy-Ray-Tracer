# TOY RAY TRACER

Based on the book [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by *Peter Shirley*. Modified to work under macOS, Linux and Windows and utilized OpenMP.

## Changes
* Replaced the built-in RNG (rand()) with xorshf96 (https://github.com/raylee/xorshf96).
* Utilized OpenMP for faster rendering time.
* Several modifications were made to the source code.

## Compile

* macOS/Linux:

`$make`

* Windows using MinGW32/64

`>mingw32-make`

The source code has been successfully compiled and tested on the following platforms:

* macOS (High Sierra, Catalina, Big Sur, Monterey)
* Ubuntu (18.04, 20.10, 22.04)
* Windows 10 Pro

## Run

For single-threaded application
`$./bin/<platform>/raytracer`	

For multi-threaded application
`$./bin/<platform>/raytracer_mp`

Replace <platform> with 'linux', 'dawrwin', 'win32', 'win64' depends on your actual OS. Output image is Portable Pixmap Image (P6).
## Results

Test scene has the resolution of 1280x720 and sampling count was set at 100. The higher the sampling count, the better the output result, but the time needed to render the scene is also increased. See the included benchmark.txt for more details.

![](https://github.com/dzutrinh/Ray-Tracing-In-One-Weekend/blob/master/output.png)
