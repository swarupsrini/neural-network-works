//
//  NeuralNetwork.hpp
//  Practice
//

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include <stdio.h>
#include <vector>
#include "NNet.h"
#include "NetworkStructure.hpp"

using namespace std;

//Layer type to store Neurons
typedef vector<Neuron> Layer;


//******************Network Class**********************\\

class NeuralNetwork{
public:
    NeuralNetwork(networkStructure *NetStruct);
    
private:
    //Create a vector to store all the layers of our network->NetworkLayers[layerNum][neuronNum]
    vector<Layer> NetworkLayers;
    
    
};




//******************Network Class**********************\\





#endif /* NeuralNetwork_hpp */
