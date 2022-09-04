#include<stdio.h>

int main(void)
{
	int num = 0;
	
	char *ptr = &num;

	printf("Enter the number: \n");
	scanf("&d", &num);
	
	if(*ptr != 0)
	{
		printf("This is big endian system\n");
	}
	else
	{
		printf("This is small endian system\n");
	}
	return 0;
}