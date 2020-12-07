//
// Created by Maximo Cravero on 27/11/2020.
//

#include <cmath>
#include <vector>
#include <algorithm>
#include "AudioFile/AudioFile.h"

using namespace std;

#ifndef SIGNAL_PROCESSING_SIGNALPROCESSER_H
#define SIGNAL_PROCESSING_SIGNALPROCESSER_H


class SignalProcessor {
public:
    // constructors and destructors
    SignalProcessor();
    SignalProcessor(const AudioFile<double>& signal);
    ~SignalProcessor();

    // set methods
    void SetSignal(vector<double>& signal);
    void RemoveNoise(int window);

    void GenerateHistogram(int n_bins);

    // get methods (const)
    // get
    vector<double> getRawSignal();
    void getNoiseRemovedSignal();

    // Signal.to_file(asjdlfkasjdf)

private:
    vector<double> mSignal;
    vector<double> mFFTSignal;
    vector<double> mNoiseRemovedSignal;
    vector<double> mSortedSignal;
};


#endif //SIGNAL_PROCESSING_SIGNALPROCESSER_H
