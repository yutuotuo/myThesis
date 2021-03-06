#ifndef PYRAMIDS_H
#define PYRAMIDS_H

#include <bmpAccess/bmpStructs.h>

#define NULL 0

GIMAGE** GaussianPyramid(GIMAGE *inImage, GTYPE stepSize, int numLayers, FILE *logFile = stdout, char *PROJECT_FOLDER = NULL);
GIMAGE**** LaplacianPyramid(GIMAGE *inImage, GTYPE sigma, int octaves, int numBlurs, FILE *logFile = stdout, char *PROJECT_FOLDER = NULL);
void releaseLaplacianPyramid (GIMAGE**** Pyramid, int numOctaves, int numBlurs);
#endif