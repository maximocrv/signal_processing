//
// Created by Sergei Kliavinek & Maximo Cravero on 30/11/2020.
//


#ifndef SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP
#define SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP

#include <complex>
#include <vector>
#include <stack>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iostream>
using namespace std;
typedef complex<double> comp;
/**
 * Class with all functions for Fast Fourier transformation
 */
class FourierTransform {
public:
    // Constructors and destructors
    FourierTransform();
    ~FourierTransform();

    // Methods
    void FastFourierTransform(vector<double>* signals,vector<comp>* signal, bool invert = false);
    void FFT_filter(vector<double>& signals, double percentage);
    void inverse_fourier_transform(vector<double>* signals = new vector<double>, vector<comp>* signal = new vector<comp>);
    void Print();
    void Savefile(string filename);

private:
    vector<comp>* mFourierSignal;
    static bool pairCompare(const pair<double, int>& firstElem, const pair<double, int>& secondElem);
    void butterfly(vector<comp> &array, comp w);
    unsigned int backwards(unsigned int x, int length);
    void reposition(vector<comp> &array);
    static void conjugate(vector<comp> &signal);
    bool isPower2(int n)

};


#endif //SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP
