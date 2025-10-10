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