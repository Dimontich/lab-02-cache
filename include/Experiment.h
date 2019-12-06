#pragma once
#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <random>

struct Experimets_duration
{
    double direct;
    double reverse;
    double random;
};

class Experiment
{
private:
    void Direct_passage();
    void Reverse_passage();
    void Random_passage();
public:
    explicit Experiment(uint64_t number);
    uint64_t elements_amount;
    uint64_t* buffer;
    Experimets_duration time{};
    void Begin_passages();
    ~Experiment();
};


