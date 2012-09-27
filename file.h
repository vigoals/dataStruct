#ifndef FILE_H
#define FILE_H

enum
{
	F_SRC,
	F_RHUF,
	F_WHUF,
	F_DST
};

int mf_open(int fmode,char * fname);
int mf_close(int fmode);
unsigned char read_bit(int fmode);
unsigned char * read_byte(int fmode);
int write_bit(int fmode,unsigned char b);
int write_byte(int fmode,unsigned char *b);
int write_bytes(int fmode,void * buf,int size);
int read_bytes(int fmode,void * buf,int size);

#endif // FILE_H
