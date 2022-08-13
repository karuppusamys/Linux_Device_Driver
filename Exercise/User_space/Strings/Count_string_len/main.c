#include<stdio.h>

int Count_str_len(char *strdata);

int main(void)
{
	char my_string[50];

	printf("Enter the input string max of 50 char: ");
	scanf("%[^\n]s", &my_string);

	printf("Length of string: %s is %d\n", my_string, Count_str_len(my_string));

	return 0;
}

int Count_str_len(char *strdata)
{
	int count = 0;
	while(strdata[count] != '\0')
	{
		count++;
	}
	return count;
}



// #include<string.h>
//int len =strlen(str);