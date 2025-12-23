#include "nn/neuron.h"
#include "nn/linear.h"
#include "nn/mlp.h"
#include "nn/classifier.h"
#include "nn/relu.h"

Classifier::Classifier(int inputDim, const vector<int>& hiddenDims, const vector<string>& classes) {
    //_mlp = MLP(inputDim, hiddenDims, classes.size());
};

string Classifier::action(vector<float> inputs) {
   // vector<float> logits = _mlp.forward(inputs); 
   return "";
};