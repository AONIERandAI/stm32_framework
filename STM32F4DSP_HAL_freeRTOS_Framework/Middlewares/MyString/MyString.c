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
void *mymemcpy(void *des,const void *src,size_t len)
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

char *strchr(const char *s, int c) {
    const char c_ = (char)c;
    do {
        if (*s == c_) {
            return (char *)s;
        }
    } while (*s++ != '\0');
    return NULL;
}

size_t strcspn(const char *s1, const char *s2) {
    size_t res = 0;
    while (*s1 != '\0') {
        if (strchr(s2, *s1) == NULL) {
            ++s1;
            ++res;
        } else {
            return res;
        }
    }
    return res;
}

/***************************��*s�ַ�����*delim�ָ�÷�����������*****************************/
char *mystrtok(char *s, const char *delim) {
    static char *last;

    if (s == NULL) {
        s = last;
    }
    int ch;
    do {
        ch = *s++;
        if (ch == '\0') {
            return NULL;
        }
    } while (strchr(delim, ch));
    --s;
    last = s + strcspn(s, delim);
    if (*last != '\0') {
        *last++ = '\0';
    }
    return s;
}
/*�÷�����
	char *buf4tok,i; //���浱ǰtok�ͼ���
	char srt_buf[50] = {"a,bc,d-ef,1 23,!,@a aa,\n,ee-e,@#$^&,ww, "}; //Ҫ��','����' '����'-'�ָ���ַ���
	
	buf4tok = mystrtok(srt_buf," ,-"); //�ȵ���һ�Σ���ȡ��һ��tok
    if(buf4tok != NULL)
    {
        for(i = 0;buf4tok != NULL;i++)
        {
            printf("%3d : %s\r\n",i,buf4tok);
            buf4tok = mystrtok(NULL," ,-"); //Ȼ��ѭ�����ã��ڶ��κ�֮������NULL��ÿ�ε��ö����ؽ�������tok��ֱ������NULLΪֹ
        }
    }
*/


