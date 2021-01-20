//
// Created by Maximo Cravero on 19/01/2021.
//

#include <cmath>
#include <vector>
#include <algorithm>
#include <complex>
#include "../AudioFile/AudioFile.h"

using namespace std;
typedef complex<double> comp;

#ifndef SIGNAL_PROCESSING_BASESIGNALPROCESSOR_HPP
#define SIGNAL_PROCESSING_BASESIGNALPROCESSOR_HPP

class BaseSignalProcessor {

    // two private variable - raw and processed signal (add extra for fourier transform class)
    // saving method - inputs -- column names -- signal -- filename
public:
    // constructors and destructors
    BaseSignalProcessor() {};
    BaseSignalProcessor(const AudioFile<double>& signal);
    virtual ~BaseSignalProcessor();

    // set methods
    template<typename T>
    void SetTimeSignal(const T& signal);

    // get methods (const)
    vector<double> getTimeSignal() {return mTimeSignal; };
    vector<double> getFilteredTimeSignal() {return mFilteredTimeSignal; };
    vector<comp> getFourierSignal() {return mFourierSignal; };
    vector<comp> getFilteredFourierSignal() {return mFilteredFourierSignal; };

    void SaveFile(const string& filename);

protected:
    vector<double> mTimeSignal;
    vector<double> mFilteredTimeSignal;
    vector<comp> mFourierSignal;
    vector<comp> mFilteredFourierSignal;
};


#endif //SIGNAL_PROCESSING_BASESIGNALPROCESSOR_HPP
