#ifndef __DFT_H__
#define __DFT_H__

#include <complex>
#include <vector>
using namespace std;

typedef complex<double> comp;
class FFT_preproc
{
private:
    void butterfly(vector<comp> &array, comp w);
    unsigned int backwards(unsigned int x, int length);
    void reposition(vector<comp> &array);
};
#endif