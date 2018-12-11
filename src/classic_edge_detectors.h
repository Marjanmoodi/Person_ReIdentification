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
//#ifndef CLASSIC_EDGE_DETECTORS_HEADER
//#define CLASSIC_EDGE_DETECTORS_HEADER
//
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
//                     float threshold, int padding_method);
//
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
//                     float threshold, int padding_method);
//
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
//                   float threshold, int padding_method);
//
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
//float *edges_mh(float *im, int w, int h,
//                float sigma, int n, float tzc, int padding_method);
//
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
//                    float sigma, int n, float tzc, int padding_method);
//
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
//                      float rhozero, int padding_method);
//
//
//#endif /* !CLASSIC_EDGE_DETECTORS_HEADER */
