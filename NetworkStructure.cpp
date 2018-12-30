//
//  NetworkStructure.cpp
//  Practice
//

#include "NetworkStructure.hpp"

//function to get a suitable Network structure type
networkStructure* NeuralNetworkCreateStructure(unsigned TotalLayers, unsigned NumberInputNodes, unsigned NumberHiddenNodes, unsigned NumberOutputNodes){
    networkStructure *temp;
    temp = (networkStructure*)malloc(sizeof(networkStructure));
    temp->TotalLayers = TotalLayers;
    temp->NumberInputNodes = NumberInputNodes;
    temp->NumberHiddenNodes = NumberHiddenNodes;
    temp->NumberOutputNodes = NumberOutputNodes;
    return temp;
}
