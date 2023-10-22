#include "LTE-eNB-DataTypes.h"
#include "dl_nprach_head.h"
CPLX32 mulcom(CPLX32 stVar1, CPLX32 stVar2)
{
    CPLX64 stTemp;
    CPLX32 stRes;
    stTemp.real = (stVar1.real * stVar2.real) - (stVar2.imag * stVar1.imag);
    stTemp.imag = (stVar1.imag * stVar2.real) + (stVar2.imag * stVar1.real);
    stRes.real = stTemp.real >> DOWN_SCL8 ;
    stRes.imag = stTemp.imag >> DOWN_SCL8 ;
    return (stRes);
}

// CPLXF function add
CPLX32 addcom(CPLX32 stVar1, CPLX32 stVar2)
{
    CPLX32 stTemp;
    stTemp.real = stVar1.real + stVar2.real;
    stTemp.imag = stVar1.imag + stVar2.imag;
    return (stTemp);
}

// Print CPLXF numbers
void printcom(CPLX32 stVar1)
{
    printf("%ld + i %ld\n", stVar1.real, stVar1.imag);
}

//absolute value of CPLXF numbers
DOUBLE abscom(CPLX32 d)
{
    DOUBLE absolute;
    absolute = sqrt((d.real * d.real) + (d.imag * d.imag));
    return (absolute);
}

CPLX32 conjcom(CPLX32 stVar1)
{
    CPLX32 stAbsolute;
    stAbsolute.real =stVar1.real ;
    stAbsolute.imag = -1*stVar1.imag;
    return (stAbsolute);
}

INT32 mean(INT32 ai32Arr[],INT16 si16len)
{

    INT32 i32Total = 0;
    INT32 i32Avg;
    if (si16len > 1)
    {
        for (int si8row = 0; si8row < si16len; si8row++) //definedsi8row as int
        {
            i32Total = i32Total + ai32Arr[si8row];

        }
        i32Avg = i32Total / si16len;

        return i32Avg;
    }
    else
    {
        return ai32Arr[0];                 //HERE INPUT SHOULD BE ARRAY ONLY
    }
}

INT32 sum(INT32 ai32Arr[],INT16 si16len)
{

    INT32 i32Total = 0;
    if (si16len > 1)
    {
        for (int si8row = 0; si8row < si16len; si8row++)
        {
            i32Total = i32Total + ai32Arr[si8row];
        }

        return i32Total;
    }
    else
    {
        return ai32Arr[0];                 //HERE INPUT SHOULD BE ARRAY ONLY
    }
}


void MatSlice (CPLX32 *pcplx32Input, CPLX32 *pcplx32Output, UINT16 ui16StRow, UINT16 ui16EnRow, UINT16 ui16StCol, UINT16 ui16EnCol,UINT16 NCols)
{

  for (UINT32 ui32Row = ui16StRow; ui32Row < ui16EnRow; ui32Row++)
  {
    for (UINT32 ui32Col = ui16StCol; ui32Col < ui16EnCol; ui32Col++)
    {
      pcplx32Output[(ui32Row - ui16StRow)*(ui16EnCol-ui16StCol) + (ui32Col - ui16StCol)] = pcplx32Input[ui32Row * NCols + ui32Col];
    }
  }
}
