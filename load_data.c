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
		sscanf(str, "%hd", &(data_in[i]));
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
	for(int i = 0; i < ch; i++)
	{
		for(int j = 0; j < col; j++)
		{
			for(int k = 0; k < row; k++)
			{
				rx_mat[k][j][i] = data_in[c]; //changed  i,jk
				c++;
			}
		}
	}
}

void load_data_all(weights_t *nn_w, LUT_t *sig_lut)//, LUT_t *lgsm_lut)
{
	DATA data_in[500000];


	// // RX DATA MATRIX
	// read_file("RxData/rxDataMat_Err_UAD.txt", NUM_ITEM*2*SMPL_PER_PRMB, data_in);
	// load_rx_mat3d(NUM_ITEM, 2, SMPL_PER_PRMB, rx_data->rxDataMat, data_in);

	// LAYER 1
	read_file("/home/linux/EDL_GCC/Weights/L1_0_w.txt", 32*2*5, data_in);
	load_mat3d(32, 2, 5, &(nn_w->L1_0_w), data_in);
	read_file("/home/linux/EDL_GCC/Weights/L1_0_b.txt", 32, nn_w->L1_0_b);
	read_file("/home/linux/EDL_GCC/Weights/L1_1_w.txt", 32, nn_w->L1_1_w);
	read_file("/home/linux/EDL_GCC/Weights/L1_1_b.txt", 32, nn_w->L1_1_b);
	read_file("/home/linux/EDL_GCC/Weights/L1_1_mean.txt", 32, nn_w->L1_1_mean);
	read_file("/home/linux/EDL_GCC/Weights/L1_1_var.txt", 32, nn_w->L1_1_var);
/*
    // LAYER 2
	read_file("/home/edc/EDL_2023_200030053/ubuntu/Weights/L2_0_w.txt", 48*32*2, data_in);
	load_mat3d(48, 32, 2, &(nn_w->L2_0_w), data_in);
	read_file("/home/edc/EDL_2023_200030053/ubuntu/Weights/L2_0_b.txt", 48, nn_w->L2_0_b);
	read_file("/home/edc/EDL_2023_200030053/ubuntu/Weights/L2_1_w.txt", 48, nn_w->L2_1_w);
	read_file("/home/edc/EDL_2023_200030053/ubuntu/Weights/L2_1_b.txt", 48, nn_w->L2_1_b);
	read_file("/home/edc/EDL_2023_200030053/ubuntu/Weights/L2_1_mean.txt", 48, nn_w->L2_1_mean);
	read_file("/home/edc/EDL_2023_200030053/ubuntu/Weights/L2_1_var.txt", 48, nn_w->L2_1_var);




	// LAYER 3
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L3_0_w.txt", 48*48*2, data_in);
	load_mat3d(48, 48, 2, &(nn_w->L3_0_w), data_in);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L3_0_b.txt", 48, nn_w->L3_0_b);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L3_1_w.txt", 48, nn_w->L3_1_w);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L3_1_b.txt", 48, nn_w->L3_1_b);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L3_1_mean.txt", 48, nn_w->L3_1_mean);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L3_1_var.txt", 48, nn_w->L3_1_var);

	// LAYER 4
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L4_0_w.txt", 1*96*192, data_in);
	load_mat3d(1, 96, 192, &(nn_w->L4_0_w), data_in);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L4_0_b.txt", 192, nn_w->L4_0_b);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L4_1_w.txt", 192, nn_w->L4_1_w);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L4_1_b.txt", 192, nn_w->L4_1_b);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L4_1_mean.txt", 192, nn_w->L4_1_mean);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L4_1_var.txt", 192, nn_w->L4_1_var);

    // Layer 7
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L7_0_w.txt", 1*192*1, data_in);
	load_mat3d(1, 192, 1, &(nn_w->L7_0_w), data_in);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/Weights/L7_0_b.txt", 1, nn_w->L7_0_b);





	// Sigmoid LUT
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/LUT/sigmoid_LUT_x.txt", LUT_LEN, sig_lut->x);
	read_file("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/LUT/sigmoid_LUT_y.txt", LUT_LEN, sig_lut->y);

}

void load_rx_data_ant2(rxData_ant2_t *rx_data)
{
	DATA data_in[500000];
	//DATA data_in[NUM_INP_SMPL];
    //printf("%d\n",35);
	// RX DATA MATRIX
    read_file("/home/linux/EDL_GCC/RxData/rxDataMat_Err_UAD.txt", NUM_ITEM*2*SMPL_PER_PRMB, data_in);
	//read_file("RxData/rxDataMat_Err_UAD.txt", NUM_ITEM*2*SMPL_PER_PRMB, data_in);
        //load_rx_mat3d(NUM_ITEM, 2, SMPL_PER_PRMB, rx_data->rxDataMat, data_in);
}
