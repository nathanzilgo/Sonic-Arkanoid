#ifndef KRANDOM_H

int rand_ex_i(int min, int max); // integer version 
float rand_ex_f(float min, float max); // floating point, with 3 decimals x.xxx

// version for switching the sign (positive, negative)
int rand_sign_switch(int number);
float rand_sign_switch(float number);

#endif
