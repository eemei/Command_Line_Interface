#include "build/temp/_test_strtonum.c"
#include "strtonum.h"
#include "unity.h"








void setUp(void){}



void tearDown(void){}



void test_strtonum_given_1234_abcd_and_expect_1234_basedTen(void)

{

  char *ptr;

  long val;

  char value2Parse[] ="1234 abcd";

  val = strtol("1234 abcd", 

                           ((void *)0)

                               , 10);

  UnityAssertEqualNumber((UNITY_INT)((1234)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_INT);

}



void test_strtonum_given_8765_abcd_expect_8756(void)

{

  long val;

  char value2Parse[] =" 8756 abcd";

  val = strtol(value2Parse, 

                           ((void *)0)

                               , 10);

  UnityAssertEqualNumber((UNITY_INT)((8756)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

}





void test_strtonum_given_with__4567_abcd_expect_4567(void)

{

  long val;

  char value2Parse[] ="\t\t4567 abcd";

  val = strtol(value2Parse, 

                           ((void *)0)

                               , 10);

  UnityAssertEqualNumber((UNITY_INT)((4567)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT);

}



void test_strtonum_given_0x34567_abc_expect_0(void)

{

  long val;

  char *ptr;

  char value2Parse[] ="0x234567 abc";

  val = strtol(value2Parse, &ptr, 10);

    UnityAssertEqualNumber((UNITY_INT)(('x')), (UNITY_INT)((*ptr)), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);

     UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((val)), (

    ((void *)0)

    ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT);

}



void test_strtonum_given_0x123456_abc_expect_whitespace(void)

{

  long val;

  char *ptr;

  char value2Parse[] ="0x123456 abc";

  val = strtol(value2Parse, &ptr, 16);

  UnityAssertEqualNumber((UNITY_INT)((' ')), (UNITY_INT)((*ptr)), (

 ((void *)0)

 ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_INT);

 }



void test_strtonum_given_write_0x123123_abc_expect_w(void)

{

  long val;

  char *ptr;

  char value2Parse[] ="write 0x123123 abc";

  val = strtol(value2Parse, &ptr, 16);

  UnityAssertEqualNumber((UNITY_INT)(('w')), (UNITY_INT)((*ptr)), (

 ((void *)0)

 ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);

}



void test_strtonum_given_0x123123_abc_expect_whitespace(void)

{

  long val;

  char *ptr;

  char value2Parse[] =" 0x123123 abc";

  val = strtol(value2Parse, &ptr, 16);

  UnityAssertEqualNumber((UNITY_INT)((' ')), (UNITY_INT)((*ptr)), (

 ((void *)0)

 ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT);

}





void test_strtonum_given_write_0x123123_abc_expect_whitespace(void)

{

  long val;

  char *ptr;

  char value2Parse[] =" write 0x123123 abc";

  val = strtol(value2Parse, &ptr, 0);

  UnityAssertEqualNumber((UNITY_INT)((' ')), (UNITY_INT)((*ptr)), (

 ((void *)0)

 ), (UNITY_UINT)(81), UNITY_DISPLAY_STYLE_INT);

}



void test_strtonum_given__0x124556__0x1234_123_expect_whitespace(void)

{

  long val;

  char *ptr;

  char value2Parse[] ="\t0x124556 \t0x1234 123";

  val = strtol(value2Parse, &ptr, 16);

  UnityAssertEqualNumber((UNITY_INT)((' ')), (UNITY_INT)((*ptr)), (

 ((void *)0)

 ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT);

}



void test_strtonum_given__0xaaaaaaaa_expect_0xaaaaaaaa(void)

{

  unsigned long val;

  char *ptr;

  char value2Parse[] ="0xaaaaaaaa";

  val = strtoul(value2Parse, &ptr, 16);

  UnityAssertEqualNumber((UNITY_INT)((0xaaaaaaaa)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(99), UNITY_DISPLAY_STYLE_INT);

}

void test_sscanf_given_write_read(void)

{

  char *str = "write read";

  int n;

  char data[15];

  n = sscanf(str,"%s",data);

  printf("%s\n\n", data);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((n)), (

 ((void *)0)

 ), (UNITY_UINT)(275), UNITY_DISPLAY_STYLE_INT);

}



void test_sscanf_given__test(void)

{

  char *str = " \t test";

  int n;

  char data[100];

  n = sscanf(str, "%*[ \t]%s", data);

  printf("%s\n\n", data);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((n)), (

 ((void *)0)

 ), (UNITY_UINT)(285), UNITY_DISPLAY_STYLE_INT);

}



void test_sscanf_given__the_write(void)

{

  char *str = "\t the write";

  int n;

  char data[100];

  n = sscanf(str, "%*[\t] the %s", data);

  printf("%s\n\n", data);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((n)), (

 ((void *)0)

 ), (UNITY_UINT)(295), UNITY_DISPLAY_STYLE_INT);

}
