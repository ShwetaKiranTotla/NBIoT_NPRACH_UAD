#include "dl_nprach_head.h"

void print_mat3d(int ch, int row, int col, DATA (*mat)[ch][row][col])
{
	for(int i = 0; i < ch; i++)
	{
		for(int j = 0; j < row; j++)
		{
			for(int k = 0; k < col; k++)
			{
				printf("%d ", (*mat)[i][j][k]);
			}
			printf("\n");
		}
	}
}

void print_mat1d(int size, DATA *mat)
{
	for(int i = 0; i < size; i++)
	{
		printf("%d\n", mat[i]);
	}
}

int main()
{
	if(NUM_RX_ANTENNA == 2)
	{
		// Structure to store all weights and biases of CNN
		weights_t nn_w;
		rxData_ant2_t rx_data;
		LUT_t sig_lut;

		rx_data.rxDataMat = createMatrix_3D(NUM_ITEM, 2 , SMPL_PER_PRMB);//changed
		load_data_all(&nn_w, &sig_lut);//, &lgsm_lut);
		load_rx_data_ant2(&rx_data);
		UAD_PRM0_CVA12_eval_ant2(&nn_w, &rx_data, &sig_lut);//, &lgsm_lut);
	}
	else
	{
		printf("Number of Rx Antenna can be 1 or 2");
	}

	//print_mat3d(NUM_ITEM, 2, 160, &rx_data.rxDataMat);
}
