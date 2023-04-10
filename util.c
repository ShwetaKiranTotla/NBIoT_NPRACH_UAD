// Utility functions

#include "dl_nprach_head.h"

DATA** createMatrix_2D(int row, int col)
{
    int i = 0;
    DATA **matrix = NULL;
    matrix = (DATA**)malloc(sizeof(DATA*) * row);
    if(matrix == NULL)
        printf("Matrix2D malloc failed\n");
    for(i = 0; i < row; i++)
    {
        matrix[i] = (DATA*)malloc(sizeof(DATA) * col);
        if(matrix[i] == NULL)  
            printf("Matrix2D malloc failed\n");
    }

    return matrix;
}

DATA*** createMatrix_3D(int depth, int row, int col)
{
    int i = 0;
    DATA ***matrix = NULL;

    matrix = (DATA***)malloc(sizeof(DATA**) * depth);
    if(matrix == NULL)
        printf("Matrix3D malloc failed at depth\n");
    for(int j = 0; j < depth; j++)
    {
        matrix[j] = (DATA**)malloc(sizeof(DATA*) * row);
        if(matrix[j] == NULL)
            printf("Matrix3D malloc failed at row\n");
        for(i = 0; i < row; i++)
        {
            matrix[j][i] = (DATA*)malloc(sizeof(DATA) * col);
            if(matrix[j][i] == NULL)  
                printf("Matrix3D malloc failed at col\n");
        }
    }

    return matrix;
}

void memory_free(DATA **matrix, int row)
{
    int i = 0;
    for(i = 0; i < row; i++)
        free(matrix[i]);
    free(matrix);
}

DATA** flatten_mat(int row, int col, DATA **matrix)
{
    DATA **flat_mat = createMatrix_2D(row*col, 1);
    
    int c = 0;
    for(int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            flat_mat[c][0] = matrix[i][j];
            c++;
        }
    }

    memory_free(matrix, row);

    return flat_mat;
}

DATA** transpose_mat(int row, int col, DATA **matrix)
{
    DATA **trans_mat = createMatrix_2D(col, row);

    for(int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            trans_mat[j][i] = matrix[i][j];
        }
    }

    memory_free(matrix, row);

    return trans_mat;
}

void write_data(char *name, DATA *mat)
{
    FILE *fptr = fopen(name, "w");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    int temp = 0;
    for(int i = 0; i < NUM_ITEM; i++)
    {   
        temp = (int)mat[i];
        //printf("%d , %d\n", temp, i);
        fprintf(fptr, "%d,\n", temp);
    }

    fclose(fptr);
}

DATA mult_fixed(DATA a, DATA b)
{
    DATA y;

    long int mult = ((long int)a) * ((long int)b);
    mult = mult / SCALE_FAC;
    y = (DATA)mult;       
    //printf("%hi\n",y);
    return y;
}

DATA divide_fixed(DATA a, DATA b)
{
    DATA y;

    int div = ((int)a * SCALE_FAC);
    div = (div / (int)b);
    y = (DATA)div;

    return y;
}

DATA sqrt_fixed(DATA a)
{
    DATA y;

    int sq = ((int)a * SCALE_FAC);
    sq = sqrt(sq);
    y = (DATA)sq;

    return y;
}

DATA lookup_LUT(LUT_t *lut, DATA x)
{
    DATA diff_prev = abs(x - lut->x[0]);
    DATA diff = 0;
    DATA y = 0;
    DATA flag = 0;
    DATA sig_lut_min = (-4 * SCALE_FAC);
    DATA sig_lut_max = (4 * SCALE_FAC);

    if(x > sig_lut_min && x < sig_lut_max)
    {
        // Checks for nearest value in LUT->x
        for(int i = 1; i < LUT_LEN; i++)
        {
            diff = abs(x - lut->x[i]);
            if(diff >= diff_prev)
            {
                y = lut->y[i-1];
                flag = 1;
                break;
            }
            diff_prev = diff;
        }
    }
    else if(x > sig_lut_max) // approximately 1
    {
        y = (1 * SCALE_FAC - 1);
    }
    else if(x < sig_lut_min) // approximately 0
    {
        y = 1;
    }

    return y;
}

DATA** sum_vectors(int size, DATA **x, DATA **y)
{
    DATA **sum = createMatrix_2D(size, 1);
    for(int i = 0; i < size; i++)
    {
        sum[i][0] = (x[i][0] + y[i][0]);
    }

    return sum;
}
