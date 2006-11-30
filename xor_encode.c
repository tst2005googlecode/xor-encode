#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>


/* from "mtwist.h" */
extern void mt_seed32new(unsigned long);
extern unsigned long mt_lrand(void);


typedef size_t fast_t;
typedef unsigned char byte;
#define BUFSIZE (2 << 14)    /* it must be exactly n*sizeof(fast_t) (here, 32768) */


int xor_encode(int key, FILE *in, FILE *out)
{
    size_t i, nread;

    const size_t optcoef = sizeof(fast_t) / sizeof(byte);
    const size_t n = BUFSIZE / optcoef;

    byte inbuf[BUFSIZE], outbuf[BUFSIZE];
    fast_t *_inbuf = (fast_t *)inbuf;
    fast_t *_outbuf = (fast_t *)outbuf;

    assert(in != NULL);
    assert(out != NULL);

    setbuf(in, NULL);
    setbuf(out, NULL);

    mt_seed32new(key);

    do
    {
        nread = fread(inbuf, sizeof(byte), BUFSIZE, in);

        for (i = 0; i < n; ++i)
            _outbuf[i] = _inbuf[i] ^ mt_lrand();

        fwrite(outbuf, sizeof(byte), nread, out);
    }
    while (nread);

    memset(inbuf, 0, BUFSIZE);
    memset(outbuf, 0, BUFSIZE);

    if (ferror(in) || ferror(out))
        return 0;

    return 1;
}
