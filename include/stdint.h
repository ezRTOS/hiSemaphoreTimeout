/**
 * @file stdint.h
 *
 */
/* ezRTOS by BASEVER TECHNOLOGY INC., Copyright (C) 2019.  All rights reserved. */

#ifndef _STDINT_H_
#define _STDINT_H_

typedef char                          int8_t;
typedef short                         int16_t;
typedef int                           int32_t;
typedef long long                     int64_t;

typedef unsigned char                 uint8_t;
typedef unsigned short                uint16_t;
typedef unsigned int                  uint32_t;
typedef unsigned long long            uint64_t;

typedef volatile char                 vint8_t;
typedef volatile short                vint16_t;
typedef volatile int                  vint32_t;
typedef volatile long long            vint64_t;

typedef volatile unsigned char        vuint8_t;
typedef volatile unsigned short       vuint16_t;
typedef volatile unsigned int         vuint32_t;
typedef volatile unsigned long long   vuint64_t;

typedef unsigned int                  size_t;
typedef unsigned char                 bool;

#ifndef NULL
  #define NULL                        (0)
#endif

#ifndef true
  #define true                        ((bool)1)
#endif

#ifndef false
  #define false                       ((bool)0)
#endif

#ifndef max
  #define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
  #define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef LONG_MIN
  #define LONG_MIN                    (0x8000000000000000)
#endif

#ifndef LONG_MAX
  #define LONG_MAX                    (0x7FFFFFFFFFFFFFFF)
#endif

#ifndef INT_MIN
  #define INT_MIN                     (0x80000000)
#endif

#ifndef INT_MAX
  #define INT_MAX                     (0x7FFFFFFF)
#endif

#endif /* _STDINT_H_ */
