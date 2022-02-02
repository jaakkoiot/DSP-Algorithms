#ifndef FILTER_HP_FO_H
#define FILTER_HP_FO_H

/*IRR hp filter*/
typedef struct{

    float out;           //Filter output
    float inp;           //previous filter input used in calculations
    float coeff;         //coefficients used in the differential calculation, updated each time the cutoff changes
    float fs;         //sampling frequency

}highpass_first_order;

void highpass_first_order_init(highpass_first_order *filt, float fc, float fs);

void highpass_first_order_set_cutoff(highpass_first_order *filt, float fc);

float highpass_first_order_update(highpass_first_order *filt, float inp);

#endif