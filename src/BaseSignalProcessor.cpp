//
// Created by Maximo Cravero on 19/01/2021.
//

#include "BaseSignalProcessor.hpp"

/** Custom constructor */
BaseSignalProcessor::BaseSignalProcessor(const AudioFile<double> &signal) {
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
 * Methods for setting the time signal (saving)
 * \param signal: input signal
 */
template<typename T>
void BaseSignalProcessor::SetTimeSignal(const T &signal) {
    for (int i = 0; i < signal.getNumSamplesPerChannel(); i++) {
        mTimeSignal.push_back(signal.samples[0][i]);
    }
}

/**
 * Method for saving a given file.
 * \param filename
 */
void BaseSignalProcessor::SaveFile(const string& file_name, const string& signal_name) {
    std::ofstream out;
    out.exceptions(ofstream::badbit);
    try {
        out.open(file_name);
        out << "index" << " " << "signal_value" << "\n";
        if (signal_name == "filtered_signal"){
            for (int i = 0; i < mFilteredTimeSignal.size(); i++) {
                out << i << " " << mFilteredTimeSignal[i] << "\n";
            }
        } else if (signal_name == "raw_signal"){
            for (int i = 0; i < mTimeSignal.size(); i++) {
                out << i << " " << mTimeSignal[i] << "\n";
            }
        } else {
            std::cout << "Please fill in a valid signal to save!";
        }
        cout << std::endl;
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
    std::sort(sorted_signal->begin(), sorted_signal->end());

//    mSortedSignal = std::sort(mSignal->begin(), mSignal->end()); check initialization to avoid unnecessarily sorting
    int min = floor(sorted_signal->front());
    int max = ceil(sorted_signal->back());
    double bin_width = ((double) max - (double) min) / (double) n_bins;


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
            double lower_bin = min + (double) bin * bin_width;
            double upper_bin = min + (double) (bin + 1) * bin_width;

            mHistogram.push_back(make_pair(lower_bin, make_pair(upper_bin, bin_frequencies[bin])));
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