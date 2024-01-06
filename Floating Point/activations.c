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
                y[ch_i][size_i] = 0;
            else
                y[ch_i][size_i] = x[ch_i][size_i];
        }
    }

    // To free the memory for the output matrix of previous function
    memory_free(x, in_ch);

    return y;
}

