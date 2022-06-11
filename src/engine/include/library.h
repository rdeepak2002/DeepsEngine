#ifndef NATIVE_LIBRARY_H
#define NATIVE_LIBRARY_H

extern "C" {
class polygon {
protected:
    double side_length_;

public:
    polygon()
            : side_length_(0) {}

    virtual ~polygon() {}

    void set_side_length(double side_length) {
        side_length_ = side_length;
    }

    virtual double area() const = 0;
};

// the types of the class factories
typedef polygon* create_t();
typedef void destroy_t(polygon*);
}

#endif

//#ifndef NATIVE_LIBRARY_H
//#define NATIVE_LIBRARY_H
//
//#pragma once
//
//extern "C" {
//void print_name(const char* type);
//}
//
//#endif //NATIVE_LIBRARY_H
