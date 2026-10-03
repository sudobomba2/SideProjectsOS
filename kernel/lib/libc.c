/* Low Budget Libc */

#include "libc.h"

static void reverse2(char* str,int length){
	int start=0;
	int end=length-1;
	while (start<end){
		char tmp=str[start];
		str[start]=str[end];
		str[end]=tmp;
		start++;
		end--;
	}
}

void *memcpy(void *restrict dest,const void *restrict src,size_t n){
	uint8_t *restrict pdest=dest;
	const uint8_t *restrict psrc=src;
	for(size_t i=0;i<n;i++){pdest[i]=psrc[i];}
	return dest;
}

void *memset(void *s,int c,size_t n){
	uint8_t *p=s;
	for(size_t i=0;i<n;i++){p[i]=(uint8_t)c;}
	return s;
}

void *memmove(void *dest,const void *src,size_t n){
	uint8_t *pdest=dest;
	const uint8_t *psrc=src;
	if((uintptr_t)src>(uintptr_t)dest){for(size_t i=0;i<n;i++){pdest[i]=psrc[i];}}else if((uintptr_t)src<(uintptr_t)dest){for(size_t i=n;i>0;i--){pdest[i-1]=psrc[i-1];}}
	return dest;
}

int memcmp(const void *s1,const void *s2,size_t n){
	const uint8_t *p1=s1;
	const uint8_t *p2=s2;
	for(size_t i=0;i<n;i++){if(p1[i]!=p2[i]){return p1[i]<p2[i]?-1:1;}}
	return 0;
}

void *memchr(const void *a,int b,size_t c){
	const uint8_t* p=(const uint8_t*)a;
	for(size_t i=0;i<c;i++){if(p[i]==(uint8_t)b){return (void*)(p+i);}}
	return 0;
}

int strlen(const char *s){
	int i=0;
	while(s[i]){i++;}
	return i;
}

char *strncpy(char *dest,const char *src,size_t n){
	size_t i;
	for(i=0;i<n&&src[i]!='\0';i++){dest[i]=src[i];}
	for(;i<n;i++){dest[i]='\0';}
	return dest;
}

int strcmp(const char *a,const char *b){
	int i=0;
	while(a[i]&&b[i]&&a[i]==b[i]){i++;}
	return a[i]-b[i];
}


int strncmp(const char *s1,const char *s2,size_t n){
	while(n&&*s1&&(*s1==*s2)){s1++;s2++;n--;}
	if(n==0){return 0;}
	return *(unsigned char *)s1-*(unsigned char *)s2;
}

char *strcpy(char *a,const char *b){
	char *d=a;
	while((*d++=*b++));
	return a;
}

char *strcat(char *a,const char *b){
	char *d=a+strlen(a);
	while((*d++=*b++));
	return a;
}

char *strncat(char *a,const char *b,size_t c){
	char *d=a+strlen(a);
	size_t i;
	for(i=0;i<c&&b[i];i++){d[i]=b[i];}
	d[i]=0;
	return a;
}

char *strchr(const char *s,int c){
	while(*s){if(*s==(char)c){return (char *)s;}s++;}
	if((char)c=='\0'){return (char *)s;}
	return NULL;
}

char *strrchr(const char *s,int c){
	char *last=NULL;
	do{if(*s == (char)c){last=(char *)s;}}while(*s++);
	return last;
}

char *strstr(const char *haystack,const char *needle){
	size_t n=strlen(needle);
	if(!n){return (char *)haystack;}
	while(*haystack){if(!strncmp(haystack,needle,n)){return (char *)haystack;}haystack++;}
	return NULL;
}

char *strtok(char *str,const char *delim){
	static char *last;
	if(str){last=str;}
	else if(!last){return NULL;}
	char *start=last;
	while(*start){const char *d=delim;int found=0;while(*d){if(*start==*d){found=1;break;}d++;}if(!found){break;}start++;}
	if(*start==0){last=NULL;return NULL;}
	char *end=start;
	while(*end){const char *d=delim;while(*d){if(*end==*d){*end=0;last=end+1;return start;}d++;}end++;}
	last=NULL;
	return start;
}

char *strsep(char **stringp,const char *delim){
	char *s=*stringp;
	if(!s){return NULL;}
	char *token=s;
	while(*s){const char *d=delim;while(*d){if(*s==*d){*s='\0';*stringp=s+1;return token;}d++;}s++;}
	*stringp=NULL;
	return token;
}

char *strrev(char *str){
	char *end=str;
	while(*end){end++;}
	end--;
	while(str<end){char tmp=*str;*str=*end;*end=tmp;str++;end--;}
	return str;
}

int atoi(const char* str){
	int r=0;
	int s=1;
	while(*str==' '||*str=='\t'){str++;}
	if(*str=='-'){s=-1;str++;}
	else if(*str=='+'){str++;}
	while(*str>='0'&&*str<='9'){r=r*10+(*str-'0');str++;}
	return r*s;
}

char* itoa(int value,char* str,int base){
	int i=0;
	int negative=0;
	if(base<2||base>16){str[0]='\0';return str;}
	if(value==0){str[i++]='0';str[i]='\0';return str;}
	if(value<0&&base==10){negative=1;value=-value;}
	while(value!=0){int remainder=value%base;if(remainder>9){str[i++]=(remainder-10)+'A';}else{str[i++]=remainder+'0';}value/=base;}
	if(negative){str[i++]='-';}
	str[i]='\0';
	reverse2(str,i);
	return str;
}

int streq(const char *a,const char *b){
	while(*a&&*b){
		if(*a!=*b){return 0;}
		a++;
		b++;
	}
	return *a==*b;
}
int namecmp(const char *a,const char *b){
	char ca;
	char cb;
	while(*a&&*b){
		ca=*a;
		cb=*b;
		if(ca>='A'&&ca<='Z'){ca+=32;}
		if(cb>='A'&&cb<='Z'){cb+=32;}
		if(ca<cb){return -1;}
		if(ca>cb){return 1;}
	}
	if(!*a && *b){return -1;}
	if(*a&&!*b){return 1;}
	return 0;
}

int isdigit(int c){return (c >='0'&&c<='9');}
int isalpha(int c){return ((c>='A'&&c<='Z')||(c>='a'&&c<='z'));}
int isalnum(int c){return isalpha(c)||isdigit(c);}
int islower(int c){return (c>='a'&&c<='z');}
int isupper(int c){return (c>='A'&&c<='Z');}
int isspace(int c){return (c==' '||c=='\t'||c == '\n'||c=='\r'||c=='\f'||c=='\v');}
int isxdigit(int c){return isdigit(c)||(c>='A'&&c<='F')||(c>='a'&&c<='f');}
int isprint(int c){return(c>=32&&c<=126);}
int iscntrl(int c){return (c>=0&&c<32)||c==127;}
int tolower(int c){if(isupper(c)){return c+32;}return c;}
int toupper(int c){if(islower(c)){return c-32;}return c;}

int strcasecmp(const char *s1,const char *s2){
	const unsigned char *p1=(const unsigned char *)s1;
	const unsigned char *p2=(const unsigned char *)s2;
	int result;
	if(p1==p2){return 0;}
	while((result=tolower(*p1)-tolower(*p2))==0){if(*p1=='\0'){break;}p1++;p2++;}
	return result;
}

int strncasecmp(const char *s1,const char *s2,size_t n){
	const unsigned char *p1=(const unsigned char *)s1;
	const unsigned char *p2=(const unsigned char *)s2;
	int result=0;
	if(n==0){return 0;}
	while(n-->0){result=tolower(*p1)-tolower(*p2);if(result!=0||*p1=='\0'){break;}p1++;p2++;}
	return result;
}











































/*
▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄■■■■■■■■■■■■
*/ /* Seriously wtf is this hellish shit */
