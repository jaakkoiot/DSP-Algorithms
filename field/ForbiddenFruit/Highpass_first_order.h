#ifndef FILTER_HP_FO_H
#define FILTER_HP_FO_H

typedef struct{

    float out;           //Filter output
    float inp;           //previous filter input
    float coeff;         //coefficients used in the differential calculations, updated each time the cutoff changes
    float fs_Hz;         //sampling frequency

}highpass_first_order;

void highpass_first_order_init(highpass_first_order *filt, float fc_Hz, float fs_Hz);

void highpass_first_order_set_cutoff(highpass_first_order *filt, float fc_Hz);

float highpass_first_order_update(highpass_first_order *filt, float inp);

#endif