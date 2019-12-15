#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int i_flag = 0;
  int c_flag = 0;
  int invalid_flag = 0;
  char opt;

  while ((opt = getopt(argc, argv, "ic")) != -1) {
    switch (opt) {
    case 'i':
      i_flag = 1;
      break;
    case 'c':
      c_flag = 1;
      break;
    case '?':

      invalid_flag = 1;
      fprintf(stderr, "INVALID ARGUMENT");
      exit(EXIT_FAILURE);

    default:

      fprintf(stderr, "SOME ERROR");
      exit(EXIT_FAILURE);
    }
  }

  FILE *fp;
  char buffer[500];
  char buffer_temp[500];
  char *pattern;
  pattern = argv[optind];
  optind = optind + 1;
  int lines;
  lines = 0;

  if ((optind + 1) > argc) {
    fprintf(stderr, "INVALID ARGUMENT\n");
    return EXIT_FAILURE;
  } else {
    while (optind < argc) {
      if ((fp = fopen(argv[optind], "r")) != NULL) {
        if ((((i_flag == 0) && (c_flag == 0)) ||
             ((i_flag == 0) && (c_flag == 1))) &&
            (invalid_flag == 0)) {
          while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, pattern)) {
              printf("%s: %s", argv[optind], buffer);
            }
            memset(buffer, 0, sizeof(buffer));
            lines = lines + 1;
          }
        } else if ((((i_flag == 1) && (c_flag == 0)) ||
                    ((i_flag == 1) && (c_flag == 1))) &&
                   (invalid_flag == 0)) {
          for (int i = 0; pattern[i]; i++) {
            *pattern = tolower(*pattern);
          }
          while (fgets(buffer, sizeof(buffer), fp)) {
            for (int i = 0; buffer[i]; i++) {
              buffer_temp[i] = tolower(buffer[i]);
            }
            if (strstr(buffer_temp, pattern)) {
              printf("%s: %s", argv[optind], buffer);
            }
            memset(buffer, 0, sizeof(buffer));
            memset(buffer_temp, 0, sizeof(buffer_temp));
            lines = lines + 1;
          }
        }

        optind = optind + 1;
        fclose(fp);
      } else {

        fprintf(stderr, "ERROR WHILE OPENING THE FILE\n");
        break;
      }
    }
  }
  if (c_flag == 1) {
    printf("Total lines scanned: %d\n", lines);
  }
  return EXIT_SUCCESS;
}
