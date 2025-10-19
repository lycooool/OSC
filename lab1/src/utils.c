/*
string part
*/
int utils_str_compare(char *a, char *b){ //if same return 1
    char aa, bb;
    while(1)
    {
        aa = (char)*a++;
        bb = (char)*b++;
        if (aa != bb)
            return 0;
        if (aa == '\0')
            return 1;
    }
}

void utils_uint2str_hex(unsigned int num, char *str){

    // write 0x
    *str = '0';
    str++;
    *str = 'x';
    str++;
    unsigned int temp = num;
    int digit = -1;
    while (temp > 0)
    {
        temp /= 16;
        digit++;
    }
    for (int i = digit; i >= 0; i--)
    {
        int t = 1;
        for (int j = 0; j < i; j++)
        {
            t *= 16;
        }
        if (num / t >= 10) *str = 'a' + (num / t - 10);
        else *str = '0' + num / t;
        num = num % t;
        str++;
    }
    *str = '\0';
}

void utils_uint2str_dec(unsigned int num, char *str)
{

    unsigned int temp = num;
    int digit = -1;
    while (temp > 0)
    {
        temp /= 10;
        digit++;
    }
    for (int i = digit; i >= 0; i--)
    {
        int t = 1;
        for (int j = 0; j < i; j++)
        {
            t *= 10;
        }
        *str = '0' + num / t;
        num = num % t;
        str++;
    }
    *str = '\0';
}