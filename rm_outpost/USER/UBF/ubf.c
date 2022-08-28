#include "ubf.h"

#include "string.h"
#include "stdlib.h"

struct _ubf_t
{
    void* pbuff;//���������׵�ַ
    uint32_t num;//num��size�ֽڵ����ݵ�Ԫ
    uint32_t size;
    uint32_t write;//��д�뵥Ԫ������(write-1)ָ����������
};

ubf_t ubf_create(uint32_t num, uint32_t size)
{
    ubf_t pubf = (ubf_t)malloc(sizeof(struct _ubf_t));
    memset(pubf, 0, sizeof(struct _ubf_t));
    if (pubf)
    {
        pubf->num = num;
        pubf->size = size;
        pubf->pbuff = calloc(num, size);
        return pubf;
    }
    return NULL;
}

void ubf_delete(ubf_t ubf)
{
    free(ubf);
}

uint8_t ubf_input(ubf_t ubf, const void* pdata)
{
    if (ubf == NULL)
        return 1;
    memcpy((uint8_t*)ubf->pbuff+ubf->write*ubf->size, pdata, ubf->size);
    if (++ubf->write >= ubf->num)
        ubf->write = 0;
    return 0;
}

void* ubf_get(ubf_t ubf, uint32_t k)
{
    void* res;
    if (ubf == NULL)//������������
        res = NULL;
    else if (k < ubf->write)//��ǰ��ȡ
        res = (uint8_t*)ubf->pbuff + (ubf->write-1-k)*ubf->size;
    else if (k < ubf->num)//�ۻ�β����ȡ
        res = (uint8_t*)ubf->pbuff + ((ubf->num - 1) - (k - ubf->write)) * ubf->size;
    else//������������
        res = NULL;
    return res;
}

void ubf_clear(ubf_t ubf)
{
    if (ubf == NULL)//������������
        return;
    memset(ubf->pbuff, 0, ubf->num * ubf->size);
    ubf->write = 0;
}

/**
 * @brief ģ����Դ���,��ע�ͺ����в鿴�ڴ�ֵ��֤
 */
//#define TEST_ENABLE

#ifdef TEST_ENABLE
struct _test_t
{
    float a;
    int b;
    char c;
}test;

int main()
{
    uint8_t i;
    struct _test_t* tt;
    test.a = 0.1;
    test.b = 0;
    test.c = 124;

    ubf_t ubf = ubf_create(5, sizeof(test));

    for (i=0; i<8; i++)
    {
        ubf_input(ubf, &test);
        test.b++;
    }
    for (i=0; i<8; i++)
    {
        tt = ubf_get(ubf, i);
    }
    ubf_delete(ubf);
    return 0;
}
#endif

