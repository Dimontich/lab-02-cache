#include "Investigation.h"


Investigation::Investigation()
{
    buffer.first_size = 0.5 * cache.min_size;
    buffer.current_size = buffer.first_size;
    buffer.last_size = 1.5 * cache.max_size;
}

void Investigation::Begin_expirement()
{
    uint64_t elements_amount = buffer.first_size / sizeof(uint64_t);
    uint64_t cache_size_degree = log2(buffer.first_size);
    while (buffer.current_size <= buffer.last_size)
    {
        auto *experiment = new Experiment(elements_amount);
        experiment->Begin_passages();
        result.push_back(experiment);
        cache_size_degree++;
        buffer.current_size = pow(2, cache_size_degree);
        elements_amount = buffer.current_size / sizeof(uint64_t);
    }
}

void Investigation::End_expirement(std::ofstream& file)
{
    file << "investigaion:" << std::endl;
    file << "	travel_order: \"Direction\"" << std::endl;
    file << "	experiments:" << std::endl;
    file << "	- experiment:" << std::endl;
    for (size_t i = 0; i < result.size(); i++)
    {
        file << "		number: " << i + 1 << std::endl;
        file << "		input_data:" << std::endl;
        file << "			buffer_size:" << result[i]->elements_amount * sizeof(uint64_t) / 1024<< " kB" << std::endl;
        file << "		results:" << std::endl;
        file << "			duration:" << result[i]->time.direct << " ms" << std::endl;
    }

    file << "investigaion:" << std::endl;
    file << "	travel_order: \"Reverse\"" << std::endl;
    file << "	experiments:" << std::endl;
    file << "	- experiment:" << std::endl;
    for (size_t i = 0; i < result.size(); i++)
    {
        file << "		number: " << i + 1 << std::endl;
        file << "		input_data:" << std::endl;
        file << "			buffer_size:" << result[i]->elements_amount * sizeof(uint64_t) / 1024<< " kB" << std::endl;
        file << "		results:" << std::endl;
        file << "			duration:" << result[i]->time.reverse << " ms" << std::endl;
    }

    file << "investigaion:" << std::endl;
    file << "	travel_order: \"Random\"" << std::endl;
    file << "	experiments:" << std::endl;
    file << "	- experiment:" << std::endl;
    for (size_t i = 0; i < result.size(); i++)
    {
        file << "		number: " << i + 1 << std::endl;
        file << "		input_data:" << std::endl;
        file << "			buffer_size:" << result[i]->elements_amount * sizeof(uint64_t) / 1024 << " kB" << std::endl;
        file << "		results:" << std::endl;
        file << "			duration:" << result[i]->time.random << " ms" << std::endl;
    }
}

Investigation::~Investigation()
= default;

