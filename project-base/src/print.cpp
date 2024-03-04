#include "../lib/hw.h"
#include "../h/syscall_c.h"

void printInteger(uint64 integer)
{
    static char digits[] = "0123456789";
    char buf[16];
    int i, neg;
    uint x;

    neg = 0;
    if (integer < 0)
    {
        neg = 1;
        x = -integer;
    } else
    {
        x = integer;
    }

    i = 0;
    do
    {
        buf[i++] = digits[x % 10];
    } while ((x /= 10) != 0);
    if (neg)
        buf[i++] = '-';

    while (--i >= 0) { putc(buf[i]); }

}
void printHexa(uint64 xx,uint padding){
    char buffer[16];
    for (int i = 7; i >= 0; i--)
    {
        uint8 byte = (xx >> (8 * i)) & 0xFF; // i-ti bajt
        buffer[15 - (i*2 + 1)] = ("0123456789ABCDEF"[byte >> 4]);
        buffer[15 - (i*2)] = ("0123456789ABCDEF"[byte & 0x0F]);
    }

    putc('0'); putc('x');

    int i = 0;
    while (i < 15 && buffer[i] == '0') i++;

    int len = 16 - i;
    int diff = padding - len;

    for (int j = 0; j < diff; j++) putc('0'); // padding
    while (i < 16) putc(buffer[i++]);
}
void printString(const char *string) {
    while(*string!='\0'){
        putc(*string);
        string++;
        }
}