#include<stdio.h>		//printf, scanf
#include<fcntl.h>		//O_RDWR
#include<stdlib.h>		//exit()
#include<unistd.h>		//close()
#include<sys/ioctl.h>	//_IOR, _IOW

#define USR_WR_CMD _IOW('A', 'a', int32_t*)
#define USR_RD_CMD _IOR('A', 'b', int32_t*)

int32_t ioctl_val = 5;

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
			ioctl(fd, USR_RD_CMD, (int32_t*)&ioctl_val);
			printf("Read data: %d\n", ioctl_val);
			break;
		case 2:
			printf("Enter the value write\n");
			scanf("%d", &ioctl_val);
			ioctl(fd, USR_WR_CMD, (int32_t*)&ioctl_val);
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