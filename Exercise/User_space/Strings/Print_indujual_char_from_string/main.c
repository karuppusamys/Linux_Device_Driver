#include<stdio.h>

int Count_str_len(char *strdata);

int main(void)
{
	char my_string[50];
	int str_len = 0;
	int cnt = 0;

	printf("Enter the input string max of 50 char: ");
	scanf("%[^\n]s", &my_string);

	str_len = Count_str_len(my_string);
	
	printf("Received string: ");
	for(cnt = 0; cnt <= str_len; cnt++)
	{
		printf("%c", my_string[cnt]);
	}
	printf("\n");
	
//	or
	
	printf("Received string: ");
	for(cnt = 0; my_string[cnt] != '\0'; cnt++)
	{
		printf("%c", my_string[cnt]);
	}
	printf("\n");

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