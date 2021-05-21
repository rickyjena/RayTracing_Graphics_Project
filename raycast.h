#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum JSONObjType{
    NO_TYPE, CAMERA, SPHERE, PLANE
} JSONObj;

typedef struct RGBPixel_t {
    unsigned char r, g, b;
} RGBPixel;

typedef struct PPMMetaData_t{
    int format;
    int height;
    int width;
    int maxVal;
    RGBPixel *pixmap;
} PPMMetaData;

typedef struct camera_t {

  float cam_width;
  float cam_height;

} camera;

// just sphere
typedef struct sphere_t {

  float *color;
  float *position;
  float radius;

} sphere;

// just plane
typedef struct plane_t {

  float *color;
  float *position;
  float *normal;

} plane;

typedef struct object_t {
  //enum JSONObjType objTypeA;
  int objType;

  union {
    camera camData;
    sphere sphrData;
    plane planeData;
  };

} object;

static inline float sqr(float v);
void jsonParsing(FILE *inputFile);
void ppm_write3(FILE *fp, int size, PPMMetaData *md);
void fail(char *str);
int getCamerasFromJson( object *objects );
void shadePixamapPixel(float *color, int row, int col, PPMMetaData *img);
float planeIntersect(float *Ro, float *Rd, float *Pos, float *Norm);
float sphereIntersect(float *Ro, float *Rd, float *center, float radius);
void raycastScene( PPMMetaData *img, float camWidth, float camHeight, object *objects);