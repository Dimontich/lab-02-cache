// Copyright 2019 Dimontich
#include <algorithm>
#include <random>
#include "Experiment.h"

Experiment::Experiment(uint64_t number)
{
    elements_amount = number;
    buffer = new uint64_t[elements_amount];

    std::srand(clock());
    for (uint64_t i = 0; i < elements_amount; ++i)
        buffer[i] = rand_r(reinterpret_cast<unsigned int *>(1));
}

void Experiment::Direct_passage()
{
    uint64_t value = 0;

    auto begin = std::chrono::system_clock::now();
    for (size_t i = 0; i < 1000; i++)
        for (size_t j = 0; j < elements_amount; j++)
            value = buffer[j];
    auto end = std::chrono::system_clock::now();
    buffer[0] = value;

    time.direct = std::chrono::duration_cast<std::chrono::milliseconds>(
            end - begin).count();
}

void Experiment::Reverse_passage()
{
    uint64_t value = 0;

    auto begin = std::chrono::system_clock::now();
    for (size_t i = 0; i < 1000; i++)
        for (size_t j = elements_amount; j > 0; j--)
            value = buffer[j];
    auto end = std::chrono::system_clock::now();
    buffer[0] = value;

    time.reverse = std::chrono::duration_cast<std::chrono::milliseconds>(
            end - begin).count();
}

void Experiment::Random_passage()
{
    int64_t value = 0;
    std::vector<uint64_t> index;
    for (size_t i = 0; i < elements_amount; i++)
        index.push_back(i);
    std::shuffle(index.begin(), index.end(), std::mt19937(
            std::random_device()()));

    auto begin = std::chrono::system_clock::now();
    for (size_t i = 0; i < 1000; i++)
        for (size_t j : index)
            value = buffer[j];
    auto end = std::chrono::system_clock::now();
    buffer[0] = value;

    time.random = std::chrono::duration_cast<std::chrono::milliseconds>(
            end - begin).count();
}

void Experiment::Begin_passages()
{
    Direct_passage();
    Reverse_passage();
    Random_passage();
}

Experiment::~Experiment()
{
    delete[] buffer;
}


