# CS450-Computer-Graphics Project-3

# Authors
Matthew Rittenback (mrr342@nau.edu) 
Saurabh Jena (skj64@nau.edu)

# Usage
This program implements a basic raycaster that can raycast mathematical
primitives into a scene based on a JSON input file. The program parses the
modified JSON format input file and builds a pixel buffer based on the data 
of the raycaster and then writes the pixel buffer to a PPM formatted file image.
The JSON file used for this program is a modified JSON file that is derived 
from a CSV format. In the input file, there is only one object per line, 
with the first element declaring the object, and then the following elements 
are defining properties of each object. Each of the descriptive properties
following the object type, has a property name with a value, seperated by a
colon.
To call the program, use the following calling structure "raycast width height
input.json output.ppm". The width and height in the command call are what 
define the size of the final image. Following the width and height, is the 
input file (modified CSV JSON) that you wish the program to render and raycast.
Then the final parameter is the output file name you want the program to render
the image to.

# Known Issues
All functions in the raycaster are working as intended based on our observations
looking at various test input files, and we have not identified any errors
inside the program.
