#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include </home/luigi/apue.3e/include/apue.h>

char buf1[] = "aababababsjallaifa";
char buf2[] = "babababbababababba";

int main(void)
{
     int fd;
     
     //Creiamo un file
     if((fd = creat("file.txt",FILE_MODE)) < 0 ) printf("creat error");
     
     //Scriviamo all'interno del file
     if(write(fd,buf1,10) != 10) printf("write error");
     
     //Posizionamoci al byte 40
     if(lseek(fd,10,SEEK_SET) == -1) 	printf("lseek error");
     
     //Scriviamo al byte 40
     if(write(fd,buf2,10) != 10) printf("write error");
     
     //Ora ci troveremo in posizione 50 (40 + 10)
     
     exit(0);
}
