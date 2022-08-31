#include "Highpass_first_order.h"

#define twopi 6.28318530718f

void highpass_first_order_init(highpass_first_order *filt, float fc, float fs){

    highpass_first_order_set_samplerate(filt, fs);
    highpass_first_order_set_cutoff(filt, fc);

    //Reset output and input during initialisation
    filt->out = 0.0f;
    filt->inp = 0.0f;
}

void highpass_first_order_set_samplerate(highpass_first_order *filt, float fs){
    if(fs > (11000)){
        filt->fs = fs;
    }
    else{
        fs = 11000;
        filt->fs = fs;
    }

}

//Compute and store filter coefficients -> this is important to save resources performing the differential equation calculations
void store_coefficients(highpass_first_order *filt, float fc){
    float alpha = twopi * fc / filt->fs;  //alpha = 2 * pi * fc / fs

    filt->coeff = 1.0f / (1.0f + alpha);  //alpha / (1 + alpha)
}

void highpass_first_order_set_cutoff(highpass_first_order *filt, float fc){

    //Clamp cutoff freq to stay in bounds (below nyquist limit / positive)
    if(fc > (0.5 * filt->fs)){
        fc = (0.5 * filt->fs);
    }else if(fc < 0.0f){
        fc = 0.0f;
    }

    store_coefficients(filt, fc);
}

float highpass_first_order_update(highpass_first_order *filt, float inp){
    //IIR filter update to get new output sample
    //Vout[n] = 1 / (1 + alpha) * (Vin[n] - Vin[n-1 + Vout[n-1]]
    filt->out = filt->coeff * (inp - filt->inp + filt->out);
    filt->inp = inp;

    //clamp output in case
    if(filt->out > 1.0f){
        filt->out = 1.0f;
    }else if(filt->out < -1.0f){
        filt->out = -1.0f;
    }

    //return filter outout
    return filt->out;
}