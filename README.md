# RAY TRACER

Based on the book "*Ray Tracing in One Weekend*" by *Peter Shirley*. Modified to work under macOS, Linux and Windows.

## Compile

* macOS/Linux:

`$make`

* Windows using MinGW32

`>mingw32-make`

The source code has been successfully compiled on the following platforms:

* macOS (High Sierra, Catalina, Big Sur)
* Ubuntu (18.04, 20.10)
* Windows 10 using MinGW32

## Run

`$./raytracer`

## Results

Test scene has the resolution of 1280x720 and sampling count was set at 100. The higher the sampling count, the better the output result, but the time needed to render the scene is also increased. The Ray Tracer was tested under the following configurations: 

* Core i5-5257U @ 2.7Ghz (macOS High Sierra): 738.74 seconds 
* Xeon E5-2678 V3 @ 2.5Ghz (Windows 10 Pro Workstation ): 804.043 seconds
* Xeon E3-1230 V2 @ 3.3Ghz (Windows Server 2008): 1,160.75 seconds
* Core i5-4200M 2.5Ghz (Windows 10 Pro): 1,237.54 seconds
* Core 2 Duo @ 2.0Ghz (Ubuntu 18.04): 1,628.93 seconds
* Core i5-560M @ 2.6Ghz (Ubuntu 20.10): 923.821 seconds

![](https://github.com/dzutrinh/Ray-Tracing-In-One-Weekend/blob/master/out.png)
