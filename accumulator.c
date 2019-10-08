
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv)
{
		int dev;
		int number2 = 0;
		char buffer[1024];

		dev = open("/dev/sysprog_device", O_RDWR);
		
		if(dev == -1)
		{
				perror("failed to open; becuse ");
				return 1;
		}
		
		while(1)
		{
			printf("Input the value\n");
			scanf("%d", &number2);
			write(dev, &number2, sizeof(int));
			read(dev, buffer, sizeof(int));
			printf("The accumulated number in kernel space is %d\n", *buffer);
		}
		
		close(dev);
		
		exit(EXIT_SUCCESS);
}
