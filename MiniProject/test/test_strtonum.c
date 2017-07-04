#include "unity.h"
#include "strtonum.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void setUp(void){}

void tearDown(void){}

void test_strtonum_given_1234_abcd_and_expect_1234_basedTen(void)
{
  char *ptr;
  long val;
  char value2Parse[] ="1234 abcd";
  val = strtol("1234 abcd", NULL, 10);
  TEST_ASSERT_EQUAL(1234, val);
}

void test_strtonum_given_8765_abcd_expect_8756(void)
{
  long val;
  char value2Parse[] =" 8756 abcd";
  val = strtol(value2Parse, NULL, 10);
  TEST_ASSERT_EQUAL(8756, val);
}


void test_strtonum_given_with__4567_abcd_expect_4567(void)
{
  long val;
  char value2Parse[] ="\t\t4567 abcd";
  val = strtol(value2Parse, NULL, 10);
  TEST_ASSERT_EQUAL(4567, val);
}

void test_strtonum_given_0x34567_abc_expect_0(void)
{
  long val;
  char *ptr; 
  char value2Parse[] ="0x234567 abc";
  val = strtol(value2Parse, &ptr, 10);
    TEST_ASSERT_EQUAL('x',*ptr);
     TEST_ASSERT_EQUAL(0, val);
}

void test_strtonum_given_0x123456_abc_expect_whitespace(void)
{
  long val;
  char *ptr; 
  char value2Parse[] ="0x123456 abc";
  val = strtol(value2Parse, &ptr, 16);
  TEST_ASSERT_EQUAL(' ',*ptr);
 } 
 
void test_strtonum_given_write_0x123123_abc_expect_w(void)
{
  long val;
  char *ptr; 
  char value2Parse[] ="write 0x123123 abc";
  val = strtol(value2Parse, &ptr, 16);
  TEST_ASSERT_EQUAL('w',*ptr);
}

void test_strtonum_given_0x123123_abc_expect_whitespace(void)
{
  long val;
  char *ptr; 
  char value2Parse[] =" 0x123123 abc";
  val = strtol(value2Parse, &ptr, 16);
  TEST_ASSERT_EQUAL(' ',*ptr);
}


void test_strtonum_given_write_0x123123_abc_expect_whitespace(void)
{
  long val;
  char *ptr; 
  char value2Parse[] =" write 0x123123 abc";
  val = strtol(value2Parse, &ptr, 0);
  TEST_ASSERT_EQUAL(' ',*ptr);
}

void test_strtonum_given__0x124556__0x1234_123_expect_whitespace(void)
{
  long val;
  char *ptr; 
  char value2Parse[] ="\t0x124556 \t0x1234 123";
  val = strtol(value2Parse, &ptr, 16);
  TEST_ASSERT_EQUAL(' ',*ptr);
}

void test_string_compare_insensitive_given_wRite_and_write(void){
  char *a = "wRite";
  char *b = "write";
  int cmp = strcmpInsensitive(a, b);
  TEST_ASSERT_EQUAL(0, cmp);
}
void test_string_compare_insensitive_given_write_and_writee(void){
  char *a = "write";
  char *b = "writee";
  int cmp = strcmpInsensitive(a, b);
  TEST_ASSERT_EQUAL(-1, cmp);
}
void test_string_compare_insensitive_given_write_and_write(void){
  char *a = "write";
  char *b = "write";
  int cmp = strcmpInsensitive(a, b);
  TEST_ASSERT_EQUAL(0, cmp);
}


void test_loop(void)
{
  char str[] = "124 125 126";
  char *endptr = str;
  int val;
  
  val = loop(&endptr);
  TEST_ASSERT_EQUAL(3,val);
} 

void test_loop_with_2(void)
{
  char str[] = "124 write 0x125 126";
  char *endptr = str;
  int val;
  
  val = loop(&endptr);
  TEST_ASSERT_EQUAL(3,val);
} 

void test_loop_with_3(void)
{
  char str[] = "20x124 write 0x125 126";
  char *endptr = str;
  int val;
  
  val = loop(&endptr);
  TEST_ASSERT_EQUAL(2,val);
} 


void test_getNumber_given_write_expect_ERR(void)
{
  char *str = "wrITe";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(2, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
}  

void test_getNumber_given_write__0X123456_expect_ERR(void)
{
  char *str = "write\t0X123456\t";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(2, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(1193046, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
}  

void test_getNumber_given_write__0x123456_expect_ERR(void)
{
  char *str = "write\t0x123456\t";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(2, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(1193046, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
}  

void test_getNumber_given__0x123456_write_expect_ERR(void)
{
  char *str = "\t0x123456 write ";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(1193046, val);  
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(2, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
} 

void test_getNumber_given__0x123456_writ_expect_ERR(void)
{
  char *str = "\t0x123456 writ ";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(1193046, val);  
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
} 

void test_getNumber_given_123456_reaD_expect_ERR(void)
{
  char *str = "123456 reaD";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(123456, val);  
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(2, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
} 

void test_getNumber_given__1x123456_wrITe_00x123_expect_ERR(void)
{
  char *str = "\t1x123456 wrIte 00x123";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(2, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
} 

void test_getNumber_given_0x1_expect_1(void)   
{
  char *str = "0x1";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(1, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);  
} 

void test_getNumber_given_20x1234_124_expect_ERR(void)   
{
  char *str = "20x1234 124";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(124, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
} 

void test_getNumber_given_02x1234_expect_ERR(void)   
{
  char *str = "02x1234\t";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
} 

void test_getNumber_given_write__0x1234_0x1_1_3expect_ERR(void)   
{
  char *str = "write \t 0x1234 0x1 1 3 ";
  long val = getNumber(&str);
  TEST_ASSERT_EQUAL(2, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(4660, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(1, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(1, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(3, val);
  val = getNumber(&str);
  TEST_ASSERT_EQUAL(-1, val);
} 
void test_loop_given_write__0x1234_0x1_1_3expect_ERR(void)   
{
  char str[] = "write \t 0x1234 0x1 1 3 ";
  char *endptr = str;
  int val;
  
  val = loop(&endptr);
  TEST_ASSERT_EQUAL(4,val);
} 

//sscanf

void test_sscanf_given_write_read(void)   
{
  char *str = "write read";
  int n;
  char data[15];
  n = sscanf(str,"%s",data);
  printf("%s\n\n", data);
  TEST_ASSERT_EQUAL(1, n);
} 

void test_sscanf_given__test(void)   
{
  char *str = " \t test";
  int n;
  char data[100];
  n = sscanf(str, "%*[ \t]%s", data);
  printf("%s\n\n", data);
  TEST_ASSERT_EQUAL(1,n);
} 

void test_sscanf_given__the_write(void)   
{
  char *str = "\t the write";
  int n;
  char data[100];
  n = sscanf(str, "%*[\t] the %s", data);
  printf("%s\n\n", data);
  TEST_ASSERT_EQUAL(1,n);
}  
