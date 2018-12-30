//
//  main.cpp
//  Practice
//

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef enum e_ActivationFunctionTypes{
    ActF_Sigmoid,
    ActF_Perceptron
}e_ActivationFunctionTypes;

#define OUTPUT_NETWORK_GEN_DEBUG_ENABLE 1
#define MAX_NUM_HIDDEN_LAYERS 10

class Neuron {
public:
    //accepts the number of inputs, and type of act function to use
    Neuron(unsigned numOutputs, e_ActivationFunctionTypes neuronActF);
    
    //setters
    
    //set the neuron's input array
    void setInputs(vector<double> *InpVect);
    
    //set our weights
    void setWeights(vector<double> &WtVect);
private:
    //each neuron knows its activation function
    e_ActivationFunctionTypes Function;
    
    //each neuron knows the number of outputs it will take
    unsigned numOutputs;
    
    //each neuron has an array to store the Inputs
    vector<double> InputArray;
    
    //each neuron has an array to store weights
    vector<double> WeightsArray;
    
    //each neuron has a bias
    double Bias;
    
    double Sum;
    double Output;
    

};

Neuron::Neuron(unsigned numberOfOutputs, e_ActivationFunctionTypes neuronActF){
    Function = neuronActF;
    numOutputs = numberOfOutputs;
    
    //debug
    cout << "Neuron!: " << numberOfOutputs << " Outputs" << endl;
}

void Neuron::setInputs(vector<double> *InpVect){
    InputArray = *InpVect;
}

void Neuron::setWeights(vector<double> &WtVect){
    InputArray = WtVect;
}


//Layer type
typedef vector<Neuron> Layer;

//topology:
//sets the number of input Neurons, number of neurons is each hidden layer, and output neurons
typedef struct NNTopology{
    
    unsigned numberInputNeurons;
    unsigned numberHiddenLayers;
    
    
    //layer number -> number of neurons per layer
    unsigned numberHiddenNeurons[MAX_NUM_HIDDEN_LAYERS];
    
    unsigned numberOutputNeurons;
    
    e_ActivationFunctionTypes NeuronType;
    
    
    
}NNTopology;

//create a new topolgy structure for our network
NNTopology* NNcreateTopology(unsigned numberInputNeurons,
                              unsigned *numberHiddenNeurons,
                              unsigned numberHiddenLayers,
                              unsigned numberOutputNeurons,
                              e_ActivationFunctionTypes NeuronType){
    
    NNTopology *temp;
    temp = (NNTopology*)malloc(sizeof(NNTopology));
    
    temp->numberInputNeurons = numberInputNeurons;
   
    //add each hidden layer's number of hidden neurons to the topology
    for (unsigned HLayerNum = 0; HLayerNum < numberHiddenLayers; ++HLayerNum) {
        temp->numberHiddenNeurons[HLayerNum] = *numberHiddenNeurons;
        numberHiddenNeurons++;
        
    }

    temp->numberHiddenLayers = numberHiddenLayers;
    temp->numberOutputNeurons = numberOutputNeurons;
    
    return temp;
}


class NeuralNetwork {
public:
    //constructor
    NeuralNetwork(NNTopology &networkTopology);
    void Feedforward();
private:
    //array to store the Neurons in their respective Layers
    vector<Neuron> InputLayer;
    
    //array of arrays to store the collection of hidden layers and their neurons
    vector<Layer> HiddenLayers;
    
    //array to store output Neurons
    vector<Neuron> OutputLayer;
};

NeuralNetwork::NeuralNetwork(NNTopology &networkTopology){

    //create all the input neurons and add them to our Network Layer vector; repeat for all neurons in input layer
    for (int inputNeuronNum = 0; inputNeuronNum < networkTopology.numberInputNeurons; inputNeuronNum++) {
        //add a new neuron to the input layer
        //set the number of outputs of the input neuron to the number of hidden neurons
        //Set the new neuron's activation type
        InputLayer.push_back(Neuron(networkTopology.numberHiddenNeurons[0], networkTopology.NeuronType));
        
    }


    //check if we're at the last(or only) hidden layer
    if (networkTopology.numberHiddenLayers > 1) {
            //for each hidden layer, fill it with the topology's specified number of neurons (-1 as the last layer needs to connect to the number of Ouput layers)
        int hiddenLayerNum;
        for (hiddenLayerNum = 0; hiddenLayerNum < networkTopology.numberHiddenLayers - 1; hiddenLayerNum++) {
                
                HiddenLayers.push_back(Layer());
                //now add a new neuron to our current hidden layer
                for (int hiddenNeuronNum = 0; hiddenNeuronNum < networkTopology.numberHiddenNeurons[hiddenLayerNum]; hiddenNeuronNum++) {
                    //add a new neuron to our hidden layer
                    //set the number of outputs to the number of neurons in the next layer
                    //set the type of Neuron, currently supports one neuron type per network
                    HiddenLayers.back().push_back(Neuron(networkTopology.numberHiddenNeurons[hiddenLayerNum + 1], networkTopology.NeuronType));
                }

        }
        
        
        //now connect the last hidden layer to the neurons in output layer
        HiddenLayers.push_back(Layer());
        //add the hidden neurons with numOutputs equal to number of output neurons
        for (int hiddenNeuronNum = 0; hiddenNeuronNum < networkTopology.numberHiddenNeurons[hiddenLayerNum]; hiddenNeuronNum++) {
            
            //add a new neuron to our hidden layer
            //set the number of outputs to the number of neurons in the next layer (as calulated and stored in HiddenlayerOuputs[])
            //set the type of Neuron, currently supports one neuron type per network
            HiddenLayers.back().push_back(Neuron(networkTopology.numberOutputNeurons, networkTopology.NeuronType));
        
        }
    
    }else{
        //else we have just one hidden layer, so number of hidden neuron outputs = number of outputneurons

        //add the layer
        HiddenLayers.push_back(Layer());

    
        //add the hidden neurons with numOutputs equal to number of output neurons
        for (int hiddenNeuronNum = 0; hiddenNeuronNum < networkTopology.numberHiddenNeurons[0]; hiddenNeuronNum++) {
            
                //add a new neuron to our hidden layer
                //set the number of outputs to the number of neurons in the next layer (as calulated and stored in HiddenlayerOuputs[])
                //set the type of Neuron, currently supports one neuron type per network
                HiddenLayers.back().push_back(Neuron(networkTopology.numberOutputNeurons, networkTopology.NeuronType));
        
        }
        
        
    }
    

    //add all the output neurons to the output Layer
    for (int outputNeuronNum = 0; outputNeuronNum < networkTopology.numberOutputNeurons; outputNeuronNum++) {
        //add a new neuron to the input layer
        //set the number of outputs of the output neuron to 1 as each output neuron gives one output
        //Set the new neuron's activation type
        OutputLayer.push_back(Neuron(1, networkTopology.NeuronType));

    }
    
   
    
#if(OUTPUT_NETWORK_GEN_DEBUG_ENABLE == 1)
    cout << "DEBUG ENABLED{ \n\t" << "[INPUT NEURONS]: ";
    
    //print the input vector using an iterator
    for (auto i = InputLayer.begin(); i != InputLayer.end(); ++i) {
        cout << &*i << ' ';
    }
    
    //print the hidden Layer vector
    
    
    for(unsigned hl = 0; hl < networkTopology.numberHiddenLayers; hl++){
        
        cout << "\n\t[HIDDEN LAYER " << hl << "]:";
        for (auto hn = HiddenLayers[hl].begin(); hn !=  HiddenLayers[hl].end(); ++hn) {
            cout << &*hn << ' ';
        }
    }
    
    cout << "\n\t[OUTPUT LAYER]: ";
    //print the output vector
    for (auto o = OutputLayer.begin(); o != OutputLayer.end(); ++o) {
        cout << &*o << ' ';
    }
    
    cout << "\n}DEBUG ENABLED" << endl;
    
#endif
    
}/* NeuralNetwork() */

void NeuralNetwork::Feedforward(){
    
}/* Feedforward */



int main(int argc, const char * argv[]) {
    
    unsigned hiddenArr[] = {5};
    NeuralNetwork mynet = NeuralNetwork(*NNcreateTopology(2, hiddenArr, 1, 1, ActF_Sigmoid));
    
}
