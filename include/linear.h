#pragma once 
#include "neuron.h"
#include <vector>

using namespace std;

class Linear {
public:
    Linear(int inputSize, int outputSize);
    ~Linear();
    vector<Neuron>& getNeurons();
    vector<float> forward(const vector<float>& inputs);


private:
    vector<Neuron> _neurons;
};