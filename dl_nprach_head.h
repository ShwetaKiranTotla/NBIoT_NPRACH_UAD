#include <stdio.h>
#include <stdlib.h>
#include <math.h>

////////// CONSTANTS //////////
#define NUM_ITEM	2
#define NUM_INP_SMPL	160
#define SMPL_PER_PRMB	40 //40 for cva1 160 for cva 2 and 640 for cva 3
#define SCALE_FAC	16	// 2^8
#define SCALE_BITS	4
#define UAD_THRESHOLD	0.7 //0.65
#define LUT_LEN		161
#define NUM_RX_ANTENNA	2
#define DOWN_SCL8	4

////////// DATA TYPE DEFINITION //////////
typedef short DATA;

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
	DATA L4_0_w[1][192][96];
	DATA L4_0_b[192];
	DATA L4_1_w[192];
	DATA L4_1_b[192];
	DATA L4_1_mean[192];
	DATA L4_1_var[192];

	// Layer 5
	DATA L5_0_w[1][192][1];
	DATA L5_0_b[1];

};
typedef struct weights weights_t;

struct rxData
{
	DATA ***rxDataMat;
};
typedef struct rxData rxData_t;

struct LUT
{
	DATA x[LUT_LEN];
	DATA y[LUT_LEN];
};
typedef struct LUT LUT_t;

////////// FUNCTION PROTOTYPES //////////

void read_file(char* name, int size, DATA *data_in);
void print_mat3d(int ch, int row, int col, DATA (*mat)[ch][row][col]);
void print_mat1d(int size, DATA *mat);
DATA** createMatrix_2D(int row, int col);
DATA*** createMatrix_3D(int depth, int row, int col);
DATA** flatten_mat(int row, int col, DATA **matrix);
DATA** transpose_mat(int row, int col, DATA **matrix);
void memory_free(DATA **matrix, int row);
void write_data(char *name, DATA *mat);
DATA mult_fixed(DATA a, DATA b);
DATA divide_fixed(DATA a, DATA b);
DATA sqrt_fixed(DATA a);
DATA lookup_LUT(LUT_t *lut, DATA x);
DATA** sum_vectors(int size, DATA **x, DATA **y);

void load_mat3d(int ch, int row, int col, DATA (*mat)[ch][row][col], DATA *data_in);
void load_rx_mat3d(int ch, int row, int col, DATA ***rx_mat, DATA *data_in);
void load_data_all(weights_t *nn_w, LUT_t *sig_lut);//, LUT_t *lgsm_lut);
void load_rx_data_ant1(rxData_t *rx_data);
void load_rx_data_ant2(rxData_ant2_t *rx_data);

//void UAD_PRM0_CVA12_eval(weights_t *nn_w, rxData_t *rx_data, LUT_t *sig_lut, LUT_t *lgsm_lut);
void UAD_PRM0_CVA12_eval_ant2(weights_t *nn_w, rxData_ant2_t *rx_data, LUT_t *sig_lut);//, LUT_t *lgsm_lut);
DATA** UAD_PRM0_CVA12_NN(weights_t *nn_w, DATA **x);
DATA** UAD_PRM0_CVA12_Layer7(weights_t *nn_w, DATA **x, LUT_t *sig_lut);
DATA** UAD_PRM0_CVA12_Layer6a(weights_t *nn_w, DATA **x);
DATA infer_uad(DATA **x);
DATA infer_cva(DATA **x, DATA uad);

DATA** conv1d(int f_n, int f_ch, int f_size, DATA conv_w[f_n][f_ch][f_size], DATA conv_b[f_n], int stride,
            int in_ch, int in_size, DATA **x,
            int out_ch, int out_size);
DATA** batchnorm1d(int ch, DATA bnorm_w[ch], DATA bnorm_b[ch], DATA bnorm_mean[ch], DATA bnorm_var[ch],
                    int in_ch, int in_size, DATA **x);
DATA** batchnorm1d_1(int ch, DATA bnorm_w[ch], DATA bnorm_b[ch], DATA bnorm_mean[ch], DATA bnorm_var[ch],
                    int in_ch, int in_size, DATA **x);
DATA** linear(int w_row, int w_col, DATA lin_w[1][w_row][w_col], DATA lin_b[w_col],
                int in_size, DATA **x);

DATA** relu(int in_ch, int in_size, DATA **x);
DATA** relu_1(int in_ch, int in_size, DATA **x);
DATA** sigmoid(int in_ch, int in_size, DATA **x, LUT_t *sig_lut);

