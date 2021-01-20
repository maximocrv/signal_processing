//
// Created by Maximo Cravero on 19/01/2021.
//

#include "BaseSignalProcessor.hpp"

// Custom constructor
BaseSignalProcessor::BaseSignalProcessor(const AudioFile<double> &signal) {
    for (int i = 0; i < signal.getNumSamplesPerChannel(); i++) {
        mTimeSignal.push_back(signal.samples[0][i]);
    }
}


// destructors
/** Destructor, clean field mSignal and mNoiseRemovedSignal */
BaseSignalProcessor::~BaseSignalProcessor() {
    mTimeSignal.clear();
    mFilteredTimeSignal.clear();
    mFourierSignal.clear();
    mFilteredFourierSignal.clear();
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
 * @param filename
 */
void BaseSignalProcessor::SaveFile(const string& filename) {
    std::ofstream out;
    out.exceptions(ofstream::badbit);
    try {
        out.open(filename);
        out << "index" << " " << "signal_value" << "\n";
        for (int i=0; i < mFilteredTimeSignal.size(); i++){
            out << i << " " << mFilteredTimeSignal[i] << '\n';
        }
        cout << std::endl;
    }
    catch (const ofstream::failure& e) {
        cerr << "A file opening error has occurred. Please try again.";
    }
    out.close();
}