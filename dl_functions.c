// This file has the functions required for the following NN layers
// 1. Conv1D
// 2. Batchnorm1D
// 3. Linear

#include "dl_nprach_head.h"

// Function: conv1d()
// Input:   f_n         = number of filters,
//          f_ch        = number of channels on each filter,
//          f_size      = size of filter,
//          conv_w      = filter weight matrix,
//          conv_b      = bias matrix,
//          stride      = stride for convolution
//          in_ch       = input channels,
//          in_size     = size of input data,
//          x           = input data matrix,
//          out_ch      = output channels,
//          out_size    = size of output data
// Return:  y           = output data matrix
DATA** conv1d(int f_n, int f_ch, int f_size, DATA conv_w[f_n][f_ch][f_size], DATA conv_b[f_n], int stride,
            int in_ch, int in_size, DATA **x,
            int out_ch, int out_size)
{
    DATA **y = createMatrix_2D(out_ch, out_size);
    DATA temp = 0;

    for(int ch_i = 0; ch_i < out_ch; ch_i++) // iterate over output channels
    {
        for(int size_i = 0; size_i < out_size; size_i++) // iterate over the size of output
        {
            temp = 0;
            // Calculate the convolution sum for 1 output sample
            for (int x_ch = 0; x_ch < in_ch; x_ch++) // iterate over input channels
            {
                int start_pt = size_i * stride;
                for(int i = start_pt, j = 0; i < (start_pt + f_size); i++, j++) // data slice to multiply with filter
                {
                    temp = temp + mult_fixed(x[x_ch][i], conv_w[ch_i][x_ch][j]);
                    // temp = temp + (x[x_ch][i] * conv_w[ch_i][x_ch][j]);
                }
            }
            y[ch_i][size_i] = temp + conv_b[ch_i];
            // if(ch_i == 0)
            //     printf("%d\n", temp);
        }
    }

    // To free the memory for the output matrix of previous function
    memory_free(x, in_ch);

    return y;
}

// Fucntion: batchnorm1d()
// Input:

DATA** batchnorm1d(int ch, DATA bnorm_w[ch], DATA bnorm_b[ch], DATA bnorm_mean[ch], DATA bnorm_var[ch],
                    int in_ch, int in_size, DATA **x)
{
    DATA **y = createMatrix_2D(in_ch, in_size);
    DATA eps = 1;   // Lowest positive number representation for fixed point arithmetic

    for(int ch_i = 0; ch_i < in_ch; ch_i++)
    {
        DATA ch_std = sqrt_fixed(bnorm_var[ch_i] + eps);

        for(int size_i = 0; size_i < in_size; size_i++)
        {
            y[ch_i][size_i] = divide_fixed(mult_fixed((x[ch_i][size_i] - bnorm_mean[ch_i]), bnorm_w[ch_i]), ch_std) + bnorm_b[ch_i];
            // y[ch_i][size_i] = (((x[ch_i][size_i] - bnorm_mean[ch_i]) * bnorm_w[ch_i])/ ch_std) + bnorm_b[ch_i];
        }
    }

    // To free the memory for the output matrix of previous function
    memory_free(x, in_ch);

    return y;
}

// Function: linear()
// Input:   w_row       = rows in weight matrix,
//          w_col       = colunmns in weight matrix,
//          lin_w       = weight matrix,
//          lin_b       = bias vector,
//          in_size     = size of input vector,
//          x           = input data matrix
// Return:  y           = output data matrix
DATA** linear(int w_row, int w_col, DATA lin_w[1][w_row][w_col], DATA lin_b[w_col],
                int in_size, DATA **x)
{
    DATA **y = createMatrix_2D(w_col, 1);
    DATA temp = 0;

    for(int col_i = 0; col_i < w_col; col_i++)
    {
        temp = 0;
        for(int row_i = 0; row_i < w_row; row_i++)
        {
            temp = temp + mult_fixed(x[row_i][0], lin_w[0][row_i][col_i]);
            //temp = temp + (x[row_i][0] * lin_w[0][row_i][col_i]);
        }
        y[col_i][0] = temp + lin_b[col_i];
        //printf("%d\n", y[0][col_i]);
    }

    // To free the memory for the output matrix of previous function
    memory_free(x, in_size);

    return y;
}
