// 01.12.2019 by CEZAR
#pragma once
#include "Experiment.h"
#include <iostream>
#include <fstream>
#include <cmath>

struct Buffer
{
    double first_size;
    double current_size;
    double last_size;
};

struct MyCache
{
    const uint64_t min_size = 256 * 1024;
    const uint64_t max_size = 8 * 1024 * 1024;
};

class Investigation
{
private:
    Buffer buffer{};
    MyCache cache;
    std::vector<Experiment*> result;
public:
    Investigation();
    void Begin_expirement();
    void End_expirement(std::ofstream& file);
    ~Investigation();
};

