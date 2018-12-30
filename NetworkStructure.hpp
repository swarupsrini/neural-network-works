//
//  NetworkStructure.hpp
//  Practice
//

#ifndef NetworkStructure_hpp
#define NetworkStructure_hpp

#include <stdio.h>
#include <stdlib.h>

//structure to define overall network
typedef struct networkStructure{

    unsigned TotalLayers;
    unsigned NumberInputNodes;
    unsigned NumberOutputNodes;


}networkStructure;

//function to create a new structure
networkStructure* NeuralNetworkCreateStructure(
  unsigned TotalLayers,
  unsigned NumberInputNodes,
  unsigned NumberHiddenNodes,
  unsigned NumberOutputNodes
);

#endif /* NetworkStructure_hpp */
