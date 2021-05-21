#include "v3math.h"

/* Function Name: v3_from_points
 * Algorithm: takes in two points and returns the vector
 * 	      between the two points
 */
void v3_from_points(float *dst, float *a, float *b){
	
	dst[0] = b[0] - a[0];
	dst[1] = b[1] - a[1];
	dst[2] = b[2] - a[2];

}

/* Function Name: v3_add
 * Algorithm: takes in two vectors, adds them together
 *            and returns the result in the destination vector
 */
void v3_add(float *dst, float *a, float *b){
	
	dst[0] = a[0] + b[0];
	dst[1] = a[1] + b[1];
	dst[2] = a[2] + b[2];

}

/* Function Name: v3_subtract
 * Algorithm: takes in two vectors, subtracts the second from the first
 *            and returns the result in the destination vector
 */
void v3_subtract(float *dst, float *a, float *b){

	dst[0] = a[0] - b[0];
        dst[1] = a[1] - b[1];
        dst[2] = a[2] - b[2];

}

/* Function Name: v3_dot_product
 * Algorithm: takes in two vectors, finds the dot product of the them
 *            and returns the result
 */
float v3_dot_product(float *a, float *b){
	
	float dotProduct = 0.0;
	dotProduct = (a[0]*b[0]) + (a[1]*b[1]) + (a[2]*b[2]);
	return dotProduct;	

}

/* Function Name: v3_cross_product
 * Algorithm: takes in two vectors, finds the cross product of the them
 *            and returns the result in the destination vector
 */
void v3_cross_product(float *dst, float *a, float *b){
	
	dst[0] = (a[1]*b[2]) - (a[2]*b[1]);
	dst[1] = (a[2]*b[0]) - (a[0]*b[2]);
	dst[2] = (a[0]*b[1]) - (a[1]*b[0]);

}

/* Function Name: v3_dot_product
 * Algorithm: takes in a vector and scalar, scales the vector
 *            with the given scalar, and returns the result in
 *            the destination vector
 */
void v3_scale(float *dst, float s){

	dst[0] = s * dst[0];
	dst[1] = s * dst[1];
	dst[2] = s * dst[2];

}

/* Function Name: v3_angle
 * Algorithm: takes in two vectors, finds the angle between them
 *            and returns the result (using cosine)
 */
float v3_angle(float *a, float *b){ 

	float angle = 0.0;
	angle = (float)(acos((double)((v3_dot_product(a,b))/(v3_length(a)*v3_length(b)))));
	return angle;
	
}

/* Function Name: v3_angle_quick
 * Algorithm: takes in two vectors, finds the angle between them
 *            and returns the result (without using cosine)
 */
float v3_angle_quick(float *a, float *b) // angle between a and b; no cos-1
{
        float angle = 0.0;
	angle = (float)((v3_dot_product(a,b))/(v3_length(a)*v3_length(b)));
	return angle;
       
}

/* Function Name: v3_reflect
 * Algorithm: takes in a vector, then finds the reflected vector 
 *            and returns the result in the destination vector
 */
void v3_reflect(float *dst, float *v, float *n){

	dst[0] = v[0] - 2*(n[0]-v[0])*n[0];
	dst[1] = v[1] - 2*(n[1]-v[1])*n[1];
	dst[2] = v[2] - 2*(n[2]-v[2])*n[2];

}

/* Function Name: v3_cross_product
 * Algorithm: takes in a vector, finds the length of the vector
 *            and returns the result in the destination vector
 */
float v3_length(float *a){

	float length = 0.0;
	length = (float)(sqrt((double)((a[0]*a[0]) + (a[1]*a[1]) + (a[2]*a[2]))));
	return length;

}

/* Function Name: v3_cross_product
 * Algorithm: takes in a vector, then normalizes the vector
 *            and returns the result in the destination vector
 */
void v3_normalize(float *dst, float *a){

	dst[0] = a[0] / v3_length(a);
	dst[1] = a[1] / v3_length(a);
	dst[2] = a[2] / v3_length(a);

}


