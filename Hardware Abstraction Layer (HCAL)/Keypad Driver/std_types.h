/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	std_types.h

[AUTHOR]       :	MOHANAD K. SAEED

[DATA CREATED] :	07/02/2021

[DESCRIPTION]  :	This file has been created to include all data types used in embedded 
					system becacuse the size of integer depends on the type of the compiler 
					which has written by compiler writer for the underlying processor. 
					You can see compilers merrily changing the size of integer according to 
					convenience and underlying architectures. So it is my recommendation to 
					use the C99 integer data types ( uin8_t, uin16_t, uin32_t ..) in place 
					of standard int.
------------------------------------------------------------------------------------------*/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Boolean Data Type */
typedef unsigned char bool;

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */
typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;         /*       0..18446744073709551615  */
typedef signed long long      sint64;
typedef float                 float32;
typedef double                float64;

#endif 