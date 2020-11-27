//
// Created by Maximo Cravero on 27/11/2020.
//

#include <vector>

#include "AudioFile/AudioFile.h"

#ifndef SIGNAL_PROCESSING_SIGNALPROCESSER_H
#define SIGNAL_PROCESSING_SIGNALPROCESSER_H


class SignalProcesser {
public:
    // constructors and destructors
    SignalProcesser();
    SignalProcesser(const AudioFile<double>& signal);
    ~SignalProcesser();

    // set methods
    void SetSignal(std::vector<double>& signal);
    // set ft via fft
    // set noise removed signal
    void RemoveNoise(int window);

    // get methods (const)
    // get
    void getNoiseRemovedSignal();

    // Signal.to_file(asjdlfkasjdf)

private:
    std::vector<double> mSignal;
    std::vector<double> mFFTSignal;
    std::vector<double> mNoiseRemovedSignal;
};


#endif //SIGNAL_PROCESSING_SIGNALPROCESSER_H
