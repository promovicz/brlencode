
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int res, i;
  /* read buffer */
  char buf[64];
  /* enable CTYPE locale */
  setlocale(LC_CTYPE, "");
  /* loop */
  while(1) {
    /* read chars from stdin */
    res = read(0, buf, sizeof(buf));
    /* zero bytes means end-of-file */
    if(res == 0) {
      break;
    }
    /* handle read errors */
    if(res == -1) {
      if(errno == EAGAIN) {
	/* ignore EAGAIN */
	continue;
      } else {
	/* print error and quit */
	perror("read");
	return 1;
      }
    }
    /* emit each byte on stdout as braille */
    for(i = 0; i < res; i++) {
      wchar_t w = 0x2800 + (buf[i] & 0xFF);
      fputwc(w, stdout);
    }
  }
  /* flush output */
  fflush(stdout);
  /* done */
  return 0;
}
