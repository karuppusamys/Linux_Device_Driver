#include<stdio.h>

int main(void)
{
	char my_string[50];

	printf("Enter the input string max of 50 char: ");
	scanf("%s", &my_string);

	printf("Enter string: %s\n", my_string);

	return 0;
}