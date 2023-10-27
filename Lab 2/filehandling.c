#include<stdio.h>
#include<stdlib.h>
int main()
{
    FILE * ptr;
    FILE * ptr1;
    ptr=fopen("Input1.txt","r");
    char c;
    
    while(1)
    {
        c=fgetc(ptr);
        if(feof(ptr))
        break;
        printf("%c",c);
    }
    fclose(ptr);
    ptr=fopen("Input1.txt","r");
    ptr1=fopen("Output.txt","w+");
    while(1)
    {
        c=fgetc(ptr);
        if(feof(ptr))
        break;
        else if(65<=c && c<=91)
           { printf("%c",c+32); }
        else if(97<=c && c<=122)
           { printf("%c",c-32);  }
        else
       { printf("%c",c); }
       fputc(c,ptr1);
    }
    fclose(ptr);
    fclose(ptr1);
    return 0;
}