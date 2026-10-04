#ifndef DECODE_H
#define DECODE_H
#include <stdio.h>
#include "common.h"
#include "types.h" // Contains user defined types

/*
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

typedef struct _DecodeInfo
{
   
    /* Secret File Info */
    char extn_secret_file[5];       //name of file extension (.txt)
    long extn_size;
    long size_secret_file;          //size of secret file

    /* Stego Image Info */
    char *stego_image_fname;         //encoded file name
    FILE *fptr_stego_image;          //adress of encoded file

    /*output file info */
    char output_fname[100];          //output file name
    FILE *fptr_output;                //address of output file

} DecodeInfo;
/* Read and validate decode args from argv*/
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform the encoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_decode_files(DecodeInfo *decInfo);

/* Store Magic String */
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo);

/*decode extension size*/
Status decode_secret_file_extn_size(long *size, DecodeInfo *decInfo);

/* decode secret file extenstion */
Status decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo);

/* decode secret file size */
Status decode_secret_file_size(long *file_size, DecodeInfo *decInfo);

/* decode secret file data*/
Status decode_secret_file_data(DecodeInfo *decInfo);

/* decode a byte into LSB of image data array */
Status decode_byte_to_lsb(char *data, char *image_buffer);

/*  decode a size to lsb */
Status decode_size_to_lsb(long *size, char *imageBuffer);
  
/* concatinate the output file and extension */
Status concatanate_file_extension(char *filename, char *extension);


/* open output file */
Status open_output_files(DecodeInfo *decInfo);

#endif
