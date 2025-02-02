#include "s21_string.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1024

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *s = (const unsigned char *)str;
  unsigned char ch = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    if (s[i] == ch) {
      return (void *)(s + i);
    }
  }

  return s21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *p1 = (const unsigned char *)str1;
  const unsigned char *p2 = (const unsigned char *)str2;

  for (s21_size_t i = 0; i < n; i++) {
    if (p1[i] < p2[i]) {
      return -1;
    } else if (p1[i] > p2[i]) {
      return 1;
    }
  }

  return 0;
}

void *s21_memcpy(void *destination, const void *source, s21_size_t n) {
  unsigned char *dest = (unsigned char *)destination;
  const unsigned char *src = (const unsigned char *)source;

  for (s21_size_t i = 0; i < n; i++) {
    dest[i] = src[i];
  }
  dest[n] = '\0';
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = (unsigned char)c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = 0;
  s21_size_t i;

  while (dest[dest_len] != '\0') {
    dest_len++;
  }

  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[dest_len + i] = src[i];
  }

  dest[dest_len + i] = '\0';

  return dest;
}

char *s21_strchr(const char *str, int c) {
  while (*str != '\0') {
    if (*str == (char)c) {
      return (char *)str;
    }
    str++;
  }
  return (c == '\0') ? (char *)str : s21_NULL;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (; n > 0; n--, str1++, str2++) {
    if (*str1 != *str2) {
      break;
    }
  }
  if (n == 0)
    return 0;
  else
    return (*(unsigned char *)str1 - (*(unsigned char *)str2));
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (!dest || !src) return NULL;

  if (n == 0) {
    *dest = '\0';
    return dest;
  }

  s21_size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  for (; i < n; i++) {
    dest[i] = '\0';
  }

  dest[i] = '\0';

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t size = 0;
  while (!s21_strchr(str2, *str1) && *str1 != '\0') {
    str1++;
    size++;
  }
  return size;
}

char *s21_strerror(int errnum) {
  static char buffer[256];
#ifdef __linux__
#define S21_ERR_NUM 134
  static const char *s21_errlist[] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
  };
#elif defined(__APPLE__)
#define S21_ERR_NUM 107
  static const char *s21_errlist[] = {
      "Undefined error: 0",        "Operation not permitted",
      "No such file or directory", "No such process",
      "Interrupted system call",   "Input/output error",
      "Device not configured",     "Argument list too long",
      "Exec format error",         "Bad file descriptor",
      "No child processes",        "Resource deadlock avoided",
      "Cannot allocate memory",    "Permission denied",
  };
#else
#error "Unsupported platform"
#endif

  if (errnum >= 0 && errnum < S21_ERR_NUM) {
    return (char *)s21_errlist[errnum];
  } else {
    char num_str[12];
    int num = errnum;
    int is_negative = 0;
    int i = 0;
    if (num < 0) {
      is_negative = 1;
      num = -num;
    }
    do {
      num_str[i++] = '0' + (num % 10);
      num /= 10;
    } while (num > 0);
    if (is_negative) {
      num_str[i++] = '-';
    }
    num_str[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
      char temp = num_str[j];
      num_str[j] = num_str[i - j - 1];
      num_str[i - j - 1] = temp;
    }
    const char *unknown_error = "Unknown error ";
    size_t msg_len = s21_strlen(unknown_error);
    s21_memcpy(buffer, unknown_error, msg_len);
    s21_memcpy(buffer + msg_len, num_str, s21_strlen(num_str) + 1);

    return buffer;
  }
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (str && str[length] != '\0') {
    length++;
  }
  return length;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  if (!str1 || !str2) return NULL;

  while (*str1) {
    const char *s = str2;
    while (*s) {
      if (*str1 == *s) {
        return (char *)str1;
      }
      s++;
    }
    str1++;
  }

  return NULL;
}

char *s21_strrchr(const char *str, int c) {
  int is_flag = 0;
  char *char_res = s21_NULL;
  s21_size_t len_str = s21_strlen(str);
  str = str + len_str;

  for (int i = (int)len_str; !is_flag && i >= 0; i--) {
    if (*str == c) {
      char_res = (char *)str;
      is_flag = 1;
    }
    str--;
  }
  return char_res;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = s21_NULL;
  int err = 0;
  for (int x = 0; haystack[x] != '\0'; x++) {
    err = 0;
    for (int y = 0; needle[y] != '\0'; y++) {
      if (needle[y] != haystack[x + y]) {
        err = 1;
        break;
      }
    }
    if (err == 0) {
      res = (char *)&haystack[x];
      break;
    }
  }
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last = s21_NULL;
  char *token = s21_NULL;

  if (str != s21_NULL) {
    last = str;
  }

  while (last != s21_NULL && *last && s21_strchr(delim, *last)) {
    last++;
  }

  if (last == s21_NULL || *last == '\0') {
    token = s21_NULL;
  } else {
    token = last;

    while (*last && !s21_strchr(delim, *last)) {
      last++;
    }

    if (*last) {
      *last = '\0';
      last++;
    }
  }

  return token;
}

int is_int(char val) {
  int res = 1;
  if (val >= 48 && val <= 57) res = 0;
  return res;
}

char *int_in_str(int val, int *length, int plus_flag, int null_flag,
                 int accuracy_flag, int accuracy) {
  int len = 0;
  int res_val = val;
  if (val == 0)
    len = 1;
  else {
    if (res_val < 0) res_val = -res_val;
    len = (int)(log10(res_val)) + 1;
  }
  int size = len;
  int count = 0;
  int cura = 0;
  if (val < 0) len++;
  if (len > (*length)) (*length) = len;
  if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1 && accuracy_flag == 0) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  if (plus_flag == 1) {
    if (val < 0) {
      res[(*length) - len] = '-';
      count = (*length) - len + 1;
    } else
      count = (*length) - len;
    for (int i = count - accuracy + len; i < count; i++) {
      res[i] = '0';
    }

    for (int i = count; i < (*length); i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  } else {
    if (val < 0) {
      count = 1;
      res[0] = '-';
    }
    int res_size = size;
    for (int i = count; i < accuracy - len; i++) {
      res[i] = '0';
      count++;
    }
    for (int i = count; i < res_size + count; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  }
  return res;
}

char *long_int_in_str(long int val, int *length, int plus_flag, int null_flag,
                      int accuracy_flag, int accuracy) {
  int len = 0;
  long int res_val = val;
  if (val == 0)
    len = 1;
  else {
    if (res_val < 0) res_val = -res_val;
    len = (int)(log10(res_val)) + 1;
  }
  int size = len;
  int count = 0;
  int cura = 0;
  if (val < 0) len++;
  if (len > (*length)) (*length) = len;
  if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1 && accuracy_flag == 0) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  if (plus_flag == 1) {
    if (val < 0) {
      res[(*length) - len] = '-';
      count = (*length) - len + 1;
    } else
      count = (*length) - len;
    for (int i = count - accuracy + len; i < count; i++) {
      res[i] = '0';
    }

    for (int i = count; i < (*length); i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  } else {
    if (val < 0) {
      count = 1;
      res[0] = '-';
    }
    int res_size = size;
    for (int i = count; i < accuracy - len; i++) {
      res[i] = '0';
      count++;
    }
    for (int i = count; i < res_size + count; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  }

  return res;
}

char *short_int_in_str(short int val, int *length, int plus_flag, int null_flag,
                       int accuracy_flag, int accuracy) {
  int len = 0;
  short int res_val = val;
  if (val == 0)
    len = 1;
  else {
    if (res_val < 0) res_val = -res_val;
    len = (int)(log10(res_val)) + 1;
  }
  int size = len;
  int count = 0;
  int cura = 0;
  if (val < 0) len++;
  if (len > (*length)) (*length) = len;
  if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1 && accuracy_flag == 0) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  if (plus_flag == 1) {
    if (val < 0) {
      res[(*length) - len] = '-';
      count = (*length) - len + 1;
    } else
      count = (*length) - len;
    for (int i = count - accuracy + len; i < count; i++) {
      res[i] = '0';
    }

    for (int i = count; i < (*length); i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  } else {
    if (val < 0) {
      count = 1;
      res[0] = '-';
    }
    int res_size = size;
    for (int i = count; i < accuracy - len; i++) {
      res[i] = '0';
      count++;
    }
    for (int i = count; i < res_size + count; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  }

  return res;
}

char *long_long_int_in_str(long long int val, int *length, int plus_flag,
                           int null_flag, int accuracy_flag, int accuracy) {
  int len = 0;
  long long int res_val = val;
  if (val == 0)
    len = 1;
  else {
    if (res_val < 0) res_val = -res_val;
    len = (int)(log10(res_val)) + 1;
  }
  int size = len;
  int count = 0;
  int cura = 0;
  if (val < 0) len++;
  if (len > (*length)) (*length) = len;
  if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1 && accuracy_flag == 0) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  if (plus_flag == 1) {
    if (val < 0) {
      res[(*length) - len] = '-';
      count = (*length) - len + 1;
    } else
      count = (*length) - len;
    for (int i = count - accuracy + len; i < count; i++) {
      res[i] = '0';
    }

    for (int i = count; i < (*length); i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  } else {
    if (val < 0) {
      count = 1;
      res[0] = '-';
    }
    int res_size = size;
    for (int i = count; i < accuracy - len; i++) {
      res[i] = '0';
      count++;
    }
    for (int i = count; i < res_size + count; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  }

  return res;
}

char *unsigned_int_in_str(unsigned int val, int *length, int plus_flag,
                          int null_flag, int accuracy_flag, int accuracy) {
  int len = 0;
  unsigned int res_val = val;
  if (val == 0)
    len = 1;
  else {
    len = (int)(log10(res_val)) + 1;
  }
  int size = len;
  int count = 0;
  int cura = 0;

  if (len > (*length)) (*length) = len;
  if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1 && accuracy_flag == 0) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  if (plus_flag == 1) {
    count = (*length) - len;
    for (int i = count - accuracy + len; i < count; i++) {
      res[i] = '0';
    }

    for (int i = count; i < (*length); i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  } else {
    int res_size = size;
    for (int i = count; i < accuracy - len; i++) {
      res[i] = '0';
      count++;
    }
    for (int i = count; i < res_size + count; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  }

  return res;
}

char *unsigned_short_int_in_str(unsigned short int val, int *length,
                                int plus_flag, int null_flag, int accuracy_flag,
                                int accuracy) {
  int len = 0;
  unsigned short int res_val = val;
  if (val == 0)
    len = 1;
  else {
    len = (int)(log10(res_val)) + 1;
  }
  int size = len;
  int count = 0;
  int cura = 0;

  if (len > (*length)) (*length) = len;
  if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1 && accuracy_flag == 0) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  if (plus_flag == 1) {
    count = (*length) - len;
    for (int i = count - accuracy + len; i < count; i++) {
      res[i] = '0';
    }

    for (int i = count; i < (*length); i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  } else {
    int res_size = size;
    for (int i = count; i < accuracy - len; i++) {
      res[i] = '0';
      count++;
    }
    for (int i = count; i < res_size + count; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  }

  return res;
}

char *unsigned_long_int_in_str(unsigned long int val, int *length,
                               int plus_flag, int null_flag, int accuracy_flag,
                               int accuracy) {
  int len = 0;
  unsigned long int res_val = val;
  if (val == 0)
    len = 1;
  else {
    len = (int)(log10(res_val)) + 1;
  }
  int size = len;
  int count = 0;
  int cura = 0;

  if (len > (*length)) (*length) = len;
  if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1 && accuracy_flag == 0) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  if (plus_flag == 1) {
    count = (*length) - len;
    for (int i = count - accuracy + len; i < count; i++) {
      res[i] = '0';
    }

    for (int i = count; i < (*length); i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  } else {
    int res_size = size;
    for (int i = count; i < accuracy - len; i++) {
      res[i] = '0';
      count++;
    }
    for (int i = count; i < res_size + count; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  }

  return res;
}

char *unsigned_long_long_int_in_str(unsigned long long int val, int *length,
                                    int plus_flag, int null_flag,
                                    int accuracy_flag, int accuracy) {
  int len = 0;
  unsigned long long int res_val = val;
  if (val == 0)
    len = 1;
  else {
    len = (int)(log10(res_val)) + 1;
  }
  int size = len;
  int count = 0;
  int cura = 0;

  if (len > (*length)) (*length) = len;
  if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1 && accuracy_flag == 0) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  if (plus_flag == 1) {
    count = (*length) - len;
    for (int i = count - accuracy + len; i < count; i++) {
      res[i] = '0';
    }

    for (int i = count; i < (*length); i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  } else {
    int res_size = size;
    for (int i = count; i < accuracy - len; i++) {
      res[i] = '0';
      count++;
    }
    for (int i = count; i < res_size + count; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
  }

  return res;
}

char *char_in_str(char val, int *length, int plus_flag) {
  if ((*length) < 1) (*length) = 1;
  char *res = malloc(sizeof(char) * (*length));
  for (int i = 0; i < (*length); i++) {
    res[i] = ' ';
  }
  if (plus_flag == 1) {
    res[(*length) - 1] = val;
  } else {
    res[0] = val;
  }
  return res;
}

char *str_in_str(char *val, int *length, int plus_flag, int accuracy,
                 int accuracy_flag) {
  int len = 0;
  while (1) {
    if (val[len] == '\0' || (len >= accuracy && accuracy_flag == 1)) break;
    len++;
  }
  if (len > (*length)) (*length) = len;
  char *res = malloc(sizeof(char) * (*length));
  for (int i = 0; i < (*length); i++) {
    res[i] = ' ';
  }
  if (plus_flag == 1) {
    int count = 0;
    for (int i = (*length) - len; i < (*length); i++) {
      res[i] = val[count];
      count++;
    }
  } else {
    for (int i = 0; i < len; i++) {
      res[i] = val[i];
    }
  }
  return res;
}

char *float_in_str(double val, int *length, int plus_flag, int accuracy,
                   int null_flag, int accuracy_flag) {
  int zn = 0;
  if (val < 0) {
    zn = 1;
    val = -val;
  }
  int N = (int)val;
  int pointer = 6;
  int count = 0;
  int cura = 0;
  if (accuracy_flag == 1 && accuracy >= 0) pointer = accuracy;
  int R = rint(((val - (int)val) * pow(10, pointer + 1)) / 10);
  int len_1 = 0;
  if (N == 0)
    len_1 = 1;
  else
    len_1 = (int)log10(N) + 1;
  int len_2 = pointer;
  int len = len_1 + len_2;
  if (zn == 1) len++;
  int size = len_1;
  int size_2 = len_2;
  if (pointer != 0) len++;
  if (len > (*length)) (*length) = len;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  int res_val = N;
  if (plus_flag == 1) {
    if (zn == 1) {
      res[(*length) - len] = '-';
      count = (*length) - len + 1;
    } else
      count = (*length) - len;
    for (int i = count; i < (*length) - len_2 - 1; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
    if (pointer > 0) res[(*length) - len_2 - 1] = '.';
    for (int i = (*length) - len_2; i < (*length); i++) {
      cura = (int)(R / pow(10, size_2 - 1)) + 48;
      res[i] = cura;
      R = R - pow(10, size_2 - 1) * (cura - 48);
      size_2--;
    }
  } else {
    if (zn == 1) {
      res[0] = '-';
      count = 1;
      len_1++;
    } else
      count = 0;
    for (int i = count; i < len_1; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
    if (pointer > 0) res[len_1] = '.';
    for (int i = len_1 + 1; i < len; i++) {
      cura = (int)(R / pow(10, size_2 - 1)) + 48;
      res[i] = cura;
      R = R - pow(10, size_2 - 1) * (cura - 48);
      size_2--;
    }
  }
  return res;
}

char *double_in_str(double val, int *length, int plus_flag, int accuracy,
                    int null_flag, int accuracy_flag) {
  int zn = 0;
  if (val < 0) {
    zn = 1;
    val = -val;
  }
  int N = (int)val;
  int pointer = 6;
  int count = 0;
  int cura = 0;
  if (accuracy_flag == 1 && accuracy >= 0) pointer = accuracy;
  int R = rint(((val - (int)val) * pow(10, pointer + 1)) / 10);
  int len_1 = 0;
  if (N == 0)
    len_1 = 1;
  else
    len_1 = (int)log10(N) + 1;
  int len_2 = pointer;
  int len = len_1 + len_2;
  if (zn == 1) len++;
  int size = len_1;
  int size_2 = len_2;
  if (pointer != 0) len++;
  if (len > (*length)) (*length) = len;
  char *res = malloc(sizeof(char) * (*length));
  char point = ' ';
  if (null_flag == 1) point = '0';
  for (int i = 0; i < (*length); i++) {
    res[i] = point;
  }
  int res_val = N;
  if (plus_flag == 1) {
    if (zn == 1) {
      res[(*length) - len] = '-';
      count = (*length) - len + 1;
    } else
      count = (*length) - len;
    for (int i = count; i < (*length) - len_2 - 1; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
    if (pointer > 0) res[(*length) - len_2 - 1] = '.';
    for (int i = (*length) - len_2; i < (*length); i++) {
      cura = (int)(R / pow(10, size_2 - 1)) + 48;
      res[i] = cura;
      R = R - pow(10, size_2 - 1) * (cura - 48);
      size_2--;
    }
  } else {
    if (zn == 1) {
      res[0] = '-';
      count = 1;
      len_1++;
    } else
      count = 0;
    for (int i = count; i < len_1; i++) {
      cura = (int)(res_val / pow(10, size - 1)) + 48;
      res[i] = cura;
      res_val = res_val - pow(10, size - 1) * (cura - 48);
      size--;
    }
    if (pointer > 0) res[len_1] = '.';
    for (int i = len_1 + 1; i < len; i++) {
      cura = (int)(R / pow(10, size_2 - 1)) + 48;
      res[i] = cura;
      R = R - pow(10, size_2 - 1) * (cura - 48);
      size_2--;
    }
  }
  return res;
}

void spech(char *str, int *count, int *i, char format_1, char format_2,
           char format_3, va_list *arg, int length, int accuracy_flag,
           int accuracy, int plus_flag, int null_flag) {
  char *res = NULL;
  if (format_1 == 'd') {
    int val = va_arg(*arg, int);
    res =
        int_in_str(val, &length, plus_flag, null_flag, accuracy_flag, accuracy);
  } else if (format_1 == 'l' && format_2 == 'd') {
    (*i)++;
    long int val = va_arg(*arg, long int);
    res = long_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag,
                          accuracy);
  } else if (format_1 == 'h' && format_2 == 'd') {
    (*i)++;
    short int val = va_arg(*arg, int);
    res = short_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag,
                           accuracy);
  } else if (format_1 == 'l' && format_2 == 'l' && format_3 == 'd') {
    (*i) += 2;
    long long int val = va_arg(*arg, long long int);
    res = long_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag,
                          accuracy);
  } else if (format_1 == 'u') {
    unsigned int val = va_arg(*arg, unsigned int);
    res = unsigned_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag,
                              accuracy);
  } else if (format_1 == 'l' && format_2 == 'u') {
    (*i)++;
    unsigned long int val = va_arg(*arg, unsigned long int);
    res = unsigned_long_int_in_str(val, &length, plus_flag, null_flag,
                                   accuracy_flag, accuracy);
  } else if (format_1 == 'h' && format_2 == 'u') {
    (*i)++;
    unsigned short int val = va_arg(*arg, int);
    res = unsigned_short_int_in_str(val, &length, plus_flag, null_flag,
                                    accuracy_flag, accuracy);
  } else if (format_1 == 'l' && format_2 == 'l' && format_3 == 'u') {
    (*i) += 2;
    unsigned long long int val = va_arg(*arg, unsigned long long int);
    res = unsigned_long_long_int_in_str(val, &length, plus_flag, null_flag,
                                        accuracy_flag, accuracy);
  } else if (format_1 == 'c') {
    char val = va_arg(*arg, int);
    res = char_in_str(val, &length, plus_flag);
  } else if (format_1 == 's') {
    char *val = va_arg(*arg, char *);
    res = str_in_str(val, &length, plus_flag, accuracy, accuracy_flag);
  } else if (format_1 == 'f') {
    double val = va_arg(*arg, double);
    res = float_in_str(val, &length, plus_flag, accuracy, null_flag,
                       accuracy_flag);
  } else if (format_1 == 'l' && format_2 == 'f') {
    (*i)++;
    double val = va_arg(*arg, double);
    res = double_in_str(val, &length, plus_flag, accuracy, null_flag,
                        accuracy_flag);
  }
  if (res != NULL) {
    for (int x = 0; x < length; x++) {
      str[(*count)++] = res[x];
    }
    free(res);
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  int count = 0;
  for (int i = 0; format[i] != '\0'; i++) {
    if (format[i] == '%' && format[i + 1] != '\0') {
      i++;
      int plus_flag = 1;
      int null_flag = 0;
      int length = 0;
      int accuracy = 0;
      int accuracy_flag = 0;
      if (format[i] == ' ' || format[i] == '+') {
        i++;
        plus_flag = 1;
      } else if (format[i] == '-') {
        i++;
        plus_flag = 0;
      } else if (format[i] == '0') {
        i++;
        null_flag = 1;
      }
      if (format[i] == '*') {
        length = va_arg(arg, int);
        i++;
      } else if (!is_int(format[i])) {
        int size = 0;
        char *char_int_1 = malloc(sizeof(char) * size);
        char *char_int = s21_NULL;
        while (!is_int(format[i])) {
          char_int = realloc(char_int_1, sizeof(char) * (++size));
          char_int[size - 1] = format[i];
          i++;
          char_int_1 = char_int;
        }
        for (int x = 0; x < size; x++) {
          length += (pow(10, size - x - 1)) * (char_int[x] - 48);
        }
        free(char_int);
        char_int = NULL;
      }
      if (format[i] == '.') {
        i++;
        if (format[i] == '*') {
          accuracy = va_arg(arg, int);
          accuracy_flag = 1;
          i++;
        } else if (!is_int(format[i])) {
          accuracy_flag = 1;
          int size = 0;
          char *char_int_1 = malloc(sizeof(char) * size);
          char *char_int = s21_NULL;
          while (!is_int(format[i])) {
            char_int = realloc(char_int_1, sizeof(char) * (++size));
            char_int[size - 1] = format[i];
            i++;
            char_int_1 = char_int;
          }
          for (int x = 0; x < size; x++) {
            accuracy += (pow(10, size - x - 1)) * (char_int[x] - 48);
          }
          free(char_int);
          char_int = NULL;
        }
      }
      spech(str, &count, &i, format[i], format[i + 1], format[i + 2], &arg,
            length, accuracy_flag, accuracy, plus_flag, null_flag);
    } else {
      str[count++] = format[i];
    }
  }
  str[count] = '\0';
  va_end(arg);
  return count;
}

void *s21_to_upper(const char *str) {
  char *result = s21_NULL;
  if (str) {
    s21_size_t len = s21_strlen(str);
    result = malloc((len + 1) * sizeof(char));
    if (result) {
      for (s21_size_t i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          result[i] = str[i] - 32;
        } else {
          result[i] = str[i];
        }
      }
      result[len] = '\0';
    }
  }
  return result;
}

void *s21_to_lower(const char *str) {
  char *result = s21_NULL;
  if (str) {
    s21_size_t len = s21_strlen(str);
    result = malloc((len + 1) * sizeof(char));
    if (result) {
      for (s21_size_t i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          result[i] = str[i] + 32;
        } else {
          result[i] = str[i];
        }
      }
      result[len] = '\0';
    }
  }
  return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = s21_NULL;
  if (src && str && start_index <= s21_strlen(src)) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);
    result = malloc((src_len + str_len + 1) * sizeof(char));
    if (result) {
      s21_memcpy(result, src, start_index);
      s21_memcpy(result + start_index, str, str_len);
      s21_memcpy(result + start_index + str_len, src + start_index,
                 src_len - start_index);
      result[src_len + str_len] = '\0';
    }
  }
  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  if (src && trim_chars) {
    s21_size_t start = 0, end = s21_strlen(src);

    while (start < end && s21_strchr(trim_chars, src[start])) {
      start++;
    }

    while (end > start && s21_strchr(trim_chars, src[end - 1])) {
      end--;
    }

    s21_size_t len = end - start;
    result = malloc((len + 1) * sizeof(char));
    if (result) {
      s21_memcpy(result, src + start, len);
      result[len] = '\0';
    }
  }
  return result;
}