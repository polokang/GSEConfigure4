
/**************************************************************
* Copyright (c) 2011-2012, xdsac
* All rights reserved.
* Author : RenGuangYu
**************************************************************/

#ifndef _HIO_H
#define _HIO_H


/****************************************************************/
#ifdef	__cplusplus
extern "C"
{
#endif
typedef struct _hio_data{
        int 	sn;
        char 	desc[64];
        struct _hio_data *next;
}HIO_DATA;

	
typedef struct _hio_info{
 	HIO_DATA *hdi;
	HIO_DATA *hdo;
	HIO_DATA *gdi;
	HIO_DATA *gdo;
	HIO_DATA *hai;
        HIO_DATA *gao;	//Ä£Äâ³ö
}HIO_INFO;

extern HIO_INFO hioinfo;

int RD_Initialize(char *strHwCfgFile);
	
#ifdef	__cplusplus
}
#endif
#endif
