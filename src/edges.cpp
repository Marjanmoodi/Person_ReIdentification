///*
//   this file tests all the edge detection algorithms implemented in
//   edge_detectors.c. it also leads with input/output and with the
//   parameters handling.
//
//   copyright (c) 2011-2013, haldo sponton <haldos@fing.edu.uy>
//   copyright (c) 2011-2013, juan cardelino <juanc@fing.edu.uy>
//
//   this program is free software: you can redistribute it and/or
//   modify it under the terms of the gnu general public license as
//   published by the free software foundation, either version 3 of
//   the license, or (at your option) any later version.
//
//   this program is distributed in the hope that it will be useful,
//   but without any warranty; without even the implied warranty of
//   merchantability or fitness for a particular purpose. see the
//   gnu general public license for more details.
//
//   you should have received a copy of the gnu general public license
//   along with this program. if not, see <http://www.gnu.org/licenses/>.
//*/
//
//#include <stdio.h>
//#include <stdlib.h>
//#include "classic_edge_detectors.h"   // edge detection algorithms
//#include "io_png.h"                   // image input/output
//
///*display help function */
//void displayhelp(void) {
//    printf("usage: edges [options] input.png\n"
//           "  -r <th>                roberts' algorithm\n"
//           "                            th      threshold (float in [0,1])\n"
//           "  -p <th>                prewitt's algorithm\n"
//           "                            th      threshold (float in [0,1])\n"
//           "  -s <th>                sobel's algorithm\n"
//           "                            th      threshold (float in [0,1])\n"
//           "  -m <sigma> <n> <th>    marr-hildreth algorithm (gaussian)\n"
//           "                            sigma   std dev of gaussian kernel\n"
//           "                            n       size of gaussian kernel (int)\n"
//           "                            th      threshold (float in [0,1])\n"
//           "  -l <sigma> <n> <th>    marr-hildreth algorithm (log)\n"
//           "                            sigma   std dev of log kernel\n"
//           "                            n       size of log kernel (int)\n"
//           "                            th      threshold (float in [0,1])\n"
//           "  -h <th>                haralick's algorithm\n"
//           "                            th      threshold (float in [0,1])\n"
//           "  -h                     display this help\n"
//           "\nmore than one option can be used together. "
//           "output is written to image files.\n");
//}
//
///* main function */
//int main(int argc, char *argv[]) {
//
//    /* start */
//    printf("a review of classic edge detection algorithms\n");
//    printf("haldo sponton & juan cardelino, ipol 2013\n\n");
//
//    /* options and parameters handling */
//    int argc_sobel = 0;         //
//    int argc_prewitt = 0;       //
//    int argc_roberts = 0;       // indexes in argv[]
//    int argc_mh = 0;            //
//    int argc_mhl = 0;           //
//    int argc_haralick = 0;      //
//    int padding_method = 1;     // reflection of image boundary. hard-coded.
//                                // can be changed to 0 (zero-padding)
//
//    for(int n = 1; n<argc; n++ ) {           // scan through args
//        switch( (int)argv[n][0] ) {          // check for option character
//            case '-':
//                switch( (int)argv[n][1] ) {
//                    case 'r':  argc_roberts = n;
//                               break;
//                    case 'p':  argc_prewitt = n;
//                               break;
//                    case 's':  argc_sobel = n;
//                               break;
//                    case 'm':  argc_mh = n;
//                               break;
//                    case 'l':  argc_mhl = n;
//                               break;
//                    case 'h':  argc_haralick = n;
//                               break;
//                  //  case 'h':  /* display help! */
//                               displayhelp();
//                               exit(1);
//                               break;
//                    default:   printf("error: invalid option -> %s. valid"
//                                      " options are -r, -p, -s, -h, -m and -l"
//                                      " (-h for help).\n", argv[n]);
//                               exit(1);
//                               break;
//                }
//
//                /* error message if an option is the last input parameter
//                   or if the next parameter after an option is another option */
//                if( n==argc-1 ) {
//                    printf("error: missing parameter(s) for %s option.\n",
//                           argv[n]);
//                    exit(1);
//                    break;
//                } else if( argv[n+1][0]=='-' ) {
//                    printf("error: missing parameter(s) for %s option.\n",
//                            argv[n]);
//                    exit(1);
//                    break;
//                }
//                /* in the case of -m and -l, three parameters are needed */
//                if( (argv[n][1]=='m') || (argv[n][1]=='l') ) {
//                    if( n+3>argc-1 ) {
//                        printf("error: missing parameter(s) for %s option.\n",
//                               argv[n]);
//                        exit(1);
//                        break;
//                    } else if( (argv[n+2][0]=='-') || (argv[n+3][0]=='-') ) {
//                        printf("error: missing parameter(s) for %s option.\n",
//                               argv[n]);
//                        exit(1);
//                        break;
//                    }
//                }
//            default:
//                break;
//        }
//    }
//
//    /* check for total number of parameters */
//    int nparam = 2;
//    if(argc_roberts!=0)  nparam+=2;
//    if(argc_prewitt!=0)  nparam+=2;
//    if(argc_sobel!=0)    nparam+=2;
//    if(argc_mh!=0)       nparam+=4;
//    if(argc_mhl!=0)      nparam+=4;
//    if(argc_haralick!=0) nparam+=2;
//    if(nparam!=argc) {
//        printf("error: wrong number of arguments (%d instead of %d)\n"
//               "usage: %s [options] input.png\n"
//               "for help type %s -h.\n",argc-1,nparam-1,argv[0],argv[0]);
//        exit(1);
//    }
//
//    /* load input image */
//    size_t w, h;
//    float *im = io_png_read_f32_gray(argv[argc-1], &w, &h);
//    printf("input image: %s\n",argv[argc-1]);
//    printf("size: %zd x %zd\n\n",w,h);
//
//    /* roberts edge detection algorithm */
//    if(argc_roberts!=0) {
//        float th_roberts = atof(argv[argc_roberts+1]); // threshold
//        printf("running roberts, threshold=%.2f",th_roberts);
//        float *im_roberts = edges_roberts(im, w, h, th_roberts, padding_method);
//        io_png_write_f32("out_roberts.png", im_roberts, w, h, 1);
//        printf(" output: out_roberts.png\n");
//        free(im_roberts);
//    }
//
//    /* prewitt edge detection algorithm */
//    if(argc_prewitt!=0) {
//        float th_prewitt = atof(argv[argc_prewitt+1]); // threshold
//        printf("running prewitt, threshold=%.2f",th_prewitt);
//        float *im_prewitt = edges_prewitt(im, w, h, th_prewitt, padding_method);
//        io_png_write_f32("out_prewitt.png", im_prewitt, w, h, 1);
//        printf(" output: out_prewitt.png\n");
//        free(im_prewitt);
//    }
//
//    /* sobel edge detection algorithm */
//    if(argc_sobel!=0) {
//        float th_sobel = atof(argv[argc_sobel+1]); // threshold
//        printf("running sobel, threshold=%.2f",th_sobel);
//        float *im_sobel = edges_sobel(im, w, h, th_sobel, padding_method);
//        io_png_write_f32("out_sobel.png", im_sobel, w, h, 1);
//        printf(" output: out_sobel.png\n");
//        free(im_sobel);
//    }
//
//    /* marr-hildreth (gaussian) edge detection algorithm */
//    if(argc_mh!=0) {
//        float sigma_m = atof(argv[argc_mh+1]); // gaussian kernel's std dev.
//        int   n_m     = atoi(argv[argc_mh+2]); // kernel size
//        float tzc_m   = atof(argv[argc_mh+3]); // threshold for zero-crossing
//        printf("running marr-hildreth (gaussian), sigma=%.2f, n=%d, tzc=%.2f",
//               sigma_m, n_m, tzc_m);
//        float *im_mh = edges_mh(im, w, h, sigma_m, n_m, tzc_m, padding_method);
//        io_png_write_f32("out_mh.png", im_mh, w, h, 1);
//        printf(" output: out_mh.png\n");
//        free(im_mh);
//    }
//
//    /* marr-hildreth (log) edge detection algorithm */
//    if(argc_mhl!=0) {
//        float sigma_l = atof(argv[argc_mhl+1]); // gaussian kernel's std dev.
//        int   n_l     = atoi(argv[argc_mhl+2]); // kernel size
//        float tzc_l   = atof(argv[argc_mhl+3]); // threshold for zero-crossing
//        printf("running marr-hildreth (log), sigma=%.2f, n=%d, tzc=%.2f",
//               sigma_l, n_l, tzc_l);
//        float *im_mhl = edges_mh_log(im, w, h,
//                                     sigma_l, n_l, tzc_l, padding_method);
//        io_png_write_f32("out_mhl.png", im_mhl, w, h, 1);
//        printf(" output: out_mhl.png\n");
//        free(im_mhl);
//    }
//
//    /* haralick edge detection algorithm */
//    if(argc_haralick!=0) {
//        float rhozero = atof(argv[argc_haralick+1]); // threshold
//        printf("running haralick, rhozero=%.2f",rhozero);
//        float *im_haralick = edges_haralick(im, w, h, rhozero, padding_method);
//        io_png_write_f32("out_haralick.png", im_haralick, w, h, 1);
//        printf(" output: out_haralick.png\n");
//        free(im_haralick);
//    }
//
//    /* memory free */
//    free(im);
//
//    exit(exit_success);
//}
