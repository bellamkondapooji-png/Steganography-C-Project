#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "decode.h"
#include "types.h"

OperationType check_operation_type(char *);

int main(int argc, char *argv[]) // .aout -e <source_file> <secret_data_file> <optional>
{
    //step 1 -> check check_operation_type(argv[1]) is returning e_encode or not
    if((check_operation_type(argv[1])) == e_encode)
    
    {
            // yes -> EncodeInfo encInfo;
        EncodeInfo encInfo;
        
            // check read_and_validate_encode_args(argv, &encInfo) is returning e_success or e_failure
            if((read_and_validate_encode_args(argv, &encInfo))!=e_success)
            {
                // failure -> print error msg and stop
                printf("Error : Read and validations for encode failed\n");
                return 1;
            }    
                // success -> print success msg 
                printf("Successfully read and validations for encode\n");

                            // check do_encoding(&encInfo) is returning e_success or e_failure
                            if((do_encoding(&encInfo))!=e_success)
                            {
                                    // failure -> print error msg and stop
                                    printf("Error : Encoding failed\n");
                                    return 1;
                            }        
                                    // success -> print success msg and stop
                            printf("Successfully encoded\n");
        
    }
    else if(check_operation_type(argv[1])==e_decode)
    {
    DecodeInfo decInfo;
        
            // check read_and_validate_decode_args(argv, &decInfo) is returning e_success or e_failure
            if((read_and_validate_decode_args(argv, &decInfo))!=e_success)
            {
                // failure -> print error msg and stop
                printf("Error : Read and validations for decode failed\n");
                return 1;
            }    
                // success -> print success msg 
                printf("Successfully read and validations for decode\n");

                            // check do_encoding(&decInfo) is returning e_success or e_failure
                            if((do_decoding(&decInfo))!=e_success)
                            {
                                    // failure -> print error msg and stop
                                    printf("Error : Decoding failed\n");
                                    return 1;
                            }        
                                    // success -> print success msg and stop
                            printf("Successfully decoded\n");
    }
    else
    {
        printf("Unsupported operation\n");
        return 1;
    }                        
    return 0;                            
}

OperationType check_operation_type(char *symbol)
{
    //step 1 -> check symbol is -e or not
    if(strcmp(symbol, "-e")==0)
    {
        // yes -> return e_encode
        return e_encode;
    }
    // step 2 -> check symbol is -d or not
    if(strcmp(symbol, "-d")==0)
    {
        // yes -> return e_decode
        return e_decode;
    }    
    // return e_unsupported
    return e_unsupported;
}
