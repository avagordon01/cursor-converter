/* ani2ico: program created by TeoBigusGeekus - October 2012 *
 * Extract .ico images from .ani animated Windows cursors.   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReadFile(char *name);
int test_for_icon_string(char *buffer,int start);

int main(int argc, char **argv)
{
    if (argc != 2) {
		fprintf(stderr, "Please give an .ani filename as an argument.\n");
        return 0;
    }

	ReadFile(*(argv+1));
	return 0;
}

int test_for_icon_string(char *buffer,int start)
{
    if (*(buffer+start) == 0x69) {
        if (*(buffer+start+1) == 0x63) {
            if (*(buffer+start+2) == 0x6f) {
                if (*(buffer+start+3) == 0x6e) {
                    return 1;
                }
            }
        }
    } else return 0;
}

void ReadFile(char *name)
{
	FILE *file;
	char *buffer,*fileName;
	unsigned long fileLen;

    if (!strstr(name,".ani")) {
		fprintf(stderr, "Please give an .ani filename as an argument.\n");
        return;
    }

    fileName=malloc(strlen(name)+1);
    if (!fileName) {
		fprintf(stderr, "Memory error!\n");
        return;
    }

    strcpy(fileName,name);
    *strstr(fileName,".ani")='\0';

	file = fopen(name, "rb");
	if (!file) {
		fprintf(stderr, "Unable to open file %s.\n", name);
        free(fileName);
		return;
	}
	
	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer=(char *)malloc(fileLen+1);
	if (!buffer) {
		fprintf(stderr, "Memory error!\n");
        fclose(file);
        free(fileName);
		return;
	}

	fread(buffer, fileLen, 1, file);
	fclose(file);

    char *new_ico_name=malloc(strlen(name)+5);
    if (!new_ico_name) {
		fprintf(stderr, "Memory error!\n");
        free(fileName);
        free(buffer);
        return;
    }

    char ico_counter_string[5];
	int i,j,ico_counter=1;
    FILE *ico_image;

	for (i=0;i <= fileLen;i++) {
        if (ico_counter == 9999) {
			free(fileName);
			free(buffer);
			free(new_ico_name);
            return;
		}
		
        if ((i+4 <= fileLen) && test_for_icon_string(buffer,i) == 1) {
            sprintf(ico_counter_string,"%d",ico_counter);
            strcpy(new_ico_name,fileName);
            strcat(new_ico_name,ico_counter_string);
            strcat(new_ico_name,".ico");
            ico_counter++;

            ico_image = fopen(new_ico_name,"wb");
            if (!ico_image) {
                fprintf(stderr, "Unable to open file %s.\n", new_ico_name);
                free(fileName);
                free(buffer);
                free(new_ico_name);
                return;
            }

            j=8;
            while (i+j+4 <= fileLen) {
                if (test_for_icon_string(buffer,i+j+1) == 1)
                    break;
                if (j==10)
                    putc(0x01,ico_image);
                else
                    putc(*(buffer+i+j),ico_image);
                j++;
            }
            if (i+j <= fileLen)
                putc(*(buffer+i+j),ico_image);
            if (fileLen-i-j<=3) {
                putc(*(buffer+i+j+1),ico_image);
                putc(*(buffer+i+j+2),ico_image);
            }
            fclose(ico_image);
            i+=j;
        }
    }
        
    free(new_ico_name);
    free(buffer);
    free(fileName);
}
