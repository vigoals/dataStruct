#include <stdio.h>
#include <gtk/gtk.h>
#include "myerror.h"

char * serr[]={"�޴���",
				"Դ�ļ�����",
				"�������ļ�����",
				"Ŀ���ļ�����",};

void myperror(int errnum)
{
	fprintf(stderr,"err:%s\n",serr[-errnum]);
}
