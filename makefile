CXX=g++
TARGET=raytracer
CFLAGS=-O3 -fopenmp --std=c++11 -o $(TARGET)
LDFLAGS=-lm -lpthread
HEADERS=vec3.h \
		ray.h \
		sphere.h \
		hitable.h \
		hitable_list.h \
		material.h \
		rng.h \
		camera.h
SOURCE=main.cpp

all: $(SOURCE) $(HEADERS)
	$(CXX) $(CFLAGS) $(SOURCE) $(LDFLAGS)

clean:
	rm -f $(TARGET)

