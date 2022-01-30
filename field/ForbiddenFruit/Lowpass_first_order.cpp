#include "Lowpass_first_order.h"

#define twopi 6.28318530718f

void lowpass_first_order_init(lowpass_first_order *filt, float fc_Hz, float fs_Hz){

    filt->fs_Hz = fs_Hz;            //store sampling freq
    lowpass_first_order_set_cutoff(filt, fc_Hz);

    //Reset output
    filt->out = 0.0f;

}

void lowpass_first_order_set_cutoff(lowpass_first_order *filt, float fc_Hz){

    //Clamp cutoff freq to stay in bounds (below nyquist limit / positive)
    if(fc_Hz > (0.5 * filt->fs_Hz)){
        fc_Hz = (0.5 * filt->fs_Hz);
    }else if(fc_Hz < 0.0f){
        fc_Hz = 0.0f;
    }

    //Compute and store filter coefficients -> this is important to save resources performing the differential equation calculations
    float alpha = twopi * fc_Hz / filt->fs_Hz;  //alpha = 2 * pi * fc / fs
    filt->coeff[0] = alpha / (1.0f + alpha);    //alpha / (1 + alpha)
    filt->coeff[1] = 1.0f / (1.0f + alpha);     //1 / (1 + alpha)
}

float lowpass_first_order_update(lowpass_first_order *filt, float inp){
    //IIR filter update to get new output sample
    //Vout[n] = alpha / (1 + alpha) * Vin[n] + 1 / (1 + alpha) * Vout[n - 1]
    filt->out = filt->coeff[0] * inp + filt->coeff[1] * filt->out;

    //clamp output in case
    if(filt->out > 1.0f){
        filt->out = 1.0f;
    }else if(filt->out < -1.0f){
        filt->out = -1.0f;
    }

    //return filter outout
    return filt->out;
}