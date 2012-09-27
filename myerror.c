#include <stdio.h>
#include <gtk/gtk.h>
#include "myerror.h"

char * serr[]={"无错误",
				"源文件错误。",
				"哈夫曼文件错误。",
				"目标文件错误。",};

void myperror(int errnum)
{
	fprintf(stderr,"err:%s\n",serr[-errnum]);
}
