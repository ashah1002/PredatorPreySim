#pragma once 
#include <vector>

using namespace std;

class Neuron {
public:
    Neuron(int dim, bool random=true);

    float activate(vector<float> x);
    vector<float> getParameters() const;  
    void loadWeights(vector<float> weights);
    
private:
    int _dim;
    vector<float> _weights;
    float _bias;
};