//
// Created by Sergei Kliavinek & Maximo Cravero on 30/11/2020.
//

#include <iostream>
#include "gtest/gtest.h"
#include "../src/FourierTransform.hpp"
#include "../src/TimeSignalProcessor.hpp"


TEST (FourierTransform, fft_1){
    // Compare output with that of built in fft class. Input (vector <double> signals)- simple signal length eight.
    // Output(vector <comp> signal) - Fourier transformation of signal.
    // vector <comp> tests - "ideal" output, that should be.
    FourierTransform fft;
    vector<double> signals = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    vector <comp> signal = {};
    fft.FastFourierTransform(signals, signal);
    vector <comp> tests={comp(1,0), comp(0.707107,-0.707107), comp(0.000000,-1.000000),\
    comp(-0.707107,-0.707107), comp(-1.000000,0.000000), comp(-0.707107,0.707107),\
    comp(0.000000,1.000000), comp(0.707107,0.707107)};
    for (int i=0; i<8; i+=1){
        ASSERT_EQ (tests[i], signal[i]);
    }
}

TEST (FourierTransform, fft_2){
    // Compare output with that of built in fft class. Input (vector <double> signals) -
    // simple signal length eight. Output(vector <comp> signal) - Fourier
    // transformation of signal. vector <comp> tests - "ideal" output, that should be.
    FourierTransform fft;
    vector<double> signals = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    vector <comp> signal = {};
    fft.FastFourierTransform(signals, signal);
    vector <comp> tests={};
    comp c1(1, 0);
    for (int i=0; i<8; i+=1){
        tests.push_back(c1);
    }
    for (int i=0; i<8; i+=1){
        ASSERT_EQ (tests[i], signal[i]);
    }
}

TEST (FourierTransform, inverse_fft_1){
    // Compare inverse output with that of built in fft class. Input (vector <comp> signal)- simple signal length eight.
    // Output(vector <comp> signal) - Fourier transformation of signal. vector <comp> tests -
    // "ideal" output, that should be.
    FourierTransform fft;
    vector<double> signals = {};
    vector <comp> signal={comp(1,0), comp(0.707107,-0.707107), comp(0.000000,-1.000000),\
    comp(-0.707107,-0.707107), comp(-1.000000,-0.000000), comp(-0.707107,0.707107),\
    comp(0.000000,1.000000), comp(0.707107,0.707107)};
    fft.InverseFourierTransform(signals, signal);
    vector <comp> tests = {comp(0), comp(1), comp(0), comp(0), comp(0), comp(0), comp(0), comp(0)};
    for (int i=0; i<8; i+=1){
        ASSERT_LT (abs((tests[i]-signal[i]).real()), 0.000001);
        ASSERT_LT (abs((tests[i]-signal[i]).imag()), 0.000001);
    }
}

TEST (FourierTransform, inverse_fft_2){
    // Compare inverse output with that of built in fft class. Input (vector <comp> signal)- simple signal length eight.
    // Output(vector <comp> signal) - Fourier transformation of signal. vector <comp> tests -
    // "ideal" output, that should be.
    FourierTransform fft;
    vector<double> signals = {};
    vector <comp> signal={comp(1,0), comp(1,0), comp(1,0), comp(1,0),comp(1,0),\
                        comp(1,0),comp(1,0), comp(1,0)};
    fft.InverseFourierTransform(signals, signal);
    vector <comp> tests = {comp(1), comp(0), comp(0), comp(0), comp(0), comp(0), comp(0), comp(0)};
    for (int i=0; i<8; i+=1){
        ASSERT_LT (abs((tests[i]-signal[i]).real()), 0.000001);
        ASSERT_LT (abs((tests[i]-signal[i]).imag()), 0.000001);
    }
}

TEST (FourierTransform, fft_filter){
    // Compare ideal fourier filter results with that of built in fft class. Input (vector <comp> signals)-
    // simple signal length eight with a little noise.
    // Output(vector <comp> signal) - Fourier Filtered signal vector <comp> tests -"ideal" output, that should be.
    FourierTransform fft;
    vector <double> signal={};
    vector <comp> signals = {comp(0.250625,0.000000), comp(-0.087946,0.036170), comp(-0.125000,0.124375),\
    comp(0.087946,-0.213830), comp(-0.000625,0.000000), comp(0.087946,0.213830), \
    comp(-0.125000,-0.124375), comp(-0.087946,-0.036170)};
    fft.FFTFilter(signal, 99.8, signals);
    vector <comp> tests = {comp(0.250000,0.000000), comp(-0.088388,0.036612), comp(-0.125000,0.125000),\
    comp(0.088388,-0.213388), comp(0.000000,0.000000), comp(0.088388,0.213388), \
    comp(-0.125000,-0.125000), comp(-0.088388,-0.036612)};
    for (int i=0; i<8; i+=1){
        ASSERT_LT (abs((tests[i]-signals[i]).real()), 0.000001);
        ASSERT_LT (abs((tests[i]-signals[i]).imag()), 0.000001);
    }
}

TEST (TimeSignalProcessor, remove_noise){
        // simple test to check the moving average generates the correct output, and has the correct size (i.e. taking
        // into account the fact that we will lose some elements due to the initialization of the moving average)
        int window_size = 3;
        vector<double> test_vector = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
        vector<double> correct_output_moving_average = {2.0, 3.0, 4.0, 5.0};

        TimeSignalProcessor test_signal_processor;
        test_signal_processor.SetTimeSignal(test_vector);
        test_signal_processor.RemoveNoise(window_size, "moving_average", 0.5);
        vector<double> noise_removed_signal = test_signal_processor.getFilteredTimeSignal();

        for (int i = 0; i < correct_output_moving_average.size(); i++){
            ASSERT_EQ (noise_removed_signal[i], correct_output_moving_average[i]);
        }

        ASSERT_EQ (test_vector.size() - window_size + 1, noise_removed_signal.size());
    }

TEST (TimeSignalProcessor, histogram_testing){
        // simple test to check that the histogram outputs the correct bin frequencies and that their sum is equal to
        // the total number of samples provided in the input
        vector<double> test_vector = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 , 9.0};

        TimeSignalProcessor test_signal_processor;
        test_signal_processor.SetTimeSignal(test_vector);
        test_signal_processor.RemoveNoise(2, "moving_average", 0.5);

        test_signal_processor.GenerateHistogram(9);
        vector<pair<double, pair<double, double> > > outputHistogram = test_signal_processor.getHistogram();

        int total_elements = 0;
        for (int i = 0; i < outputHistogram.size(); i++){
            total_elements += outputHistogram[i].second.second;
            ASSERT_EQ (outputHistogram[i].second.second, 1.0);
        }

        ASSERT_EQ (test_vector.size(), total_elements);
    }


int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
