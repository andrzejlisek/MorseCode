#include "fftx.h"

FFTX::FFTX()
{
    /*cos_table[4500];
    sin_table[4500];
    FourierWindowVals[9000];*/
    cos_table = new FloatingType[4000000];
    sin_table = new FloatingType[4000000];
    FourierWindowVals = new FloatingType[8000000];
}

FFTX::~FFTX()
{
    delete[] cos_table;
    delete[] sin_table;
    delete[] FourierWindowVals;
}

#define FourierMinThreshold 0.001
#define FourierResolutionV 256.0
#define FourierResolutionB 8

FloatingType FFTX::roundf(FloatingType V)
{
    if (V < 0)
    {
        return ceil(V - 0.5);
    }
    else
    {
        return floor(V + 0.5);
    }
}

// #define size_t unsigned long
#define Xmalloc(X) (FloatingType*)malloc(X)
#define Xcalloc(X, Y) (FloatingType*)calloc(X, Y)
#define Xmemdup(X, Y) (FloatingType*)memdup(X, Y)

#define cos(X) cosf(X)
#define sin(X) sinf(X)

#define FloatingType float




void FFTX::Init(size_t FourierBase, int FourierWindow, double WinFactor)
{
    size_t I;
    FourierWindow_ = FourierWindow;
    FourierBase_ = FourierBase;
    transform_radix2_init(FourierBase);

    double FourierBaseX = FourierBase >> 1;
    int WinT = round((FourierBaseX * (1024.0 - WinFactor)) / 1024.0);
    for (I = 0; I < FourierBase; I++)
    {
        FourierWindowVals[I] = 0;
    }
    if (FourierWindow == 0)
    {
        // Rectangle
        for (I = WinT; I < (FourierBase - WinT); I++)
        {
            FourierWindowVals[I] = 1;
        }
    }
    if (FourierWindow == 1)
    {
        // Triangle
        for (I = WinT; I < (FourierBase - WinT); I++)
        {
            FloatingType T1 = (I - WinT) * 2;
            FloatingType T2 = FourierBase - WinT - WinT;
            FloatingType T3 = (T1 - T2) / T2;
            if (T3 >= 0)
            {
                FourierWindowVals[I] = 1.0 - T3;
            }
            else
            {
                FourierWindowVals[I] = 1.0 + T3;
            }
        }
    }
    if (FourierWindow == 2)
    {
        // Hanning
        for (I = WinT; I < (FourierBase - WinT); I++)
        {
            FloatingType T1 = (I - WinT);
            FloatingType T2 = FourierBase - WinT - WinT - 1;
            FourierWindowVals[I] = (0.5 - 0.5 * cos(2 * M_PI * (T1 / T2)));
        }
    }
    if (FourierWindow == 3)
    {
        // Blackman
        for (I = WinT; I < (FourierBase - WinT); I++)
        {
            FloatingType T1 = I - WinT;
            FloatingType T2 = (FourierBase - WinT - WinT) - 1;
            FourierWindowVals[I] = ((0.42 - 0.5 * cos(2 * M_PI * (T1 / T2))) + (0.08 * cos(4 * M_PI * (T1 / T2))));
        }
    }
    if (FourierWindow == 4)
    {
        // Hamming
        for (I = WinT; I < FourierBase - WinT; I++)
        {
            FloatingType T1 = I - WinT;
            FloatingType T2 = FourierBase - WinT - WinT - 1;
            FourierWindowVals[I] = (0.54 - 0.46 * cos(2 * M_PI * (T1 / T2)));
        }
    }
}

void FFTX::transform_radix2_init(size_t n)
{
    size_t i;

    // Compute levels = floor(log2(n))
    {
        size_t temp = n;
        Fourier_levels = 0;
        while (temp > 1)
        {
            Fourier_levels++;
            temp >>= 1;
        }
    }

    // Trignometric tables
    for (i = 0; i < n / 2; i++)
    {
        cos_table[i] = cos(2 * M_PI * i / n);
        sin_table[i] = sin(2 * M_PI * i / n);
    }
}

void FFTX::transform_radix2(FloatingType real[], FloatingType imag[], size_t n)
{
    size_t size;
    size_t i;
    size_t x;

    // Bit-reversed addressing permutation
    for (i = 0; i < n; i++)
    {
        unsigned int k;
        size_t j = 0;
        x = i;
        for (k = 0; k < Fourier_levels; k++, x >>= 1)
        {
            j = (j << 1) | (x & 1);
        }

        if (j > i)
        {
            FloatingType temp = real[i];
            real[i] = real[j];
            real[j] = temp;
            temp = imag[i];
            imag[i] = imag[j];
            imag[j] = temp;
        }
    }

    // Cooley-Tukey decimation-in-time radix-2 FFT
    for (size = 2; size <= n; size *= 2)
    {
        size_t halfsize = size / 2;
        size_t tablestep = n / size;
        for (i = 0; i < n; i += size)
        {
            size_t j;
            size_t k;
            for (j = i, k = 0; j < i + halfsize; j++, k += tablestep)
            {
                FloatingType tpre =  real[j+halfsize] * cos_table[k] + imag[j+halfsize] * sin_table[k];
                FloatingType tpim = -real[j+halfsize] * sin_table[k] + imag[j+halfsize] * cos_table[k];
                real[j + halfsize] = real[j] - tpre;
                imag[j + halfsize] = imag[j] - tpim;
                real[j] += tpre;
                imag[j] += tpim;
            }
        }
        if (size == n)  // Prevent overflow in 'size *= 2'
        {
            break;
        }
    }
}



void FFTX::FFT(FloatingType real[], FloatingType imag[])
{
    uint I;
    transform_radix2(real, imag, FourierBase_);
    for (I = 0; I < FourierBase_; I++)
    {
        real[I] = real[I] / FourierBase_;
        imag[I] = imag[I] / FourierBase_;
    }
}
void FFTX::FFTW(FloatingType real[], FloatingType imag[])
{
    uint I;
    for (I = 0; I < FourierBase_; I++)
    {
        real[I] = real[I] * FourierWindowVals[I];
        imag[I] = 0;
    }
    transform_radix2(real, imag, FourierBase_);
    for (I = 0; I < FourierBase_; I++)
    {
        real[I] = real[I] / FourierBase_;
        imag[I] = imag[I] / FourierBase_;
    }
}
void FFTX::IFFT(FloatingType real[], FloatingType imag[])
{
    transform_radix2(imag, real, FourierBase_);
}

FloatingType FFTX::Magnitude(FloatingType real, FloatingType imag)
{
    return sqrt((real * real) + (imag * imag));
}

FloatingType FFTX::Phase(FloatingType real, FloatingType imag)
{
    if (((real * real) + (imag * imag)) < 0.00001)
    {
        return 0;
    }
    else
    {
        return atan2(real, imag);
    }
}
