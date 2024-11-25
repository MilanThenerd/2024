#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>
#include <linux/limits.h>

#define MAX_HEADER_SIZE 512

typedef struct PixelNode {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
    unsigned char CdfValue;
    struct PixelNode* up;
    struct PixelNode* down;
    struct PixelNode* left;
    struct PixelNode* right;
} PixelNode;

extern PixelNode* readPPM(const char* filename); 
extern void computeCDFValues(PixelNode* head);
extern void applyHistogramEqualisation(PixelNode* head);
extern void writePPM(const char* filename, const PixelNode* head);

int main() {
    const char* inputFilename = "input.ppm";
    const char* outputFilename = "output.ppm";

    PixelNode* imageHead = readPPM(inputFilename);
    if(imageHead == NULL)
    {
      return 1;
    }

    computeCDFValues(imageHead);
    applyHistogramEqualisation(imageHead);

    PixelNode* current = imageHead;
    while(current != NULL)
    {
      PixelNode* row = current;
      while(row != NULL)
      {
        printf("R: %d, G: %d, B: %d, CDF: %d\n", row->Red , row->Green , row->Blue , row->CdfValue);
        row = row->right;
      }
      current = current->down;
    }

    writePPM(outputFilename, imageHead);

    return 0;
}
