#pragma once 

class Neuron {
public:
    Neuron();
    Neuron(float weight, float bias);

    float activate(float x);
    float backpropagate(float target);
    float& getWeight() const; 
    float& getBias() const;
    
private:
    float _weight;
    float _bias;
};