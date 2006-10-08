#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE (2 << 14)    /* it must be exactly n*sizeof(fast_t) (here, 32768) */

typedef size_t fast_t;
#define FAST_MAX ULONG_MAX
typedef unsigned char byte;


int xor_encode(int key, FILE *in, FILE *out)
{
    size_t i, nread;

    const size_t optcoef = sizeof(fast_t) / sizeof(byte);
    const size_t n = BUFSIZE / optcoef;
    const size_t randcoef = FAST_MAX / RAND_MAX;

    byte inbuf[BUFSIZE], outbuf[BUFSIZE];
    fast_t *_inbuf = (fast_t *)inbuf;
    fast_t *_outbuf = (fast_t *)outbuf;

    assert(in != NULL);
    assert(out != NULL);

    setbuf(in, NULL);
    setbuf(out, NULL);

    srand(key);

    do
    {
        nread = fread(inbuf, sizeof(byte), BUFSIZE, in);

        for (i = 0; i != n; ++i)
            _outbuf[i] = _inbuf[i] ^ (rand() * randcoef);

        fwrite(outbuf, sizeof(byte), nread, out);
    }
    while (nread);

    memset(inbuf, 0, BUFSIZE);
    memset(outbuf, 0, BUFSIZE);

    if (ferror(in) || ferror(out))
        return 0;

    return 1;
}
