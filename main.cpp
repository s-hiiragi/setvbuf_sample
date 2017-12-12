#include <cstdio>
using namespace std;

int main()
{
//    FILE *fp = fopen("/dev/null", "wb+");  // can not read data from fp
//    FILE *fp = fopen("hoge.tmp", "wb+");  // OK
    FILE *fp = tmpfile();  // OK
    if (fp == NULL) {
        fprintf(stderr, "fopen error\n");
        return 1;
    }

    // assign buffer to fp
    char fbuf[256] = {};
    setvbuf(fp, fbuf, _IOFBF, sizeof(fbuf));

    // write data to fp
    const char *msg = "Hello, Buffer as FILE!";
    printf("write message = %s\n", msg);
    fputs(msg, fp);

    printf("buffer = %s\n", fbuf);

    // rewind fp to head
    if (fseek(fp, 0L, SEEK_SET) != 0) {
        fprintf(stderr, "fseek error\n");
        goto err;
    }

    // read data from fp
    char rbuf[sizeof(fbuf)];
    fgets(rbuf, sizeof(rbuf), fp);
    printf("read buffer = \"%s\"\n", rbuf);

err:
    fclose(fp);

    return 0;
}

