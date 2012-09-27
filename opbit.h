#ifndef OPBIT_H
#define OPBIT_H

const static unsigned char bit_mask[]=
				{0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

static inline unsigned char
get_bit(unsigned char * buf,int posbyte,int posbit)
{
	return buf[posbyte]&bit_mask[posbit];
}

static inline void
set_bit(unsigned char * buf,int posbyte,int posbit)
{
	buf[posbyte]|=bit_mask[posbit];
}

static inline void
clr_bit(unsigned char * buf,int posbyte,int posbit)
{
	buf[posbyte]&=~bit_mask[posbit];
}

#endif // OPBIT_H
