/******************************************************************************
** FILENAME:          $Source: typedef.h $
**
** COPYRIGHT:         Conti Automotive GmbH
** DESCRIPTION:       Generic header file for global type definitions
**
** DATE CREATED:      tt.mm.jjjj
** LAST CHANGE:       $Date: 2014/07/16 13:22:51CEST $
** VERSION:           $Revision: 1.2 $
** CHECKPOINT:        $ProjectRevision: Last Checkpoint: 1.14 $
** CHANGE PACKAGE:    $Name:  $
**
** LIST OF MODIFICATIONS:
**  Rev     Date              Author                      Reason
**  1         28.09.2009   M.Stratesteffen        First version.
**
*/

#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

/******************************************************************************
*   
*   TYPE DEFINITIONS
*
******************************************************************************/
/* Standard types */
#define false 0
#define true  1
typedef unsigned char       bool;           /* boolean type */
typedef unsigned char       u8;             /* unsigned byte */
typedef signed char         s8;             /* signed byte */
typedef unsigned short int  u16;            /* unsigned 2 byte-word */
typedef signed short int    s16;            /* signed 2 byte-word */

typedef unsigned long int   u24;            /* unsigned 3 byte-word */
typedef signed long int     s24;            /* signed 3 byte-word */

typedef unsigned long int   u32;            /* unsigned 4 byte-word */
typedef signed long int     s32;            /* signed 4 byte-word */
/* Bitfields */
typedef unsigned char       bitfield8;      /* for 1 byte-bitfield */
typedef unsigned short int  bitfield16;     /* for 2 byte-bitfield */
typedef unsigned long int   bitfield32;     /* for 4 byte-bitfield */
/* Pointers types */
typedef void                *pvoid;         /* pointer to void */
typedef bool                *pbool;         /* pointer to boolean */
typedef u8                  *pu8;           /* pointer to unsigned byte */
typedef s8                  *ps8;           /* pointer to signed byte */
typedef u16                 *pu16;          /* pointer to unsigned 2 byte-word */
typedef s16                 *ps16;          /* pointer to signed 2 byte-word */
typedef u32                 *pu32;          /* pointer to unsigned 4 byte-word */

typedef volatile unsigned char* TSFRPtr;

/******************************************************************************
*   
*   DEFINES AND MACROS
*
******************************************************************************/
#ifndef TRUE
  #define TRUE  1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

#ifndef NULL
 #define NULL  0
#endif

#define STATIC_ASSERT(EXPR)  char (* static_assert_fn(void)) [!!(EXPR)*2-1]

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#define U8_MIN ((u8) 0)
#define U8_MAX ((u8) 0xFFU)                  /* 255 */

#define S8_MIN ((s8) 0x80)                   /* -128 */
#define S8_MAX ((s8) 0x7F)                   /*  127 */

#define U16_MIN ((u16) 0U)
#define U16_MAX ((u16) 0xFFFFU)              /* 65535 */

#define S16_MIN ((s16)  0x8000)              /* -32768 */
#define S16_MAX ((s16)  0x7FFF)              /*  32767  */

#define U32_MIN ((u32) 0UL)
#define U32_MAX ((u32) 0xFFFFFFFFUL)         /* 4294967295 */

#define S32_MIN ((s32) 0x80000000L)          /* -2147483648  */
#define S32_MAX ((s32) 0x7FFFFFFFL)          /*  2147483647  */

#define _LITTLE_ENDIAN

/* convert a big/little endian-ordered byte array to a wider int  */
#if defined(_LITTLE_ENDIAN)

#define BE_ARRAY_TO_U16(array, offset, var) do { ((u8*)&(var))[0]=((u8*)(array))[(offset)+1]; ((u8*)&(var))[1]=((u8*)(array))[(offset)+0];  } while(0)
#define BE_ARRAY_TO_U32(array, offset, var) do { ((u8*)&(var))[0]=((u8*)(array))[(offset)+3]; ((u8*)&(var))[1]=((u8*)(array))[(offset)+2]; ((u8*)&(var))[2]=((u8*)(array))[(offset)+1]; ((u8*)&(var))[3]=((u8*)(array))[(offset)+0];  } while(0)
#define LE_ARRAY_TO_U16(array, offset, var) do { (var) = *(u16*)(((u8 *)(array)) + (offset)); } while(0)
#define LE_ARRAY_TO_U32(array, offset, var) do { (var) = *(u32*)(((u8 *)(array)) + (offset)); } while(0)

#define U16_TO_BE_ARRAY(array, offset, var) do { ((u8*)(array))[(offset)+0]=((u8*)&(var))[1]; ((u8*)(array))[(offset)+1]=((u8*)&(var))[0];  } while(0)
#define U32_TO_BE_ARRAY(array, offset, var) do { ((u8*)(array))[(offset)+0]=((u8*)&(var))[3]; ((u8*)(array))[(offset)+1]=((u8*)&(var))[2]; ((u8*)(array))[(offset)+2]=((u8*)&(var))[1]; ((u8*)(array))[(offset)+3]=((u8*)&(var))[0];  } while(0)
#define U16_TO_LE_ARRAY(array, offset, var) do { *(u16*)(((u8 *)(array)) + (offset)) = (var); } while(0)
#define U32_TO_LE_ARRAY(array, offset, var) do { *(u32*)(((u8 *)(array)) + (offset)) = (var); } while(0)


#elif defined(_BIG_ENDIAN)

#define LE_ARRAY_TO_U16(array, offset, var) do { ((u8*)&(var))[0]=((u8*)(array))[(offset)+1]; ((u8*)&(var))[1]=((u8*)(array))[(offset)+0];  } while(0)
#define LE_ARRAY_TO_U32(array, offset, var) do { ((u8*)&(var))[0]=((u8*)(array))[(offset)+3]; ((u8*)&(var))[1]=((u8*)(array))[(offset)+2]; ((u8*)&(var))[2]=((u8*)(array))[(offset)+1]; ((u8*)&(var))[3]=((u8*)(array))[(offset)+0];  } while(0)
#define BE_ARRAY_TO_U16(array, offset, var) do { (var) = *(u16*)(((u8 *)(array)) + (offset)); } while(0)
#define BE_ARRAY_TO_U32(array, offset, var) do { (var) = *(u32*)(((u8 *)(array)) + (offset)); } while(0)

#define U16_TO_LE_ARRAY(array, offset, var) do { ((u8*)(array))[(offset)+0]=((u8*)&(var))[1]; ((u8*)(array))[(offset)+1]=((u8*)&(var))[0];  } while(0)
#define U32_TO_LE_ARRAY(array, offset, var) do { ((u8*)(array))[(offset)+0]=((u8*)&(var))[3]; ((u8*)(array))[(offset)+1]=((u8*)&(var))[2]; ((u8*)(array))[(offset)+2]=((u8*)&(var))[1]; ((u8*)(array))[(offset)+3]=((u8*)&(var))[0];  } while(0)
#define U16_TO_BE_ARRAY(array, offset, var) do { *(u16*)(((u8 *)(array)) + (offset)) = (var); } while(0)
#define U32_TO_BE_ARRAY(array, offset, var) do { *(u32*)(((u8 *)(array)) + (offset)) = (var); } while(0)

#else

#define BE_ARRAY_TO_U16(array, offset, var) do { (var) = ((u16)((u8 *)(array))[(offset)+0] <<  8) | ((u8 *)(array))[(offset)+1]; } while(0)
#define LE_ARRAY_TO_U16(array, offset, var) do { (var) = ((u16)((u8 *)(array))[(offset)+1] <<  8) | ((u8 *)(array))[(offset)+0]; } while(0)
#define BE_ARRAY_TO_U32(array, offset, var) do { (var) = ((u32)((u8 *)(array))[(offset)+0] << 24) | ((u32)((u8 *)(array))[(offset)+1] << 16) | ((u16)((u8 *)(array))[(offset)+2] << 8) | ((u8 *)(array))[(offset)+3]; } while(0)
#define LE_ARRAY_TO_U32(array, offset, var) do { (var) = ((u32)((u8 *)(array))[(offset)+3] << 24) | ((u32)((u8 *)(array))[(offset)+2] << 16) | ((u16)((u8 *)(array))[(offset)+1] << 8) | ((u8 *)(array))[(offset)+0]; } while(0)

#define U16_TO_BE_ARRAY(array, offset, var) do { ((u8 *)(array))[(offset)+0] = (u8)((var) >>  8); ((u8 *)(array))[(offset)+1] = (u8)(var); } while(0)
#define U16_TO_LE_ARRAY(array, offset, var) do { ((u8 *)(array))[(offset)+1] = (u8)((var) >>  8); ((u8 *)(array))[(offset)+0] = (u8)(var); } while(0)
#define U32_TO_BE_ARRAY(array, offset, var) do { ((u8 *)(array))[(offset)+0] = (u8)((var) >> 24); ((u8 *)(array))[(offset)+1] = (u8)((var) >> 16); ((u8 *)(array))[(offset)+2] = (u8)((var) >> 8); ((u8 *)(array))[(offset)+3] = (u8)(var); } while(0)
#define U32_TO_LE_ARRAY(array, offset, var) do { ((u8 *)(array))[(offset)+3] = (u8)((var) >> 24); ((u8 *)(array))[(offset)+2] = (u8)((var) >> 16); ((u8 *)(array))[(offset)+1] = (u8)((var) >> 8); ((u8 *)(array))[(offset)+0] = (u8)(var); } while(0)

#endif


#endif /* _TYPEDEF_H_ */
