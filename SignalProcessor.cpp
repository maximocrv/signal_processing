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
void SignalProcessor::getNoiseRemovedSignal() {
    for (double &c : mNoiseRemovedSignal) {
        std::cout << c << "\n";
    }
}


/** Function for different types of noise removing:
 *        - moving_average: simple average of signal over a window
 *        - exponential_average: averaging, what use mixing with previous value in signal
 * \param window: averaging size
 * \param flag: type of Noise removing
 * \param m: mixing parameter
 */
void SignalProcessor::RemoveNoise(int window, string flag, double m) {
    if (flag == "moving_average") {

        double avg = accumulate(mSignal.begin(), mSignal.begin() + window - 1, 0.0) / (double) window;
        mNoiseRemovedSignal.push_back(avg);

        for (int i = window; i < mSignal.size(); i++) {
            avg -= mSignal[i - window] / window;
            avg += mSignal[i] / window;
            mNoiseRemovedSignal.push_back(avg);
        }
    } else if (flag == "exponential_average") {
        mNoiseRemovedSignal.push_back(mSignal[0]);

        for (int i = 1; i < mSignal.size(); i++) {
            double EMA = m * mSignal[i] + (1 - m) * mNoiseRemovedSignal[i - 1];
            mNoiseRemovedSignal.push_back(EMA);
        }

        mNoiseRemovedSignal = mSignal;
    } else {
        std::cout << "Please input a valid flag ('moving_average', 'exponential_average')" << "\n";
    }
}


/** Method generating output file containing bin intervals and their corresponding bin frequencies for the signal
 * intensity
 * \param n_bins: number of intervals into the signal
 */
void SignalProcessor::GenerateHistogram(int n_bins) {
    auto sorted_signal = new vector<double>;
    *sorted_signal = mSignal;
    std::sort(sorted_signal->begin(), sorted_signal->end());

//    mSortedSignal = std::sort(mSignal->begin(), mSignal->end()); check initialization to avoid unnecessarily sorting
    int min = floor(sorted_signal->front());
    int max = ceil(sorted_signal->back());
    double bin_width = ((double) max - (double) min) / (double) n_bins;

    std::cout << "bin minimum: " << min << "\t bin maximum: " << max << "\n";

    vector<int> bin_frequencies(n_bins);
    int counter = 0;

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
        std::cout << "bin start: " << min + (double) bin * bin_width << "\t bin end: "
                  << min + (double) (bin + 1) * bin_width
                  << "\t bin frequency: " << bin_frequencies[bin] << "\n";
    }

    std::cout << "Vector size" << sorted_signal->size() << "\t sum bin frequencies (should be equal): " <<
              accumulate(bin_frequencies.begin(), bin_frequencies.end(), 0) << "\n";
    delete sorted_signal;
}
