#include "dl_nprach_head.h"
#include "LTE-eNB-DataTypes.h"

void print_mat3d(int ch, int row, int col, DATA (*mat)[ch][row][col])
{
	for(int i = 0; i < ch; i++)
	{
		for(int j = 0; j < row; j++)
		{
			for(int k = 0; k < col; k++)
			{
				printf("%f ", (*mat)[i][j][k]);
			}
			printf("\n");
		}
	}
}

void print_mat1d(int size, DATA *mat)
{
	for(int i = 0; i < size; i++)
	{
		printf("%f\n", mat[i]);
	}
}

int main()
{
	// Structure to store all weights and biases of CNN
	weights_t nn_w;
	rxData_t rx_data;
	rx_data.rxDataMat = createMatrix_3D(NUM_ITEM, 2 , SMPL_PER_PRMB);

	load_data_all(&nn_w, &rx_data);

	UAD_PRM0_CVA12_eval(&nn_w, &rx_data);

	//print_mat3d(NUM_ITEM, 2, 160, &rx_data.rxDataMat);
	//print_mat1d(2, nn_w.L6a_0_w[0][127]);
}
