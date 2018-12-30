//
//  NeuralNetwork.cpp
//  Practice
//

#include "NeuralNetwork.h"

//TODO: Port all NNet.h code to C++

//constructor
NeuralNetwork::NeuralNetwork(networkStructure *NetStruct){
    for (unsigned LayerNum = 0; LayerNum < NetStruct->TotalLayers; LayerNum++) {

        //Add the current Layer to the NetworkLayer Array(vector)
        NetworkLayers.push_back(Layer());

        //add all the input Neurons to the Input Neuron Vector
        for (unsigned numNs = 0; numNs < NetStruct->; numNs++) {
            //access the NetworkLayer's Current Layer, and add a new inputNeuron to that Layer
            NetworkLayers[LayerNum].push_back(NeuronObj);

        }
    }
}
