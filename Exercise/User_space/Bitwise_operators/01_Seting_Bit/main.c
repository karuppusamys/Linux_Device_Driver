#include<stdio.h>

int main(void)
{
	int int_num = 0;
	unsigned short pit_pos = 0;
	printf("Enter the number: ");
	scanf("%d", &int_num);
	
	printf("Enter the set bit position to set: ");
	scanf("%hu", &pit_pos);
	
	printf("Number before set the bit: %d\n", int_num);
	
	int_num = int_num | ((int)1 << pit_pos);

	printf("Number after set the bit: %d\n", int_num);
	
	return 0;
	
}