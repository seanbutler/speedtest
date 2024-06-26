#include <iostream>
#include <chrono>

#include <unistd.h>

#include <matplot/matplot.h>

const long int dim = 4*1024;
const long int max_iterations = 32;

const long int rows = dim;
const long int cols = dim;

const long int array_size = cols * rows;

void exp_rowfirst()
{
    std::vector<int> timings{};

    // lets run it many times in a row to see what happens?
    for (int iterations = 0; iterations < max_iterations; ++iterations)
    {
        // int *array = new int[cols * rows];
        int *array = (int*) malloc(sizeof(int)*cols*rows);

        auto start = std::chrono::high_resolution_clock::now();

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                array[(y * cols) + x] *= rand();
            }
        }

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        free(array);

        timings.push_back((double)duration.count());
    }

    matplot::plot(timings);
}

void exp_colfirst()
{

    std::vector<int> timings{};

    // lets run it many times in a row to see what happens?
    for (int iterations = 0; iterations < max_iterations; ++iterations)
    {
        int *array = (int*) malloc(sizeof(int)*cols*rows);

        auto start = std::chrono::high_resolution_clock::now();

        for (int x = 0; x < cols; ++x)
        {
            for (int y = 0; y < rows; ++y)
            {
                array[(y * cols) + x] = rand();
            }
        }

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        free(array);

        timings.push_back((double)duration.count());
    }

    matplot::plot(timings);
}

int main(int argc, char *argv[])
{
    matplot::title("Row First Array Access Time Plot");

    matplot::xlabel("Run");
    matplot::ylabel("Time");
    matplot::hold(matplot::on);

    sleep(1);

    exp_rowfirst();

    sleep(1);

    exp_colfirst();

    sleep(1);

    matplot::show();

    return 0;
}
