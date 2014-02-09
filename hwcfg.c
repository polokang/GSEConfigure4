/**************************************************************
* Copyright (c) 2011-2012, xdsac
* All rights reserved.
* Author : RenGuangYu
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
//#include "hwcfg.h"
#include "base.h"
#include "realdata.h"
#include "hio.h"


HIO_INFO hioinfo;

/***********************************************************************
* RD_Cfg_Resource - װ����Դ������Ŀ
* ���������Ŀ�Ƿ��г�ͻ
*
* RETURNS: 
*			FT_SUCCESS, ��������
*			FT_BUF_ERR, �ڴ����
*
***********************************************************************/
static int RD_Cfg_Resource(unsigned char *pucCfg, /* ϵͳ��Դ����ָ�� */
									   unsigned int ulLen		/* ���� */)
{
	RD_PART_INFO	*p_part;
	unsigned char	*puc;

	rdinfo_g.unPartNum = U8_TO_U16(pucCfg[1],pucCfg[0]);
	//��֧�������䣬����ȫ��֧��
	//if(pucCfg[2] != 0 || pucCfg[4] != 0)
	//{
	//	return -1;
	//}

        //rdinfo_g.b64KOptCh1 = t_FALSE;
        //rdinfo_g.b2MOptCh1 = t_FALSE;
        //rdinfo_g.b64KOptCh2 = t_FALSE;
        //rdinfo_g.b2MOptCh2 = t_FALSE;

	///* 3.36��Լ֧�� */
        //rdinfo_g.bSamePole = t_FALSE;
        //rdinfo_g.bHdlBox = t_FALSE;
        //rdinfo_g.bAssmDev_9_1 = t_FALSE;
        //rdinfo_g.bAssmDev_xn = t_FALSE;
        //rdinfo_g.bVirtBox = t_FALSE;

	//ϵͳ����(ϵͳƵ�ʡ����)
	//rdinfo_g.ucEnvType = pucCfg[3];
	//switch(pucCfg[3])
	//{
	//	case 0x00:
	//		uiPwrFreq_g = 50;
        //		bOneAmpSys_g = t_FALSE;
        //		bFiveAmpSys_g = t_TRUE;
	//		break;
	//	case 0x01:
	//		uiPwrFreq_g = 50;
        //		bOneAmpSys_g = t_TRUE;
        //		bFiveAmpSys_g = t_FALSE;
	//		break;
	//	case 0x80:
	//		uiPwrFreq_g = 50;
        //		bOneAmpSys_g = t_TRUE;
        //		bFiveAmpSys_g = t_TRUE;
	//		break;
	//	default:
	//		return -1;
	//}
	//ADģ������
	//DI/DOˢ������
	//�Ƿ�֧��˫CPU
	uiAppType_g = pucCfg[6];//Ӧ������
	puc = pucCfg + 8;

	for(p_part = apartinf_g; p_part < apartinf_g + rdinfo_g.unPartNum; p_part++)
	{
		uint8_t	ucTotalLength;
		uint8_t	ucaucIdLength;

		ucTotalLength = U8_TO_U16(puc[1],puc[0]);
		ucaucIdLength = puc[2];

		memset(p_part->aucId,0,MAX_ID_LEN + 1);
		memcpy(p_part->aucId,puc + 3,puc[2]);
		puc += puc[2] + 3;

		p_part->ucType = *puc++;
		p_part->ucPosition = *puc++;
		p_part->aucHwAddr[0] = *puc++;
		p_part->aucHwAddr[1] = *puc++;
		p_part->aucHwAddr[2] = *puc++;
		p_part->aucHwAddr[3] = *puc++;

		if(p_part->ucPosition == RD_VT_BOX)
		{
			p_part->iVtBoxSeqNo = *puc - 1;		/* serial number of the virtual box, begin from 0. */
			puc++;

			memcpy(p_part->aucVtBoxFd,puc + 1,puc[0]);
			puc += 1 + puc[0];

			p_part->iVtBoxAddrInSameKind = *puc - 1;		/* address of this kind. */
			puc++;
		}
		puc += 3;
		p_part->ucAoNum = *puc++;
		p_part->ucAiNum = *puc++;
		p_part->ucDiNum = *puc++;
		p_part->ucDoNum = *puc++;

		p_part->ulDIModCurVaule = 0;
		p_part->servertype = 0;

		puc += 2;
	}


	return 0;
}


/***********************************************************************
* RD_Cfg_DI - ����������Ŀ
*
* RETURNS: 
*			FT_SUCCESS, ��������
*			FT_BUF_ERR, �ڴ����
*
*/
static int RD_Cfg_DI(unsigned char *pucCfg, /* ϵͳ��Դ����ָ�� */
							   unsigned int ulLen		/* ���� */)
{
	RD_LGC_DI_CH *pch;
	uint8_t		*puc;
	RD_PART_INFO *p_part; 
	int			iChCfgLen;
	uint8_t		aucModId[MAX_ID_LEN + 1];

	iLgcDiChNum_g = U8_TO_U16(pucCfg[1],pucCfg[0]); 
	if((plgcdich_g = calloc(iLgcDiChNum_g,sizeof(*plgcdich_g))) == NULL)
	{
		return -1;
	}

	/* Skip DICount and reserved 4 bytes. */
	puc = pucCfg + 6; 		
	for(pch = plgcdich_g; pch < plgcdich_g + iLgcDiChNum_g; pch++)
	{
		iChCfgLen = U8_TO_U16(puc[1],puc[0]);  

		iChCfgLen -= puc[2];
		memcpy(pch->aucId,puc + 3,puc[2]);  
		puc += 3 + puc[2];

		pch->unLgcSN = U8_TO_U16(puc[1],puc[0])+1;  
		puc += 2;

		iChCfgLen -= puc[0];
		memcpy(pch->aucName,puc + 1,puc[0]);  
		puc += 1 + puc[0];

		pch->aucABRV[0] = *puc++;	/* �ڲ���� */
		pch->aucABRV[1] = *puc++;
		pch->aucABRV[2] = *puc++;
		pch->aucABRV[3] = *puc++;

		pch->ulFiltTime = BYTES_TO_U32(puc) * 1000;		/* ȥ����ʱ�䣬ת��Ϊus */ 
		puc += 4;
		pch->ReserveAttribute = *puc++;		/* �Ƿ�����ƽ̨ʹ�� */

		/* ���DI��Чʱ��ȱʡֵ */
		/* puc++; */
		if((*puc++) == 0)
		{
                        pch->bDIInvalidDftVal = t_FALSE;
		}
		else
		{
                        pch->bDIInvalidDftVal = t_TRUE;
		}
		pch->ucMmiShow = *puc++;				/* �Ƿ���ʾ */
		puc += 5;								/* ���� */
		pch->ucDIRefreshRate = puc[0];			/* ˢ������ */ 
		puc++;
		iChCfgLen -= puc[0];
		memcpy(aucModId,puc + 1,puc[0]);  
		aucModId[puc[0]] = '\0';
		puc += 1 + puc[0];

		for(p_part = apartinf_g; p_part < apartinf_g + MAX_PART_NUM; p_part++)
		{
			if(!strcmp((char *)p_part->aucId,(char *)aucModId))
			{
				break;
			}
		}
		
		//assert(p_part < apartinf_g + MAX_PART_NUM);  
		pch->p_part = p_part;  
#if 0
		if(p_part->ucPosition != 0)			/* ������ */
		{
			return -1;
		}
#endif
		
		pch->mod = RD_SPI_DI;	/* ������ */
		pch->ucModCh = *puc++;	/* ��������ģ����� */ 
		pch->bRec = *puc++; 
		//¼������
		if(pch->bRec)
		{
			iChCfgLen -= 1 + puc[0];
			memcpy(pch->aucRecId,puc + 1,puc[0]);
			puc += 1 + puc[0];
		}
		//��־����
		pch->bFlag = *puc++;
		if(pch->bFlag)
		{
			iChCfgLen -= 1 + puc[0];
			memcpy(pch->aucFlagId,puc + 1,puc[0]);
			puc += 1 + puc[0];
		}
		//ң������
		pch->bMea = *puc++;  
		if(pch->bMea)
		{
			iChCfgLen -= 1 + puc[0];
			memcpy(pch->aucMeaId,puc + 1,puc[0]);
			puc += 1 + puc[0];
		}
		pch->iMeaCh = -1;
	}
	if(puc - pucCfg != ulLen)
	{
		return -1;
	}
	return 0;
}


/***********************************************************************
	RD_Cfg_DO - ����������Ŀ
		����ָ�� 
		����
	RETURNS: 
			EP_SUCCESS, ��������
			EP_BUF_ERR, �ڴ����

***********************************************************************/
static int RD_Cfg_DO(uint8_t *pucCfg, uint32_t ulLen)
{
	RD_LGC_DO_CH *pch;
	RD_PART_INFO *p_part;
	int			iChCfgLen;
	uint8_t		*puc;
	uint8_t		aucModId[MAX_ID_LEN + 1];

	iLgcDoChNum_g = U8_TO_U16(pucCfg[1],pucCfg[0]);
	if((plgcdoch_g = calloc(iLgcDoChNum_g,sizeof(*plgcdoch_g))) == NULL)
	{
		return -1;
	}

	puc = pucCfg + 6;   					/* Skip DOCount and reserved 4 bytes. */

	for(pch = plgcdoch_g; pch < plgcdoch_g + iLgcDoChNum_g; pch++)
	{
		iChCfgLen = U8_TO_U16(puc[1],puc[0]);

		iChCfgLen -= puc[2];
		memset(pch->aucId,0,MAX_ID_LEN + 1);
		memcpy(pch->aucId,puc + 3,puc[2]);
		puc += 3 + puc[2];

		pch->unLgcSN = U8_TO_U16(puc[1],puc[0])+1;
		puc += 2;

		iChCfgLen -= puc[0];
		memset(pch->aucName,0,MAX_ID_LEN + 1);
		memcpy(pch->aucName,puc + 1,puc[0]);
		puc += 1 + puc[0];

		pch->aucABRV[0] = *puc++;
		pch->aucABRV[1] = *puc++;
		pch->aucABRV[2] = *puc++;
		pch->aucABRV[3] = *puc++;

		pch->ReserveAttribute = *puc++;		/* �Ƿ�����ƽ̨ʹ�� */
		pch->ucMmiShow = *puc++;		/* �Ƿ���ʾ */

		puc += 2;

		iChCfgLen -= puc[0];
		memset(aucModId,0,MAX_ID_LEN + 1);
		memcpy(aucModId,puc + 1,puc[0]);
		puc += 1 + puc[0];

		for(p_part = apartinf_g; p_part < apartinf_g + MAX_PART_NUM; p_part++)
		{
			if(!strcmp((char *)p_part->aucId,(char *)aucModId))
			{
				break;
			}
		}

		assert(p_part < apartinf_g + MAX_PART_NUM);

		pch->p_part = p_part;
		/*
				if (p_part->ucPosition == 0)
				{
					puc += 7;
					continue;
					return FT_CFG_ERR;
				}
		*/
		pch->mod = RD_SPI_DO;
		pch->ucModCh = *puc++;
		pch->bValid = *puc++;		/* �Ƿ���Ч */
		puc += 5;					/* ���� */

		assert(iChCfgLen == 20);
                pch->bVal = t_FALSE;
		pch->iTripDOCnt = 0;
	}

	if(puc - pucCfg != ulLen)
	{
                assert(t_FALSE);
		return -1;
	}
	return 0;
}

/***********************************************************************
* RD_Cfg_Hw_AI - ģ������Ӳ��ͨ��������Ŀ
*
* RETURNS: 
*			EP_SUCCESS, ��������
*			EP_BUF_ERR, �ڴ����
*
*/
static int RD_Cfg_Hw_AI(uint8_t *pucCfg, uint32_t ulLen)
{
	RD_PART_INFO *p_part;
	RD_HW_AI_CH	*pch;
	int			iChCfgLen;
	int			i;
	uint8_t		*puc;
	uint8_t		aucModId[MAX_ID_LEN + 1];

	iHwAiChNum_g = U8_TO_U16(pucCfg[1],pucCfg[0]);
	if((phwaich_g = calloc(iHwAiChNum_g,sizeof(*phwaich_g))) == NULL)
	{
		return -1;
	}

	puc = pucCfg + 6;
	for(i = 0; i < iHwAiChNum_g; i++)
	{
		iChCfgLen = U8_TO_U16(puc[1],puc[0]);

		pch = phwaich_g + puc[7 + puc[2]];

		/* Never used before. */
		assert(pch->aucId[0] == '\0');

		iChCfgLen -= puc[2];
		memcpy(pch->aucId,puc + 3,puc[2]);

		puc += 3 + puc[2];
		pch->aucABRV[0] = *puc++;
		pch->aucABRV[1] = *puc++;
		pch->aucABRV[2] = *puc++;
		pch->aucABRV[3] = *puc++;

		puc++;

		pch->fMaxVal = BYTES_TO_FLT(puc);
		puc += 4;

		pch->fMinVal = BYTES_TO_FLT(puc);
		puc += 4;

		pch->FactorSetModWord = *puc++;		 /* ���÷�ʽ������ */
		if((pch->FactorSetModWord) & 0x01)
		{
			iChCfgLen -= puc[0];
			iChCfgLen--;										/* ����ǰ��Լ��һ��*/
			memcpy(pch->MaxValueDingzhiTagBase,puc + 1,puc[0]);	/* ���ֵ�ڲ���ֵ�߼���־�ַ��� */
			puc += 1 + puc[0];
		}
		if((pch->FactorSetModWord) & 0x02)
		{
			iChCfgLen -= puc[0];
			iChCfgLen--;
			memcpy(pch->MinValueDingzhiTagBase,puc + 1,puc[0]);				/* ��Сֵ�ڲ���ֵ�߼���־�ַ��� */
			puc += 1 + puc[0];
		}
		if((pch->FactorSetModWord) & 0x04)
		{
			iChCfgLen -= puc[0];
			iChCfgLen--;
			memcpy(pch->ScalefactorDingzhiTagBase,puc + 1,puc[0]);					/* ��Сֵ�ڲ���ֵ�߼���־�ַ��� */
			puc += 1 + puc[0];
		}

		pch->bSetAo = *puc++; 
		if(pch->bSetAo)
		{
			iChCfgLen -= puc[0];
			iChCfgLen--;
			memcpy(pch->aucAoLogicId,puc + 1,puc[0]);					/* AO�߼���־�ַ��� */
			puc += 1 + puc[0];
		}

		puc += 1;		/* ���� */
		pch->ucMmiShow = *puc++;

		puc += 1;

		iChCfgLen -= puc[0];
		memset(aucModId,0,MAX_ID_LEN + 1);
		memcpy(aucModId,puc + 1,puc[0]);
		puc += 1 + puc[0];
		for(p_part = apartinf_g; p_part < apartinf_g + MAX_PART_NUM; p_part++)
		{
			/* logMsg("p_part->ucType = %d p_part->aucHwAddr[0] = %d\n",p_part->ucType,p_part->aucHwAddr[0],0,0,0,0); */
			if(!strcmp((char *)p_part->aucId,(char *)aucModId))
			{
				break;
			}
		}
		assert(p_part < apartinf_g + MAX_PART_NUM);

		pch->p_part = p_part;
#if 0
		if (p_part->ucPosition == 0)
		{
			pch->paimod = &aimodDsp_g;/*���ػ���*/
		}
#endif
		pch->ucModCh = *puc++;

		pch->fGain = 1.0;   			  /* If no gain file, use this. */
		pch->fExcCoff = 0.0;				/* If no gain file, use this */
		pch->fRatio = 1.0;  			  /* If no CT ratio file, use this. */
		pch->fCoff = BYTES_TO_FLT(puc);
		pch->fOriginCoff = pch->fCoff;		/* ԭʼ */
		pch->fSetCoff = pch->fCoff;		/* �趨ϵ�� */
		puc += 4;

		pch->ucUnit = *puc++;

		/* �µ�ʵ�� */
		if(puc[0] == 1)
		{
                        pch->bSetOptAo = t_TRUE;
			puc++;
			iChCfgLen = iChCfgLen - 1 - puc[0]; 						  /* ���ù��ݱ�־��Ϊ�����޸ģ�2006-2-8 */
			memcpy(pch->aucAoId,puc + 1,puc[0]);
			puc += 1 + puc[0];
		}
		else if(puc[0] == 0)
		{
                        pch->bSetOptAo = t_FALSE;
			puc++;
		}
		else
		{
                        assert(t_FALSE);
		}
		assert(iChCfgLen == 27);		/* ˥�����油�����䶨ֵʱΪ27 DY 12/19/2006 */
	}

	if(puc - pucCfg != ulLen)
	{
                assert(t_FALSE);
		return -1;
	}

	return 0;
}

/***********************************************************************
* RD_Cfg_Lgc_AI - ģ�������߼�ͨ��������Ŀ
*
* RETURNS: 
*			EP_SUCCESS, ��������
*			EP_BUF_ERR, �ڴ����
*
***********************************************************************/
static int RD_Cfg_Lgc_AI(uint8_t *pucCfg, uint32_t ulLen)
{
	RD_LGC_AI_CH *pch;
	int			iChCfgLen;
	uint8_t		*puc;

	iLgcAiChNum_g = U8_TO_U16(pucCfg[1],pucCfg[0]);			/* Virtual AI belongs to logic AI. */
	if((plgcaich_g = calloc(iLgcAiChNum_g,sizeof(*plgcaich_g))) == NULL)
	{
		return -1;
	}

	puc = pucCfg + 6;   					/* Skip AICount and reserved 4 bytes. */
	for(pch = plgcaich_g; pch < plgcaich_g + iLgcAiChNum_g; pch++)
	{
		iChCfgLen = U8_TO_U16(puc[1],puc[0]);

		iChCfgLen -= puc[2];
		memcpy(pch->aucId,puc + 3,puc[2]);
		puc += 3 + puc[2];

		pch->unLgcSN = U8_TO_U16(puc[1],puc[0])+1;

		puc += 2;
		puc += 3;   					  /* Skip reserved 4 bytes. */

		if(puc[0] == 1)
		{
                        pch->bSetAo = t_TRUE;
			puc++;
			iChCfgLen = iChCfgLen - 1 - puc[0]; 			/* ����AO��־ */
			memcpy(pch->aucAoId,puc + 1,puc[0]);
			puc += 1 + puc[0];
		}
		else if(puc[0] == 0)
		{
                        pch->bSetAo = t_FALSE;
			puc++;
		}
		else
		{
                        assert(t_FALSE);
		}

		assert(puc[0] < iHwAiChNum_g && phwaich_g);
		pch->phwai = phwaich_g + *puc++;

		pch->ucFiltTp = *puc++;
		pch->ucUnit = *puc++;

		pch->bRec = *puc++;
		if(pch->bRec)
		{
			iChCfgLen -= 1 + puc[0];
			memcpy(pch->aucRecId,puc + 1,puc[0]);
			puc += 1 + puc[0];
		}

		pch->bFlag = *puc++;
		if(pch->bFlag)
		{
			iChCfgLen -= 1 + puc[0];
			memcpy(pch->aucFlagId,puc + 1,puc[0]);
			puc += 1 + puc[0];
		}

		pch->bMea = *puc++;
		if(pch->bMea)
		{
			iChCfgLen -= 1 + puc[0];
			memcpy(pch->aucMeaId,puc + 1,puc[0]);
			puc += 1 + puc[0];
		}

		assert(iChCfgLen == 13);
	}

	if(puc - pucCfg != ulLen)
	{
                assert(t_FALSE);
		return -1;
	}

	return 0;
}

/***********************************************************************
* RD_Cfg_AO - AO��������ý���
*
* RETURNS: ��
*
***********************************************************************/
static int RD_Cfg_AO(uint8_t *pucCfg, uint32_t ulLen)
{
	RD_PART_INFO *p_part;
	RD_HW_AO_CH	*pch;
	int			iChCfgLen;
	int			i;
	uint8_t		*puc;
	uint8_t		aucModId[MAX_ID_LEN + 1];
	int			iIdStrLen;
	int			iNameStrLen;
	int			iAONum;
        //t_BOOL			bInitVtBoxAOCfg[MAX_VT_BOX_COUNT] ={t_FALSE};

	iHwAoChNum_g = U8_TO_U16(pucCfg[1],pucCfg[0]); /* AO�������� */
	if((phwaoch_g = calloc(iHwAoChNum_g,sizeof(*phwaoch_g))) == NULL)
	{
		return -1;
	}

	puc = pucCfg + 6;
	for(i = 0; i < iHwAoChNum_g; i++)
	{
		iChCfgLen = U8_TO_U16(puc[1],puc[0]);

		iIdStrLen = puc[2]; 					/* AO�߼���־�ַ������� */
		iNameStrLen = puc[3 + iIdStrLen];   	/* �ڲ������ַ������� */
		iAONum = puc[8 + iIdStrLen + iNameStrLen]; 	/* ����ͨ�����е���� */
		pch = phwaoch_g + iAONum;
		pch->unLgcSN = iAONum+1;
		
		assert(pch->aucId[0] == '\0');				 /* Never used before. */

		iChCfgLen -= puc[2];
		memcpy(pch->aucId,puc + 3,puc[2]);
		puc += 3 + puc[2];

		iChCfgLen -= puc[0];
		memcpy(pch->aucName,puc + 1,puc[0]);
		puc += 1 + puc[0];

		pch->aucABRV[0] = *puc++;  /* �ڲ���� */
		pch->aucABRV[1] = *puc++;
		pch->aucABRV[2] = *puc++;
		pch->aucABRV[3] = *puc++;

		puc++;

		pch->fMaxVal = BYTES_TO_FLT(puc); /* �������ֵ*/
		puc += 4;

		pch->fMinVal = BYTES_TO_FLT(puc);		/* ������Сֵ*/

		puc += 4;

		pch->FactorSetModWord = *puc++;		 /* ���÷�ʽ������ */
		if((pch->FactorSetModWord) & 0x01)
		{
			iChCfgLen -= puc[0];
			iChCfgLen--;		/* ����ǰ��Լ��һ��*/
			memcpy(pch->MaxValueDingzhiTagBase,puc + 1,puc[0]);			/* ���ֵ�ڲ���ֵ�߼���־�ַ��� */
			puc += 1 + puc[0];
		}
		if((pch->FactorSetModWord) & 0x02)
		{
			iChCfgLen -= puc[0];
			iChCfgLen--;
			memcpy(pch->MinValueDingzhiTagBase,puc + 1,puc[0]);				/* ��Сֵ�ڲ���ֵ�߼���־�ַ��� */
			puc += 1 + puc[0];
		}
		if((pch->FactorSetModWord) & 0x04)
		{
			iChCfgLen -= puc[0];
			iChCfgLen--;
			memcpy(pch->ScalefactorDingzhiTagBase,puc + 1,puc[0]);					/* ��Сֵ�ڲ���ֵ�߼���־�ַ��� */
			puc += 1 + puc[0];
		}

		pch->ucAttr = *puc++;		/* ˢ���ٶ� */
		puc += 1;
		if(*puc++)
		{
			/* �Ƿ�AO����Դ */
			iChCfgLen -= puc[0];
			iChCfgLen--;
			memcpy(pch->aucSrcId,puc + 1,puc[0]);					/* ��Сֵ�ڲ���ֵ�߼���־�ַ��� */
			puc += 1 + puc[0];	

			pch->ucSrcType = *puc++;		/* ȡֵ�㷨���� */
			iChCfgLen--;
		}

		pch->ucOptAOOutputIntv = *puc++;		/* ����������ͼ�����Բ�����Ϊ��λ */

		iChCfgLen -= puc[0];
		memset(aucModId,0,MAX_ID_LEN + 1);
		memcpy(aucModId,puc + 1,puc[0]);  /* ��������ģ����־�ַ��� */
		puc += 1 + puc[0]; /* Խ����־�ַ��� */

		for(p_part = apartinf_g; p_part < apartinf_g + MAX_PART_NUM; p_part++)
		{
			/* Ѱ����������ģ�� */
			if(!strcmp((char *)p_part->aucId,(char *)aucModId)) 				/* aucModIdΪ��������ģ����־�ַ��� */
			{
				break;
			}
		}
		assert(p_part < apartinf_g + MAX_PART_NUM);
		pch->p_part = p_part;

		pch->ucModCh = *puc++; 				/* ������ģ���е����*/
		pch->fOriCoff = BYTES_TO_FLT(puc);
		pch->fCoff = pch->fOriCoff; 		/* ͨ������ϵ�� */
		pch->fSetCoff = pch->fOriCoff;		/* �趨ϵ�� */
		puc += 4;

		pch->ucUnit = *puc++;  				/* ����ͨ�����ݵ�λ */
		pch->iAOSrcType = 0;//DA_VOID_SRC; 		/* ������Դ���� */
		pch->pvSrc = NULL; 					/* ������Դ�ص� */
	}
	if(puc - pucCfg != ulLen)
	{
                assert(t_FALSE);
		return -1;
	}

	return 0;
}
/***********************************************************************
* RD_Deal_Cfg_Item - ��������
*
* RETURNS: 
*			FT_SUCCESS, ��������
*			FT_BUF_ERR, �ڴ����
*
*/
static int RD_Deal_Cfg_Item(unsigned char *pucDat, unsigned int ulBufLen, unsigned char ucType)
{
	int	ret;

	if(pucDat == NULL || ulBufLen <= 0)
	{
		return -1;
	}

	switch(ucType)
	{
		case 0:
			ret = RD_Cfg_Resource(pucDat,ulBufLen);
			printf("Resource %d\n",ret);
			break;
		case 1:
			ret = RD_Cfg_Hw_AI(pucDat,ulBufLen);
			printf("HW AI %d\n",ret);
			break;
		case 2:
			ret = RD_Cfg_Lgc_AI(pucDat,ulBufLen);
			printf("LGC AI %d\n",ret);
			break;
		case 3:
			ret = RD_Cfg_DI(pucDat,ulBufLen);
			printf("DI %d\n",ret);
			break;
		case 4:
			ret = RD_Cfg_DO(pucDat,ulBufLen);
			printf("DO %d\n",ret);
			break;
		case 5:
			ret = 0;
			break;
		case 6:
			ret = 0;
			break;
		case 7:
			ret = 0;
			break;
		case 8:
			ret = 0;
			break;
		case 9:
			ret = RD_Cfg_AO(pucDat,ulBufLen);
			printf("AO %d\n",ret);
			break;
		case 0xa:
			ret = 0;
			break;
		case 0xb:
			ret = 0;
			break;
		default:
			ret = -1;
	}

	return ret;
}

/***********************************************************************
* RD_Initialize - ��ʼ������ʵʱ����ģ��
* strHwCfgFile Ӳ�������ļ����� 
*
* RETURNS: 
*		  FT_SUCCESS, ��������
*		  FT_BUF_ERR, �ڴ����
*			
***********************************************************************/
int RD_Initialize(char *strHwCfgFile)
{
	int				stsRet = 0;
	int				fd,pos = -1;
	int				i, ul, itemNum;
	unsigned short	hwVer;
	unsigned char	aucBuf[100];
	unsigned char	ucType;
	unsigned char	*pucDat;
	unsigned int	ulLen, ulBufLen;
	//RD_HW_CFG_ITEM HwConfItem;

	if((fd = open(strHwCfgFile,O_RDONLY|O_BINARY,0)) <= 0)
	{
		stsRet = -1;
		return stsRet;
	}
#if 0
	if (read(fd,aucBuf,12) != 12 || aucBuf[11]!=0x01)
	{
		close(fd);
		stsRet = FT_CFG_ERR;
		return stsRet;
	}
	
	//����ļ�β��
	lseek(fd,-6,SEEK_END);
	pos = -6;

	if (read(fd,aucBuf,4) != 4 || aucBuf[0] != 0x14 
		|| aucBuf[1] != 0 || aucBuf[2] != 0 || aucBuf[3] != 0xEB)
	{
		close(fd);
		stsRet = FT_CFG_ERR;
		return stsRet;
	}
#endif
	//�ļ�ͷ���
	lseek(fd,0,SEEK_SET);
	pos = 0;
	if(read(fd,aucBuf,8) != 8 || aucBuf[0] != 0x11 || aucBuf[1] != 0 || aucBuf[2] != 0 || aucBuf[3] != 0xEE)
	{
		close(fd);
		stsRet = -1;
		return stsRet;
	}
	//Ӳ�����ð汾���߼�ͼ���ð汾���
	hwVer = U8_TO_U16(aucBuf[5],aucBuf[4]);
	if(0)
	{
		close(fd);
		stsRet = -1;
		return stsRet;
	}

	if(read(fd,aucBuf,4) != 4)
	{
		close(fd);
		stsRet = -1;
		return stsRet;
	}
	
	pos = 12;
	//��Ŀ���ø���
	itemNum = aucBuf[0];
	/* Ӳ�����ð汾�� */
	//appHwConfVer = U8_TO_U16(aucBuf[2],aucBuf[1]); 
	for(i = 0; i < itemNum; i++)
	{
		ul = read(fd,aucBuf,5);
		if(ul != 5)
		{
			close(fd);
			printf("step 1\n");
			stsRet = -1;
			return stsRet;
		}
		pos += ul;
		ucType = aucBuf[0];	//����
		ulBufLen = BYTES_TO_U32(aucBuf + 1);  //���� 
		if((pucDat = (unsigned char*)malloc(ulBufLen)) == NULL)
		{
			close(fd);
			printf("step 2\n");
			stsRet = -1;
			return stsRet;
		}
		ulLen = read(fd,pucDat,ulBufLen);	//������ 
		if(ulLen != ulBufLen)
		{
			close(fd);
			printf("ulLen %d ulBufLen %d\n",ulLen,ulBufLen);
			printf("step 3\n");
			stsRet = -1;
			return stsRet;
		}
		pos += ulLen;
		//������Ŀ
		if(RD_Deal_Cfg_Item(pucDat,ulBufLen,ucType) != 0)
		{
			free(pucDat);
			pucDat = NULL;
			close(fd);
			return -1;
		}

		free(pucDat);
		pucDat = NULL;
	}	
	RD_data_trans();
        //return &hioinfo;
        return stsRet;
}


/*************************************************************/
void show_io(HIO_DATA *da)
{
	HIO_DATA *sda = da;
	printf("*********************************************\n");
	while(sda)
	{
		printf("%02d    %s",sda->sn,sda->desc);
		sda = sda->next;
	}
}



void RD_data_trans()
{
    int i,j;
	RD_LGC_DI_CH 	*plgcdi;
	RD_LGC_DO_CH 	*plgcdo;
	RD_LGC_AI_CH 	*plgcai;
	RD_HW_AO_CH 	*phwao;
	HIO_DATA 			*hda,*phda = NULL;
	HIO_DATA 			*gda,*pgda = NULL;

        i = 0;
        j = 0;
	for(plgcdi = plgcdich_g;plgcdi < plgcdich_g+iLgcDiChNum_g;plgcdi++)
	{
		if(plgcdi->p_part->ucPosition == 0x0a)
		{
			gda = (HIO_DATA *)malloc(sizeof(HIO_DATA));
                        gda->sn = ++i;//plgcdi->unLgcSN;
			sprintf(gda->desc,"%s\n",plgcdi->aucName);
			gda->next = NULL;
			if(hioinfo.gdi==NULL)
			{
				hioinfo.gdi = gda;
			}else
			{
				pgda->next = gda;
			}
			pgda = gda;
			
		}else
		{
			hda = (HIO_DATA *)malloc(sizeof(HIO_DATA));
                        hda->sn = ++j;//plgcdi->unLgcSN;
			sprintf(hda->desc,"%s\n",plgcdi->aucName);
			hda->next = NULL;
			if(hioinfo.hdi==NULL)
			{
				hioinfo.hdi = hda;
			}else
			{
				phda->next = hda;
			}
			phda = hda;
		}
	}
	
        i = 0;
        j = 0;
	for(plgcdo = plgcdoch_g;plgcdo < plgcdoch_g+iLgcDoChNum_g;plgcdo++)
	{
		if(plgcdo->p_part->ucPosition == 0x0a)
		{
			gda = (HIO_DATA *)malloc(sizeof(HIO_DATA));
                        gda->sn = ++i;//plgcdo->unLgcSN;
			sprintf(gda->desc,"%s\n",plgcdo->aucName);
			gda->next = NULL;
			if(hioinfo.gdo==NULL)
			{
				hioinfo.gdo = gda;
			}else
			{
				pgda->next = gda;
			}
			pgda = gda;
			
		}else
		{
			hda = (HIO_DATA *)malloc(sizeof(HIO_DATA));
                        hda->sn = ++j;//plgcdo->unLgcSN;
			sprintf(hda->desc,"%s\n",plgcdo->aucName);
			hda->next = NULL;
			if(hioinfo.hdo==NULL)
			{
				hioinfo.hdo = hda;
			}else
			{
				phda->next = hda;
			}
			phda = hda;
		}
	}
	
	for(plgcai = plgcaich_g;plgcai < plgcaich_g+iLgcAiChNum_g;plgcai++)
	{
		hda = (HIO_DATA *)malloc(sizeof(HIO_DATA));
		hda->sn = plgcai->unLgcSN;
		sprintf(hda->desc,"%s\n",plgcai->aucId);
		hda->next = NULL;
		if(hioinfo.hai==NULL)
		{
			hioinfo.hai = hda;
		}else
		{
			phda->next = hda;
		}
		phda = hda;
	}
        i = 0;
	for(phwao = phwaoch_g;phwao < phwaoch_g+iHwAoChNum_g;phwao++)
	{
		gda = (HIO_DATA *)malloc(sizeof(HIO_DATA));
                gda->sn = ++i;//phwao->unLgcSN;
		sprintf(gda->desc,"%s\n",phwao->aucId);
		gda->next = NULL;
		if(hioinfo.gao==NULL)
		{
			hioinfo.gao = gda;
		}else
		{
			pgda->next = gda;
		}
		pgda = gda;
	}
	
//        show_io(hioinfo.hdi);
//        show_io(hioinfo.hdo);
//        show_io(hioinfo.gdi);
//        show_io(hioinfo.gdo);
//        show_io(hioinfo.hai);
//        show_io(hioinfo.gao);
	
}

