#include<stdio.h>

int Count_str_len(char *strdata);
void sort_string(char *mydata);

int main(void)
{
	char my_string[50];

	printf("Enter the input string max of 50 char: ");
	scanf("%[^\n]s", &my_string);

	sort_string(my_string);
	
	printf("Value of string after sorting: %s\n", my_string);

	return 0;
}

void sort_string(char *mydata)
{
	int str_len = 0;
	int Cnt_1 = 0, Cnt_2 = 0;
	char tmp = 0;

	str_len = Count_str_len(mydata);

	
	for(Cnt_1 = 0; Cnt_1 < str_len; Cnt_1++)
	{
		for(Cnt_2 = Cnt_1 + 1; Cnt_2 < str_len; Cnt_2++)
		{
			if(mydata[Cnt_1] > mydata[Cnt_2])
			{
				tmp = mydata[Cnt_1];
				mydata[Cnt_1] = mydata[Cnt_2];
				mydata[Cnt_2] = tmp;
			}
		}
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