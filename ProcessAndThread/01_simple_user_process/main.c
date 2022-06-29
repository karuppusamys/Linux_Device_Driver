#include<stdio.h>    // printf snd scanf

int main(void)
{
	unsigned int Cnt = 0;

	printf("I am in main\n");
	
	Cnt = 0;
	while(Cnt < 0x0000FFFF)
	{
		printf("I am in process - %u\n", Cnt);
		Cnt++;
	}
	
	//sleep(30);
	printf("I am in end of main\n");

	return 0;
}