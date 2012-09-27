#include "file.h"
#include "haf.h"
#include "opbit.h"
#include "myerror.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

typedef struct Huftree_node
{
	int num;
	int lchild,rchild;
	unsigned int times;
	struct Huftree_node * next;
}Huftree_node,* PHuftree_node;

typedef struct Huftree_map
{
	int l;
	unsigned char code[17];
}Huftree_map,*PHuftree_map;

static Huftree_node huftree[513];
static Huftree_map tree_map[513];


int build_huftree();
int build_treemap(PHuftree_node node);
int load_huftree();
int save_huftree();
int fzip();
int funzip();

int unzip(char *fsrc,char *fhuf,char *fdst)
{
	int ret=0;
	FILE * ftest;
	int i;

	printf("%s\n",fsrc);
	printf("%s\n",fhuf);
	printf("%s\n",fdst);

	if (mf_open(F_SRC,fsrc)<0)
	{
		ret=-E_SRC;
		goto e_src;
	}
	//if (mf_open(F_RHUF,fhuf)<0)
	//{
	//	ret=-E_HUF;
	//	goto e_huf;
	//}
	if (mf_open(F_DST,fdst)<0)
	{
		ret=-E_DST;
		goto e_dst;
	}

	//load_huftree();

	ftest=fopen(fhuf,"r");
	for (i=0;i<513;i++)
	{
		fscanf(ftest,"%d%d%d",&huftree[i].num,&huftree[i].lchild,&huftree[i].rchild);;
	}
	fclose(ftest);

	funzip();

	mf_close(F_SRC);
	//mf_close(F_RHUF);
	mf_close(F_DST);

	goto outt;

e_dst:
	//mf_close(F_RHUF);
	mf_close(F_SRC);
e_src:
outt:
	printf("解压完成。\n");
	return ret;
}

int zip(char *fsrc,char *fhuf,char *fdst)
{
	int ret=0;

	int i;
	FILE * ftest;

	printf("%s\n",fsrc);
	printf("%s\n",fhuf);
	printf("%s\n",fdst);

	if (mf_open(F_SRC,fsrc)<0)
	{
		ret=-E_SRC;
		goto e_src;
	}
	//if (mf_open(F_WHUF,fhuf)<0)
	//{
	//	ret=-E_HUF;
	//	goto e_huf;
	//}
	if (mf_open(F_DST,fdst)<0)
	{
		ret=-E_DST;
		goto e_dst;
	}

	build_huftree();
	tree_map[512].l=0;
	ftest=fopen(fhuf,"w");
	for (i=0;i<513;i++)
	{
		fprintf(ftest,"%d %d %d\n",huftree[i].num,huftree[i].lchild,huftree[i].rchild);;
	}
	fclose(ftest);
	build_treemap(&huftree[512]);
	//save_huftree();
	mf_close(F_SRC);
	if (mf_open(F_SRC,fsrc)<0)
	{
		ret=-E_SRC;
		goto e_src;
	}
	fzip();

	mf_close(F_SRC);
	//mf_close(F_WHUF);
	mf_close(F_DST);
	goto outt;

e_dst:
	//mf_close(F_WHUF);
	mf_close(F_SRC);
e_src:
outt:
	printf("压缩完成。\n");
	return ret;
}

int build_huftree()
{
	int i,now;
	unsigned char * b;
	Huftree_node head;
	PHuftree_node p,q;

	for (i=0;i<513;i++)
	{
		huftree[i].times=0;
		huftree[i].num=i;
		huftree[i].lchild=i;
		huftree[i].rchild=i;
	}

	do
	{
		b=read_byte(F_SRC);
		if (b!=NULL)
			huftree[*b].times++;
	}while(b!=NULL);
	huftree[256].times=1;
	now=257;

	head.times=0;
	head.next=NULL;

	for (i=0;i<257;i++)
	{

		p=&head;
		while ((p!=NULL)&&(p->times<=huftree[i].times))
		{
			q=p;
			p=p->next;
		}
		q->next=&huftree[i];
		huftree[i].next=p;
	}

	for (i=0;i<256;i++)
	{
		p=head.next;
		q=head.next->next;
		head.next=q->next;
		huftree[now].lchild=p->num;
		huftree[now].rchild=q->num;
		p=&head;
		while ((p!=NULL)&&(p->times<=huftree[now].times))
		{
			q=p;
			p=p->next;
		}
		q->next=&huftree[now];
		huftree[now].next=p;

		now++;
	}

	return 0;
}

int build_treemap(PHuftree_node node)
{
	PHuftree_map m,lm,rm;
	if ( node->num < 257 )
	{
		return 0;
	}

	m=&tree_map[node->num];
	lm=&tree_map[node->lchild];
	rm=&tree_map[node->rchild];
	lm->l=m->l+1;
	rm->l=m->l+1;
	memcpy(lm->code,m->code,17);
	memcpy(rm->code,m->code,17);
	clr_bit(lm->code,(lm->l-1)/8,(lm->l-1)%8);
	set_bit(rm->code,(rm->l-1)/8,(rm->l-1)%8);

	build_treemap(&huftree[node->lchild]);
	build_treemap(&huftree[node->rchild]);

	return 0;
}

int load_huftree()
{
	read_bytes(F_RHUF,huftree,513*sizeof(Huftree_node));
	return 0;
}

int save_huftree()
{
	write_bytes(F_WHUF,huftree,513*sizeof(Huftree_node));
	return 0;
}

int fzip()
{
	unsigned char * b, p;
	int i;

	do
	{
		b=read_byte(F_SRC);
		//printf("%d\n",(int)(*b));
		if (b!=NULL)
		{
			for (i=0;i<tree_map[*b].l;i++)
			{
				p=get_bit(tree_map[*b].code,i/8,i%8);
				if (p)
					write_bit(F_DST,1);
				else
					write_bit(F_DST,0);
			}
		}
	}while(b!=NULL);

	for (i=0;i<tree_map[256].l;i++)
	{
		p=get_bit(tree_map[256].code,i/8,i%8);
		if (p)
			write_bit(F_DST,1);
		else
			write_bit(F_DST,0);
	}

	return 0;
}

int funzip()
{
	PHuftree_node p;
	unsigned char b,byte;

	p=&huftree[512];

	while (p->num != 256)
	{
		b=read_bit(F_SRC);

		if (b)
			p=&huftree[p->rchild];
		else
			p=&huftree[p->lchild];

		if (p->num < 256)
		{
			byte=(unsigned char)(p->num);
			write_byte(F_DST,&byte);
			p=&huftree[512];
		}
	}
	return 0;
}
