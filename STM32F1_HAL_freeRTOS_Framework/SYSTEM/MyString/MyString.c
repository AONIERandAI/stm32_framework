#include "MyString.h"


/********************��ȡ�ַ�������**********************************/
int mystrlen (const char *str)
{
    char *s = (char *)str;
    int len = 0;

    if (s == NULL)
        return 0;

    while (*s++ != '\0')
        ++len;

    return len;
}

/**********************�ַ���ƴ��*********************************/
char * mystrcat (char *dest, const char *src)
{
    char *dp;
    char *sp = (char *)src;

    if ((dest != NULL) && (src != NULL))
    {
        dp = &dest[mystrlen(dest)];

        while (*sp != '\0')
        {
            *dp++ = *sp++;
        }
        *dp = '\0';
    }
    return dest;
}

/*************************�ַ���ǰn��ƴ��***************************************/
char * mystrncat (char *dest, const char *src, int n)
{
    char *dp;
    char *sp = (char *)src;

    if ((dest != NULL) && (src != NULL) && (n > 0))
    {
        dp = &dest[mystrlen(dest)];

        while ((*sp != '\0') && (n-- > 0))
        {
            *dp++ = *sp++;
        }
        *dp = '\0';
    }
    return dest;
}

/***************************�ַ�������*************************************/
char * mystrcpy (char *dest, const char *src)
{
    char *dp = (char *)dest;
    char *sp = (char *)src;

    if ((dest != NULL) && (src != NULL))
    {
        while (*sp != '\0')
        {
            *dp++ = *sp++;
        }
        *dp = '\0';
    }
    return dest;
}

/****************************�ַ���ǰn���************************************/
char * mystrncpy (char *dest, const char *src, int n)
{
    char *dp = (char *)dest;
    char *sp = (char *)src;

    if ((dest != NULL) && (src != NULL) && (n > 0))
    {
        while ((*sp != '\0') && (n-- > 0))
        {
            *dp++ = *sp++;
        }
        *dp = '\0';
    }
    return dest;
}

/************************�ַ����Ƚϣ�һ�·���0****************************************/
int mystrcmp (const char *s1, const char *s2)
{
    /* No checks for NULL */
    char *s1p = (char *)s1;
    char *s2p = (char *)s2;

    while (*s2p != '\0')
    {
        if (*s1p != *s2p)
            break;

        ++s1p;
        ++s2p;
    }
    return (*s1p - *s2p);
}

/************************�ַ���ǰn��Ƚϣ�һ�·���0****************************************/
int mystrncmp (const char *s1, const char *s2, int n)
{
    /* No checks for NULL */
    char *s1p = (char *)s1;
    char *s2p = (char *)s2;

    if (n <= 0)
        return 0;

    while (*s2p != '\0')
    {
        if (*s1p != *s2p)
            break;

        if (--n == 0)
            break;

        ++s1p;
        ++s2p;
    }
    return (*s1p - *s2p);
}

/***************************����һ���ڴ�����n��������Ϊc�β�*************************************/
void * mymemset (void *s, int c, unsigned n)
{
    /* Not optimized, but very portable */
    uint8 *sp = (uint8 *)s;

    if ((s != NULL) && (n > 0))
    {
        while (n--)
        {
            *sp++ = (uint8)c;
        }
    }
    return s;
}

/***************************�ڴ濽��*****************************/
void *memcpy(void *des,const void *src,size_t len)
{
	char * result =des;
	const char * from = src;
	//assert(des&&src);
	while(len--)
	{   
		 *(result++) = *(from++);
	}      
	return des;
}


