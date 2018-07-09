CXX=g++
TARGET=raytracer
CFLAGS=-O3 --std=c++11 -o $(TARGET)
LDFLAGS=-lm
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

