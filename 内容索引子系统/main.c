#include "fenci.h"
#include "daopai.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char *words[]={
	"北京安立文高新技术公司", 
	"新一代的网络访问技术",
	"北京卫星网络有限公司", 
	"是最先进的总线技术",
	"北京升平卫星技术有限公司的新技术有",
	"待查询语句"};
char *dict[16];
char *use_dict[]={"北京","高新","技术","公司",
"新","网络","访问","卫星","先进","总线","升平","安","立","文"}; 
int nums[10];
double w[sizeof(use_dict)/sizeof(*use_dict)];
double tensor[6][sizeof(use_dict)/sizeof(*use_dict)]={0},sim[5];
const int WORDS_NUM=sizeof(words)/sizeof(*words);

void CosSim();
void Weight();//TF-IDF
void IDF();
int is_inu_d(char data[]);
double mo(double a[]);
double tensor_dian(double a[],double b[]);
void max_n_in_arr(double arr[],int len,int n);

int main()
{
	//memset(tensor,0,sizeof(tensor));
	int len=0;
	FILE *fp;
	fp = fopen("word.txt","r");
	while(!feof(fp))
	{
		dict[len]=(char *)malloc(20);
		fscanf(fp,"%s",dict[len++]);
	}
	fclose(fp);
	char search[20];
	printf("请输入您想查询的语句：");
	gets(search);
	words[5]=search;
	fmm(words);
	daopai();
	free(dict);
	IDF();
	Weight();
	CosSim();
	for(int i=0;i<5;i++){
		if (isnan(sim[i]))//如果计算非法(无穷小)
		{
			printf("查询语句与文档%d相似度:0.000000\n",(i+1));
			continue;
		}
		printf("查询语句与文档%d相似度:%lf\n",(i+1),sim[i]); 
	}
	printf("\n");
	max_n_in_arr(sim,5,3);
	system("pause");
	return 0;
}

void max_n_in_arr(double arr[],int len,int n)
{
    double max[n];
    int ind[n];
    memset(max,0,n*8);
    memset(ind,0,n+1);
    for(int i=0;i<n;i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (i>0)
            {
                if (arr[j]>max[i]&&arr[j]<=max[i-1]&&j!=ind[i-1])
                {
                    max[i]=arr[j];
                    ind[i]=j;
                }
            }
            else if (arr[j]>max[i])
            {
                max[i]=arr[j];
                ind[i]=j;
            }
        }
        printf("%d:文档%d，相似度为:%lf\n",i+1,ind[i]+1,max[i]);
    }
}

void IDF()
{
	struct Node*p;
	double num_in_doc_add1=0;
	for(unsigned int i=0;i<(sizeof(use_dict)/sizeof(*use_dict));i++){
		for(p=head;p!=NULL;p=p->next)
		{
			if(strcmp(p->word,use_dict[i])==0)
			{
				num_in_doc_add1=p->Indoc_num;
				break;
			}
		}
		//w[i]=log10(5/num_in_doc_add1);
		w[i]=log10((sizeof(words)/sizeof(*words))/num_in_doc_add1);
	}
}

int is_inu_d(char data[]){
	for(unsigned int i=0;i<(sizeof(use_dict)/sizeof(*use_dict));i++){
		if(strcmp(data,use_dict[i])==0){
			return i;
		}
	}
	return -1;
}

void Weight()
{
	for(int j=0;j<6;j++){
		char ch='1';
		char file[10]={0};
		file[0]=ch+j;
		strcat(file,".txt");
		FILE * fps;
		fps=fopen(file,"r");
		char con[20];
		memset(con,0,20);
		struct Node*p;
		double num_word_in_txt=0;
		for(int i = 0;fscanf(fps, "%s", con)>=0; i++)
		{
			int res=is_inu_d(con);
			if(res<0){
				continue;
			}
			int flag=0;
			for(p=head;p!=NULL;p=p->next)
			{
				if(strcmp(p->word,con)==0){
					for(int k=0;k<p->Indoc_num;k++)
					{
						if(strcmp(p->dif[k].name,file)==0){
							num_word_in_txt=p->dif[k].freq;
							flag=1;
							break;
						}
					}
				}
				if(flag)break;
			}
			tensor[j][res]=num_word_in_txt/nums[j]*w[res];
			memset(con,0,20);
		}
		fclose(fps);
	}
//	tensor[5][1]=w[1]/3;
//	tensor[5][2]=w[2]/3;
//	tensor[5][3]=w[3]/3;
}

double mo(double a[])
{
	double sum=0;
	for(unsigned int i=0;i<(sizeof(use_dict)/sizeof(*use_dict));i++)
	{
		sum+=a[i]*a[i];
	}
	sum=sqrt(sum);
	return sum;
}

double tensor_dian(double a[],double b[])
{
	double sum=0;
	for(unsigned int i=0;i<(sizeof(use_dict)/sizeof(*use_dict));i++)
	{
		sum+=a[i]*b[i];
	}
	return sum;
}
void CosSim()
{
	double pos=mo(tensor[5]);
	for(unsigned int i=0;i<(sizeof(words)/sizeof(*words)-1);i++){
		sim[i]=tensor_dian(tensor[i],tensor[5])/(mo(tensor[i])*pos);	
	}
	//printf("%lf",pos);	
}
