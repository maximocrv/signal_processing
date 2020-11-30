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

#include "AudioFile/AudioFile.h"
#include "SignalProcesser.hpp"

int main(){
    AudioFile<double> audioFile;

    audioFile.load("../tone.wav");

    audioFile.printSummary();

    SignalProcesser cheese(audioFile);

    int window = 10;
    cheese.RemoveNoise(window);

    cheese.getNoiseRemovedSignal();

//    cheese.getNoiseRemovedSignal();

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
