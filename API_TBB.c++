#include <tbb/parallel_for.h>
#include <iostream>

int main()
{
    tbb::parallel_for(0, 10, [](int i)
                      { std::cout << "Iteración " << i << std::endl; });
    return 0;
}
