#ifndef __LIBC_H__
#define __LIBC_H__
#pragma once 

#include "stddef.h"
#include "stdbool.h"
#include "stdint.h"

#define FLAG_SET(x,flag) x|=(flag)
#define FLAG_UNSET(x,flag) x&=~(flag)

typedef long ssize_t;
typedef long off_t;
typedef int pid_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef unsigned int mode_t;
typedef unsigned int dev_t;
typedef unsigned long ino_t;
typedef unsigned long nlink_t;
typedef long blksize_t;
typedef long blkcnt_t;
typedef long time_t;
typedef long suseconds_t;

struct stat{
	dev_t st_dev;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	off_t st_size;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
};

#define _STREQ(a,b) (strcmp((a),(b))==0)
void *memcpy(void *restrict dest,const void *restrict src,size_t n);
void *memset(void *s,int c,size_t n); 
void *memmove(void *dest,const void *src,size_t n);
int memcmp(const void *s1,const void *s2,size_t n);
void *memchr(const void *a,int b,size_t c);
int strlen(const char *s);
int strcmp(const char *a,const char *b);
int strncmp(const char *s1,const char *s2,size_t n);
char *strcpy(char *a,const char *b);
char *strncpy(char *dest,const char *src,size_t n);
char *strcat(char *a,const char *b);
char *strncat(char *a,const char *b,size_t c);
char *strchr(const char *s,int c);
char *strrchr(const char *s,int c);
char *strstr(const char *haystack,const char *needle);
char *strtok(char *str,const char *delim);
char *strsep(char **stringp,const char *delim);
char *strrev(char *str);
char *strerror(int errnum);
char* itoa(int value,char* str,int base);
int streq(const char *a,const char *b);
int namecmp(const char *a,const char *b);
int isdigit(int c);
int isalpha(int c);
int isalnum(int c);
int islower(int c);
int isupper(int c);
int isspace(int c);
int isxdigit(int c);
int isprint(int c);
int iscntrl(int c);
int tolower(int c);
int toupper(int c);
int starts(const char *s,const char *p);
int ends(const char *s,const char *p);
char *skip(char *s);
int strcasecmp(const char *s1,const char *s2);
int strncasecmp(const char *s1,const char *s2,size_t n);
#endif

/*
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢠⢰⢰⢢⢢⢰⢠⢀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡌⡎⣎⢮⢺⡸⡕⡧⡳⡱⡕⡕⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢣⡣⡇⣗⢵⢝⣎⢗⣝⢞⡎⡧⡫⡅⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢐⡜⣜⢜⢮⡺⡼⣕⢗⣗⣕⣗⣝⢮⡳⡢⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣇⢧⢫⡺⣪⣺⡪⣗⢧⡳⣕⣗⢗⢵⣟⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⡘⡸⡜⡮⡪⡲⡽⣝⢵⣝⢞⢮⡫⡺⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢣⢪⢺⢸⠎⡎⣎⢯⢮⡳⡕⡽⣕⣗⢭⢫⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⢜⢕⢕⢕⠥⡑⡜⢜⢕⢪⡪⡣⡳⡵⣝⢮⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⡎⡧⡳⡱⡱⡱⣕⢳⢕⠵⣝⢞⢞⡞⠜⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡪⢮⡫⣗⢧⢪⣪⢪⣳⢽⡺⣝⠕⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⡳⡹⣮⡻⣜⡮⣳⢯⢯⢯⢎⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⡸⣸⡹⣺⡺⣺⣝⢮⢯⢏⡗⡭⣓⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢱⢱⡣⡯⣺⣪⡳⣝⢽⢕⣗⢭⢺⢸⢢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⡣⡳⣕⣝⢞⢮⣺⡺⣪⢯⣳⣳⣣⢳⡹⡜⣅⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢔⢕⣝⢜⢮⢎⢯⣳⡳⣝⡮⣗⣗⣗⣕⢗⣝⢮⡪⡄⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢰⢸⢸⡱⣪⣫⡫⡯⣳⡳⡽⣮⣻⣺⣺⣺⡪⣗⢧⡳⣕⢕⠄⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡔⡕⡕⡕⡵⡹⣜⢮⢮⡻⡮⣯⣻⣺⣺⣺⣺⣺⡺⡮⡳⣝⢮⢳⢕⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢀⢄⢔⢜⢜⢜⡜⣜⢎⡗⣝⢮⡫⣗⣯⣻⣺⣺⢞⣞⣞⣞⡮⣯⡫⡯⡮⣳⡣⣏⢇⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⣎⢮⢪⢪⡪⡪⡪⣎⢞⢼⡱⣝⢮⡳⣯⣳⣳⣳⢗⡯⣟⡮⣗⣗⣟⣞⢮⢯⢯⣺⢺⡜⡵⡅⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⡠⣪⢺⢜⢜⢎⢧⡣⣫⢺⢜⣕⢧⣻⡪⣗⣟⣞⡾⡵⡯⣯⢯⣗⡯⣗⡷⣳⢯⢯⢯⣳⣳⡳⣝⢞⢼⠄⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⢐⢎⢮⡳⣝⢼⡱⣣⡫⣎⢮⡳⣕⢷⢵⣝⣞⣞⡾⣽⢽⢯⢯⣟⡾⣽⣳⢯⣗⡯⣯⣳⣳⡳⣽⡪⡯⡮⣫⡀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⢀⢧⡫⡳⣝⢎⢮⢺⡪⡮⡺⣜⣞⢮⢯⣳⣳⣳⢗⡯⣗⡯⡿⣽⣺⢽⣳⢯⣗⡷⣫⣗⣗⣗⣟⢮⢯⡳⣝⣜⢆⠀⠀⠀
*⠀⠀⠀⠀⠀⠠⣝⢮⢮⢯⢮⢣⡫⣺⢪⡳⣝⢮⢮⢯⣳⣳⡳⡯⡯⡯⣗⡯⣟⣗⡯⣟⡾⣽⣺⢽⣳⣳⣳⢷⢽⢽⡳⣝⢮⣪⡳⡀⠀⠀
*⠀⠀⠀⠀⠀⢎⢮⡳⣳⢝⢮⢣⡫⡮⣳⢽⢮⡻⣮⣳⣳⡳⣯⣻⢽⣫⣗⡯⣗⡯⡯⣗⡯⣗⡯⣟⢾⣕⡯⡯⣯⣳⢯⣳⡳⡵⡹⡂⠀⠀
*⠀⠀⠀⠀⢰⡹⣕⢽⡺⡝⡎⡮⢮⡻⡮⡯⣗⣟⣞⣞⢾⣝⡷⡽⣽⡺⡮⡯⣗⡯⣟⡵⡯⣗⡯⣯⡻⡮⣯⣻⣺⣺⣳⡳⡽⡵⡝⡆⠀⠀
*⠀⠀⠀⠀⡪⡺⡼⣕⢯⢪⡺⣜⢷⣝⡯⣯⣗⣗⣗⡯⣟⡮⡯⡯⣗⡯⡯⡯⣗⢯⣗⢯⢯⣗⢯⣗⡯⡯⣗⣗⣗⣗⡷⡽⣝⢮⡫⠂⠀⠀
*⠀⠀⠀⠀⢪⣫⡺⣪⡳⣕⢝⡮⣗⡷⡯⣗⡷⣯⣺⢽⡳⣯⣻⢽⡳⡯⡯⡯⣯⡳⡽⣝⢷⣝⣗⣗⡯⡯⣗⡯⣞⢾⢽⣝⢮⡳⡝⠀⠀⠀
*⠀⠀⠀⠀⢘⢖⡽⡵⡹⣮⡳⣝⡾⡽⣽⡳⣯⣗⡯⣯⣻⣺⣺⢽⢽⢽⢽⢽⢮⢯⣻⡪⣗⣗⣗⣗⡯⡯⣗⡯⡯⡯⣗⡯⣗⠽⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⢳⢽⢽⣝⣗⡯⡷⡽⣝⣗⡯⣗⡷⡯⣗⡯⣞⡾⡽⣽⢽⢽⢽⣝⣗⢷⣝⣞⣞⣞⡮⡯⡯⣗⢯⢯⣻⢵⡫⡏⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠈⠽⣕⣗⡯⣯⢿⣝⣗⡯⡯⣗⡯⣟⣗⡯⣗⡯⣯⣗⡯⡯⣟⣞⢾⣝⣞⣞⣞⢾⢽⢽⢽⣺⣝⣗⡯⡯⡏⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠱⣳⢯⢿⣽⢷⡯⡿⣽⣳⢯⣗⡷⡯⣗⡯⣗⣗⡯⣯⢗⡯⣟⣞⣞⣞⡾⡽⡽⡽⣽⣺⣺⣺⠽⠋⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠘⠯⠛⠽⣻⡽⣯⢗⡯⣟⡾⣽⢽⣳⢯⣗⡯⣟⢾⢽⣺⢵⣳⣳⢗⡯⡯⣯⣻⡺⠊⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠹⡽⣽⢽⡳⡯⣗⣟⡾⣽⣺⢽⣳⢯⣟⡾⣽⣺⢾⢽⣺⠽⠓⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠹⢽⡽⣯⢗⣯⢯⣗⡯⣟⡾⣽⣺⣽⣳⣯⢿⡭⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢽⡇⠀⢈⣩⡭⠍⠉⠛⠛⠙⠞⠟⠾⣻⢿⡽⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣕⡯⣧⢴⡺⠓⠃⠀⠀⠀⠀⠀⠀⠀⠀⠈⡿⡍⠓⠿⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣀⣴⣺⢜⡮⣗⣏⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠝⠀⠀⠈⠹⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⢠⡤⣖⡾⡽⠾⠙⠈⠁⢕⣟⠈⠑⠯⣳⣲⣢⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠦⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠁⠀⠀⠀⠀⠀⣣⡳⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⣳⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*/ /* Dove Braille*/
