#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long byte_int(unsigned char *bytes)
{
	unsigned long  num = bytes[3] & 0xFF;
	num |= ((bytes[2] << 8) & 0xFF00);
	num |= ((bytes[1] << 16) & 0xFF0000);
	num |= ((bytes[0] << 24) & 0xFF000000);
	return num;
}

unsigned long GenerateCRC32(unsigned char *DataBuf, unsigned long len)
{
	unsigned char bSrc[4];
	unsigned   long crc;
	unsigned   long i, j;
	unsigned   long temp;
	crc = 0xFFFFFFFF;
	for (i = 0; i < len; i++)
	{
		memset(bSrc, 0x00, 4);

		if (i == len - 1)
		{
			if (DataBuf[i * 4] == 0xcd)
			{
				DataBuf[i * 4] = 0x00;
			}
			if (DataBuf[i * 4 + 1] == 0xcd)
			{
				DataBuf[i * 4 + 1] = 0x00;
			}
			if (DataBuf[i * 4 + 2] == 0xcd)
			{
				DataBuf[i * 4 + 2] = 0x00;
			}
			if (DataBuf[i * 4 + 3] == 0xcd)
			{
				DataBuf[i * 4 + 3] = 0x00;
			}
		}
		bSrc[0] = DataBuf[i * 4];
		bSrc[1] = DataBuf[i * 4 + 1];
		bSrc[2] = DataBuf[i * 4 + 2];
		bSrc[3] = DataBuf[i * 4 + 3];
		temp = byte_int(bSrc);


		for (j = 0; j < 32; j++)
		{
			if ((crc ^ temp) & 0x80000000)
			{
				crc = 0x04C11DB7 ^ (crc << 1);
			}
			else
			{
				crc <<= 1;
			}
			temp <<= 1;
		}
	}
	return crc;
}

int main(){
	FILE *fp;
	long fileLen = 0;
	unsigned char *filePtr = NULL;
	unsigned long crc32;
	if ((fp = fopen("AhanFu_VM601.020_20150823_00000000.bin", "rb")) != NULL){
		fseek(fp, 0L, SEEK_END);
		fileLen = ftell(fp);
		if (filePtr = (unsigned char *)malloc(fileLen + 1)){
			memset(filePtr, 0x00, fileLen);
			fseek(fp, 0L, SEEK_SET);
			fread(filePtr, fileLen, 1, fp);
			*(filePtr + fileLen) = 0;
			crc32 = GenerateCRC32(filePtr, fileLen % 4);
		}
	}
}
