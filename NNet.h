//
//  NNet.h
//  NNet
//
//  neuron:
//     1) get inputs
//     2) multiply weights
//     3) Sum the two values
//     4) apply act func
//      
//  Feed-forwarding:
//      1) 
//      
//  Simple BackProp:
//     1) Learn Partial Derivitives
//
//
//


#ifndef NNet_h
#define NNet_h

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#define FUNCTION_ACTIV_PERCEPTRON 0
#define FUNCTION_ACTIV_SIGMOID 1
#define FUNCTION_ACTIV_RELU 2
#define FUNCTION_ACTIV_SOFTMAX 3

#define LAYER_INPUT 0
#define LAYER_1 1
#define LAYER_OUTPUT 2



//maximum inputs to any neuron in network
const unsigned int maxInputs = 3;


typedef enum {Input, Hidden, Output} layerType;


//ReLU act func's max function
inline int max ( int a, int b ) { return a > b ? a : b; }

//multiplier of last deltaweight i.e momentum of change
double alpha = 0.01;


//Neuron Structure
typedef struct Neuron{
    
    uint8_t layerNumber;
    layerType LayerType;
    int8_t ACTIVATION_FUNCTION;
    uint8_t NumberInputs;
    
    double Inputs[maxInputs];
    double Weights[maxInputs];
    double Sum;
    double Output;
    
    //test
    double Error;
    
    //for output neurons
    double Expected;
    
    
}Neuron;

//Perceptron Structure
typedef struct Perceptron{
    uint8_t layerNumber;
    double Bias;
    double Inputs[2];
    double Weights[2];
    double Sum;
    double Output;
}Perceptron;


//double newDeltaWeight = (eta * neuron.getOutputValue() * n_gradient) + (alpha * oldDeltaWeight);

//Neuron Functions
struct Neuron *create_Neuron(uint8_t layerNumber, uint8_t NumberInputs, int8_t ACTIVATION_FUNCTION);
void neuron_SetInputs(Neuron* neuron, double* inputArray);
double neuron_GetOutput(Neuron* neuron);
void neuron_SetWeights(Neuron* neuron, double* WeightsArray);
void neuron_AdjustWeights(Neuron* neuron, double ERROR, float LearningRate);
void neuron_Init(Neuron* neuron, double* inputArray, bool SetRandomInitialWeights);
void neuron_calculateError(Neuron* neuron);

//Perceptron Functions
struct Perceptron *create_Perceptron(uint8_t layerNumber, double bias);
void perceptron_setBias(Perceptron* perceptron, double bias);
void perceptron_SetInputs(Perceptron* perceptron, double* inputArray);
double perceptron_GetOutput(Perceptron* perceptron);
void perceptron_SetWeights(Perceptron* perceptron, double* WeightsArray);

//act funcs
double activationFunctionSigmoid(double x);
double dervitiveFunctionSigmoid(double y);

double activationFunctionRelu(double x);
double activationFunctionSoftMax(double x);
double activationFunctionPerceptron(double x);


//activation Functions
double activationFunctionSigmoid(double x){
    return 1/(1 + exp(-x));
}

double derivitiveFunctionSigmoid(double y){
    return y*(1 - y);
}

//double activationFunctionRelu(double x){
//    return max(0, x);
//}

double activationFunctionSoftMax(double x){
    return 1;
}



//create a new Neuron
Neuron *create_Neuron(uint8_t layerNumber, uint8_t NumberInputs, int8_t ACTIVATION_FUNCTION){
    
    Neuron *temp;
    temp = (Neuron*)malloc(sizeof(Neuron));
    temp->layerNumber=layerNumber;
    //temp->next=NULL;
    temp->NumberInputs = NumberInputs;
    temp->ACTIVATION_FUNCTION = ACTIVATION_FUNCTION;
    //Debug
    printf("created Neuron temp->layerNumber=%d\n",temp->layerNumber);
    
    return temp;
    
}


void neuron_Init(Neuron* neuron, double* inputArray, bool SetRandomInitialWeights){
    neuron_SetInputs(neuron, inputArray);
    if (SetRandomInitialWeights == true) {
        //initial weights are random
        for (int i = 0; i < neuron->NumberInputs; i++) {
            float num = (rand()%10);
            neuron->Weights[i] = num/10;
        }
        
    }
    
}

double neuron_GetOutput(Neuron* neuron){
    
    for (int i = 0; i < neuron->NumberInputs; i++) {
        neuron->Sum += (neuron->Weights[i]);
    }
    
    switch (neuron->ACTIVATION_FUNCTION) {
        case FUNCTION_ACTIV_SIGMOID:
            neuron->Output = activationFunctionSigmoid(neuron->Sum);
            break;
        //case FUNCTION_ACTIV_RELU:
          //  neuron->Output = activationFunctionRelu(neuron->Sum);
            //break;
        case FUNCTION_ACTIV_SOFTMAX:
            neuron->Output = activationFunctionSoftMax(neuron->Sum);
            break;
        default:
            break;
    }
    
    return neuron->Output;
}



void neuron_SetInputs(Neuron* neuron, double* inputArray){
    
    //assert(sizeof(inputArray)/sizeof(double) >= neuron->NumberInputs);
    
    for (int i = 0; i < neuron->NumberInputs; i++) {
        neuron->Inputs[i] = *inputArray;
        inputArray++;
    }
    
}



void neuron_SetWeights(Neuron* neuron, double* WeightsArray){
    
    //assert(sizeof(WeightsArray)/sizeof(double) >= neuron->NumberInputs);
    
    for (int i = 0; i < neuron->NumberInputs; i++) {
        neuron->Weights[i] = *WeightsArray;
        WeightsArray++;
    }
}



void neuron_AdjustWeights(Neuron* neuron, double ERROR, float LearningRate){
    
    for (int i = 0; i < neuron->NumberInputs; i++) {
        
        neuron->Weights[i] += (LearningRate * neuron_GetOutput(neuron) * ERROR) + (alpha * neuron->Weights[i]);
        
    }
    
}

void neuron_calculateError(Neuron* neuron){
    double output = neuron_GetOutput(neuron);
    
    switch (neuron->LayerType) {
        case Input:
            //input Neuron calc error
            return;
            break;
        case Hidden:
            neuron->Error = (neuron->Expected - output) * derivitiveFunctionSigmoid(output);
            return;
        case Output:
            neuron->Error = (neuron->Expected - output) * derivitiveFunctionSigmoid(output);
        default:
            break;
    }
}




//----Perceptron stuff----


//create a new Perceptron
Perceptron *create_Perceptron(uint8_t layerNumber, double bias){
    
    Perceptron *temp;
    temp = (Perceptron*)malloc(sizeof(Perceptron));
    temp->layerNumber = layerNumber;
    temp->Bias = bias;
    
    
    //Debug
    //printf("created Perceptron temp->layerNumber=%d\n",temp->layerNumber);
    
    return temp;
    
}

void perceptron_setBias(Perceptron* perceptron, double bias){
    perceptron->Bias = bias;
}

void perceptron_SetInputs(Perceptron* perceptron, double* inputArray){
    for (int i = 0; i < 2; i++) {
        perceptron->Inputs[i] = *inputArray;
        inputArray++;
    }
}

void perceptron_SetWeights(Perceptron* perceptron, double* WeightsArray){
    for (int i = 0; i < 2; i++) {
        perceptron->Weights[i] = *WeightsArray;
        WeightsArray++;
    }
}

double perceptron_GetOutput(Perceptron* perceptron){
    for (int i = 0; i < 2; i++) {
        perceptron->Sum += (perceptron->Inputs[i] * perceptron->Weights[i]);
    }
    if ((perceptron->Sum + perceptron->Bias) >= 0) {
        return 1.0000;
    }else{
        return 0.0000;
    }
}


//Prototypes:

//Massive forward propogation Alogirthm:

double NNetwork_Propogate(unsigned numInputNeurons){
    return 0;
}




#endif /* NNet_h */
