/*
Author: Tahmina Akther Munni
Course: CSCI-135
Instructors: Tong yi, 
Assignment: Lab_8 G
Description:
    The program reads a PGM image from the file "inImage.pgm",
    and outputs a modified image to "outImage.pgm"
*/


#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;

// Reads a PGM file.
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
char c;
int x;
ifstream instr;
instr.open("inImage.pgm");

// read the header P2
instr >> c;
assert(c == 'P');
instr >> c;
assert(c == '2');

while ((instr>>ws).peek() == '#') {
instr.ignore(4096, '\n');
}

instr >> width;
instr >> height;

assert(width <= MAX_W);
assert(height <= MAX_H);
int max;
instr >> max;
assert(max == 255);

for (int row = 0; row < height; row++)
for (int col = 0; col < width; col++)
instr >> image[row][col];
instr.close();
return;
}


// Writes a PGM file
// Need to provide the array data and the image dimensions
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
ofstream ostr;
ostr.open("outImage.pgm");
if (ostr.fail()) {
cout << "Unable to write file\n";
exit(1);
};

// print the header
ostr << "P2" << endl;
// width, height
ostr << width << ' ';
ostr << height << endl;
ostr << 255 << endl;

for (int row = 0; row < height; row++) {
for (int col = 0; col < width; col++) {
assert(image[row][col] < 256);
assert(image[row][col] >= 0);
ostr << image[row][col] << ' ';
ostr << endl;
}
}
ostr.close();
return;
}

int main() {

int img[MAX_H][MAX_W];
int H, W;

readImage(img, H, W); // read it from the file "inImage.pgm"
// h and w were passed by reference and
// now contain the dimensions of the picture
// and the 2-dimesional array img contains the image data

// Now we can manipulate the image the way we like
// for example we copy its contents into a new array
int out[MAX_H][MAX_W];

//create a temp matrix initialised as black(0) with size 1 more on each edges
int temp[MAX_H+2][MAX_W+2];
memset(temp,0,sizeof(temp)); //initialise with 0

//copy original image into temp image
for(int row = 0; row < H; row++) {
for(int col = 0; col < W; col++) {
temp[row+1][col+1] = img[row][col]; //skipping first row and first column of temp image
}
}

int a,b,c,d,e,f,g,h,i;
int func;
for(int row =1; row<H+1; row++ ){
for(int col=1; col<W+1; col++){
a= temp[row-1][col-1];
b=temp[row-1][col];
c=temp[row-1][col+1];
//no use of d,e,f
g=temp[row+1][col-1];
h=temp[row+1][col];
i=temp[row+1][col+1];

func= (g+2*h+i)-(a+2*b+c);
if(func<0) func=0;
if(func>255) func=255;

//put it in output image at its correct position

out[row-1][col-1] = func;
}
}

// and save this new image to file "outImage.pgm"
writeImage(out, H, W);

}
