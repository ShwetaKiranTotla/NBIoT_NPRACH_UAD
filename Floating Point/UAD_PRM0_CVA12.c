// CNN based NPRACH Receiver to get UAD and CVA estimates from Rx data

#include "dl_nprach_head.h"

void UAD_PRM0_CVA12_eval(weights_t *nn_w, rxData_t *rx_data)
{
    DATA** uad = createMatrix_2D(1, NUM_ITEM);
    DATA** cva = createMatrix_2D(1, NUM_ITEM);
    DATA** y;
    DATA** y_temp;

    for(int prm_i = 0; prm_i < NUM_ITEM; prm_i++)
    {
        DATA** x = rx_data->rxDataMat[prm_i];

        y = UAD_PRM0_CVA12_NN(nn_w, x);

        y_temp = UAD_PRM0_CVA12_Layer6(nn_w, y);
        uad[0][prm_i] = infer_uad(y_temp);

        y_temp = UAD_PRM0_CVA12_Layer6a(nn_w, y);
        cva[0][prm_i] = infer_cva(y_temp, uad[0][prm_i]);
    }
    //print_mat1d(NUM_ITEM, cva[0]);
    write_data("results/uad.txt", uad[0]);
    write_data("results/cva.txt", cva[0]);
}

DATA** UAD_PRM0_CVA12_NN(weights_t *nn_w, DATA **x)
{
    //DATA** x = rx_data->rxDataMat[0];
    DATA** y;

    ////////// LAYER 1 //////////
    y = conv1d(32, 2, 5, nn_w->L1_0_w, nn_w->L1_0_b, 5,
            2, 160, x, 32, 32);
    y = batchnorm1d(32, nn_w->L1_1_w, nn_w->L1_1_b, nn_w->L1_1_mean, nn_w->L1_1_var,
            32, 32, y);
    y = relu(32, 32, y);

    ////////// LAYER 2 //////////
    y = conv1d(48, 32, 2, nn_w->L2_0_w, nn_w->L2_0_b, 2,
            32, 32, y, 48, 16);
    y = batchnorm1d(48, nn_w->L2_1_w, nn_w->L2_1_b, nn_w->L2_1_mean, nn_w->L2_1_var,
            48, 16, y);
    y = relu(48, 16, y);

    ////////// LAYER 3 //////////
    y = conv1d(48, 48, 2, nn_w->L3_0_w, nn_w->L3_0_b, 2,
            48, 16, y, 48, 8);
    y = batchnorm1d(48, nn_w->L3_1_w, nn_w->L3_1_b, nn_w->L3_1_mean, nn_w->L3_1_var,
            48, 8, y);
    y = relu(48, 8, y);

    // Flatten
    y = flatten_mat(48, 8, y);

    ////////// LAYER 4 //////////
    y = linear(384, 192, nn_w->L4_0_w, nn_w->L4_0_b, 384, y);
    y = batchnorm1d(192, nn_w->L4_1_w, nn_w->L4_1_b, nn_w->L4_1_mean, nn_w->L4_1_var,
            192, 1, y);
    y = relu(192, 1, y);

    ////////// LAYER 5 //////////
    y = linear(192, 128, nn_w->L5_0_w, nn_w->L5_0_b, 192, y);
    y = batchnorm1d(128, nn_w->L5_1_w, nn_w->L5_1_b, nn_w->L5_1_mean, nn_w->L5_1_var,
            128, 1, y);
    y = relu(128, 1, y);

    return y;

//     y = UAD_PRM0_CVA12_Layer6a(nn_w, y);

//     y = transpose_mat(2, 1, y);
//     print_mat1d(2, y[0]);
}

DATA** UAD_PRM0_CVA12_Layer6(weights_t *nn_w, DATA **x)
{
    DATA** y;
    y = linear(128, 1, nn_w->L6_0_w, nn_w->L6_0_b, 128, x);
    y = sigmoid(1, 1, y);

    return y;
}

DATA** UAD_PRM0_CVA12_Layer6a(weights_t *nn_w, DATA **x)
{
    DATA** y;
    y = linear(128, 2, nn_w->L6a_0_w, nn_w->L6a_0_b, 128, x);
    y = logsoftmax(2, 1, y);

    return y;
}

DATA infer_uad(DATA **x)
{
    if(x[0][0] >= UAD_THRESHOLD)
        return 1;
    else
        return 0;
}

DATA infer_cva(DATA **x, DATA uad)
{
    if(x[0][0] > x[1][0])
        return (1 * uad);
    else
        return (2 * uad);
}