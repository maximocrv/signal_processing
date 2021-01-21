//
// Created by Maximo Cravero and Sergei Kliavinek.
//

#include "BaseSignalProcessor.hpp"
#include "fstream"
#include "vector"

using namespace std;

/** Custom constructor */
BaseSignalProcessor::BaseSignalProcessor(const AudioFile<double>& signal) {
    for (int i = 0; i < signal.getNumSamplesPerChannel(); i++) {
        mTimeSignal.push_back(signal.samples[0][i]);
    }
}

/** Destructor, clean field mSignal and mNoiseRemovedSignal */
BaseSignalProcessor::~BaseSignalProcessor() {
    mTimeSignal.clear();
    mFilteredTimeSignal.clear();
    mHistogram.clear();
}

/**
 * Overloaded function for setting the time signal (in this case from an AudioFile<double> variable).
 * \param signal: input signal
 */
void BaseSignalProcessor::SetTimeSignal(AudioFile<double>& signal) {
    for (int i = 0; i < signal.getNumSamplesPerChannel(); i++) {
        mTimeSignal.push_back(signal.samples[0][i]);
    }
}

/**
 * Overloaded function for setting the time signal (in this case from a vector<double> variable).
 * \param signal: input signal
 */
void BaseSignalProcessor::SetTimeSignal(vector<double>& signal){
    for (int i = 0; i < signal.size(); i++){
        mTimeSignal.push_back(signal[i]);
    }
}

/**
 * Method for saving a given file.
 * \param filename
 */
void BaseSignalProcessor::SaveTimeSignal(const string& file_name, const string& signal_name) {
    ofstream out;
    out.exceptions(ofstream::badbit);
    try {
        out.open(file_name);
        out << "index" << " " << "signal_value" << "\n";

        vector<double> output;
        if (signal_name == "filtered_signal"){
            for (int i = 0; i < mFilteredTimeSignal.size(); i++) {
                out << i << " " << mFilteredTimeSignal[i] << "\n";
            }
        } else if (signal_name == "raw_signal"){
            for (int i = 0; i < mTimeSignal.size(); i++) {
                out << i << " " << mTimeSignal[i] << "\n";
            }
        } else {
            cout << "Please fill in a valid signal to save!";
        }
        cout << endl;
    }
    catch (const ofstream::failure& e) {
        cerr << "A file opening error has occurred. Please try again.";
    }
    out.close();
}

/** Method generating output file containing bin intervals and their corresponding bin frequencies for the signal
 * intensity
 * \param n_bins: number of intervals into the signal
 */
void BaseSignalProcessor::GenerateHistogram(int n_bins) {
    try {
        if (n_bins<=1){
            throw -1;
        }
    }
    catch (int a) {
        cerr << "n_bins should be bigger than 1. Please change it.";
    }

    auto sorted_signal = new vector<double>;
    *sorted_signal = mTimeSignal;
    sort(sorted_signal->begin(), sorted_signal->end());

//    double min = floor(sorted_signal->front()) - 0.1;
//    double max = ceil(sorted_signal->back()) + 0.1;
    double min = sorted_signal->front() - 0.1;
    double max = sorted_signal->back() + 0.1;
    double bin_width = (max - min) / (double) n_bins;

    vector<int> bin_frequencies(n_bins);
    int counter = 0;
    double current = sorted_signal->at(counter);
        for (int bin = 0; bin < n_bins; bin++) {
            double lower = min + (double) bin * bin_width;
            double upper = min + (double) (bin + 1) * bin_width;
            if (counter < sorted_signal->size()) {
                while (current >= lower && current < upper && counter < sorted_signal->size()) {
                    bin_frequencies[bin]++;
                    counter++;
                    if (counter < sorted_signal->size()) {
                        current = sorted_signal->at(counter);
                    }
                }
            } else {
                bin_frequencies[bin] = 0.0;
            }

            mHistogram.push_back(make_pair(lower, make_pair(upper, bin_frequencies[bin])));
        }

    delete sorted_signal;
}

/** Method for saving the histogram bins to an output file
 *
 * \param file_name
 */
void BaseSignalProcessor::SaveHistogram(const string &file_name) {
    std::ofstream out;
    out.exceptions(ofstream::badbit);
    try {
        out.open(file_name);
        out << "bin_left" << " " << "bin_right" << " " << "frequency" << "\n";

        for (int bin = 0; bin < mHistogram.size(); bin++) {
            out << mHistogram[bin].first << " " << mHistogram[bin].second.first << " " << mHistogram[bin].second.second
                << "\n";
        }
    }
    catch (const ofstream::failure& e){
        cerr << "A file opening error has occurred. Please try again.";
    }

    out.close();
}
