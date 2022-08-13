#include<stdio.h>

int Count_str_len(char *strdata);

int main(void)
{
	char my_string[50];
	unsigned short alpa_count = 0, Cnt = 0;

	printf("Enter the input string max of 50 char: ");
	scanf("%[^\n]s", &my_string);

	for(Cnt = 0; my_string[Cnt] != '\0'; Cnt++)
	{
		if((my_string[Cnt] >= 'a') && (my_string[Cnt] <= 'z') || (my_string[Cnt] >= 'A') && (my_string[Cnt] <= 'Z'))
			alpa_count++;
	}
	printf("Number of alpa in string: %s is %hu\n", my_string, alpa_count);

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