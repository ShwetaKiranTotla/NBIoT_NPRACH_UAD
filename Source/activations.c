// All the required activation functions for the CNN

#include "dl_nprach_head.h"

// Function: relu()
DATA** relu(int in_ch, int in_size, DATA **x)
{
    DATA **y = createMatrix_2D(in_ch, in_size);

    for(int ch_i = 0; ch_i < in_ch; ch_i++)
    {
        for(int size_i = 0; size_i < in_size; size_i++)
        {
            if(x[ch_i][size_i] < 0)
            {
                y[ch_i][size_i] = 0;
                //printf("%hi\n",y[ch_i][size_i]);
            }

            else
            {
                y[ch_i][size_i] = x[ch_i][size_i];
                //printf("%hi\n",y[ch_i][size_i]);
            }
        }
        //write_data("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/results/uad.txt", y[ch_i]);

    }

    // To free the memory for the output matrix of previous function
    memory_free(x, in_ch);

    return y;
}

// Function: relu()
DATA** relu_1(int in_ch, int in_size, DATA **x)
{
    //printf("%d\n",3);
    DATA **y = createMatrix_2D(in_ch, in_size);

    for(int ch_i = 0; ch_i < in_ch; ch_i++)
    {
        for(int size_i = 0; size_i < in_size; size_i++)
        {
            if(x[ch_i][size_i] < 0)
            {
                y[ch_i][size_i] = 0;
                printf("%d\n",y[ch_i][size_i]);
            }

            else
            {
                y[ch_i][size_i] = x[ch_i][size_i];
                printf("%d\n",y[ch_i][size_i]);
            }
        }
        //write_data("/home/edc/EDL_2023_200030053/DL_Receiver_C_Fixed_Rxsignal/CodeBlocks_Project/results/uad.txt", y[ch_i]);

    }

    // To free the memory for the output matrix of previous function
    memory_free(x, in_ch);

    return y;
}

// Function: sigmoid()
DATA** sigmoid(int in_ch, int in_size, DATA **x, LUT_t *sig_lut)
{
    DATA **y = createMatrix_2D(in_ch, in_size);
    DATA temp;

    for(int ch_i = 0; ch_i < in_ch; ch_i++)
    {
        for(int size_i = 0; size_i < in_size; size_i++)
        {
            y[ch_i][size_i] = lookup_LUT(sig_lut, x[ch_i][size_i]);
            // temp = exp(-1 * x[ch_i][size_i]);
            // y[ch_i][size_i] = 1 / (1 + temp);
        }
    }

    return y;
}
