#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

//typedef float* vectorPointVal;

void v3_from_points(float *dst, float *a, float *b); // form v3from a to b
void v3_add(float*dst,float *a, float *b);
void v3_subtract(float*dst,float *a, float *b);
float v3_dot_product(float *a, float *b);
void v3_cross_product(float*dst,float *a, float *b);
void v3_scale(float*dst,float s);
float v3_angle(float *a, float *b);
float v3_angle_quick(float *a, float *b);// angle between a and b;no cos-1
void v3_reflect(float*dst, float *v, float *n);// something wrong with this
float v3_length(float *a);
void v3_normalize(float *dst, float *a);
