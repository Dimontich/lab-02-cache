#include <header.hpp>
#include <iostream>
#include <vector>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;



void report(int number, int& buffer_size) {
    std::cout << "- experiment:\n";
    std::cout << "number:" << number+1 << std::endl;
    std::cout << "input_data:\n";
    std::cout << " buffer_size:" << buffer_size << " kb" << std::endl;
    std::cout << "results:\n";
}

class HashMemory
{
    std::vector <int> Exp;
    friend void report(int number, int& buffer_size);
public:

    void ExpNumOne()
    {
        srand(0);


        std::cout << "\ninvestigation:\n";
        std::cout << "travel_variant: straight" << std::endl;
        std::cout << "experiments:\n";
        int g = Exp.size();

        for (int i=0; i< g; i++) // прямой проход массива
        {
            // инициализация + прогревание буффера
            int n = Exp[i]*1024/sizeof(int);
            int *array = new int[n];
            for (int j = 0; j<n; j++)
            {
                array[j]=rand() % 100;
                array[j]*=15;
                array[j]+=90;
            }

            // циклический проход

            auto t1 = Clock::now();

            for (int j = 0; j<1000; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    array[k]*=1000;
                }
            }

            auto t2 = Clock::now();


            report (i,Exp[i]);

            std::cout << " duration:" << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
                      << " nanoseconds" << std::endl;


        }



    }

    void ExpNumSec()
    {
        srand(0);

        std::cout << "\ninvestigation:\n";
        std::cout << "travel_variant: reverse" << std::endl;
        std::cout << "experiments:\n";

        int g = Exp.size();

        for (int i=0; i< g; i++) // обратный проход массива
        {
            // инициализация + прогревание буффера
            int n = Exp[i]*1024/sizeof(int);
            int *array = new int[n];
            for (int j = 0; j<n; j++)
            {
                array[j]=rand()% 100;;
                array[j]*=15;
                array[j]+=90;
            }

            // циклический проход

            auto t1 = Clock::now();

            for (int j = 0; j<1000; j++)
            {
                for (int k = n-1; k>=0; k--)
                {
                    array[k]*=1000;
                }
            }

            auto t2 = Clock::now();


            report (i,Exp[i]);

            std::cout << " duration:" << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
                      << " nanoseconds" << std::endl;


        }

    }

    void ExpNumThird()
    {
        srand(0);

        std::cout << "\ninvestigation:\n";
        std::cout << "travel_variant: random" << std::endl;
        std::cout << "experiments:\n";
        int g = Exp.size();

        for (int i=0; i< g; i++) // случайный проход массива
        {
            // инициализация + прогревание буффера
            int n = Exp[i]*1024/sizeof(int);
            int *array = new int[n];
            for (int j = 0; j<n; j++)
            {
                array[j]=rand()% 100;;
                array[j]*=15;
                array[j]+=90;
            }

            for (int k = 0; k < n; k++)
            {
                std::swap(array[k], array[rand() % n]);
            }

            // циклический проход

            auto t1 = Clock::now();

            for (int j = 0; j<1000; j++)
            {
                for (int k = 0; k<n; k++)
                {
                    array[k]*=1000;
                }
            }

            auto t2 = Clock::now();


            report (i,Exp[i]);

            std::cout << " duration:" << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
                      << " nanoseconds" << std::endl;

        }


    }


    HashMemory()
    {
        int CS1 = 128; // первый уровень кэша
        const auto MAXSIZE = 1.5 * 3*1024; // максимум, 3 уровень кэша
        auto n = CS1*1/2; // минимум, первый эксперимент
        while (n<MAXSIZE)
        {
            Exp.push_back(n);
            n*=2;
        }
        Exp.push_back(MAXSIZE);
    }
};





int main ()
{
    HashMemory Object;
    Object.ExpNumOne();
    Object.ExpNumSec();
    Object.ExpNumThird();

}
