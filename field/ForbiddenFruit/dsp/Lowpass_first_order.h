#ifndef FILTER_LP_FO_H
#define FILTER_LP_FO_H

/*IRR lp filter*/
typedef struct{

    float out;           //Filter output
    float coeff[2];      //coefficients used in the differential calculations, updated each time the cutoff changes
    float fs;            //sampling frequency

}lowpass_first_order;

void lowpass_first_order_init(lowpass_first_order *filt, float fc_Hz, float fs);

void lowpass_first_order_set_cutoff(lowpass_first_order *filt, float fc);

void lowpass_first_order_set_samplerate(lowpass_first_order *filt, float fs);

float lowpass_first_order_update(lowpass_first_order *filt, float inp);

void store_coefficients(lowpass_first_order *filt, float fc);

#endif