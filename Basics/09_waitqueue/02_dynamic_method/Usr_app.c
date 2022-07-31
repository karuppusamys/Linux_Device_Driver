#include<stdio.h>
#include <fcntl.h>		//O_RDWR
#include <stdlib.h>		//exit()
#include <unistd.h>		//close()

char Rx_buff[1023];
char Tx_buff[1023] = "Hellow";

int main(void)
{
	int fd = -1;
	int option;
	
	fd = open("/dev/my_test_dev", O_RDWR);
	
	if(fd < 0)
	{
		printf("Unable to open the file\n");
		return -1;
	}
	
	printf("Enter the following options\n 1. Read\n 2. Write\n 3. Exit\n Option = ");
	scanf("%d", &option);
	printf("Selected option %d\n", option);
	
	switch(option)
	{
		case 1:
			read(fd, Rx_buff, sizeof(Rx_buff));
			printf("Read data: %s\n", Rx_buff);
			break;
		case 2:
			printf("Enter the value write\n");
			scanf("  %[^\t\n]s", Tx_buff);
			write(fd, Tx_buff, 5);
			break;
		case 3:
			close(fd);
			exit(0);
			return 0;
			break;
		default:
			printf("Invalid option %d\n");
			break;
	}
	close(fd);
	return 0;
}