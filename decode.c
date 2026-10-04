#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "types.h"
#include "common.h"



Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
   
    // step 1 -> check argv[2] is having .bmp or not
        //yes -> store the file name into decInfo -> stego_image_fname = argv[2]
        //no - > return e_failure
        char *ptr;
        ptr=strstr(argv[2], ".bmp");
        if(ptr==NULL)
        {
            return e_failure;
        }
        if(strcmp(ptr, ".bmp")!=0)
        {
           return e_failure;
        }
        decInfo->stego_image_fname = argv[2];
    // step 2 -> check argv[3] is NULL or not
        
                //yes -> store the file name into decInfo -> output_fname = argv[3]
                //no - > return e_failure
        
        //no -> store default name the decInfo -> output_fname = "output"
    if(argv[3]==NULL)
    {
        strcpy(decInfo->output_fname , "output");
    } 
    else
    {
        strcpy(decInfo->output_fname , argv[3]);
    }
    return e_success;   
}

/* Perform the encoding */
Status do_decoding(DecodeInfo *decInfo)
{
    // step 1-> check open_files(decInfo) is returning e_success or not
    if(open_decode_files(decInfo)!= e_success)
    {
        //no-> print error return e_failure
        printf("Error : Failed to open files\n");
        return e_failure;
    }
        //yes -> print success and goto next step
    printf("Stego image opened successfully\n");

    //step 2 -> call decode_magic_string(MAGIC_STRING, decInfo)
    if(decode_magic_string(MAGIC_STRING, decInfo)!=e_success)
    {
        //no -> print error return e_failure
        printf("Error : Failed to decode magic string\n");
        return e_failure;
    }
        // yes -> print success and goto next step
    printf("Decoded magic string successfully\n");

    //step 3 -> call decode_secret_file_extn_size(strlen(decInfo -> extn_secret_file), decInfo)
    if((decode_secret_file_extn_size(&decInfo->extn_size, decInfo))!=e_success)
    {
        //no -> print error return e_failure
        printf("Error : Failed to decode secret file extension size\n");
        return e_failure;
    }
        // yes -> print success and goto next step
        printf("Decoded secret file extension size successfully\n");

    if((decode_secret_file_extn(decInfo -> extn_secret_file, decInfo))!=e_success)
    {
        //no -> print error return e_failure
        printf("Error : Failed to decode secret file extension\n");
        return e_failure;
    }
        // yes -> print success and goto next step
        printf("Decoded secret file extension successfully\n");

    if(concatanate_file_extension(decInfo->output_fname,decInfo->extn_secret_file)!=e_success)
        {
            //no -> print error return e_failure
           printf("Error : Failed to concatinate theoutput file and extension\n");
            return e_failure; 
        }
        // yes -> print success and goto next step
        printf("Concatinated successfully\n");

    

    if(open_output_files( decInfo)!=e_success)
    {
        //no -> print error return e_failure
        printf("Error : Failed to open  output file\n");
        return e_failure;
    }
        // yes -> print success and goto next step
        printf("Output file opened successfully\n");

    if((decode_secret_file_size(&decInfo ->  size_secret_file, decInfo))!=e_success)
    {
        //no -> print error return e_failure
        printf("Error : Failed to decode secret file size\n");
        return e_failure;
    }
        // yes -> print success and goto next step
        printf("Decoded secret file size successfully\n");
        //printf("Secret file size = %ld\n", decInfo->size_secret_file);

    if((decode_secret_file_data(decInfo))!=e_success)
     {
        //no -> print error return e_failure
        printf("Error : Failed to decode secret file data\n");
        return e_failure;
     }
        // yes -> print success 
        printf("Decoded secret file data successfully\n");

    fclose(decInfo->fptr_stego_image);
    fclose(decInfo->fptr_output);

    return e_success;    
}

/* Get File pointers for i/p and o/p files */
Status open_decode_files(DecodeInfo *decInfo)
{
    // Stego Image file
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "rb");

    // Do Error handling
    if(decInfo->fptr_stego_image==NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: unable to open file %s\n", decInfo->stego_image_fname );
        return e_failure;
    }
    
    // No failure return e_success
    return e_success;
}


/*to open output file */
Status open_output_files(DecodeInfo *decInfo)
{
    // output file
    decInfo->fptr_output = fopen(decInfo->output_fname, "wb");

    // Do Error handling
    if(decInfo->fptr_output == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: unable to open file %s\n", decInfo->output_fname );
        return e_failure;
    } 
    
    // No failure return e_success
    return e_success;
}

/* Store Magic String */
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo)
{
    //skip header file
    fseek(decInfo->fptr_stego_image, 54, SEEK_SET);

    //read 8 bytes from stego file
    char buffer[8];
    char decoded_magic_string[20];
    char decoded_char;
    for(int i=0;i<strlen(magic_string);i++)
    {
        fread(buffer, 1, 8, decInfo->fptr_stego_image);

        //  call decode_byte_to_lsb(&decoded_char, buffer)
        decode_byte_to_lsb(&decoded_char, buffer);
        decoded_magic_string[i]=decoded_char;
    }
    decoded_magic_string[strlen(magic_string)]='\0';

    //check decoded_magic_string, magic_string are matching or not
    if(strcmp(decoded_magic_string, magic_string)!=0)
    {
    return e_failure;
    }
    return e_success;
}

/*Encode extension size*/
Status decode_secret_file_extn_size(long *size, DecodeInfo *decInfo)
{
    char buffer[32];

    // step-1 read 32 bytes from stego file
    fread(buffer, 1, 32, decInfo->fptr_stego_image);

    //step 2 -> call decode_size_to_lsb(size, buffer)
    decode_size_to_lsb(size, buffer);

    return e_success;
}

/* Encode secret file extenstion */
Status decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo)
{
    char buffer[8];
    char data;

    //check extension had size 4 or not
    if(decInfo->extn_size > 4)
    {
        printf("Invalid extension size = %ld\n", decInfo->extn_size);
        return e_failure;
    }

    for(int i=0;i<decInfo->extn_size ;i++)
    {
     
    //step 1 -> read 8 bytes from stego file
     fread(buffer, 1, 8, decInfo-> fptr_stego_image);

     //step 2 -> call decode_byte_to_lsb(&data, buffer)
     decode_byte_to_lsb(&data, buffer);
     file_extn[i]=data;
    }
    file_extn[decInfo->extn_size]='\0';
    return e_success;
}

/* Encode secret file size */
Status decode_secret_file_size(long *file_size, DecodeInfo *decInfo)
{
    char buffer[32];

    //step 1 -> read 32 bytes from stego file
    fread(buffer, 1, 32, decInfo->fptr_stego_image);

    //step 2 -> call decode_size_to_lsb(file_size, buffer)
    decode_size_to_lsb(file_size, buffer);

    return e_success;
}

/* Encode secret file data*/
Status decode_secret_file_data(DecodeInfo *decInfo)
{
    char buffer[8];
    char data;

    //read 8 bytes from stego file
    for(int i=0;i<decInfo->size_secret_file;i++)
    {
    fread(buffer, 1, 8, decInfo->fptr_stego_image );

    //call decode_byte_to_lsb(&data, buffer)
    decode_byte_to_lsb(&data, buffer);

    // write it on output file
    fwrite(&data, 1, 1, decInfo->fptr_output);
    }
    return e_success;
}

/* decode a byte into LSB of image data array */
Status decode_byte_to_lsb(char *data, char *image_buffer)
{

    // write logic to decode the char
    int byte=0;
    for(int i=0;i<8;i++)
    {
        int get=image_buffer[i] & 1;
        byte=(byte << 1) |get;
    }
    *data =byte;

    //return e_success
    return e_success;
}

// decode a size to lsb
Status decode_size_to_lsb(long *size, char *imageBuffer)
{

    // write logic to decode the long
    long decoded_size=0;
    for(int i=0;i<32;i++)
    {
        int get = imageBuffer[i] & 1;
        decoded_size=(decoded_size << 1) |get;
    }
    *size =decoded_size;

    //return e_success
    return e_success;
}
 
/* concatination function*/
Status concatanate_file_extension(char *filename, char *extension)
{
    //concatinate output and extension
    strcat(filename, extension);

    //return e_success
    return e_success;
}
