//
// Created by Сергей Клявинек on 22.11.2020.
//
#include <string>
#include <vector>
#ifndef FIRST_PROJECT_PCSC_OUTPIT_H
#define FIRST_PROJECT_PCSC_OUTPIT_H
class Output
{
private:
    std::string mTag, mProblem;
public:
    Output(std::string tagString, std::string probString);
    Output();
    void Print(std::vector<float> freq,std::vector<float> intensity) const;
    void SaveFile(std::vector<float> freq,std::vector<float> intensity, std::string filename) const;
};
#endif //FIRST_PROJECT_PCSC_OUTPIT_H
