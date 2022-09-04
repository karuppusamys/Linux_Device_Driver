#include<stdio.h>
unsigned int swap_bytes(unsigned int *var);
void print_bits(int val, int size);

int main(void)
{
	unsigned int num = 0;
	
	printf("Enter the number: \n");
	scanf("%u", &num);
	
	swap_bytes(&num);
	return 0;
}

unsigned int swap_bytes(unsigned int *var)
{
	printf("\nBefore swaping the bits: ");
	print_bits(*var, sizeof(*var));
	
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