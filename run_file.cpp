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

#include "AudioFile/AudioFile.h"
#include "SignalProcessor.hpp"
#include "FourierTransform.hpp"

int main(){
    AudioFile<double> audioFile;

    audioFile.load("tone.wav");

    audioFile.printSummary();

    SignalProcessor test_file(audioFile);

    std::vector<double> raw_signal = test_file.getRawSignal();

    std::cout << raw_signal.size() << "\n";
    auto* signal_cut = new std::vector<double>;

    *signal_cut = std::vector<double>(raw_signal.begin(), raw_signal.begin() + pow(2, 14));

//    std::cout << signal_cut.size();

    FourierTransform fourier_instance;

    fourier_instance.FastFourierTransform(signal_cut, false);

    auto test = fourier_instance.getFTSignal();



//    fourier_instance.FastFourierTransform(*signal_cut, false);

//    int window = 10;
//    test_file.RemoveNoise(window);

//    test_file.GenerateHistogram(10);

//    test_file.getNoiseRemovedSignal();



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
