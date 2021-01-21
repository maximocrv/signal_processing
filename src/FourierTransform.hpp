//
// Created by Sergei Kliavinek & Maximo Cravero.
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
 * Class with all functions for Fast Fourier Transform. Consists of the main functions for FFT, iFFT and FourierFilter.
 * Has a single private field:
 * \param mFourierSignal class vector<comp>*.
 */
class FourierTransform {
public:
    // Constructors and destructors
    FourierTransform();
    ~FourierTransform();

    // Methods
    void FastFourierTransform(vector<double>& signals,vector<comp>& signal);
    void FFTFilter(vector<double>& signals, double percentage,vector <comp>& signal);
    void InverseFourierTransform(vector<double>& signals, vector<comp>& signal);
    void Print(string label);
    void SaveFile(string filename, string label);

private:
    vector<comp> mFourierSignal;
    vector<comp> mFourierSignalClean;
    vector<comp> mFourierFrequency;
    vector<comp> mFourierFrequencyClean;
    static bool pairCompare(const pair<double, int>& firstElem, const pair<double, int>& secondElem);
    static void butterfly(vector<comp> &array,int step,  comp w);
    static int backwards(unsigned int x, int length);
    static void reposition(vector<comp> &array);
    static void conjugate(vector<comp> &signal);
    static void checkpower2(int n);

};


#endif //SIGNAL_PROCESSING_FOURIERTRANSFORM_HPP
