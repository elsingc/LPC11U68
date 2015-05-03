/*
 * string.h
 *
 * Definitions for memory and string functions.
 */

#ifndef _STRING_H_
#define	_STRING_H_

#define __need_size_t

#ifndef NULL
#define NULL 0
#endif

void * memcpy(void *pDestination, const void *pSource, size_t num);
void * memset(void *pBuffer, int value, size_t num);
void* memmove(void *s1, const void *s2, size_t n);
int memcmp(const void *av, const void *bv, size_t len);
char * strchr(const char *pString, int character);
size_t strlen(const char *pString);
char * strrchr(const char *pString, int character);
char * strcpy(char *pDestination, const char *pSource);
int strncmp(const char *pString1, const char *pString2, size_t count);
char * strncpy(char *pDestination, const char *pSource, size_t count);
int strcmp(const char *s1, const char *s2);
char *strtok_r(char *s, const char *delim, char **last);

char *strtok(char *s, const char *delim);

/* These function names are used on Windows and perhaps other systems.  */
#ifndef strcmpi
#define strcmpi strcasecmp
#endif
#ifndef stricmp
#define stricmp strcasecmp
#endif
#ifndef strncmpi
#define strncmpi strncasecmp
#endif
#ifndef strnicmp
#define strnicmp strncasecmp
#endif


#endif /* _STRING_H_ */
