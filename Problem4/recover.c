#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //if program is not executed with exactly one command-line argument, remind the user of correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //open card.raw for reading and check for NULL
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("File is not found!");
        return 1;
    }
    
    //read 512 bytes from card.raw until reach the end
    typedef uint8_t BYTE;
    BYTE buffer[512];
    int first = 0;
    FILE *new_jpg;
    int file_counter = 0;
    while (fread(buffer, 1, 512, card) != 0x00)
    {
        //if we find the distinct header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if we have not found the first jpg
            if (first == 0)
            {
                //increment first for boolean expression
                first = 1;
                
                //write the bytes into a new file
                //1) open file
                char filename[8];
                sprintf(filename, "%03i.jpg", file_counter++);
                new_jpg = fopen(filename, "w");
                
                //2) write from buffer into new_jpg
                fwrite(buffer, 1, 512, new_jpg);
            }
            
            else
            {
                //close the previous file
                fclose(new_jpg);
                
                //write the bytes into a new file
                //1) open file
                char filename[8];
                sprintf(filename, "%03i.jpg", file_counter++);
                new_jpg = fopen(filename, "w");
                
                //2) write from buffer into new_jpg
                fwrite(buffer, 1, 512, new_jpg);
            }
        }
        
        else
        {
            //if we have found the first jpg
            if (first == 1)
            {
                //continue to write the bytes
                fwrite(buffer, 1, 512, new_jpg);
            }
        }
    }
    
    //close all files and free the memory used
    fclose(new_jpg);
    fclose(card);
}
