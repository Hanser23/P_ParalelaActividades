#include <omp.h>
void normalize_omp(float *x, float minv, float maxv, int n)
{
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        x[i] = (x[i] - minv) / (maxv - minv + 1e-8f);
    }
}
