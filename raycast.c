#include <stdio.h>
#include "raycast.h"
#include "v3math.c"
#include <math.h>
const int MAX_LINE_LENGTH = 70;
const int  MAX_COLOR_VAL = 255;
const int MAX_OBJECTS = 129;

int max_counter = 0;

// Per project specifications, the maximum amount of objects rendered
// in a scene will be no more than 128 objects.
object objects[129];

/* Function Name: sqr
 * Algorithm: Takes in a vector and squares it
 */
static inline float sqr(float v){
  return v*v;
}

/* Function Name: jsonParsing
*  Algorithm: Takes in JSON files CSV edited text and parses it.
*             Then stores values in a array of objects, also
*             prints out to make sure its been stored in
*             in desired area.
*/
void jsonParsing(FILE *inputFile) {
  printf("We have started Parsing our Json File\n");
  
  // Initialized to -1 because no objects in array
  int counter = -1;
  
  // string to store desired output
  char string[200];

  // Initializes object t no type first
  objects[counter].objType = NO_TYPE;
  
  // Endless While loop
  while (1){
    // Gets next charachter in file
    char c = fgetc(inputFile);

    if( c == EOF ) {
      printf("\nReached end of file \ncongratulations we have succesfully parsed \nthis much from the file compare it with json\n");
      max_counter = counter;
      return;
    }

    if( c != '\n' ){
      ungetc(c, inputFile);
    }

    // scanf
    fscanf(inputFile, "%s", string);

    if(strcmp(string, "camera,") == 0){
      counter++;
      objects[counter].objType = CAMERA;
      if (objects[counter].objType==CAMERA){
        printf("\n%s\n", string);
      }
      
    }

    if (strcmp(string, "width:") == 0){
      float cameraWidth;
      printf("%s: ", string);
      fscanf(inputFile, "%f", &cameraWidth);
      float tempVal = cameraWidth;
      if (tempVal <=0 ){
        fail("camera width must be positive");
        exit(1);
      }
      objects[counter].camData.cam_width = tempVal;
      printf("%f\n", objects[counter].camData.cam_width);
    }

    if (strcmp(string, "height:") == 0){
      float cameraHeight;
      printf("%s: ", string);
      fscanf(inputFile, "%f", &cameraHeight);
      float tempVal = cameraHeight;
      if (tempVal <=0 ){
        fail("camera height must be positive\n");
        exit(1);
      }
      objects[counter].camData.cam_height = tempVal;
      printf("%f\n", objects[counter].camData.cam_height);
    }

    // if sphere => type = 0
    if(strcmp(string, "sphere,") == 0){
      counter++;
      objects[counter].objType = SPHERE;
      if (objects[counter].objType == SPHERE){
        printf("\n%s\n", string);
      }
    }

    // if plane => type = 1
    if (strcmp(string, "plane,") == 0){
      counter++;
      objects[counter].objType = PLANE;
      if (objects[counter].objType == PLANE){
        printf("\n%s\n", string);
      }
    }
	  
    // if color: => save in []
    if (strcmp(string, "color:") == 0){
      // scan whole array into color array
      float * colVector = malloc(sizeof(float)*3);

      printf("%s: ", string);
      fscanf(inputFile, " [%f, %f, %f],", colVector, (colVector+1), (colVector+2));
      printf("colVector[0]:%f, colVector[1]:%f, colVector[2]:%f", *colVector, *(colVector+1), *(colVector+2));

      *colVector = MAX_COLOR_VAL * *colVector;
      *(colVector+1) = MAX_COLOR_VAL * *(colVector+1);
      *(colVector+2) = MAX_COLOR_VAL * *(colVector+2);

      if(objects[counter].objType == SPHERE){
        objects[counter].sphrData.color = colVector;
        printf("stored sphere color as ...");
      }

      else if (objects[counter].objType == PLANE){
        objects[counter].planeData.color = colVector;
        printf("stored plane color as ...");
      }
      printf("[%f, %f, %f]\n", colVector[0], colVector[1], colVector[2]);
    }

    // if position: => save in []
    if (strcmp(string, "position:") == 0){
      // scan whole array into color array
      float* posVector = malloc(sizeof(float)*3);
      printf("%s: ", string);
      fscanf(inputFile, " [%f, %f, %f],", posVector, posVector+1, posVector+2);
      if(objects[counter].objType == SPHERE){
        objects[counter].sphrData.position = posVector;
        printf("stored sphere color as ...");
      }
      else if (objects[counter].objType == PLANE){
        objects[counter].planeData.position = posVector;
        printf("stored plane color as ...");
      }
      printf("[%f, %f, %f]\n", *(posVector), *(posVector+1), *(posVector+2));
    }

    // if radius: => scan next
    if (strcmp(string, "radius:") == 0){
      // save float into radius
      float sphrRadius;
      printf("%s: ", string);
      fscanf(inputFile, "%f", &sphrRadius);
      float tempVal = sphrRadius;
      if (tempVal <=0 ){
        fail("radius must be positive");
        exit(1);
      }
      objects[counter].sphrData.radius = tempVal;
      printf("%f\n", objects[counter].sphrData.radius);
    }

    // if normal: => save in []
    if (strcmp(string, "normal:") == 0){
      float* normVector = malloc(sizeof(float)*3);
      printf("%s: ", string);
      fscanf(inputFile, " [%f, %f, %f]", normVector, normVector+1, normVector+2);
      if(objects[counter].objType == PLANE){
        objects[counter].planeData.normal = normVector;
        printf("stored planes normal vector as ...");
      }
      printf("normVector:[%f, %f, %f]\n", *normVector, *(normVector+1), *(normVector+2));
    }

  }
  
}

/* Function Name: ppm_write3
 * Algorithm: Takes in file pointer, pixmap size, pixmap metadata
 *            and then writes data to an image.
 */
void ppm_write3(FILE *fp, int size, PPMMetaData *md)
{
	char buffer[70];
	sprintf(buffer, "P3\n");
	fputs(buffer, fp);
	sprintf(buffer, "%d %d\n", md->width, md->height );
	fputs(buffer, fp);
	sprintf(buffer, "%d\n", md->maxVal );
	fputs(buffer, fp);

	int i_index,j_index;
	for (i_index=0; i_index<(md->height); i_index++) {
        	for (j_index=0; j_index<(md->width); j_index++) {
            		fprintf(fp, "%d ", md->pixmap[i_index * md->width + j_index].r);
            		fprintf(fp, "%d ", md->pixmap[i_index * md->width + j_index].g);
            		fprintf(fp, "%d\n", md->pixmap[i_index * md->width + j_index].b);
        	}
    	}

	printf("Finished writing the JSON file data to a output.ppm file\n");
}

/*
* Function Name: fail
* Algorithm: Takes in a string that describes the relevant error
*	     then prints the error, along with exiting the program.
*/
void fail(char *str) {
	fprintf(stderr, "Error: %s\n\n", str);
	exit(1);
}

/* Function Name: getCameras
 * Algorithm: Parses through the objects struct to return 
 * 	      the location of the camera objects
 */
int getCamerasFromJson( object *objects ){
	int index = 0;
	while( index < MAX_OBJECTS && objects[index].objType != NO_TYPE )
	{
		if ( objects[index].objType == CAMERA ){
			return index;
		}
		index++;
	}
	return -1;
}

/* Function Name: shade_pixel
 * Algorithm: Takes in the color for a given pixel and then
 *	      reads it to the ppm meta data, to fill in the 
 *	      color of the scene
 */
void shadePixamapPixel(float *color, int row, int col, PPMMetaData *img) {
    // the color vals are stored as values between 0 and 1, so we need to adjust
    img->pixmap[row * img->width + col].r = (int)color[0];
    img->pixmap[row * img->width + col].g = (int)color[1];
    img->pixmap[row * img->width + col].b = (int)color[2];
}

/* Function Name: planeIntersect
 * Algorithm: Tests for an intersection between a ray and a plane
 *
 * @param Ro - 3d vector of ray origin
 * @param Rd - 3d vector of ray direction
 * @param Pos - 3d vector of the plane's position
 * @param Norm - 3d vector of the normal to the plane
 * @return - distance to the object if intersects, otherwise, -1
 */
float planeIntersect(float *Ro, float *Rd, float *Pos, float *Norm) {
    float vd = -(v3_dot_product(Norm, Pos));
    float denom = v3_dot_product(Norm, Rd);

    if( denom == 0 )
    {
      return INFINITY;
    }

    return -(v3_dot_product(Norm, Ro)+ vd)/ denom;
}

/* Function Name: sphere_intersect
 * Algorithm: Tests for an intersection between a ray and a sphere
 *
 * @param Ro - 3d vector of ray origin
 * @param Rd - 3d vector of ray direction
 * @param center - 3d vector of center of sphere
 * @param Norm - 3d vector of the radius of the sphere
 * @return - distance to the object if intersects, otherwise, -1
 */
float sphereIntersect(float *Ro, float *Rd, float *center, float radius){
  float a, b, c;
  float vector_diff[3];
  v3_subtract( vector_diff, Ro, center);
  a = (float)(sqr(Rd[0]) + sqr(Rd[1]) + sqr(Rd[2]));
  b = (float)(2 * (Rd[0]*vector_diff[0] + Rd[1]*vector_diff[1] + Rd[2]*vector_diff[2]));
  c = (float)(sqr(vector_diff[0]) + sqr(vector_diff[1]) + sqr(vector_diff[2]) - sqr(radius));

  float disc = sqr(b) - 4 * a * c;
  if(disc < 0){
    return INFINITY;
  }

  float t0 = (-b - sqrt(disc)) / 2 * a;
  if (t0 > 0){
    return t0;
  }

  float t1 = (-b + sqrt(disc)) / 2 * a;
  if (t1 > 0){
    return t1;
  }

  return INFINITY;

}

/* Function Name: raycast_scene
 * Algorithm: Loops over all the tracked pixels and tests
 	      each pixel for intersection with tracked objects
	      and stores the results of each test in a pixmap
 */
void raycastScene( PPMMetaData *img, float camWidth, float camHeight, object *objects) {
    int x_coord;
    int y_coord;
    int objectIndex;
    float viewPlnPos[3] = {0, 0, 1};
    float Ro[3] = {0, 0, 0};
    float pointVpIntersection[3] = {0, 0, 0};
    float pixHeight = (float)camHeight / (float)img->height;
    float pixWidth = (float)camWidth / (float)img->width;
    float Rd[3] = {0, 0, 0};

    for ( x_coord = 0; x_coord < img->height; x_coord++) {
        for (y_coord = 0; y_coord < img->width; y_coord++) {
            pointVpIntersection[0] = viewPlnPos[0] - camWidth/2.0 + pixWidth*(y_coord + 0.5);
            pointVpIntersection[1] = -(viewPlnPos[1] - camHeight/2.0 + pixHeight*(x_coord + 0.5));
            pointVpIntersection[2] = viewPlnPos[2];

            v3_normalize(pointVpIntersection,pointVpIntersection);

            // store normalized point as our ray direction
            Rd[0] = pointVpIntersection[0];
            Rd[1] = pointVpIntersection[1];
            Rd[2] = pointVpIntersection[2];

            int best_o = 0;
            float best_t = INFINITY;
            for (objectIndex=0; objects[objectIndex].objType != NO_TYPE; objectIndex++) {
                // we need to run intersection test on each object
                float t = 0;
                switch(objects[objectIndex].objType) {
                    case NO_TYPE:
                        printf("no object found\n");
                        break;
                    case CAMERA:
                        break;
                    case SPHERE:
                        t = sphereIntersect(Ro, Rd, objects[objectIndex].sphrData.position,
                                                        objects[objectIndex].sphrData.radius);
                        break;
                    case PLANE:
                        t = planeIntersect(Ro, Rd, objects[objectIndex].planeData.position,
                                                    objects[objectIndex].planeData.normal);
                        break;
                    default:
                        // Error
                        exit(1);
                }
                if (t > 0 && t < best_t) {
                    best_t = t;
                    best_o = objectIndex;
                }
            }

            if (best_t > 0 && best_t != INFINITY) {
                if (objects[best_o].objType == PLANE) {
                  shadePixamapPixel(objects[best_o].planeData.color, x_coord, y_coord, img);
                }

                else if (objects[best_o].objType == SPHERE) {
                  shadePixamapPixel(objects[best_o].sphrData.color, x_coord, y_coord, img);
                }

            }
            
        }

    }

}