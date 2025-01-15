#ifndef __COMMONT_H 
#define __COMMONT_H
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef unsigned long long  uint64;
typedef signed char         int8;                                               // ÓĞ·ûºÅ  8 bits
typedef signed short int    int16;                                              // ÓĞ·ûºÅ 16 bits
typedef signed int          int32;                                              // ÓĞ·ûºÅ 32 bits
typedef signed long long    int64;    

#define     func_abs(x)             ((x) >= 0 ? (x): -(x))
void func_int_to_str (char *str, int32 number);
void func_double_to_str (char *str, double number, uint8 point_bit);
void func_uint_to_str (char *str, uint32 number);

#endif

