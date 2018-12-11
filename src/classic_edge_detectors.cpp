///*
//   This file implements the different edge detection algorithms
//   presented in the article "A review of classic edge detectors".
//   All functions implemented here receive only a pointer to the
//   input image (grayscale) and the different parameters of each
//   method. All them also return a pointer to the output image.
//
//   Copyright (c) 2011-2013, Haldo Sponton <haldos@fing.edu.uy>
//   Copyright (c) 2011-2013, Juan Cardelino <juanc@fing.edu.uy>
//
//   This program is free software: you can redistribute it and/or
//   modify it under the terms of the GNU General Public License as
//   published by the Free Software Foundation, either version 3 of
//   the License, or (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, see <http://www.gnu.org/licenses/>.
//*/
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include "classic_edge_detectors.h"
//
//// Useful macros
//#define MAX(x, y) (((x) > (y)) ? (x) : (y))
//#define MIN(x, y) (((x) < (y)) ? (x) : (y))
//#define THRESHOLD(x, th) (((x) > (th)) ? (255) : (0))
//
//// Fatal error, print a message to standard-error output and exit.
//static void error(char * msg) {
//    fprintf(stderr,"Error: %s\n",msg);
//    exit(EXIT_FAILURE);
//}
//
//// Memory allocation, print an error and exit if fail.
//static void * xmalloc(size_t size) {
//    void * p;
//    if( size == 0 ) error("xmalloc: zero size");
//    p = malloc(size);
//    if( p == NULL ) error("xmalloc: out of memory");
//    return p;
//}
//
//// Computes a Gaussian kernel of size n x n and standard deviation sigma.
//static float *gaussian_kernel(int n, float sigma) {
//
//    // Memory allocation for the kernel
//    float *kernel =(float *)xmalloc(n*n*sizeof(float));
//
//    // Gaussian kernel: e^{ -(x^2+y^2) / (2sigma^2) }
//    float sum = 0;
//    for(int i=0; i<n; i++) {
//        for(int j=0; j<n; j++) {
//            int x = i - n/2;
//            int y = j - n/2;
//            kernel[i+j*n] = exp( -(x*x + y*y) / (2.0*sigma*sigma) );
//            sum += kernel[i+j*n];
//        }
//    }
//
//    // Kernel normalization
//    for(int i=0; i<n*n; i++) {
//        kernel[i] = kernel[i] / sum;
//    }
//
//    return kernel;
//}
//
//// Computes a Laplacian of a Gaussian (LoG) kernel
//// of size nxn and standard deviation sigma.
//static float *LoG_kernel(int n, float sigma) {
//
//    // Memory allocation for the kernel
//    float *kernel = (float *)xmalloc(n*n*sizeof(float));
//
//    // Laplacian of a Gaussian kernel:
//    // (x^2 + y^2 - 2sigma^2) / (sigma^4) e^{ -(x^2+y^2) / (2sigma^2) }
//    float sum = 0;
//    for(int i=0; i<n; i++) {
//        for(int j=0; j<n; j++) {
//            int x = i - n/2;
//            int y = j - n/2;
//            kernel[i+j*n] = ( (x*x + y*y - 2.*sigma*sigma)
//                               / (sigma*sigma*sigma*sigma) )
//                            * exp( -(x*x + y*y) / (2.0*sigma*sigma) );
//            sum += kernel[i+j*n];
//        }
//    }
//
//    // Normalization
//    for(int i=0; i<n*n; i++) {
//        kernel[i] /= sum;
//    }
//
//    return kernel;
//}
//
//// 2D convolution of an input image (size w x h) with a square (n x n) kernel.
////
//// Two padding methods are available:
////   zero-padding (padding_method=0)
////   image boundary reflection (padding_method=1)
////
//// returns a pointer to the resulting (w+n-1) x (h+n-1) image.
//static float *conv2d(float *input, int w, int h,
//                     float *kernel, int n, int padding_method) {
//
//    // Boundary handling:
//    // aux: extension of the input image to a larger size,
//    // enough to apply the kernel to each output pixel
//    int wx = w + 2*(n-1);
//    int hx = h + 2*(n-1);
//    float *aux = (float *)xmalloc(wx*hx*sizeof(float));
//    for(int i=0; i<wx; i++) {
//        for(int j=0; j<hx; j++) {
//            if( i >= n-1 && j >= n-1 && i < w+n-1 && j < h+n-1 ) {
//                aux[i+j*wx] = input[ i-n+1 + (j-n+1)*w ];  // image at center
//            } else {
//                if(padding_method == 0) {
//                    aux[i+j*wx] = 0.0;     // zero-padding
//                } else {
//                    // reflection boundary padding
//                    int reflex_x = i<n-1 ? 2*n-3-i : i<w+n-1 ? i : 2*w+2*n-3-i;
//                    int reflex_y = j<n-1 ? 2*n-3-j : j<h+n-1 ? j : 2*h+2*n-3-j;
//                    aux[i+j*wx] = input[ reflex_x-n+1 + (reflex_y-n+1)*w ];
//                }
//            }
//        }
//    }
//
//    // get memory for output
//    int wo = w+n-1;
//    int ho = h+n-1;
//    float *out =(float *) xmalloc(wo*ho*sizeof(float));
//
//    // compute convolution
//    for(int i=0; i<wo; i++) {
//        for(int j=0; j<ho; j++) {
//            float sum = 0.0;
//            for(int k=0; k<n; k++) {
//                for(int l=0; l<n; l++) {
//                    sum += kernel[k+l*n] * aux[i+k + (j+l)*wx];
//                }
//            }
//            out[i+j*wo] = sum;
//        }
//    }
//
//    // free memory
//    free(aux);
//
//    return out;
//}
//
//// Roberts edge detector
//// inputs:
////            float *input           -    pointer to input image
////            int w, int h           -    width and height of input image
////            float threshold        -    threshold of edge detection
////            int padding_method     -    padding method for convolution
//// output:
////            float *                -    pointer to output image
//float *edges_roberts(float *im, int w, int h,
//                     float threshold, int padding_method) {
//
//    // Define operators
//    // 3x3 operators are used  (although it is unnecessary) in order to
//    // simplify the convolution application, and also to unify the three
//    // detectors of the first family.
//    float roberts_1[9] = {-1, 0, 0, 0, 1, 0, 0, 0, 0};        // ROBERTS
//    float roberts_2[9] = { 0,-1, 0, 1, 0, 0, 0, 0, 0};        // OPERATORS
//    for(int z=0; z<9; z++) { // normalization
//        roberts_1[z] /= 2.0;
//        roberts_2[z] /= 2.0;
//    }
//
//    // Convolution with operators
//    float *Gx = conv2d(im, w, h, roberts_1, 3, padding_method);
//    float *Gy = conv2d(im, w, h, roberts_2, 3, padding_method);
//
//    // Allocate memory for output image
//    float *im_roberts = (float *)xmalloc(w*h*sizeof(float));
//
//    // Two images are obtained (one for each operator). Then the gradient
//    // magnitude image is constructed using sqrt(g_x^2+g_y^2). Also
//    // the absolute maximum value of the constructed images is computed
//    float max = 0.0;
//    for(int i=0; i<w; i++) {
//        for(int j=0; j<h; j++) {
//            float gx = Gx[i+1 + (j+1)*(w+2)]; // Gx and Gy are (w+2) x (h+2)
//            float gy = Gy[i+1 + (j+1)*(w+2)]; // there is an (+1,+1) offset
//            im_roberts[i+j*w] = sqrt(gx*gx + gy*gy);
//            max = MAX(max, im_roberts[i+j*w]);
//        }
//    }
//
//    // Threshold
//    for(int i=0; i<w*h; i++) {
//        im_roberts[i] = THRESHOLD(im_roberts[i], threshold*max);
//    }
//
//    // Free memory
//    free(Gx);
//    free(Gy);
//
//    return im_roberts;
//}
//
//// Prewitt edge detector
//// inputs:
////            float *input           -    pointer to input image
////            int w, int h           -    width and height of input image
////            float threshold        -    threshold of edge detection
////            int padding_method     -    padding method for convolution
//// output:
////            float *                -    pointer to output image
//float *edges_prewitt(float *im, int w, int h,
//                     float threshold, int padding_method) {
//
//    // Define operators
//    float prewitt_1[9] = {-1,-1,-1, 0, 0, 0, 1, 1, 1};        // PREWITT
//    float prewitt_2[9] = {-1, 0, 1,-1, 0, 1,-1, 0, 1};        // OPERATORS
//    for(int z=0; z<9; z++) { // normalization
//        prewitt_1[z] /= 6.0;
//        prewitt_2[z] /= 6.0;
//    }
//
//    // Convolution with operators
//    float *Gx = conv2d(im, w, h, prewitt_1, 3, padding_method);
//    float *Gy = conv2d(im, w, h, prewitt_2, 3, padding_method);
//
//    // get memory for output
//    float *im_prewitt =(float *) xmalloc(w*h*sizeof(float));
//
//    // Two images are obtained (one for each operator). Then the gradient
//    // magnitude image is constructed using sqrt(g_x^2+g_y^2). Also
//    // the absolute maximum value of the constructed images is computed
//    float max = 0.0;
//    for(int i=0; i<w; i++) {
//        for(int j=0; j<h; j++) {
//            float gx = Gx[i+1 + (j+1)*(w+2)]; // Gx and Gy are (w+2) x (h+2)
//            float gy = Gy[i+1 + (j+1)*(w+2)]; // there is an (+1,+1) offset
//            im_prewitt[i+j*w] = sqrt(gx*gx + gy*gy);
//            max = MAX(max, im_prewitt[i+j*w]);
//        }
//    }
//
//    // Threshold
//    for(int i=0; i<w*h; i++) {
//        im_prewitt[i] = THRESHOLD(im_prewitt[i], threshold*max);
//    }
//
//    // Free memory
//    free(Gx);
//    free(Gy);
//
//    return im_prewitt;
//}
//
//// Sobel edge detector
//// inputs:
////            float *input           -    pointer to input image
////            int w, int h           -    width and height of input image
////            float threshold        -    threshold of edge detection
////            int padding_method     -    padding method for convolution
//// output:
////            float *                -    pointer to output image
//float *edges_sobel(float *im, int w, int h,
//                   float threshold, int padding_method) {
//
//    // Define operators
//    float sobel_1[9] = {-1,-2,-1, 0, 0, 0, 1, 2, 1};        // SOBEL
//    float sobel_2[9] = {-1, 0, 1,-2, 0, 2,-1, 0, 1};        // OPERATORS
//    for(int z=0; z<9; z++) { // normalization
//        sobel_1[z] /= 8.0;
//        sobel_2[z] /= 8.0;
//    }
//
//    // Convolution with operators
//    float *Gx = conv2d(im, w, h, sobel_1, 3, padding_method);
//    float *Gy = conv2d(im, w, h, sobel_2, 3, padding_method);
//
//    // Allocate memory for output image
//    float *im_sobel =(float *) xmalloc(w*h*sizeof(float));
//
//    // Two images are obtained (one for each operator). Then the gradient
//    // magnitude image is constructed using sqrt(g_x^2+g_y^2). Also
//    // the absolute maximum value of the constructed images is computed
//    float max = 0.0;
//    for(int i=0; i<w; i++) {
//        for(int j=0; j<h; j++) {
//            float gx = Gx[i+1 + (j+1)*(w+2)]; // Gx and Gy are (w+2) x (h+2)
//            float gy = Gy[i+1 + (j+1)*(w+2)]; // there is an (+1,+1) offset
//            im_sobel[i+j*w] = sqrt(gx*gx + gy*gy);
//            max = MAX(max, im_sobel[i+j*w]);
//        }
//    }
//
//    // Threshold
//    for(int i=0; i<w*h; i++) {
//        im_sobel[i] = THRESHOLD(im_sobel[i], threshold*max);
//    }
//
//    // Free memory
//    free(Gx);
//    free(Gy);
//
//    return im_sobel;
//}
//
//// Marr-Hildreth edge detector with Gaussian and Laplacian kernels
//// inputs:
////            float *input           -    pointer to input image
////            int w, int h           -    width and height of input image
////            float sigma            -    gaussian standard deviation
////            int n                  -    kernel size
////            float tzc              -    threshold in zero-crossing
////            int padding_method     -    padding method for convolution
//// output:
////            float *                -    pointer to output image
////float *edges_mh(float *im, int w, int h,
////                float sigma, int n, float tzc, int padding_method) {
////
////    // generate Gaussian kernel
////    float *kernel = gaussian_kernel(n,sigma);
////
////    // smooth input image with the Gaussian kernel
////    float *im_smoothed = conv2d(im, w, h, kernel, n, padding_method);
////
////    // compute Laplacian of the smoothed image using a 3x3 operator
////    float operator [9] = {1, 1, 1, 1, -8, 1, 1, 1, 1};
////    float *laplacian = conv2d(im_smoothed, w+n-1, h+n-1,
////                               operator, 3, padding_method);
////
////    // compute maximum of absolute Laplacian
////    float max = 0.0;
////    for(int i=0; i<w; i++) {
////        for(int j=0; j<h; j++) {
////            // laplacian is (w+n+1)x(h+n+1) with an offset of (n+1)/2 in x and y
////            float v = abs( laplacian[(i+(n+1)/2) + (j+(n+1)/2)*(w+n+1)] );
////            if( v > max ) max = v;
////        }
////    }
////
////    // compute laplacian zero-crossings
////    float *edges = (float *)xmalloc(w*h*sizeof(float));
////    for(int i=0; i<w; i++) {
////        for(int j=0; j<h; j++) {
////            // laplacian is (w+n+1)x(h+n+1) with an offset of (n+1)/2 in x and y
////            float UP_LE = laplacian[ (i-1+(n+1)/2) + (j+1+(n+1)/2)*(w+n+1) ];
////            float UP    = laplacian[ (i  +(n+1)/2) + (j+1+(n+1)/2)*(w+n+1) ];
////            float UP_RI = laplacian[ (i+1+(n+1)/2) + (j+1+(n+1)/2)*(w+n+1) ];
////            float LE    = laplacian[ (i-1+(n+1)/2) + (j  +(n+1)/2)*(w+n+1) ];
////            float RI    = laplacian[ (i+1+(n+1)/2) + (j  +(n+1)/2)*(w+n+1) ];
////            float DO_LE = laplacian[ (i-1+(n+1)/2) + (j-1+(n+1)/2)*(w+n+1) ];
////            float DO    = laplacian[ (i  +(n+1)/2) + (j-1+(n+1)/2)*(w+n+1) ];
////            float DO_RI = laplacian[ (i+1+(n+1)/2) + (j-1+(n+1)/2)*(w+n+1) ];
////            if( (LE*RI       < 0.0 && abs(LE-RI)       > tzc*max) ||
////                (UP_LE*DO_RI < 0.0 && abs(UP_LE-DO_RI) > tzc*max) ||
////                (DO_LE*UP_RI < 0.0 && abs(DO_LE-UP_RI) > tzc*max) ||
////                (UP*DO       < 0.0 && abs(UP-DO)       > tzc*max) ) {
////                edges[i+j*w] = 255.0;
////            } else {
////                edges[i+j*w] = 0.0;
////            }
////        }
////    }
////
////    // free memory
////    free(kernel);
////    free(im_smoothed);
////    free(laplacian);
////
////    return edges;
////}
//
//// Marr-Hildreth edge detector with Laplacian of Gaussian kernel
//// inputs:
////            float *input           -    pointer to input image
////            int w, int h           -    width and height of input image
////            float sigma            -    gaussian standard deviation
////            int n                  -    kernel size
////            float tzc              -    threshold in zero-crossing
////            int padding_method     -    padding method for convolution
//// output:
////            float *                -    pointer to output image
//float *edges_mh_log(float *im, int w, int h,
//                    float sigma, int n, float tzc, int padding_method) {
//
//    // compute Laplacian using a LoG (Laplacian of Gaussian) kernel
//    float *kernel = LoG_kernel(n,sigma);
//    float *laplacian = conv2d(im, w, h, kernel, n, padding_method);
//
//    // compute maximum of absolute Laplacian
//    float max = 0.0;
//    for(int i=0; i<w; i++) {
//        for(int j=0; j<h; j++) {
//            // laplacian is (w+n-1)x(h+n-1) with an offset of (n-1)/2 in x and y
//            float v = abs( laplacian[(i+(n-1)/2) + (j+(n-1)/2)*(w+n-1)] );
//            if( v > max ) max = v;
//        }
//    }
//
//    // compute laplacian zero-crossings
//    float *edges =(float *) xmalloc(w*h*sizeof(float));
//    for(int i=0; i<w; i++) {
//        for(int j=0; j<h; j++) {
//            // laplacian is (w+n-1)x(h+n-1) with an offset of (n-1)/2 in x and y
//            float UP_LE = laplacian[ (i-1+(n-1)/2) + (j+1+(n-1)/2)*(w+n-1) ];
//            float UP    = laplacian[ (i  +(n-1)/2) + (j+1+(n-1)/2)*(w+n-1) ];
//            float UP_RI = laplacian[ (i+1+(n-1)/2) + (j+1+(n-1)/2)*(w+n-1) ];
//            float LE    = laplacian[ (i-1+(n-1)/2) + (j  +(n-1)/2)*(w+n-1) ];
//            float RI    = laplacian[ (i+1+(n-1)/2) + (j  +(n-1)/2)*(w+n-1) ];
//            float DO_LE = laplacian[ (i-1+(n-1)/2) + (j-1+(n-1)/2)*(w+n-1) ];
//            float DO    = laplacian[ (i  +(n-1)/2) + (j-1+(n-1)/2)*(w+n-1) ];
//            float DO_RI = laplacian[ (i+1+(n-1)/2) + (j-1+(n-1)/2)*(w+n-1) ];
//            if( (LE*RI       < 0.0 && abs(LE-RI)       > tzc*max) ||
//                (UP_LE*DO_RI < 0.0 && abs(UP_LE-DO_RI) > tzc*max) ||
//                (DO_LE*UP_RI < 0.0 && abs(DO_LE-UP_RI) > tzc*max) ||
//                (UP*DO       < 0.0 && abs(UP-DO)       > tzc*max) ) {
//                edges[i+j*w] = 255.0;
//            } else {
//                edges[i+j*w] = 0.0;
//            }
//        }
//    }
//
//    // free memory
//    free(kernel);
//    free(laplacian);
//
//    return edges;
//}
//
//// Haralick edge detector
//// inputs:
////            float *input           -    pointer to input image
////            int w, int h           -    width and height of input image
////            float rhozero          -    threshold
////            int padding_method     -    padding method for convolution
//// output:
////            float *                -    pointer to output image
//float *edges_haralick(float *im, int w, int h,
//                      float rhozero, int padding_method) {
//
//    // Haralick's masks for computing k1 to k10
//    // New masks calculated by 2-d fitting using LS, with the function
//    //   f(x,y) = k1 + k2*x + k3*y + k4*x^2 + k5*xy
//    //            + k6*y^2 + k7*x^3 + k8*x^2y + k9*xy^2 + k10*y^3
//    float mask[10][25] = { {       425,   275,  225,  275,  425,
//                                   275,   125,   75,  125,  275,
//                                   225,    75,   25,   75,  225,
//                                   275,   125,   75,  125,  275,
//                                   425,   275,  225,  275,  425},
//                               { -2260,  -620,    0,  620, 2260,
//                                 -1660,  -320,    0,  320, 1660,
//                                 -1460,  -220,    0,  220, 1460,
//                                 -1660,  -320,    0,  320, 1660,
//                                 -2260,  -620,    0,  620, 2260},
//                               {  2260,  1660, 1460, 1660, 2260,
//                                   620,   320,  220,  320,  620,
//                                     0,     0,    0,    0,    0,
//                                  -620,  -320, -220, -320, -620,
//                                 -2260, -1660,-1460,-1660,-2260},
//                               {  1130,   620,  450,  620, 1130,
//                                   830,   320,  150,  320,  830,
//                                   730,   220,   50,  220,  730,
//                                   830,   320,  150,  320,  830,
//                                  1130,   620,  450,  620, 1130},
//                               {  -400,  -200,    0,  200,  400,
//                                  -200,  -100,    0,  100,  200,
//                                     0,     0,    0,    0,    0,
//                                   200,   100,    0, -100, -200,
//                                   400,   200,    0, -200, -400},
//                               {  1130,   830,  730,  830, 1130,
//                                   620,   320,  220,  320,  620,
//                                   450,   150,   50,  150,  450,
//                                   620,   320,  220,  320,  620,
//                                  1130,   830,  730,  830, 1130},
//                               { -8260, -2180,    0, 2180, 8260,
//                                 -6220, -1160,    0, 1160, 6220,
//                                 -5540,  -820,    0,  820, 5540,
//                                 -6220, -1160,    0, 1160, 6220,
//                                 -8260, -2180,    0, 2180, 8260},
//                               {  5640,  3600, 2920, 3600, 5640,
//                                  1800,   780,  440,  780, 1800,
//                                     0,     0,    0,    0,    0,
//                                 -1800,  -780, -440, -780,-1800,
//                                 -5640, -3600,-2920,-3600,-5640},
//                               { -5640, -1800,    0, 1800, 5640,
//                                 -3600,  -780,    0,  780, 3600,
//                                 -2920,  -440,    0,  440, 2920,
//                                 -3600,  -780,    0,  780, 3600,
//                                 -5640, -1800,    0, 1800, 5640},
//                               {  8260,  6220, 5540, 6220, 8260,
//                                  2180,  1160,  820, 1160, 2180,
//                                     0,     0,    0,    0,    0,
//                                 -2180, -1160, -820,-1160,-2180,
//                                 -8260, -6220, 5540,-6220,-8260   } };
//
//    // apply the masks operators, this will lead to coefficients k1 to k10
//    float *aux[10];
//    for(int i=0; i<10; i++) {
//        aux[i] = conv2d(im, w, h, mask[i], 5, padding_method);
//    }
//
//    // compute Haralick edges
//    float *edges = (float *)xmalloc(w*h*sizeof(float)); // get memory for output
//    for(int i=0; i<w; i++) {
//        for(int j=0; j<h; j++) {
//            // aux is (w+4)x(h+4) and there is an offset of (2,2)
//            // k1 is not used
//            float k2  = aux[1][i+2 + (j+2)*(w+4)];
//            float k3  = aux[2][i+2 + (j+2)*(w+4)];
//            float k4  = aux[3][i+2 + (j+2)*(w+4)];
//            float k5  = aux[4][i+2 + (j+2)*(w+4)];
//            float k6  = aux[5][i+2 + (j+2)*(w+4)];
//            float k7  = aux[6][i+2 + (j+2)*(w+4)];
//            float k8  = aux[7][i+2 + (j+2)*(w+4)];
//            float k9  = aux[8][i+2 + (j+2)*(w+4)];
//            float k10 = aux[9][i+2 + (j+2)*(w+4)];
//            float sintheta = - k2 / sqrt(k2*k2 + k3*k3);
//            float costheta = - k3 / sqrt(k2*k2 + k3*k3);
//            float C2 = k4  * sintheta * sintheta
//                     + k5  * sintheta * costheta
//                     + k6  * costheta * costheta;
//            float C3 = k7  * sintheta * sintheta * sintheta
//                     + k8  * sintheta * sintheta * costheta
//                     + k9  * sintheta * costheta * costheta
//                     + k10 * costheta * costheta * costheta;
//            if( fabs( C2 / (3.0 * C3) ) <= rhozero && C3 < 0.0 ) {
//                edges[i+j*w] = 255.0;
//            } else {
//                edges[i+j*w] = 0.0;
//            }
//        }
//    }
//
//    // free memory
//    for(int i=0; i<10; i++) {
//        free(aux[i]);
//    }
//
//    return edges;
//}
