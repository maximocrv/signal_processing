//
// Created by Sergei Kliavinek & Maximo Cravero on 30/11/2020.
//


#ifndef SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP
#define SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP

#include <complex>
#include <vector>
#include <stack>

using namespace std;
typedef complex<double> comp;

class FourierTransform {
public:
    // Constructors and destructors
    FourierTransform();
    ~FourierTransform();

    // Methods
    void FastFourierTransform(vector<comp>* signal, bool invert);
    vector<double> InverseFastFourierTransform();

private:
    vector<comp> mFourierSignal;

    void butterfly(vector<comp> &array, comp w);
    unsigned int backwards(unsigned int x, int length);
    void reposition(vector<comp> &array);

};


#endif //SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP
