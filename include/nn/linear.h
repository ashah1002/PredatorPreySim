#pragma once 
#include "nn/neuron.h"
#include "nn/layer.h"
#include <vector>

using namespace std;

class Linear : public Layer {
public:
    Linear(int fanIn, int fanOut, bool bias=true, bool randomInit=true);
    ~Linear() = default;

    vector<vector<float>> getParameters();
    void loadParameters(vector<vector<float>> &params);
    
    vector<float> forward(const vector<float>& input);

private:
    vector<Neuron> _neurons;
    int _fanIn;
    int _fanOut;
};