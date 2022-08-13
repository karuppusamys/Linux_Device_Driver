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
	static int Cnt = 0, str_len = 0;
	char tmp = 0;
	
	if(str_len == 0)
		str_len = Count_str_len(strdata);
	
	if(Cnt < str_len/2)
	{
		tmp = strdata[Cnt];
		strdata[Cnt] = strdata[str_len - Cnt - 1];
		strdata[str_len - Cnt - 1] = tmp;
		Cnt++;
		Rev_string(strdata);
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