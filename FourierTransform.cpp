//
// Created by Sergei Kliavinek & Maximo Cravero on 30/11/2020.
//

#include <fstream>
#include "FourierTransform.hpp"

using namespace std;
const double PI = acos(-1);

void conjugate(vector<comp> vector);
typedef complex<double> comp;

/** Default constructor of class instance */
FourierTransform::FourierTransform()= default;

/** Default destructor of class instance */
FourierTransform::~FourierTransform()= default;

/** A set of butterfly transformations that occur during a Fourier transform.
 * \param:  signal - the vector in which we perform permutations
 * \param:  w - turning factor
 * \return: signal, which has already been converted
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

/**
 * Given a number ''x'' returns the number which has the same bits as ''x'',
 * but in the reverse order
 * \param:  x - number in decimal number system
 * \param:  length - the length of the binary representation of a number
 * \return:  result  - binary representation of the "reverse" number
 */
int FourierTransform::backwards(unsigned int x, int length)
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

/**
 * Permutes elements in an array using the "backward" function
 * \param: signal - array, where we permute the elements
 * \return: signal - same array with rearranged elements
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


/** Test for the number that it is a power of 2. Auxiliary class function.
 * \param: int n - length of the signal
 * */
void FourierTransform::checkpower2(int n) {
    try {
        if (((double) ((int) log2(n)) != log2(n))||(n<=1)){
            throw "Length of input signal is not a power of 2. Change it";
        }
    }
    catch (const string &str) {
        int a=2;
        while (a<n){
            a=a*2;
        }
        cerr<<"Cut the length of signal to the "<<a<<" or increase to the "<<a*2;
    }
}

/**
 * Computes the Fourier transform using FFT with some auxiliary functions defined above.
 *              \param[in] signals - input time-dependent signal, which the function should transform
 *              \param[out]  signal - output frequency-dependent signal
 *              Transformed signal saved in  mFourierSignal parameter.
 */

void FourierTransform::FastFourierTransform(vector<double>* signals, vector<comp>* signal) {
    if(signal->empty()) {
        for (int i = 0; i < signals->size(); i++) {
            signal->push_back(((*signals)[i], 0.0));
        }
    }
    checkpower2(signals->size());
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

/**
 * Computes the inverse Fourier transform using FFT with some auxiliary functions defined above.
 *              \param[in] signals - input time-dependent signal, which the function should transform
 *              \param[out] signal - output time-dependent signal
 *              Transformed signal saved in  mFourierSignal parameter.
 */
void FourierTransform::inverse_fourier_transform(vector<double>* signals, vector<comp>* signal)
{
    if(signal->empty()) {
        for (int i = 0; i < signals->size(); i++) {
            signal->push_back(((*signals)[i], 0.0));
        }
    }
    checkpower2(signals->size());
    conjugate(*signal);
    FastFourierTransform(signals, signal);
    conjugate(*signal);
    int size = signal->size();
    for (int i = 0; i < size; i++)
        (*signal)[i] = (*signal)[i] / (double) size;

    mFourierSignal = *signal;
}


/**
 * Replaces every element of the vector by its complex conjugate.
 *              \param  signal - input array for complex conjugation
 */
void FourierTransform::conjugate(vector<comp> &signal)
{
    int size = signal.size();
    for(int i = 0; i < size; i++)
        signal[i] = conj(signal[i]);
}

/**
 * Auxiliary function for comparing 2 pairs of elements by the first element.
 *              \param  firstElem - first pair for comparison
 *              \param  secondElem - second pair for comparison
 */
bool FourierTransform::pairCompare(const pair<double, int>& firstElem, const pair<double, int>& secondElem) {
    return firstElem.first > secondElem.first;

}

/**
 * Fourier filter function. Accepts a signal at the input and a percentage in amplitude to be passed through.
 * The rest is discarded as noise.
 *              \param signal - signal for filtration
 *              \param percentage - passband
 *              \return signal - filtered signal
 */
void FourierTransform::FFT_filter(vector<double>& signals, double percentage){
    vector <comp> signal;
    FastFourierTransform(&signals, &signal);
    vector <double> amplitudes(signal.size());
    vector<pair<double,int>> res;
    if (percentage < 0){
        percentage = 0;
    }
    else if (percentage > 100){
        percentage = 100;
    }
    else if(percentage < 1){
        cout << "Passband is smaller than 1 %. Do you confident, what it is right?";
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
    inverse_fourier_transform(&signals,&signal);
}


/**
 * Function for output result on the screen
 */
void FourierTransform::Print() {
    cout<<'Frequency'<<' '<<'Intensity';
    for (int i=0; i<mFourierSignal.size(); i++)
        cout << i << " "<<sqrt(pow(mFourierSignal[i].imag(),2)+pow(mFourierSignal[i].real(),2))<<'\n';
    cout << std::endl;
}

/**
 * Function for save result in the separate file
 */
void FourierTransform::Savefile(string filename) {
    std::ofstream out;
    try {
        out.open(filename);
        cout << "Frequency" << " " << "Intensity";
        for (int i=0; i<mFourierSignal.size(); i++){
            out << i << " " << sqrt(pow(mFourierSignal[i].imag(),2)+pow(mFourierSignal[i].real(),2)) << '\n';
        }
        cout << std::endl;
        out.close();
        throw "File is not open!";
    }
    catch (const string &str) {
        cerr << "A file opening error has occurred. Please try again.";
    }
}
