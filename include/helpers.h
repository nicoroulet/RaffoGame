#pragma once

#include <iostream>
#include <string.h>

#define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)

#define CHECK(condition, error_msg) \
    if (!condition)                 \
        std::cerr << "ERROR " << __FILENAME__  << ":" \
                  << __LINE__ << " - " <<  error_msg << std::endl;

#define DBG(x) std::cerr << #x << " = " << (x) << std::endl

#include <memory>
typedef float radians;

template <class Pointee>
using sp = std::shared_ptr<Pointee>;

template <class Pointee>
using up = std::unique_ptr<Pointee>;

