#ifndef _FENCI_H_
#define _FENCI_H_
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LENGTH 100
char *dict[16];
int nums[10];

void fmm(char *words[])
{
	char input[MAX_LENGTH];  // �洢���ִʵ��ַ���
    int dict_size = 15;  // �ʵ��С
    int input_length, index, i;
    int max_word_length;
    char word[MAX_LENGTH];  // �洢�ֳ��Ĵ�
    int found_word;  // ��¼�Ƿ��ҵ�һ����

    //printf("��������ִʵ��ַ�����");
    //gets(input);
    int j=0,sum=0;
    for(j=0;j<6;j++){
    	sum=0;
    	char ch='1';
    	char file[10]={0};
    	file[0]=ch+j;
    	strcat(file,".txt");
    	if(j<5){printf("%s",file);}
		strcpy(input,words[j]);
	    input_length = strlen(input);
	    index = 0;
	    int num=0;
	    if(input_length>30)	
			num=30;
		else
			num=input_length;
		FILE * fps;
		fps=fopen(file,"w");
	    while (index < input_length) {  // ��ͷ��ʼ���������ַ���
	    	max_word_length=num;
	    	int flag=0;
	    	found_word=0;
	    	while(max_word_length>=2){
				for(i=0;i<dict_size;i++)
				{
					int word_length = strlen(dict[i]);
					if (word_length == max_word_length && strncmp(dict[i], input + index, max_word_length) == 0){
						found_word=1;
						strcpy(word,dict[i]);
						flag=1;
						break;
					}				
				}
				if(flag)
					break;
				max_word_length--;
			}
	        if (!found_word) {  // ���û��ƥ��Ĵʣ���Ĭ�Ͻ�����������Ϊһ����
	            if(input[index]<0)
					max_word_length = 2;
	            else 
					max_word_length=1;
	            strncpy(word, input + index, max_word_length);
	        }
	        fputs(word,fps);
	        fputs("\n",fps);
	        if(j<5)
	        	printf("%s|", word);  // ����ֳ��Ĵ�
	        memset(word,0,strlen(word));
	        index += max_word_length;  // ������һ��ƥ��λ��
	        sum++;
	    }
	    fclose(fps);
	    nums[j]=sum;
	    printf("\n");
	}
}
#endif
