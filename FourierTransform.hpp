//
// Created by Maximo Cravero on 29/11/2020.
//


#ifndef SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP
#define SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP

#include <complex>
#include <vector>

class FourierTransform {
public:
    // Constructors and destructors
    FourierTransform();
    ~FourierTransform();

    // Methods
    void FastFourierTransform(std::vector<double>* time_signal);
    std::vector<double> InverseFastFourierTransform();

private:
    std::vector<std::complex<double>> mFourierSignal;

};


#endif //SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP
