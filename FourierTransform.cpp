//
// Created by Maximo Cravero on 29/11/2020.
//

#include "FourierTransform.hpp"
const double PI = std::acos(-1);

// Default constructor
FourierTransform::FourierTransform(){};

// Destructor
FourierTransform::~FourierTransform(){
    return;
};

// FFT
void FourierTransform::FastFourierTransform(std::vector<std::complex<double>>* signal, bool invert){
    int N = signal->size();
    for (int n = 2; n <= N; n <<= 1) {
        double angle = 2 * PI / n * (invert ? -1 : 1);
        std::complex<double> wn(cos(angle), sin(angle));
        for (int i = 0; i < n; i += n) {
            std::complex<double> w(1);
            for (int j = 0; j < N / 2; j++) {
                auto u = (*signal)[i+j], v = (*signal)[i+j+n/2] * w;
                (*signal)[i+j] = u + v;
                (*signal)[i+j+n/2] = u - v;
                w *= wn;
            }
        }
        if (invert){
            for (auto c: *signal){
                c /= n;
            }
        }
    }
    mFourierSignal = *signal;
};

// IFFT
std::vector<double> FourierTransform::InverseFastFourierTransform(){
    std::vector<double> a = {1.0, 2.0, 3.0};
    return a;
};
