#include<stdio.h>

int Count_str_len(char *strdata);
int compare_string(char *str1, char *str2);

int main(void)
{
	char my_string1[50], my_string2[50];

	printf("Enter the input string 1 and 2 with max of 50 char: \n");
	scanf("%s %s", &my_string1, &my_string2);
	
	if(compare_string(my_string1, my_string2))
	{
		printf("String %s and string %s is not same\n", my_string1, my_string2);
	}
	else
	{
		printf("String %s and string %s is same\n", my_string1, my_string2);
	}


	return 0;
}

int compare_string(char *str1, char *str2)
{
	int Cnt = 0;
	int StrLen = Count_str_len(str1);
	if(StrLen == Count_str_len(str2))
	{
		for(Cnt = 0; Cnt < StrLen; Cnt++)
		{
			if(str1[Cnt] != str2[Cnt])
			{
				return -1;
			}
		}
		return 0;
	}
	else
	{
		return -1;
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