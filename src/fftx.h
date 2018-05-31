#ifndef FFTX_H
#define FFTX_H

#include <cmath>
#include "eden.h"

//#define size_t unsigned int
#define FloatingType float

class FFTX
{
public:
    FFTX();
    ~FFTX();
    void Init(size_t FourierBase, int FourierWindow, double WinFactor);
    void FFT(FloatingType real[], FloatingType imag[]);
    void FFTW(FloatingType real[], FloatingType imag[]);
    void IFFT(FloatingType real[], FloatingType imag[]);
    FloatingType Magnitude(FloatingType real, FloatingType imag);
    FloatingType Phase(FloatingType real, FloatingType imag);
private:
    int FourierWindow_;
    size_t FourierBase_;
    FloatingType * cos_table;
    FloatingType * sin_table;
    FloatingType * FourierWindowVals;
    unsigned int Fourier_levels;
    FloatingType roundf(FloatingType V);
    void transform_radix2_init(size_t n);
    void transform_radix2(FloatingType real[], FloatingType imag[], size_t n);
};

#endif // FFTX_H
