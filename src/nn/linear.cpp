#include "nn/neuron.h"
#include "nn/linear.h"
#include <cstdlib>

using namespace std;

Linear::Linear(int fanIn, int fanOut, bool bias, bool randomInit) {
    _fanIn = fanIn;
    _fanOut = fanOut;

    _neurons.reserve(_fanOut);
    for(int i = 0; i < _fanOut; i++) {
        _neurons.push_back(Neuron(_fanIn));
    }
}

vector<float> Linear::forward(const vector<float>& input) { 
    if(input.size() != _fanIn) {
        throw invalid_argument("Input be of size fanIn.");
    } 
    vector<float> out;
    out.reserve(_fanOut);

    for(int i = 0; i < _fanIn; i++) {
        out.push_back(_neurons[i].activate(input));
    }
}
