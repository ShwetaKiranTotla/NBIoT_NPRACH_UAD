// This file loads data, weights and baises for the NPRACH DL Receiver
#include "dl_nprach_head.h"

void read_file(char* name, int size, DATA *data_in)
{
    FILE *fptr;
    // open file using file pointer
    fptr = fopen(name, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

	int MAX_SIZE = 100;
	char str[MAX_SIZE];

	for(int i = 0; i < size; i++)
	{
		fgets(str, MAX_SIZE, fptr);
		//printf("%s ", str);
		sscanf(str, "%f", &(data_in[i]));
	}

    fclose(fptr);
}

void load_mat3d(int ch, int row, int col, DATA (*mat)[ch][row][col], DATA *data_in)
{
	int c = 0;
	for(int i = 0; i < col; i++)
	{
		for(int j = 0; j < row; j++)
		{
			for(int k = 0; k < ch; k++)
			{
				(*mat)[k][j][i] = data_in[c];
				c++;
			}
		}
	}
}

void load_rx_mat3d(int ch, int row, int col, DATA ***rx_mat, DATA *data_in)
{
	int c = 0;
	for(int i = 0; i < col; i++)
	{
		for(int j = 0; j < row; j++)
		{
			for(int k = 0; k < ch; k++)
			{
				rx_mat[k][j][i] = data_in[c];
				c++;
			}
		}
	}
}

void load_data_all(weights_t *nn_w, rxData_t *rx_data)
{
	DATA data_in[500000];

	// RX DATA MATRIX
	read_file("RxData/rxDataMat_Err_UAD.txt", NUM_ITEM*2*SMPL_PER_PRMB, data_in);
	load_rx_mat3d(NUM_ITEM, 2, SMPL_PER_PRMB, rx_data->rxDataMat, data_in);

	// LAYER 1
	read_file("Weights/L1_0_w.txt", 32*2*5, data_in);
	load_mat3d(32, 2, 5, &(nn_w->L1_0_w), data_in);
	read_file("Weights/L1_0_b.txt", 32, nn_w->L1_0_b);
	read_file("Weights/L1_1_w.txt", 32, nn_w->L1_1_w);
	read_file("Weights/L1_1_b.txt", 32, nn_w->L1_1_b);
	read_file("Weights/L1_1_mean.txt", 32, nn_w->L1_1_mean);
	read_file("Weights/L1_1_var.txt", 32, nn_w->L1_1_var);

	// LAYER 2
	read_file("Weights/L2_0_w.txt", 48*32*2, data_in);
	load_mat3d(48, 32, 2, &(nn_w->L2_0_w), data_in);
	read_file("Weights/L2_0_b.txt", 48, nn_w->L2_0_b);
	read_file("Weights/L2_1_w.txt", 48, nn_w->L2_1_w);
	read_file("Weights/L2_1_b.txt", 48, nn_w->L2_1_b);
	read_file("Weights/L2_1_mean.txt", 48, nn_w->L2_1_mean);
	read_file("Weights/L2_1_var.txt", 48, nn_w->L2_1_var);

	// LAYER 3
	read_file("Weights/L3_0_w.txt", 48*48*2, data_in);
	load_mat3d(48, 48, 2, &(nn_w->L3_0_w), data_in);
	read_file("Weights/L3_0_b.txt", 48, nn_w->L3_0_b);
	read_file("Weights/L3_1_w.txt", 48, nn_w->L3_1_w);
	read_file("Weights/L3_1_b.txt", 48, nn_w->L3_1_b);
	read_file("Weights/L3_1_mean.txt", 48, nn_w->L3_1_mean);
	read_file("Weights/L3_1_var.txt", 48, nn_w->L3_1_var);

	// LAYER 4
	read_file("Weights/L4_0_w.txt", 1*384*192, data_in);
	load_mat3d(1, 384, 192, &(nn_w->L4_0_w), data_in);
	read_file("Weights/L4_0_b.txt", 192, nn_w->L4_0_b);
	read_file("Weights/L4_1_w.txt", 192, nn_w->L4_1_w);
	read_file("Weights/L4_1_b.txt", 192, nn_w->L4_1_b);
	read_file("Weights/L4_1_mean.txt", 192, nn_w->L4_1_mean);
	read_file("Weights/L4_1_var.txt", 192, nn_w->L4_1_var);

	// LAYER 5
	read_file("Weights/L5_0_w.txt", 1*192*128, data_in);
	load_mat3d(1, 192, 128, &(nn_w->L5_0_w), data_in);
	read_file("Weights/L5_0_b.txt", 128, nn_w->L5_0_b);
	read_file("Weights/L5_1_w.txt", 128, nn_w->L5_1_w);
	read_file("Weights/L5_1_b.txt", 128, nn_w->L5_1_b);
	read_file("Weights/L5_1_mean.txt", 128, nn_w->L5_1_mean);
	read_file("Weights/L5_1_var.txt", 128, nn_w->L5_1_var);

	// Layer 6
	read_file("Weights/L6_0_w.txt", 1*128*1, data_in);
	load_mat3d(1, 128, 1, &(nn_w->L6_0_w), data_in);
	read_file("Weights/L6_0_b.txt", 1, nn_w->L6_0_b);

	// Layer 6a
	read_file("Weights/L6a_0_w.txt", 1*128*2, data_in);
	load_mat3d(1, 128, 2, &(nn_w->L6a_0_w), data_in);
	read_file("Weights/L6a_0_b.txt", 2, nn_w->L6a_0_b);
}

// void load_mat3d(char* name, DATA (*mat)[32][2][5])
// {
//     FILE *fptr;
//     // open file using file pointer
//     fptr = fopen(name, "r");
//     if (fptr == NULL)
//     {
//         printf("Cannot open file \n");
//         exit(0);
//     }

// 	int MAX_SIZE = 10000;
// 	char* c;
// 	char* token;
// 	char str[MAX_SIZE];

// 	for(int i = 0; i < 32; i++)
// 	{
// 		c = fgets(str, MAX_SIZE, fptr);
// 		token = strtok(str, " ");
// 		for(int j = 0; j < 5; j++)
// 		{
// 			for(int k = 0; k < 2; k++)
// 			{
// 				if(token != NULL)
// 				{	
// 					printf("%s ", token);
// 					sscanf(token, "%f", &(*mat)[i][j][k]);
// 					//printf("%f ", nn_w.L1_0_w[i][k][j]);
// 				}
// 				token = strtok(NULL, " ");
// 			}
// 		}
// 		printf("\n");
// 	}
//     fclose(fptr);
// }