#include<stdio.h>
#include<unistd.h>
int Count_str_len(char *strdata);
int str_comp(char * str1, char * str2);
int find_sub_strings(char * str, char * wrd);

int main(void)
{
	char my_string[50], my_sub_str[50];
	int Max_occur = 0;
	
	

	printf("Enter the input string max of 50 char: ");
	scanf("%[^\n]s", my_string);

	printf("Enter the sub string to find: ");
	scanf("%s", my_sub_str);
	
	Max_occur = find_sub_strings(my_string, my_sub_str);

	printf("Entered string is %s and sub string is %s. %d\n", my_string, my_sub_str, Max_occur);

	return 0;
}

int find_sub_strings(char * str, char * wrd)
{
	int sub_str_len = 0, main_str_len = 0, Cnt, MaxCnt = 0;
	
	sub_str_len = Count_str_len(wrd);
	main_str_len = Count_str_len(str);
	
	for(Cnt = 0; (Cnt < main_str_len - sub_str_len + 1); Cnt++)
	{
		if(!str_comp(&str[Cnt], wrd))
		{
			MaxCnt++;
		}
	}
	
	return MaxCnt;
}

int str_comp(char * str1, char * str2)
{
	int str1_len, str2_len, com_len, Cnt;
	
	str1_len = Count_str_len(str1);
	str2_len = Count_str_len(str2);
	
	if(str2_len < str1_len)
		com_len = str2_len;
	else
		com_len = str1_len;
	
	for(Cnt = 0; Cnt < com_len; Cnt++)
	{
		if(str1[Cnt] != str2[Cnt])
			return 1;
	}
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