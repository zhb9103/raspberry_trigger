/*
 * BaseFunction.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Bill.Zhang
 */



#ifndef __BASEFUNCTION_H__
#define __BASEFUNCTION_H__






unsigned int ConvertHexChar(char ch);

unsigned char hex2asc(const char *src);

unsigned char Ch2Hx(char chr);

char  *Char2Hex(char *CharBuf,char *SwapBuf) ;

unsigned char IsHexChar(char chr);

unsigned char IsHexString(char * str,unsigned int strlen);

unsigned short String2Decimal(char* str, unsigned char strlen);

unsigned char String2uint8(char* str, unsigned char strlen);

unsigned short String2uint16(char* str, unsigned char strlen);

unsigned char String2Hex(char* str, unsigned char strlen);

unsigned char String2Hex2(char* str, unsigned char strlen);

unsigned char String2Hex2reverse(char* str, unsigned char strlen);

unsigned short String2Hex4(char* str, unsigned char strlen);

unsigned int String2Hex8(char* str, unsigned char strlen);

unsigned char IsDecimalChar(char chr);

unsigned char IsDecimalString(char * str,unsigned int strlen);


unsigned char CRC7(const unsigned char *chr,int cnt);

unsigned short CRCGEN2(unsigned short crcacc,unsigned short cword);

int indexofstring(char *str,int strlen,char chr);

int indexofstring(char *str,char chr);

int stringSearchInStr(char *source, int sourcelen,char *target,int targetlen);

int strFirstPos(const char* str1, const char* str2);

unsigned char SrchStrFrmBuffer(const char * str,unsigned char strlen,const char *buffer,unsigned char bufferlen);

unsigned char SrchStrFrmBffrFll(const char * str,unsigned char strlen,const char *buffer,unsigned char bufferlen);

void StrRightTrim(char *pStr,const char trimChar);

void StrLeftTrim(char *pStr,const char trimChar);








#endif

// file end;

















