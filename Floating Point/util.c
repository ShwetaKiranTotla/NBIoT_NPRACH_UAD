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