#ifndef FILTER_LP_FO_H
#define FILTER_LP_FO_H

typedef struct{

    float out;           //Filter output
    float coeff[2];      //coefficients used in the differential calculations, updated each time the cutoff changes
    float fs_Hz;         //sampling frequency

}lowpass_first_order;

void lowpass_first_order_init(lowpass_first_order *filt, float fc_Hz, float fs_Hz);

void lowpass_first_order_set_cutoff(lowpass_first_order *filt, float fc_Hz);

float lowpass_first_order_update(lowpass_first_order *filt, float inp);

#endif