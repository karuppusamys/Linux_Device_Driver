#include<stdio.h>
//#include<string.h>
//strrev(str)

int Count_str_len(char *strdata);
void Rev_string(char *strdata);

int main(void)
{
	char my_string[50];

	printf("Enter the input string max of 50 char: ");
	scanf("%[^\n]s", &my_string);

	Rev_string(my_string);
	
	printf("Value after reversing the sting: %s\n", my_string);

	return 0;
}

void Rev_string(char *strdata)
{
	int str_len = 0;
	int Cnt = 0;
	char tmp = 0;

	str_len = Count_str_len(strdata);
	
	for(Cnt = 0; Cnt < str_len/2; Cnt++)
	{
		tmp = strdata[Cnt];
		strdata[Cnt] = strdata[str_len - Cnt - 1];
		strdata[str_len - Cnt - 1] = tmp;
	}
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