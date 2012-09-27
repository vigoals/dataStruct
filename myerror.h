#ifndef MYERROR_H
#define MYERROR_H

enum
{
	E_SRC=1,
	E_HUF,
	E_DST
};

void myperror(int errnum);

#endif // MYERROR_H
