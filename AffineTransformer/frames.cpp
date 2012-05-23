#include <Matrix/matrix.h>
#include <bmpAccess/bmpEngine.h>
#include <AffineTransformer/frames.h>

#include <stdio.h>
#include <math.h>

#define OUT_WIDTH 512
#define OUT_HEIGHT 512

void createFrames (char *fileName, char *FramesFolder, int *translation, int numFrames) {

	GIMAGE* input = Gtype(readGrey(fileName));
	GIMAGE* output = createImage(OUT_WIDTH, OUT_HEIGHT, input->numColors);

	double theta,sintheta,costheta;
	double rowcol[2];
	double rowcolOut[2];
	char filename[100];
	for (int iter = 0; iter < numFrames; iter++) {
		
		for (rowcol[0] = 0; rowcol[0] < OUT_HEIGHT; rowcol[0]++)
			for (rowcol[1] = 0; rowcol[1] < OUT_WIDTH; rowcol[1]++)
				output->imageData[((int)rowcol[0])*OUT_WIDTH+(int)rowcol[1]] = 0.5;


		theta = 2*3.14*(double)iter/(double)numFrames;
		
		sintheta = sin(theta);
		costheta = cos(theta);

		for (rowcol[0] = -input->height/2; rowcol[0] < input->height/2; rowcol[0]++)
			for (rowcol[1] = -input->width/2; rowcol[1] < input->width/2; rowcol[1]++) {
				rowcolOut[0] = rowcol[0]*costheta + rowcol[1]*sintheta;
				rowcolOut[1] = -rowcol[0]*sintheta + rowcol[1]*costheta;

				if (rowcolOut[0]+translation[1] < OUT_HEIGHT/2 && rowcolOut[0]+translation[1] >= -OUT_HEIGHT/2)
					if (rowcolOut[1]+translation[0] < OUT_WIDTH/2 && rowcolOut[1]+translation[0] >= -OUT_WIDTH/2)
						output->imageData[((int)rowcolOut[0]+translation[1]+OUT_HEIGHT/2)*OUT_WIDTH+(int)rowcolOut[1]+translation[0]+OUT_WIDTH/2] 
														= input->imageData[((int)rowcol[0]+input->height/2)*input->width+((int)rowcol[1]+input->width/2)];					
			}

		sprintf (filename,"%s\\%d.bmp",FramesFolder,iter);
		cout << filename << endl;
		writeImage (filename, output);
	}

	releaseImage (input);
	releaseImage (output);
}