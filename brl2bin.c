
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <unistd.h>

int main(int argc, char **argv) {
  /* read buffer */
  wint_t w;
  /* enable CTYPE locale */
  setlocale(LC_CTYPE, "");
  /* loop */
  while(1) {
    /* clear errno so we can detect errors */
    errno = 0;
    /* get a char */
    w = fgetwc(stdin);
    /* zero bytes means end-of-file */
    if(w == WEOF) {
      if(errno) {
	perror("fgetwc");
	return 1;
      }
      break;
    }
    /* convert braille to binary */
    if((0x2800 <= w) && (w <= 0x28FF)) {
      fputc(w & 0xFF, stdout);
    } else {
      fputwc(w, stdout);
    }
  }
  /* flush output */
  fflush(stdout);
  /* done */
  return 0;
}
