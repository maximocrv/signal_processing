//
// Created by Maximo Cravero on 22/11/2020.
//

// TODO: Include exceptions, function overloading.
// TODO: include exception catching!!
// Function declarations
//void ReadFile(std::string fileName);fileName
// Function definitions

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>

typedef std::complex<double> comp;

#include "AudioFile/AudioFile.h"
#include "SignalProcessor.hpp"
#include "FourierTransform.hpp"

// Flow
// Read in audio signal
// Process signal in time domain (i.e. do a moving average/ exponential moving average, make histogram bins)
// Return output into a file, use gnuplot to make:
// histogram plot of intensities
// plot of original signal
// plot of moving averaged/ exponential signal
// process signal in frequency domain, save output into file. Transform back to time domain, save the file
// plot of fourier domain filtered signal
// take as input the number of fourier coefficients to use

// include a check for whether the command line arguments are valid?...

int main(int argc, char* argv[]){

//    int window_size = atoi(argv[0]);
//    char* average_mode = argv[1];
//    int num_fourier_coeffs = atoi(argv[2]);

    int window_size = 100;
    std::string average_mode = "moving_average";
    int num_fourier_coeffs = 10;

    AudioFile<double> audioFile;

    audioFile.load("CantinaBand3.wav");

//    audioFile.printSummary();

    SignalProcessor test_file(audioFile);
    test_file.RemoveNoise(window_size, average_mode, 0.5);
    test_file.GenerateHistogram(50);
    test_file.SaveFile("noise_removed_signal.dat");

    std::vector<double> raw_signal = test_file.getRawSignal();

    std::cout << raw_signal.size() << "\n";
    auto* signal_cut = new std::vector<double>;

    *signal_cut = std::vector<double>(raw_signal.begin(), raw_signal.begin() + pow(2, 14));

    FourierTransform fourier_instance;

    auto* random = new vector<comp>;

//    fourier_instance.FastFourierTransform(signal_cut, random);

//    auto test = fourier_instance.getFTSignal();
//    fourier_instance.FastFourierTransform(*signal_cut, false);
//    int window = 10;

//    test_file.getNoiseRemovedSignal();

//    int channel = 0;
//    int numSamples = audioFile.getNumSamplesPerChannel();
//    auto* sampleList = new double[numSamples];
//
//    for (int i=0; i < numSamples; i++){
//        sampleList[i] = audioFile.samples[channel][i];
//        //std::cout << sampleList[i] << "\n";
//    }
//
//    std::ofstream write_output("output.dat");
//    assert(write_output.is_open());
//    for (int i = 0; i < numSamples; i++){
//        if (i % 100 == 0) {
//            write_output << i << " " << sampleList[i] << "\n";
//        }
//    }

}
