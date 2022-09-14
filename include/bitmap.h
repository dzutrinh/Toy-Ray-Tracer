#ifndef _BITMAP_H_
#define _BITMAP_H_
#include <fstream>

// represent an RGB bitmap
class bitmap {
public:
    bitmap() {
        this->data = NULL;
        this->w = this->h = 0;
        this->init = false;
    }

    bitmap(long w, long h) {
        create(w, h);
    }  

    bool create(long w, long h) {
        this->data = new char[w * h * 3];
        if (this->data) {
            this->init = true;
            this->w = w;
            this->h = h;
            return true;
        }
        return false;
    }

    void destroy() {
        if (this->data) {
            delete []this->data;
            this->data = NULL;
            this->init = false;
        }
    }

    ~bitmap() { destroy(); }

    inline long offset(int x, int y) { return (long(y * this->w) + x) * 3; }

    void plot(long x, long y, long r, long g, long b)  {
        // no range check here
        //if (x < 0 || x >= this->w) return;
        //if (y < 0 || y >= this->h) return;
        char * p = this->data + ((y * this->w + x) * 3);
        (*p++) = r;
        (*p++) = g;
        (*p++) = b;
    }

    bool save(std::string filename) {
	    // write a Portable Pixmap P6 image
        if (init && this->data) {
            std::ofstream of;
            of.open(filename, std::ios::out | std::ios::binary);
            of << "P6" << std::endl << this->w << " " << this->h << std::endl << "255" << std::endl;
            of.write(bits(), size());
            of.close();
            return true;
        }
        return false;
    }

    char * bits() const { return this->data; }

    long width() const { return this->w; }

    long height() const { return this->h; }

    long size() const { return this->w * this->h * 3; }

private:
    char * data;
    long w, h;
    bool init;
};

#endif
