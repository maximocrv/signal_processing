//
// Created by Sergei Kliavinek & Maximo Cravero.
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
void FourierTransform::butterfly(vector<comp> &signal, int step, comp w)
{
    comp pow(1.0, 0.0);
    int n = step/2;
    for(int i = 0; i < n; i++) {
        comp p = signal[i];
        comp q = signal[i+n]*pow;
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
    int a=2;
    while (a<n) {
        a = a * 2;
    }
    try {
        if (a != n){
            throw -1;
        }
    }
    catch (int b) {
        cerr<<"Length of input signal is not a power of 2."\
        <<" Change it. Cut the length of signal to the "<<double(a)/2<<" or increase to the "<<a;
    }
}

/**
 * Computes the Fourier transform using FFT with some auxiliary functions defined above.
 *              \param[in] signals - input time-dependent signal, which the function should transform
 *              \param[out]  signal - output frequency-dependent signal
 *              Transformed signal saved in  mFourierSignal parameter.
 */

void FourierTransform::FastFourierTransform(vector<double>& signals, vector<comp>& signal) {
    if(signal.empty()) {
        for (int i=0; i<signals.size(); i+=1) {
            signal.push_back(comp(signals[i], 0.0));
        }
    }
    vector <comp> slice;
    checkpower2(signal.size());
    mFourierSignal = signal;
    reposition(signal);
    int N = signal.size();
    comp w = exp(comp(0.0, -2.0 * PI / N));
    stack<comp> ws;
    for (int step = N; step != 1; step /= 2) {
        ws.push(w);
        w *= w;
    }

    for (int step = 2; step <= N; step *= 2) {
        w = ws.top();
        ws.pop();
        for (int i=0; i < N; i += step) {
            for (int k= i; k< i+step; k++){
                slice.push_back(signal[k]);
            }
            butterfly(slice,step, w);
            for (int k= i; k< i+step; k++){
                signal[k] = slice[k-i];
            }
            slice= {};
        }
    }
    for (int i = 0; i < signal.size(); i++)
        signal[i] = comp(round(signal[i].real()*1000000)/1000000,round(signal[i].imag()*1000000)/1000000);
    mFourierFrequency = signal;
}

/**
 * Computes the inverse Fourier transform using FFT with some auxiliary functions defined above.
 *              \param[in] signals - input time-dependent signal, which the function should transform
 *              \param[out] signal - output time-dependent signal
 *              Transformed signal saved in  mFourierSignal parameter.
 */
void FourierTransform::InverseFourierTransform(vector<double>& signals, vector<comp>& signal)
{
    if(signal.empty()) {
        for (int i=0; i<signals.size(); i+=1) {
            signal.push_back(comp(signals[i], 0.0));
        }
    }
    checkpower2(signal.size());
    conjugate(signal);
    FastFourierTransform(signals, signal);
    conjugate(signal);
    int size = signal.size();
    for (int i = 0; i < size; i++)
        signal[i] = signal[i] / (double) size;
    mFourierFrequency = mFourierSignal;
    mFourierSignal=signal;
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
void FourierTransform::FFTFilter(vector<double>& signals, double percentage,vector <comp>& signal){
    FastFourierTransform(signals, signal);
    vector<comp> input_signal = mFourierSignal;
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
    vector<comp> out_signal = {};
    for (int i=0; i<signal.size(); i++){
        out_signal.push_back(comp(0));
    }
    int i=0;
    while ((((sum_final+res[i].first)/sum)< (percentage/100))&&(i<signal.size())){
        sum_final +=res[i].first;
        out_signal[res[i].second]=signal[res[i].second];
        i+=1;
    }
    mFourierFrequencyClean = out_signal;
    InverseFourierTransform(signals,out_signal);
    mFourierSignalClean = out_signal;
    mFourierFrequency = signal;
    mFourierSignal = input_signal;
    signal = out_signal;
}

/**
 * Function for output result on the screen
 * \param label: the parameter, that you want to print:
 *              clean frequency, frequency, signal, clean signal
 *
 */
void FourierTransform::Print(string label) {
    vector<comp> output;
    try {
        if (label == "clean frequency") {
            output = mFourierFrequencyClean;
        } else if (label == "frequency") {
            output = mFourierFrequency;
        } else if (label == "signal") {
            output = mFourierSignal;
        } else if (label == "clean signal") {
            output = mFourierSignalClean;
        }
        else {
            throw -1;
        }
    }
    catch (int a) {
            cerr<<"Incorrect label.";
    }
    cout << "Index" << " " << "Real_Part"<<" "<<"Imagine_part"<<" "<<"Amplitude"<<"\n";
    for (int i=0; i<(output.size()); i++){
        cout << i << " " << output[i].real()<<" "<<output[i].imag()<<" "\
            <<sqrt(pow(output[i].real(),2)+pow(output[i].imag(),2)) << '\n';
    }
    cout << std::endl;
}

/**
 * Function for save result in the separate file
 * \param filename: path to the file
 * \param label: the parameter, that you want to print:
 *     clean frequency, frequency, signal, clean signal
 */
void FourierTransform::SaveFile(string filename, string label) {
    vector<comp> output;
    try {
        if (label == "clean frequency") {
            output = mFourierFrequencyClean;
        } else if (label == "frequency") {
            output = mFourierFrequency;
        } else if (label == "signal") {
            output = mFourierSignal;
        } else if (label == "clean signal") {
            output = mFourierSignalClean;
        }
        else {
            throw -1;
        }
    }
    catch (int a) {
        cerr << "Incorrect label.";
    }
    std::ofstream out;
    out.exceptions(ofstream::badbit);
    try {
        out.open(filename);
        out << "Index" << " " << "Real_Part"<<" "<<"Imagine_part"<<" "<<"Amplitude"<<"\n";
        for (int i=0; i<(output.size()); i++){
            out << i << " " << output[i].real() << " " << output[i].imag() << " " \
            << sqrt(pow(output[i].real(),2) + pow(output[i].imag(),2)) << '\n';
        }
        out.close();
    }
    catch (const ofstream::failure& e) {
        cerr << "A file opening error has occurred. Please try again.";
    }
}
