#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svm.h"

int main(int argc, char **argv)
{
    // load the data
    struct svm_problem prob;
    struct svm_node *x_space;
    prob.l = 4;
    prob.y = malloc(prob.l * sizeof(double));
    prob.x = malloc(prob.l * sizeof(struct svm_node *));
    x_space = malloc(prob.l * 2 * sizeof(struct svm_node));
    prob.x[0] = &x_space[0];
    prob.x[1] = &x_space[2];
    prob.x[2] = &x_space[4];
    prob.x[3] = &x_space[6];
    prob.y[0] = 1;
    prob.y[1] = -1;
    prob.y[2] = -1;
    prob.y[3] = 1;
    prob.x[0][0].index = 1;
    prob.x[0][0].value = 1;
    prob.x[0][1].index = 2;
    prob.x[0][1].value = 2;
    prob.x[1][0].index = 1;
    prob.x[1][0].value = -1;
    prob.x[1][1].index = 2;
    prob.x[1][1].value = -2;
    prob.x[2][0].index = 1;
    prob.x[2][0].value = -1;
    prob.x[2][1].index = 2;
    prob.x[2][1].value = -1;
    prob.x[3][0].index = 1;
    prob.x[3][0].value = 1;
    prob.x[3][1].index = 2;
    prob.x[3][1].value = 1;

    // train the SVM
    struct svm_parameter param;
    param.svm_type = C_SVC;
    param.kernel_type = LINEAR;
    param.C = 1;
    param.eps = 0.001;
    param.nr_weight = 0;
    param.weight_label = NULL;
    param.weight = NULL;
    struct svm_model *model = svm_train(&prob, &param);

    // predict new data
    struct svm_node x[3];
    x[0].index = 1;
    x[0].value = 0;
    x[1].index = 2;
    x[1].value = 0;
    x[2].index = -1;
    double prediction = svm_predict(model, x);

    // free memory
    svm_free_and_destroy_model(&model);
    free(x_space);
    free(prob.y);
    free(prob.x);

    // print prediction
    printf("Prediction: %lf\n", prediction);

    return 0;
}
