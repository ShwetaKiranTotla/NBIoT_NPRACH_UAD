#include <stdio.h>
#include <stdlib.h>
#include <math.h>

////////// CONSTANTS //////////
#define NUM_ITEM		100
#define SMPL_PER_PRMB	160
#define UAD_THRESHOLD	0.65

////////// DATA TYPE DEFINITION //////////
typedef float DATA;

////////// DATA STRUCTURES //////////

struct weights
{
	// Layer 1
	DATA L1_0_w[32][2][5];
	DATA L1_0_b[32];
	DATA L1_1_w[32];
	DATA L1_1_b[32];
	DATA L1_1_mean[32];
	DATA L1_1_var[32];

	// Layer 2
	DATA L2_0_w[48][32][2];
	DATA L2_0_b[48];
	DATA L2_1_w[48];
	DATA L2_1_b[48];
	DATA L2_1_mean[48];
	DATA L2_1_var[48];

	// Layer 3
	DATA L3_0_w[48][48][2];
	DATA L3_0_b[48];
	DATA L3_1_w[48];
	DATA L3_1_b[48];
	DATA L3_1_mean[48];
	DATA L3_1_var[48];

	// Layer 4
	DATA L4_0_w[1][384][192];
	DATA L4_0_b[192];
	DATA L4_1_w[192];
	DATA L4_1_b[192];
	DATA L4_1_mean[192];
	DATA L4_1_var[192];

	// Layer 5
	DATA L5_0_w[1][192][128];
	DATA L5_0_b[128];
	DATA L5_1_w[128];
	DATA L5_1_b[128];
	DATA L5_1_mean[128];
	DATA L5_1_var[128];

	// Layer 6
	DATA L6_0_w[1][128][1];
	DATA L6_0_b[1];

	// Layer 6a
	DATA L6a_0_w[1][128][2];
	DATA L6a_0_b[2];
};
typedef struct weights weights_t;

struct rxData
{	
	// DATA rxDataMat[NUM_ITEM][2][SMPL_PER_PRMB];
	DATA ***rxDataMat;
};
typedef struct rxData rxData_t;

////////// FUNCTION PROTOTYPES //////////

void read_file(char* name, int size, DATA *data_in);
void print_mat3d(int ch, int row, int col, DATA (*mat)[ch][row][col]);
void print_mat1d(int size, DATA *mat);
DATA** createMatrix_2D(int row, int col);
DATA*** createMatrix_3D(int depth, int row, int col);
DATA** flatten_mat(int row, int col, DATA **matrix);
DATA** transpose_mat(int row, int col, DATA **matrix);
void memory_free(float **matrix, int row);
void write_data(char *name, DATA *mat);

void load_mat3d(int ch, int row, int col, DATA (*mat)[ch][row][col], DATA *data_in);
void load_data_all(weights_t *nn_w, rxData_t *rxDataMat);

void UAD_PRM0_CVA12_eval(weights_t *nn_w, rxData_t *rx_data);
DATA** UAD_PRM0_CVA12_NN(weights_t *nn_w, DATA **x);
DATA** UAD_PRM0_CVA12_Layer6(weights_t *nn_w, DATA **x);
DATA** UAD_PRM0_CVA12_Layer6a(weights_t *nn_w, DATA **x);
DATA infer_uad(DATA **x);
DATA infer_cva(DATA **x, DATA uad);

DATA** conv1d(int f_n, int f_ch, int f_size, DATA conv_w[f_n][f_ch][f_size], DATA conv_b[f_n], int stride,
            int in_ch, int in_size, DATA **x,
            int out_ch, int out_size);
DATA** batchnorm1d(int ch, DATA bnorm_w[ch], DATA bnorm_b[ch], DATA bnorm_mean[ch], DATA bnorm_var[ch],
                    int in_ch, int in_size, DATA **x);
DATA** linear(int w_row, int w_col, DATA lin_w[1][w_row][w_col], DATA lin_b[w_col],
                int in_size, DATA **x);

DATA** relu(int in_ch, int in_size, DATA **x);
DATA** sigmoid(int in_ch, int in_size, DATA **x);
DATA** logsoftmax(int in_ch, int in_size, DATA **x);