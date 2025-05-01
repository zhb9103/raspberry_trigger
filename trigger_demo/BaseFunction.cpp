/*
 * BaseFunction.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: Bill.Zhang
 */

#include "BaseFunction.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


unsigned int ConvertHexChar(char ch)
{
   if((ch>='0')&&(ch<='9'))
	   return ch-0x30;
   else if((ch>='A')&&(ch<='F'))
	   return ch-'A'+10;
   else if((ch>='a')&&(ch<='f'))
	   return ch-'a'+10;
   else return -1;
}


unsigned char hex2asc(const char *src)
{
  char temp=0;
  int templen=0;
  templen=strlen(src);
  if (templen==0)
    return 0;
  else if (templen==1)
  {
    temp=ConvertHexChar(src[0]);
  }
  else 
  { 
    if ((src[1]>='0' && src[1]<='9') || (src[1]>='a' && src[1]<='f') || (src[1]>='A' && src[1]<='F'))
    {
      temp=ConvertHexChar(src[0]);
      temp=(temp<<4)+ConvertHexChar(src[1]);
    }
    else 
    {
      temp=ConvertHexChar(src[0]);
    }
  }
  return temp;
}

unsigned char Ch2Hx(char chr)
{
  if((chr>='0')&&(chr<='9'))
  {
    return chr-'0';
  }
  else if((chr>='a')&&(chr<='f'))
  {
    return chr-'a'+10;
  }
  else
  {
    return chr-'A'+10;
  }
}

char  *Char2Hex(char *CharBuf,char *SwapBuf) 
{
  //char *P;
  memset(SwapBuf,0,3);
  sprintf(SwapBuf,"%02x",(unsigned char)CharBuf[0]);
  //P=SwapBuf;
  return SwapBuf;
}


unsigned char IsHexChar(char chr)
{
  char tempvar=0;

  if (((chr>='0')&&(chr<='9'))||((chr>='a')&&(chr<='f'))||((chr>='A')&&(chr<='F')))
  {
    tempvar=1;
  }
  else
  {
    tempvar=255;
  }
  return tempvar;
}


unsigned char IsHexString(char * str,unsigned int strlen)
{
  unsigned char tempvar=0;
  unsigned int tempcounter=0;
  for (unsigned int i=0;i<strlen;i++)
  {
    if (IsHexChar(*str++)==1)
    {
      tempcounter++;
    }
    else
    {
      break;
    }
  }
  if (strlen==tempcounter)
  {
    tempvar=1;
  }
  else
  {
    tempvar=255;
  }
  return tempvar;
}


unsigned short String2Decimal(char* str, unsigned char strlen)
{
  unsigned short tempvar=0;
  switch (strlen)
  {
  case 1:
    tempvar=str[0]-'0';
    break;
  case 2:
    tempvar=(str[0]-'0')*10+str[1]-'0';
    break;
  case 3:
    tempvar=(str[0]-'0')*100+(str[1]-'0')*10+str[2]-'0';
    break;
  case 4:
    tempvar=(str[0]-'0')*1000+(str[1]-'0')*100+(str[2]-'0')*10+str[3]-'0';
    break;
  case 0:
  default:
    tempvar=-1;
    break;
  }
  return tempvar;
}

unsigned char String2uint8(char* str, unsigned char strlen)
{
  unsigned short tempvar=0;
  switch (strlen)
  {
  case 1:
    tempvar=str[0]-'0';
    break;
  case 2:
    tempvar=(str[0]-'0')*10+str[1]-'0';
    break;
  case 3:
    tempvar=(str[0]-'0')*100+(str[1]-'0')*10+str[2]-'0';
    break;
  case 0:
  default:
    tempvar=-1;
    break;
  }
  return tempvar;
}

unsigned short String2uint16(char* str, unsigned char strlen)
{
  unsigned short tempvar=0;
  switch (strlen)
  {
  case 1:
    tempvar=str[0]-'0';
    break;
  case 2:
    tempvar=(str[0]-'0')*10+str[1]-'0';
    break;
  case 3:
    tempvar=(str[0]-'0')*100+(str[1]-'0')*10+str[2]-'0';
    break;
  case 4:
    tempvar=(str[0]-'0')*1000+(str[1]-'0')*100+(str[2]-'0')*10+str[3]-'0';
    break;
  case 0:
  default:
    tempvar=-1;
    break;
  }
  return tempvar;
}


unsigned char String2Hex(char* str, unsigned char strlen)
{
  unsigned char tempvar;
  switch (strlen)
  {
  case 1:
    tempvar=Ch2Hx(str[0]);
    break;
  case 2:
    tempvar=(Ch2Hx(str[0])<<4)|(Ch2Hx(str[1]));
    break;
  case 0:
  default:
    tempvar=-1;
    break;
  }
  return tempvar;
}



unsigned char String2Hex2(char* str, unsigned char strlen)
{
  unsigned char tempvar;
  switch (strlen)
  {
  case 1:
    tempvar=Ch2Hx(str[0]);
    break;
  case 2:
    tempvar=(Ch2Hx(str[0])<<4)|(Ch2Hx(str[1]));
    break;
  case 0:
  default:
    tempvar=-1;
    break;
  }
  return tempvar;
}


unsigned char String2Hex2reverse(char* str, unsigned char strlen)
{
  unsigned char tempvar;
  switch (strlen)
  {
  case 1:
    tempvar=Ch2Hx(str[0]);
    break;
  case 2:
    tempvar=(Ch2Hx(str[0]))|(Ch2Hx(str[1])<<4);
    break;
  case 0:
  default:
    tempvar=-1;
    break;
  }
  return tempvar;
}

unsigned short String2Hex4(char* str, unsigned char strlen)
{
  unsigned short tempvar;
  switch (strlen)
  {
  case 1:
    tempvar=Ch2Hx(str[0]);
    break;
  case 2:
    tempvar=(Ch2Hx(str[0])<<4)|(Ch2Hx(str[1]));
    break;
  case 3:
    tempvar=(Ch2Hx(str[0])<<8)|(Ch2Hx(str[1])<<4)|(Ch2Hx(str[2]));
    break;
  case 4:
    tempvar=(Ch2Hx(str[0])<<12)|(Ch2Hx(str[1])<<8)|(Ch2Hx(str[2])<<4)|(Ch2Hx(str[3]));
    break;    
  case 0:
  default:
    tempvar=-1;
    break;
  }
  return tempvar;
}

unsigned int String2Hex8(char* str, unsigned char strlen)
{
  unsigned int tempvar;
  switch (strlen)
  {
  case 1:
    tempvar=Ch2Hx(str[0]);
    break;
  case 2:
    tempvar=(Ch2Hx(str[0])<<4)|(Ch2Hx(str[1]));
    break;
  case 3:
    tempvar=(Ch2Hx(str[0])<<8)|(Ch2Hx(str[1])<<4)|(Ch2Hx(str[2]));
    break;
  case 4:
    tempvar=(Ch2Hx(str[0])<<12)|(Ch2Hx(str[1])<<8)|(Ch2Hx(str[2])<<4)|(Ch2Hx(str[3]));
    break;    
  case 5:
    tempvar=(Ch2Hx(str[0])<<16)|(Ch2Hx(str[1])<<12)|(Ch2Hx(str[2])<<8)|(Ch2Hx(str[3])<<4)|(Ch2Hx(str[4]));
    break;  
  case 6:
    tempvar=(Ch2Hx(str[0])<<20)|(Ch2Hx(str[1])<<16)|(Ch2Hx(str[2])<<12)|(Ch2Hx(str[3])<<8)|(Ch2Hx(str[4])<<4)|(Ch2Hx(str[5]));
    break;  
  case 7:
    tempvar=(Ch2Hx(str[0])<<24)|(Ch2Hx(str[1])<<20)|(Ch2Hx(str[2])<<16)|(Ch2Hx(str[3])<<12)|(Ch2Hx(str[4])<<8)|(Ch2Hx(str[5])<<4)|(Ch2Hx(str[6]));
    break;  
  case 8:
    tempvar=(Ch2Hx(str[0])<<28)|(Ch2Hx(str[1])<<24)|(Ch2Hx(str[2])<<20)|(Ch2Hx(str[3])<<16)|(Ch2Hx(str[4])<<12)|(Ch2Hx(str[5])<<8)|(Ch2Hx(str[6])<<4)|(Ch2Hx(str[7]));
    break;      
  case 0:
  default:
    tempvar=-1;
    break;
  }
  return tempvar;
}



unsigned char IsDecimalChar(char chr)
{
  char tempvar=0;

  if ((chr>='0')&&(chr<='9'))
  {
    tempvar=1;
  }
  else
  {
    tempvar=255;
  }
  return tempvar;
}

unsigned char IsDecimalString(char * str,unsigned int strlen)
{
  unsigned char tempvar=0;
  unsigned int tempcounter=0;
  for (unsigned int i=0;i<strlen;i++)
  {
    if (IsDecimalChar(*str++)==1)
    {
      tempcounter++;
    }
    else
    {
      break;
    }
  }
  if (strlen==tempcounter)
  {
    tempvar=1;
  }
  else
  {
    tempcounter=255;
  }
  return tempvar;
}




unsigned char CRC7(const unsigned char *chr,int cnt)
{
	int i,a;
	unsigned char crc,Data;
	crc=0;
	for (a=0;a<cnt;a++)
	{
		Data=chr[a];
		for(i=0;i<8;i++)
		{
			crc<<=1;
			if((Data & 0x80)^(crc & 0x80))
				crc ^= 0x09;
			Data <<= 1;
		}
	}
	crc=(crc<<1)|1;
	return crc;
}

/*
 * application for gen2crc;
 * unsigned short crcacctest=0xffff;
 * unsigned short i;
 * byte[] test_buffer=new byte[]{0x30.....};
 * for (i=0;i<14;i++)
 * {
 * 	crcacctest = CRCGEN2(crcacctest,test_buffer[i]);
 * }
 * crcacctest = (UINT16)~crcacctest;
 */
unsigned short CRCGEN2(unsigned short crcacc,unsigned short cword)
{
	// routing to calculate crc for 1 byte (lower 8 bits of cword);
	// initially, crcacc should have been set to 0xffff;
	unsigned short i;
	unsigned short xorval;
	for (i=0;i<8;i++)
	{
		xorval = (unsigned short)(((crcacc >>8)^(cword << i)) & 0x0080);
		crcacc = (unsigned short)((crcacc << 1) & 0xfffe);
		if(xorval != 0)
		{
			crcacc ^= 0x1021;
		}
	}
	return crcacc;
}

int indexofstring(char *str,int strlen,char chr)
{
	for (int i=0;i<strlen;i++)
	{
		if(str[i]==chr)
		{
			return i;
		}
	}
	return -1;
}

int indexofstring(char *str,char chr)
{
	return indexofstring(str,strlen(str),chr);
}

int stringSearchInStr(char *source, int sourcelen,char *target,int targetlen)
{
	int tempvar=0;
	if (sourcelen>=targetlen)
	{
		for (int i=0;i<(sourcelen-targetlen);i++)
		{
			if (memcmp(&source[i],target,targetlen)==0)
			{
				tempvar=i;
				break;
			}
		}
		if (tempvar>=(sourcelen-targetlen))
		{
			return -1;
		}
		return tempvar;
	}
	else
	{
		return -1;
	}
}


int strFirstPos(const char* str1, const char* str2)
{
	int pos=-1;
	int len2=strlen(str2);
	/*
	if(!(len2=strlen(str2)))
		return -1;
	*/
	for(;*str1;++str1)
	{
		pos++;
		if((*str1==*str2)&&(strncmp(str1,str2,len2)==0))
			return pos;
	}
	return -1;
}


unsigned char SrchStrFrmBuffer(const char * str,unsigned char strlen,const char *buffer,unsigned char bufferlen)
{
	// add code;
	unsigned char a=0;
	unsigned char b=0;
	unsigned char tempvar=0;
	unsigned char tempcounter=0;
	for (a=0;a<bufferlen-strlen;a++)
	{
		// simple search;
		if (buffer[a]==str[0])
		{
			for (b=1;b<strlen;b++)
			{
				if (buffer[a+b]==str[b])
				{
					tempcounter++;
				}
				else
				{
					//tempvar=255;
					//return tempvar;
				}
			}
			if (tempcounter!=strlen-1)
			{
					tempvar=255;
					return tempvar;				
			}
			tempvar=a;
			break;
		}
	}
	if (tempcounter==0)
	{
		tempvar=255;
		return tempvar;
	}
	else
	{
		return tempvar+1;
	}
}

unsigned char SrchStrFrmBffrFll(const char * str,unsigned char strlen,const char *buffer,unsigned char bufferlen)
{
	unsigned char a;
	unsigned char tempvar;
	for (a=0;a<bufferlen;a++)
	{
		if (bufferlen-a<strlen)
		{
			return 255;
		}
		tempvar=SrchStrFrmBuffer(str,strlen,&buffer[a],bufferlen-a);
		if (tempvar!=255)
		{
			return 1;
		}
	}
	return 255;
}

void StrRightTrim(char *pStr,const char trimChar)
{
	char *pTmp=pStr+strlen(pStr)-1;
	while(*pTmp==trimChar)
	{
		*pTmp='\0';
		pTmp--;
	}
}

void StrLeftTrim(char *pStr,const char trimChar)
{
	char *pTmp=pStr;
	while(*pTmp==trimChar)
	{
		pTmp++;
	}
	while(*pTmp!='\0')
	{
		*pStr=*pTmp;
		pStr++;
		pTmp++;
	}
	*pStr='\0';
}



