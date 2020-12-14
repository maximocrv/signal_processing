//
// Created by Sergei Kliavinek & Maximo Cravero on 30/11/2020.
//

#include "FourierTransform.hpp"

using namespace std;
const double PI = acos(-1);

void conjugate(vector<comp> vector);

/* Default constructor */
FourierTransform::FourierTransform(){};

/* Destructor */
FourierTransform::~FourierTransform(){};

/*A set of butterfly transformations that occur during a Fourier transform.
 * parameters: vector <comp> array - the vector in which we perform permutations
 *             comp w - turning factor
 * return: vector <comp> array, which has already been converted.
*/
void FourierTransform::butterfly(vector<comp> &signal, comp w)
{
    comp pow(1.0, 0.0);
    int n = signal.size()/2;

    for(int i = 0; i < n; i++) {
        comp p = signal[i];
        comp q = signal[i+n]*w;
        signal[i] = p + q;
        signal[i+n] = p - q;
        pow *= w;
    }
}

/*
 * Given a number ``x'' returns the number which has the same bits as ``x'',
 * but in the reverse order
 * parameters: unsigned int x - number in decimal number system
 *             int length - the length of the binary representation of a number
 * return: int result  - binary representation of the "reverse" number
 */
unsigned int FourierTransform::backwards(unsigned int x, int length)
{
    unsigned int result = 0;
    unsigned int bit = 1u;
    unsigned int reverse = 1u<<(length-1);
    for(int i = 0; i < length && x != 0; i++) {
        if(x & bit) {
            result |= reverse;
            x &= ~bit;
        }
        bit <<= 1;
        reverse >>= 1;
    }
    return result;
}

/*
 * Permutes elements in an array using the "backward" function.
 * parameters: vector<comp> *signal - array, where we permut the elements
 */
void FourierTransform::reposition(vector<comp> &signal)
{
    // Determine the bit length
    int length = 0;
    int size = signal.size();
    while(1u << length < (unsigned int)size)
        length++;
    for(int i = 0; i < size; i++) {
        int j = backwards(i, length);
        if(i <= j)
            swap(signal[i], signal[j]);
    }
}

/*
 * Computes the Fourier transform using FFT with some auxiliary functions defined above.
 */
void FourierTransform::FastFourierTransform(vector<double>* signals,vector<comp>* signal, bool invert = false) {
    if(signal->empty()) {
        for (int i = 0; i < signals->size(); i++) {
            signal->push_back(((*signals)[i], 0.0));
        }
    }
    reposition(*signal);
    int N = signal->size();
    comp w = exp(comp(0.0, 2.0 * PI / N));
    stack<comp> ws;
    for (int step = N; step != 1; step /= 2) {
        ws.push(w);
        w *= w;
    }

    for (int step = 2; step <= N; step *= 2) {
        w = ws.top();
        ws.pop();
        for (int i; i <= N; i *= 2) {
            butterfly(*(signal + i), w);
        }
    }

    mFourierSignal = *signal;
}

/*
 * Computes the inverse Fourier transform using FFT with some auxiliary functions defined above.
 */
void FourierTransform::inverse_fourier_transform(vector<double>* signals, vector<comp>* signal)
{
    for (int i=0; i<signals->size(); i++){
        signal->push_back(((*signals)[i], 0.0));
    }
    conjugate(*signal);
    FastFourierTransform(signals, signal, false);
    conjugate(*signal);
    int size = signal->size();
    for(int i = 0; i < size; i++)
        (*signal)[i] = (*signal)[i] / (double)size;
}


/*
 * Replaces every element of the vector by its complex conjugate.
 */
void FourierTransform::conjugate(vector<comp> &signal)
{
    int size = signal.size();
    for(int i = 0; i < size; i++)
        signal[i] = conj(signal[i]);
}

bool FourierTransform::pairCompare(const pair<double, int>& firstElem, const pair<double, int>& secondElem) {
    return firstElem.first > secondElem.first;

}
void FourierTransform::FFT_filter(vector<double>& signals, double percentage){
    vector <comp> signal;
    FastFourierTransform(&signals, &signal, false);
    vector <double> amplitudes(signal.size());
    vector<pair<double,int>> res;
    if (percentage<0){
        percentage=0;
    }
    else if (percentage>100){
        percentage=100;
    }
    // compute the amplitudes for each frequency
    for (int i=0; i<signal.size(); i++){
        double real_squad = (double)signal[i].real()*(double)signal[i].real();
        double image_squad=(double)signal[i].imag()*(double)signal[i].imag();
        amplitudes[i] =sqrt(real_squad+image_squad);
        auto p = make_pair(amplitudes[i], i);
        res.push_back(p);
    }
    //sorting frequency numbers by amplitude
    sort(res.begin(), res.end(), pairCompare);
    double sum = accumulate(amplitudes.begin(), amplitudes.end(), 0.0);
    double sum_final = 0;
    for (int i=0; i<signal.size(); i++){
        signals[i]=0;
    }
    int i=0;
    while ((((sum_final+res[i].first)/sum)< (percentage/100))&&(i<signals.size())){
        sum_final +=res[i].first;
        signals[res[i].second]=res[i].first;
        i+=1;
    }
    //InverseFastFourierTransform(signal);
}
