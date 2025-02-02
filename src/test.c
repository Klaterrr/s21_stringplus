#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(test_s21_memchr_edge) {
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(s21_memchr(str, 'H', 0), NULL);
  ck_assert_ptr_eq(s21_memchr(str, 'H', 5), str);
  ck_assert_ptr_eq(s21_memchr(str, 'z', 13), NULL);
  ck_assert_ptr_eq(s21_memchr(str, 'o', 7), str + 4);
}
END_TEST

START_TEST(test_s21_memcmp_edge) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  char str3[] = "Hellx";
  ck_assert_int_eq(s21_memcmp(str1, str2, 5), 0);
  ck_assert_int_lt(s21_memcmp(str1, str3, 5), 0);
  ck_assert_int_eq(s21_memcmp(str1, str3, 4), 0);
}
END_TEST

START_TEST(test_s21_memcpy_edge) {
  char src[] = "Hello, World!";
  char dest[50];
  ck_assert_ptr_eq(s21_memcpy(dest, src, 0), dest);
  ck_assert_str_eq(s21_memcpy(dest, src, 5), "Hello");
  ck_assert_str_eq(s21_memcpy(dest, src, 13), "Hello, World!");
}
END_TEST

START_TEST(test_s21_memset_edge) {
  char str[50] = "Hello, World!";
  ck_assert_ptr_eq(s21_memset(str, 'a', 0), str);
  ck_assert_str_eq(s21_memset(str, 'x', 5), "xxxxx, World!");
  ck_assert_str_eq(s21_memset(str, 'z', 13), "zzzzzzzzzzzzz");
}
END_TEST

START_TEST(test_s21_strncat_edge) {
  char dest[50] = "Hello";
  char src[] = " World!";
  ck_assert_str_eq(s21_strncat(dest, src, 0), "Hello");
  ck_assert_str_eq(s21_strncat(dest, src, 5), "Hello Worl");
}
END_TEST

START_TEST(test_s21_strchr_edge) {
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(s21_strchr(str, 'H'), str);
  ck_assert_ptr_eq(s21_strchr(str, 'o'), str + 4);
  ck_assert_ptr_eq(s21_strchr(str, 'z'), NULL);
}
END_TEST

START_TEST(test_s21_strncmp_edge) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  char str3[] = "Hellx";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), 0);
  ck_assert_int_lt(s21_strncmp(str1, str3, 5), 0);
  ck_assert_int_eq(s21_strncmp(str1, str3, 4), 0);
}
END_TEST

START_TEST(test_s21_strncpy_edge) {
  char src[] = "Hello, World!";
  char dest[20];
  ck_assert_str_eq(s21_strncpy(dest, src, 0), "");
  ck_assert_str_eq(s21_strncpy(dest, src, 5), "Hello");
  ck_assert_str_eq(s21_strncpy(dest, src, 20), "Hello, World!");
}
END_TEST

START_TEST(test_s21_strcspn_edge) {
  char str1[] = "Hello, World!";
  char str2[] = " ,!";
  ck_assert_int_eq(s21_strcspn(str1, str2), 5);
}
END_TEST

START_TEST(test_s21_strerror_edge) {
  ck_assert_str_eq(s21_strerror(0), "Success");
  ck_assert_str_eq(s21_strerror(1), "Operation not permitted");
}
END_TEST

START_TEST(test_s21_strlen_edge) {
  char str[] = "Hello, World!";
  ck_assert_int_eq(s21_strlen(str), 13);
  ck_assert_int_eq(s21_strlen(""), 0);
}
END_TEST

START_TEST(test_s21_strpbrk_edge) {
  char str1[] = "Hello, World!";
  char str2[] = " ,!";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), str1 + 5);
}
END_TEST

START_TEST(test_s21_strrchr_edge) {
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), str + 8);
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), NULL);
}
END_TEST

START_TEST(test_s21_strstr_edge) {
  char haystack[] = "Hello, World!";
  char needle[] = "World";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), haystack + 7);
  ck_assert_ptr_eq(s21_strstr(haystack, "z"), NULL);
}
END_TEST

START_TEST(test_s21_strtok_edge) {
  char str[] = "Hello, World! How are you?";
  char *token;
  char *delim = " ,!?";
  token = s21_strtok(str, delim);
  ck_assert_str_eq(token, "Hello");
  token = s21_strtok(NULL, delim);
  ck_assert_str_eq(token, "World");
}
END_TEST

START_TEST(test_s21_sprintf_edge) {
  char buffer[100];
  ck_assert_int_eq(s21_sprintf(buffer, "%d", 40000), 5);
  ck_assert_str_eq(buffer, "40000");
  ck_assert_int_eq(s21_sprintf(buffer, "%ld", 3000000000), 10);
  ck_assert_str_eq(buffer, "3000000000");
  ck_assert_int_eq(s21_sprintf(buffer, "%hd", 16000), 5);
  ck_assert_str_eq(buffer, "16000");
  ck_assert_int_eq(s21_sprintf(buffer, "%ld", 1000000000000000000), 19);
  ck_assert_str_eq(buffer, "1000000000000000000");
  ck_assert_int_eq(s21_sprintf(buffer, "%u", 4294967254), 10);
  ck_assert_str_eq(buffer, "4294967254");
  ck_assert_int_eq(s21_sprintf(buffer, "%hu", -42), 5);
  ck_assert_str_eq(buffer, "65494");
  ck_assert_int_eq(s21_sprintf(buffer, "%lu", -42), 10);
  ck_assert_str_eq(buffer, "4294967254");
  ck_assert_int_eq(s21_sprintf(buffer, "%llu", -42), 10);
  ck_assert_str_eq(buffer, "4294967254");
  ck_assert_int_eq(s21_sprintf(buffer, "%c", 'h'), 1);
  ck_assert_str_eq(buffer, "h");
  ck_assert_int_eq(s21_sprintf(buffer, "%s", "hello world"), 11);
  ck_assert_str_eq(buffer, "hello world");
  ck_assert_int_eq(s21_sprintf(buffer, "%-lf", -123.456789), 11);
  ck_assert_str_eq(buffer, "-123.456789");
  ck_assert_int_eq(s21_sprintf(buffer, "%lf", 0.12), 8);
  ck_assert_str_eq(buffer, "0.120000");
}
END_TEST

START_TEST(test_s21_to_upper_edge) {
  char *point1 = s21_to_upper("hello");
  char *point2 = s21_to_upper("HELLO");
  char *point3 = s21_to_upper("");
  char *point4 = s21_to_upper("123abc");
  ck_assert_str_eq(point1, "HELLO");
  ck_assert_str_eq(point2, "HELLO");
  ck_assert_str_eq(point3, "");
  ck_assert_str_eq(point4, "123ABC");
  free(point1);
  free(point2);
  free(point3);
  free(point4);
}
END_TEST

START_TEST(test_s21_to_lower_edge) {
  char *point1 = s21_to_lower("HELLO");
  char *point2 = s21_to_lower("hello");
  char *point3 = s21_to_lower("");
  char *point4 = s21_to_lower("123ABC");
  ck_assert_str_eq(point1, "hello");
  ck_assert_str_eq(point2, "hello");
  ck_assert_str_eq(point3, "");
  ck_assert_str_eq(point4, "123abc");
  free(point1);
  free(point2);
  free(point3);
  free(point4);
}
END_TEST

START_TEST(test_s21_insert_edge) {
  char *point1 = s21_insert("hello", "world", 5);
  char *point2 = s21_insert("hello", "world", 0);
  char *point3 = s21_insert("", "world", 0);
  char *point4 = s21_insert("hello", "", 3);
  ck_assert_str_eq(point1, "helloworld");
  ck_assert_str_eq(point2, "worldhello");
  ck_assert_str_eq(point3, "world");
  ck_assert_str_eq(point4, "hello");
  free(point1);
  free(point2);
  free(point3);
  free(point4);
}
END_TEST

START_TEST(test_s21_trim_edge) {
  char *point1 = s21_trim("  hello  ", " ");
  char *point2 = s21_trim("--hello--", "-");
  char *point3 = s21_trim("hello", " ");
  char *point4 = s21_trim("", " ");
  ck_assert_str_eq(point1, "hello");
  ck_assert_str_eq(point2, "hello");
  ck_assert_str_eq(point3, "hello");
  ck_assert_str_eq(point4, "");
  free(point1);
  free(point2);
  free(point3);
  free(point4);
}
END_TEST

Suite *create_test_suite() {
  Suite *s = suite_create("s21_string_functions");

  TCase *tc_edge = tcase_create("Edge Cases");
  tcase_add_test(tc_edge, test_s21_memchr_edge);
  tcase_add_test(tc_edge, test_s21_memcmp_edge);
  tcase_add_test(tc_edge, test_s21_memcpy_edge);
  tcase_add_test(tc_edge, test_s21_memset_edge);
  tcase_add_test(tc_edge, test_s21_strncpy_edge);
  tcase_add_test(tc_edge, test_s21_strchr_edge);
  tcase_add_test(tc_edge, test_s21_strncmp_edge);
  tcase_add_test(tc_edge, test_s21_strncat_edge);
  tcase_add_test(tc_edge, test_s21_strcspn_edge);
  tcase_add_test(tc_edge, test_s21_strerror_edge);
  tcase_add_test(tc_edge, test_s21_strlen_edge);
  tcase_add_test(tc_edge, test_s21_strpbrk_edge);
  tcase_add_test(tc_edge, test_s21_strrchr_edge);
  tcase_add_test(tc_edge, test_s21_strstr_edge);
  tcase_add_test(tc_edge, test_s21_strtok_edge);
  tcase_add_test(tc_edge, test_s21_sprintf_edge);
  tcase_add_test(tc_edge, test_s21_to_upper_edge);
  tcase_add_test(tc_edge, test_s21_to_lower_edge);
  tcase_add_test(tc_edge, test_s21_insert_edge);
  tcase_add_test(tc_edge, test_s21_trim_edge);

  suite_add_tcase(s, tc_edge);

  return s;
}

int main() {
  Suite *s = create_test_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  srunner_set_log(sr, "test_report.log");
  srunner_free(sr);

  return 0;
}