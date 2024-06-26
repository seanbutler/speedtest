#include <iostream>
#include <chrono>
#include <unistd.h>
#include <matplot/matplot.h>

double work_on_array(long int array_size = 32 * 1024, int stride = 1, int max_runs = 10)
{
    long int *array = (long int *)malloc(sizeof(long int) * array_size);

    // lets run it many times in a row to see what happens?
    auto start = std::chrono::high_resolution_clock::now();

    for (long int run = 0; run < max_runs; ++run)
    {
        for (long int x = 0; x < array_size; x += stride)
        {
            array[x] = rand();
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    free(array);
    return (double)duration.count();
}


int main(int argc, char *argv[])
{
    const int runs = 4*1024;

    std::vector<int> timings{};
    std::vector<std::string> xlabels{};
    std::vector<double> xticks{};

    matplot::title("Time vs Size with Equal Work");
    matplot::ylabel("Time");
    matplot::xlabel("Size (skips)");
    matplot::hold(matplot::on);

    int size = 32;
    int stride = 1;

    for (int n = 0; n < 16; n++)
    {
        xticks.push_back(n+1);
        xlabels.push_back(std::to_string(size) + "k (" + std::to_string(stride) +")");

        timings.push_back(work_on_array(size * 1024, stride, runs));

        size *= 2;
        stride *= 2;
    }

    matplot::xticks(xticks);
    matplot::xticklabels(xlabels);
    matplot::plot(timings);

    matplot::show();

    return 0;
}
