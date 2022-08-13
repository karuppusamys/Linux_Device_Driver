#include<stdio.h>

int Count_str_len(char *strdata);
int string_concat(char *str1, char *str2);

int main(void)
{
	char my_string1[50], my_string2[50];
	
	printf("Enter the input string 1 and 2 with max of 50 char: \n");
	scanf("%s %s", &my_string1, &my_string2);
	
	string_concat(my_string1, my_string2);
	
	printf("String value after concatination %s: \n", my_string1);

	return 0;
}

int string_concat(char *str1, char *str2)
{
	//int str_len = Count_str_len
	int Cnt = 0, Cnt1 = 0;
	
	while(str1[Cnt] != '\0')
	{
		Cnt++;
	}
	
	while(str2[Cnt1] != '\0')
	{
		str1[Cnt + Cnt1] = str2[Cnt1];
		Cnt1++;
	}
	str1[Cnt + Cnt1]  = '\0';
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