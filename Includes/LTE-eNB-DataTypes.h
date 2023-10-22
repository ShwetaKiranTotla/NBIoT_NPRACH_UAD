/******************************************************************************
* Copyright   : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company     : Lekha Wireless Solutions Pvt. Ltd.
* File Name   : LTE_eNB_DataTypes.h
* Description : Typedef declarations
* Comments    :
******************************************************************************/

#ifndef __LTE_ENB_DATATYPES_H
#define __LTE_ENB_DATATYPES_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define BITS_IN_BYTE 8

#define MODE_FDD      1
#define MODE_TDD      0

#define FALSE 0
#define TRUE 1


typedef enum
{
    BOOL_FALSE = 0,
    BOOL_TRUE
}boolean;
typedef boolean BOOL;
typedef enum
{
    RC_SUCCESS,
    RC_PENDING,
    RC_FAILURE,
    RC_DUPLICATE,
    RC_ERROR,
    RC_ERROR_MEM,
    RC_ERROR_NOT_FOUND,
    RC_ERROR_DENIED,
    RC_ERROR_ALLOC,
    RC_ERROR_INPUT,
    RC_ERROR_FULL,
    RC_ERROR_EMPTY
}RC_t;


#define CLI_MAX_NUM_DL_UE               32
#define CLI_MAX_NUM_UL_UE               16
#define CLI_MAX_NUM_FRAMES              16
#define CLI_TTI_PER_FRAMES              10


typedef char CHAR_t;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef signed char INT8;
typedef signed char SINT8;
typedef signed short INT16;
typedef signed short SINT16;
typedef unsigned long long UINT64;
typedef signed long long INT64;
typedef signed long long SINT64;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned int UINT32;
typedef signed int INT32;
typedef UINT64 POINTER_t;
typedef unsigned int WORD_t;
typedef unsigned long long Key_t;
typedef void * taskId_t;

#if 1

typedef struct // _CPLX8
{
    INT8 imag;
    INT8 real;
} CPLX8;

typedef struct // _CPLX16
{
    INT16 imag;
    INT16 real;

} CPLX16;

typedef struct // _CPLX32
{
    INT32 imag;
    INT32 real;
} CPLX32;
//added cplx64
typedef struct // _CPLX32
{
    INT64 imag;
    INT64 real;
} CPLX64;

typedef struct // _CPLXF
{
    FLOAT imag;
    FLOAT real;
} CPLXF;

typedef struct _CPLXD
{
    DOUBLE imag;
    DOUBLE real;
} CPLXD;
#else /* _LITTLE_ENDIAN */

//#ifdef _BIG_ENDIAN
typedef struct _CPLX8
{
    INT8 real;
    INT8 imag;
} CPLX8;

typedef struct _CPLX16
{
    INT16 real;
    INT16 imag;
} CPLX16;

typedef struct _CPLX32
{
    INT32 real;
    INT32 imag;
} CPLX32;

typedef struct _CPLXF
{
    FLOAT real;
    FLOAT imag;
} CPLXF;

typedef struct _CPLXD
{
    DOUBLE real;
    DOUBLE imag;
} CPLXD;

#endif /* _BIG_ENDIAN */

typedef union // _CPLX32U
{
    CPLX32 cplx32;
    UINT64 realimag;
} CPLX32U;

typedef union // _CPLX16U
{
    CPLX16 cplx16;
    UINT32 realimag;
} CPLX16U;


#endif /* __LTE_ENB_DATATYPES_H */
