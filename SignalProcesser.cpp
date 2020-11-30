//
// Created by Maximo Cravero on 27/11/2020.
//

#include <numeric>
#include "SignalProcesser.hpp"


// Default constructor
SignalProcesser::SignalProcesser() {};

// Custom constructor (automatically sets default signal when instantiating class)
SignalProcesser::SignalProcesser(const AudioFile<double>& signal) {
    for (int i=0; i < signal.getNumSamplesPerChannel(); i++){
        mSignal.push_back(signal.samples[0][i]);
    }
}

// Destructor
SignalProcesser::~SignalProcesser() {
    mSignal.clear();
    mFFTSignal.clear();
    mNoiseRemovedSignal.clear();
}

// Set methods


// Get methods
void SignalProcesser::getNoiseRemovedSignal() {
    for (double& c : mNoiseRemovedSignal){
        std::cout << c << "\n";
    }
}

// Noise removal
void SignalProcesser::RemoveNoise(int window) {
    double avg = std::accumulate(mSignal.begin(), mSignal.begin() + window - 1, 0.0) / (double)mSignal.size();
    mNoiseRemovedSignal.push_back(avg);
    for (int i = window; i < mSignal.size(); i++) {
        avg -= mSignal[i - window] / window;
        avg += mSignal[i] / window;
        mNoiseRemovedSignal.push_back(avg);
    }
}