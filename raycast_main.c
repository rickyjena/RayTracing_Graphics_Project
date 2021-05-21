#include <stdio.h>
#include "raycast.c"

int main(int argc, char **argv)
{
  FILE *inputFilePtr;
  FILE *outputFilePtr;
  //char str[10];
  
  // ensure correct number of arguments
  if ( argc != 5) {
     fail("incorrect number of arguments.");
  }
  
  // fetch and store arguments from argv
  int imgWidth = atoi(argv[1]);
  int imgHeight = atoi(argv[2]);
  char *inputJsonFileName = argv[3];
  char *outputPPMFileName = argv[4];
  
  // try to open input file for reading
  inputFilePtr = fopen( inputJsonFileName, "r" );
  
  // check for error on file open
  if (inputFilePtr == NULL) {
     fail("input file doesn't exist.");
  }
  
  //reading json file
    // sends info into array of objects
  jsonParsing(inputFilePtr);

  // close input file
  fclose(inputFilePtr);

  PPMMetaData image;
  image.format = 3;
  image.height = imgHeight;
  image.width = imgWidth;
  image.maxVal = 255;
  image.pixmap = (RGBPixel*) malloc(sizeof(RGBPixel)*image.width*image.height);

  printf("\n");
  
  int posOfCam = getCamerasFromJson( objects );
  if (posOfCam == -1) {
        fail("No camera object found in data" );
  }
  
  // call raycast image to  raycast to the image
  raycastScene(&image, objects[posOfCam].camData.cam_width, objects[posOfCam].camData.cam_height, objects);

  // get output file ready to be written into
  int pixmapSize = 3 * image.width * image.height;
  outputFilePtr = fopen( outputPPMFileName, "w" );
  if (outputFilePtr == NULL) {
     fail("Output file doesn't have anything" );
  }

  // create the ppm
  ppm_write3(outputFilePtr, pixmapSize, &image);

  // clean allocated memory
  fclose(outputFilePtr);

  return 0;
}
