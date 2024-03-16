# NPRACH NBIoT UAD Fixed Point Implemetation
Narrowband Physical Random Access CHannel (NPRACH) Narrowband Internet of Things (NBIoT) User Activity Detection (UAD) Receiver Neural Network implementation in Fixed point C.
#
# Source File Descriptions
## Command
gcc command to run the NN.
## DL NPRACH Head
Header file for the neural network
## Activations
This file contains all the activation functions like relu, sigmoid, etc.
## Load Data
File to load all the data required for NN implementation.
l1_result contains the python output for layer 1 of the NN.
Weights and RxData have the weights of layer 1 and input data of 1 subcarrier respectively.
## DL Functions
This file contains deep learning functions used in this neural network including Batch Normalization, 1D Convolution, etc.
## UAD PRM0 CVA12
This file implements the neural network layer for User Activity Detection for Premable 0, Coverage Area 1.
## Mat Operations
Contains (fixed point) matrix operations like multiplication, addition, etc.
## Util
Ultility functions: transpose, multiplication, division and square root operations.
