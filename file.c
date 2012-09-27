#include "file.h"
#include "opbit.h"
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define BUFSIZE 4096

typedef struct Myfile
{
	int handler;
	unsigned char buf[BUFSIZE];
	int posbit,posbyte,nbytes;
}Myfile,* PMyfile;

static Myfile mf_src;
static Myfile mf_huf;
static Myfile mf_dst;

PMyfile choose_mf(int fmode);

int mf_open(int fmode,char * fname)
{
	PMyfile mf;
	int mode;

	if ((mf=choose_mf(fmode))==NULL)
	{
		return -1;
	}

	switch(fmode)
	{
	case F_SRC:
	case F_RHUF:
		mode=O_RDONLY;
		break;
	case F_WHUF:
	case F_DST:
		mode=O_WRONLY|O_CREAT|O_TRUNC;
		break;
	default:
		return -1;
	}

	if ((mf->handler=open(fname,mode))<0)
	{
		return mf->handler;
	}

	mf->posbit=0;
	mf->posbyte=0;
	mf->nbytes=0;

	return 0;
}

int mf_close(int fmode)
{
	PMyfile mf;

	if ((mf=choose_mf(fmode))==NULL)
	{
		return -1;
	}

	if (mf->posbit!=0)
		mf->posbyte++;

	if ( (mf->posbyte>0)  && ( (fmode==F_WHUF) || (fmode==F_DST) ) )
		write(mf->handler,&mf->buf,mf->posbyte);

	close(mf->handler);
	return 0;
}

unsigned char read_bit(int fmode)
{
	PMyfile mf;
	unsigned char ret=2;

	if ((mf=choose_mf(fmode))==NULL)
	{
		return ret;
	}

	if (mf->posbyte>=mf->nbytes)
	{
		if ( (mf->nbytes=read(mf->handler,mf->buf,BUFSIZE)) ==0 )
			return 2;
		else
		{
			mf->posbyte=0;
			mf->posbit=0;
		}
	}

	if (get_bit(mf->buf,mf->posbyte,mf->posbit))
		ret=1;
	else
		ret=0;

	mf->posbit++;
	if (mf->posbit==8)
	{
		mf->posbit=0;
		mf->posbyte++;
	}

	return ret;
}

unsigned char * read_byte(int fmode)
{
	PMyfile mf;
	unsigned char *ret=NULL;

	if ((mf=choose_mf(fmode))==NULL)
	{
		return ret;
	}

	if (mf->posbyte>=mf->nbytes)
	{
		if ( (mf->nbytes=read(mf->handler,mf->buf,BUFSIZE)) ==0 )
			return NULL;
		else
			mf->posbyte=0;
	}

	ret=&mf->buf[mf->posbyte];

	mf->posbyte++;

	return ret;
}

int write_bit(int fmode,unsigned char b)
{
	PMyfile mf;

	if ((mf=choose_mf(fmode))==NULL)
	{
		return -1;
	}

	if (mf->posbyte>=mf->nbytes)
	{
		if (mf->posbyte!=0)
			write(mf->handler,mf->buf,mf->posbyte);
		mf->posbyte=0;
		mf->posbit=0;
		mf->nbytes=BUFSIZE;
	}

	if (b)
		set_bit(mf->buf,mf->posbyte,mf->posbit);
	else
		clr_bit(mf->buf,mf->posbyte,mf->posbit);

	mf->posbit++;
	if (mf->posbit==8)
	{
		mf->posbit=0;
		mf->posbyte++;
	}

	return 0;
}

int write_byte(int fmode,unsigned char *b)
{
	PMyfile mf;

	if ((mf=choose_mf(fmode))==NULL)
	{
		return -1;
	}

	if (mf->posbyte>=mf->nbytes)
	{
		if (mf->posbyte!=0)
			write(mf->handler,mf->buf,mf->posbyte);
		mf->posbyte=0;
		mf->nbytes=BUFSIZE;
	}

	mf->buf[mf->posbyte]=*b;

	mf->posbyte++;

	return 0;
}

PMyfile choose_mf(int fmode)
{
	switch(fmode)
	{
	case F_SRC:
		return &mf_src;
	case F_RHUF:
	case F_WHUF:
		return &mf_huf;
	case F_DST:
		return &mf_dst;
	default:
		return NULL;
	}
}

int write_bytes(int fmode,void * buf,int size)
{
	PMyfile mf;

	if ((mf=choose_mf(fmode))==NULL)
	{
		return -1;
	}

	return write(mf->handler,buf,size);
}

int read_bytes(int fmode,void * buf,int size)
{
	PMyfile mf;

	if ((mf=choose_mf(fmode))==NULL)
	{
		return -1;
	}

	return read(mf->handler,buf,size);
}
