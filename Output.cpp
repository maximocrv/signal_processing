//
// Created by Сергей Клявинек on 22.11.2020.
//
#include <iostream>
#include "Output.h"
#include <typeinfo>
#include <fstream>
#include "qcustomplot.h"
//Constructor
using namespace std;
Output::Output() {}

void Output::Print(vector<float> freq,vector<float> intensity) const
{

        cout<<'Frequency'<<' '<<'Intensity';
        for (int i=0; i<freq.size(); i++)
            cout << freq[i] << " "<<intensity[i]<<'\n';
        cout << std::endl;
}
void Output::SaveFile(vector<float> freq,vector<float> intensity, string filename) const {
        std::ofstream out;
        out.open(filename);
        if (out.is_open()){
            cout<<'Frequency'<<' '<<'Intensity';
            for (int i=0; i<freq.size(); i++)
                out << freq[i] << " "<<intensity[i]<<'\n';
            cout << std::endl;
            out.close();
        }
        else
        {
            cout<<"File is not open!";
        }
}

void Output::Plot(vector<float> freq,vector<float> intensity) const {
    QCustomPlot *customPlot;    // Объявляем графическое полотно
    QCPGraph *graphic;          // Объявляем график

}