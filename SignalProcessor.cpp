//
// Created by Maximo Cravero on 27/11/2020.
//

#include <cmath>
#include <numeric>
#include <algorithm>
#include "SignalProcessor.hpp"

using namespace std;


/** Default constructor */
SignalProcessor::SignalProcessor() = default;


/** Custom constructor (automatically sets default signal when instantiating class) */
SignalProcessor::SignalProcessor(const AudioFile<double> &signal) {
    for (int i = 0; i < signal.getNumSamplesPerChannel(); i++) {
        mSignal.push_back(signal.samples[0][i]);
    }
}


/** Destructor, clean field mSignal and mNoiseRemovedSignal */
SignalProcessor::~SignalProcessor() {
    mSignal.clear();
    mNoiseRemovedSignal.clear();
}


/**
 * Methods for signal setting (saving)
 * \param signal: input signal
 */
template<typename T>
void SignalProcessor::SetSignal(const T &signal) {
    for (int i = 0; i < signal.getNumSamplesPerChannel(); i++) {
        mSignal.push_back(signal.samples[0][i]);
    }
}


/** Get raw signal
 * \return mSignal: saved signal
 */
std::vector<double> SignalProcessor::getRawSignal() {
    return mSignal;
}


/** Get noise removed signal
 * \return mNoiseRemovalSignal: saved signal
 */
std::vector<double> SignalProcessor::getNoiseRemovedSignal() {
    return mNoiseRemovedSignal;
}


/** Function for different types of noise removing:
 *        - moving_average: simple average of signal over a window
 *        - exponential_average: averaging, what use mixing with previous value in signal
 * \param window: averaging size
 * \param flag: type of Noise removing
 * \param m: mixing parameter
 */
void SignalProcessor::RemoveNoise(int window, const string& flag, double m) {
    try {
        if ((flag != "moving_average") && ((flag != "exponential_average"))){
            throw -1;
        }
    }
    catch (int a) {
            cerr << "Please input a valid flag ('moving_average', 'exponential_average')" << "\n";
    }
    if (flag == "moving_average") {
        try {
            if (window<=1){
                throw -1;
            }
        }
        catch (int a) {
                cerr << "Window can't be smaller than 1. Increase it.";
        }

        double avg = accumulate(mSignal.begin(), mSignal.begin() + window - 1, 0.0) / (double) window;
        mNoiseRemovedSignal.push_back(avg);

        for (int i = window; i < mSignal.size(); i++) {
            avg -= mSignal[i - window] / window;
            avg += mSignal[i] / window;
            mNoiseRemovedSignal.push_back(avg);
        }
    } else if (flag == "exponential_average") {

        try {
            if ((m > 1) || (m < 0)){
                throw -1;
            }
        }
        catch (int a) {
            cerr<<"Mixing factor should be between 0 and 1. Change it.";
        }
        mNoiseRemovedSignal.push_back(mSignal[0]);

        for (int i = 1; i < mSignal.size(); i++) {
            double EMA = m * mSignal[i] + (1 - m) * mNoiseRemovedSignal[i - 1];
            mNoiseRemovedSignal.push_back(EMA);
        }

        mNoiseRemovedSignal = mSignal;
    }
}


/** Method generating output file containing bin intervals and their corresponding bin frequencies for the signal
 * intensity
 * \param n_bins: number of intervals into the signal
 */
void SignalProcessor::GenerateHistogram(int n_bins, const string& filename) {
    try {
        if (n_bins<=1){
            throw -1;
        }
    }
    catch (int a) {
        cerr << "n_bins should be bigger than 1. Please change it.";
    }

    auto sorted_signal = new vector<double>;
    *sorted_signal = mSignal;
    std::sort(sorted_signal->begin(), sorted_signal->end());

//    mSortedSignal = std::sort(mSignal->begin(), mSignal->end()); check initialization to avoid unnecessarily sorting
    int min = floor(sorted_signal->front());
    int max = ceil(sorted_signal->back());
    double bin_width = ((double) max - (double) min) / (double) n_bins;

//    std::cout << "bin minimum: " << min << "\t bin maximum: " << max << "\n";

    vector<int> bin_frequencies(n_bins);
    int counter = 0;

    std::ofstream out;
    out.exceptions(ofstream::badbit);
    try {
        out.open(filename);
        out << "bin_left" << " " << "bin_right" << " " << "frequency" << "\n";

        for (int bin = 0; bin < n_bins; bin++) {
            double current = sorted_signal->at(counter);
            double lower = min + (double) bin * bin_width;
            double upper = min + (double) (bin + 1) * bin_width;

            // int bin_value = 0;
            while (current > lower && current <= upper && counter < sorted_signal->size() - 1) {
                bin_frequencies[bin]++;
                counter++;
                current = sorted_signal->at(counter);
            }
            out << min + (double) bin * bin_width << " " << min + (double) (bin + 1) * bin_width << " "
                << bin_frequencies[bin] << "\n";
        }
    }
    catch (const ofstream::failure& e){
        cerr << "A file opening error has occurred. Please try again.";
    }

    out.close();

    std::cout << "Vector size" << sorted_signal->size() << "\t sum bin frequencies (should be equal): " <<
              accumulate(bin_frequencies.begin(), bin_frequencies.end(), 0) << "\n";

    delete sorted_signal;
}

void SignalProcessor::SaveFile(const string& filename) {
    std::ofstream out;
    out.exceptions(ofstream::badbit);
    try {
        out.open(filename);
        out << "index" << " " << "signal_value" << "\n";
        for (int i=0; i < mNoiseRemovedSignal.size(); i++){
            out << i << " " << mNoiseRemovedSignal[i] << '\n';
        }
        cout << std::endl;
    }
    catch (const ofstream::failure& e) {
        cerr << "A file opening error has occurred. Please try again.";
    }
    out.close();
}