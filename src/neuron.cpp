#include "neuron.h"

using namespace std;

Neuron::Neuron() {
    float _weight = 0.0f;
    float _bias = 0.0f;
}

Neuron::Neuron(float weight, float bias) {
    _weight = weight;
    _bias = bias;
}

float Neuron::activate(float x) {
    return x * _weight + _bias;
}

