#include<stdio.h>

int Count_str_len(char *strdata);

int main(void)
{
	char my_string[50];
	unsigned short word_count = 0, Cnt = 0;

	printf("Enter the input string max of 50 char: ");
	scanf("%[^\n]s", &my_string);

	for(Cnt = 0; my_string[Cnt] != '\0'; Cnt++)
	{
		if((my_string[Cnt] == ' ') || (my_string[Cnt] == '\t') || (my_string[Cnt] == '\n'))
			word_count++;
	}
	printf("Number of words in string: %s is %hu\n", my_string, word_count + 1);

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