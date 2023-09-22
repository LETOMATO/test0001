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
	char input[MAX_LENGTH];  // 存储待分词的字符串
    int dict_size = 15;  // 词典大小
    int input_length, index, i;
    int max_word_length;
    char word[MAX_LENGTH];  // 存储分出的词
    int found_word;  // 记录是否找到一个词

    //printf("请输入待分词的字符串：");
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
	    while (index < input_length) {  // 从头开始遍历输入字符串
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
	        if (!found_word) {  // 如果没有匹配的词，则默认将单个汉字作为一个词
	            if(input[index]<0)
					max_word_length = 2;
	            else 
					max_word_length=1;
	            strncpy(word, input + index, max_word_length);
	        }
	        fputs(word,fps);
	        fputs("\n",fps);
	        if(j<5)
	        	printf("%s|", word);  // 输出分出的词
	        memset(word,0,strlen(word));
	        index += max_word_length;  // 更新下一个匹配位置
	        sum++;
	    }
	    fclose(fps);
	    nums[j]=sum;
	    printf("\n");
	}
}
#endif
