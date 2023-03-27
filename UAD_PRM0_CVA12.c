// CNN based NPRACH Receiver to get UAD and CVA estimates from Rx data

#include "dl_nprach_head.h"

void UAD_PRM0_CVA12_eval(weights_t *nn_w, rxData_t *rx_data, LUT_t *sig_lut, LUT_t *lgsm_lut)
{
    DATA** uad = createMatrix_2D(1, NUM_ITEM);
    DATA** cva = createMatrix_2D(1, NUM_ITEM);
    DATA** y;
    DATA** y_temp;

    for(int prm_i = 0; prm_i < NUM_ITEM; prm_i++)
    {
        DATA** x = rx_data->rxDataMat[prm_i];

        y = UAD_PRM0_CVA12_NN(nn_w, x);

        y_temp = UAD_PRM0_CVA12_Layer6(nn_w, y, sig_lut);
        uad[0][prm_i] = infer_uad(y_temp);

        y_temp = UAD_PRM0_CVA12_Layer6a(nn_w, y);
        cva[0][prm_i] = infer_cva(y_temp, uad[0][prm_i]);
    }
    // y_temp = transpose_mat(2, 1, y_temp);
    // print_mat1d(2, y_temp[0]);
    write_data("results/uad.txt", uad[0]);
}


DATA** UAD_PRM0_CVA12_NN(weights_t *nn_w, DATA **x)
{
    DATA** y;

    ////////// LAYER 1 //////////
    y = conv1d(32, 2, 5, nn_w->L1_0_w, nn_w->L1_0_b, 5, 2, 40, x, 32, 8);
    y = batchnorm1d(32, nn_w->L1_1_w, nn_w->L1_1_b, nn_w->L1_1_mean, nn_w->L1_1_var, 32, 8, y);
    y = relu(32, 8, y);

    ////////// LAYER 2 //////////
    y = conv1d(48, 32, 2, nn_w->L2_0_w, nn_w->L2_0_b, 2, 32, 8, y, 48, 4);
    y = batchnorm1d(48, nn_w->L2_1_w, nn_w->L2_1_b, nn_w->L2_1_mean, nn_w->L2_1_var, 48, 4, y);
    y = relu(48, 4, y);

    ////////// LAYER 3 //////////
    y = conv1d(48, 48, 2, nn_w->L3_0_w, nn_w->L3_0_b, 2, 48, 4, y, 48, 2);
    y = batchnorm1d(48, nn_w->L3_1_w, nn_w->L3_1_b, nn_w->L3_1_mean, nn_w->L3_1_var, 48, 2, y);
    y = relu(48, 2, y);

    // Flatten
    y = flatten_mat(48, 2, y);

    ////////// LAYER 4 //////////
    y = linear(96, 192, nn_w->L4_0_w, nn_w->L4_0_b, 96, y);
    y = batchnorm1d(192, nn_w->L4_1_w, nn_w->L4_1_b, nn_w->L4_1_mean, nn_w->L4_1_var,192, 1, y);
    y = relu(192, 1, y);

    ////////// LAYER 7 //////////
    y = linear(192, 1, nn_w->L7_0_w, nn_w->L7_0_b, 192, y);
    return y;
}

DATA infer_uad(DATA **x)
{
    if(x[0][0] >= UAD_THRESHOLD * SCALE_FAC)
        return 1;
    else
        return 0;
}

