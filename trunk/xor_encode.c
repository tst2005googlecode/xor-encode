#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>


void init_genrand(unsigned long);
unsigned long genrand_int32(void);


typedef size_t fast_t;
typedef unsigned char byte;
#define BUFSIZE 4096


int xor_encode(int key, FILE *in, FILE *out)
{
    size_t i, nread;

    const size_t n = BUFSIZE / sizeof(fast_t);

    byte inbuf[BUFSIZE], outbuf[BUFSIZE];
    fast_t *_inbuf = (fast_t *)inbuf;
    fast_t *_outbuf = (fast_t *)outbuf;

    assert(in != NULL);
    assert(out != NULL);

    init_genrand(key);

    do {
        nread = fread(inbuf, sizeof(byte), BUFSIZE, in);

        for (i = 0; i < n; ++i)
            _outbuf[i] = _inbuf[i] ^ genrand_int32();

        fwrite(outbuf, sizeof(byte), nread, out);
    }
    while (nread);

    memset(inbuf, 0, BUFSIZE);
    memset(outbuf, 0, BUFSIZE);

    if (ferror(in) || ferror(out))
        return 0;

    return 1;
}

