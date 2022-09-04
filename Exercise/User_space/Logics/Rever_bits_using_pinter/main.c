#include<stdio.h>
unsigned int swap_bits(unsigned int *var);
void print_bits(int val, int size);

int main(void)
{
	unsigned int num = 0;
	
	printf("Enter the number: \n");
	scanf("%u", &num);
	
	swap_bits(&num);
	return 0;
}

unsigned int swap_bits(unsigned int *var)
{
	printf("\nBefore swaping the bits: ");
	print_bits(*var, sizeof(*var));
	
	*var = (((*var & 0xAAAAAAAA) >> 1) | ((*var & 0x55555555) << 1));
	
	*var = (((*var & 0xCCCCCCCC) >> 2) | ((*var & 0x33333333) << 2));
	
	*var = (((*var & 0xF0F0F0F0) >> 4) | ((*var & 0x0F0F0F0F) << 4));
	
	*var = (((*var & 0xFF00FF00) >> 8) | ((*var & 0x00FF00FF) << 8));
	
	*var = (((*var & 0xFFFF0000) >> 16) | ((*var & 0x0000FFFF) << 16));
	
	printf("\nAfter swaping the bits : ");
	print_bits(*var, sizeof(*var));

	return *var;
}

void print_bits(int val, int size)
{
	int Cnt = 0;
	for(Cnt = (size * 8) - 1; (Cnt >= 0); Cnt--)
	{
		(val & (1 << Cnt)) ? printf("1") : printf("0");
	}
}