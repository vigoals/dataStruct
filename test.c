#include "test.h"
#include "file.h"
#include "myerror.h"
#include <stdio.h>

int test(char *fsrc,char *fhuf,char *fdst)
{
	int ret=0;
	unsigned char b=0;

	printf("fsrc:%s\n",fsrc);
	//printf("%s\n",fhuf);
	printf("fdst:%s\n",fdst);

	if (mf_open(F_SRC,fsrc)<0)
	{
		ret=-E_SRC;
		goto e_src;
	}
	if (mf_open(F_DST,fdst)<0)
	{
		ret=-E_DST;
		goto e_dst;
	}

	do
	{
		b=read_bit(F_SRC);
		if (b<2)
		{
			write_bit(F_DST,b);
		}
	}while(b<2);

	mf_close(F_SRC);
	mf_close(F_DST);
	goto outt;

e_dst:
	mf_close(F_SRC);
e_src:
outt:
	return ret;
}
