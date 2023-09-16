#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_WORD_LENGTH 50//单词最大长度
#define MAX_DOC_CNUM 1000//文档最大长度

typedef struct wid{
	char name[20];//文档名
	int freq;//出现频率
	int locs[MAX_DOC_CNUM];//出现位置
}wid;

//倒排索引节点
typedef struct Node
{
	char word[MAX_WORD_LENGTH];//单词
	int Indoc_num;//含有该单词的文本数量
	wid dif[10];
	struct Node *next;
} InvertedIndexNode;

typedef InvertedIndexNode*Linklist;//倒排索引表
struct Node* head=NULL;

typedef struct txtNode
{
	char name[50];
	int word[50];
	struct txtNode *next;
}TN;
typedef TN *txtlist;
struct txtNode* thead=NULL;
//文档数据结构


void add_txtNode(char data[])
{
	txtlist new_node=(txtlist)malloc(sizeof(TN));
	strcpy(new_node->name,data);
	for(int i=0;i<50;i++){
		new_node->word[i]=0;
	}
	new_node->next=thead;
	thead=new_node;
}

void add_Node(char data[],int num,char ne[],int fq,int loc)
{
	Linklist new_node = (Linklist)malloc(sizeof(InvertedIndexNode));
	strcpy(new_node->word,data);
	new_node->Indoc_num=num;
	for(int s=0;s<10;s++){
		strcpy(new_node->dif[s].name,"0");
	}
	strcpy(new_node->dif[0].name,ne);
	new_node->dif[0].freq=fq;
	new_node->dif[0].locs[0]=loc;
	new_node->next = head;
	head = new_node;
}

int is_in(struct Node *header, char posData[],char posdoc[],int loc)
{
    struct Node *p = header;
    int lns=0;
    if (p == NULL)
    {
        return -2;
    }
    else
    {
        while (strcmp(p->word,posData)!=0)
        {
            p = p->next;
            if(p == NULL)
            {
                return -2;
            }
            lns++;
        }
        int i=0;
        while(i<10)
        {
			i++;
			if(strcmp(p->dif[i].name,posdoc)==0)
			{p->dif[i].locs[p->dif[i].freq]=loc;p->dif[i].freq+=1;return -1;}
		}
		strcpy(p->dif[p->Indoc_num].name,posdoc);
		p->dif[p->Indoc_num].freq=1;
		p->dif[p->Indoc_num].locs[0]=loc;
		p->Indoc_num+=1;
    }
    return lns;
}

int main()
{
	FILE* fp = NULL;
	char file[20];
	struct txtNode*f;//文件名指针
	struct Node*p;//倒排表指针
	printf("请输入想要倒排的文件：(以#结束！)\n");
	gets(file);
	int shumu=0;
	while(file[0]!='#'){
		add_txtNode(file);
		shumu++;
		gets(file);
	}
    int sum=0;
    f=thead;
	for(int i=0;i<shumu;i++){
		char files[50];
		strcpy(files,"C:\\Users\\asus\\Desktop\\txt\\daopi\\");
		strcat(files,f->name);
		fp = fopen(files, "r");//TODO
		if(fp == NULL) // 打开文件失败
		{
			printf("第%d个文件打开失败\n",i+1);
			f=f->next;
			continue;
		}
		memset(files,0,50);
		strcpy(files,f->name);
		char con[20];
    	for(int j = 0;fscanf(fp, "%s", con)>=0; j++)
    	{
    		p=head;
			int flag=is_in(p,con,files,j);
    		if(flag >= -1){
    			if(flag>=0){
					f->word[sum-flag-1]=1;
				}
				continue;
			}
			add_Node(con,1,files,1,j);
			f->word[sum]=1;
			sum++;	
			//memset(con,0,20);		
    	}
		fclose(fp);
		f=f->next;
	}
	int s=sum; 
	for(p=head;p!=NULL;p=p->next){
		printf("%d%s\n",s--,p->word);
	}
	printf("文件\t");
	for(int j=1;j<=sum;j++)
		printf("序%d\t",j);
	for(f=thead;f!=NULL;f=f->next){
		printf("\n%s\t",f->name);
		for(int j=0;j<sum;j++)
			printf("%d\t",f->word[j]);
	}
	printf("\n以下倒排文件所处地址为C:/Users/asus/Desktop/txt/daopi。");
	for(p=head;p!=NULL;p=p->next){
		printf("\n%2d%-14s(%d)\t",sum--,p->word,p->Indoc_num);
		for(int i=0;i<p->Indoc_num;i++)
			for(int j=0;j<p->dif[i].freq;j++)
				printf("%s(%d,%d)\t",p->dif[i].name,p->dif[i].freq,p->dif[i].locs[j]);
	}
	return 0;
}
