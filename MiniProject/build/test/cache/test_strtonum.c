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



void test_string_compare_insensitive_given_wRite_and_write(void){

  char *a = "wRite";

  char *b = "write";

  int cmp = strcmpInsensitive(a, b);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((cmp)), (

 ((void *)0)

 ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_INT);

}

void test_string_compare_insensitive_given_write_and_writee(void){

  char *a = "write";

  char *b = "writee";

  int cmp = strcmpInsensitive(a, b);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((cmp)), (

 ((void *)0)

 ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_INT);

}

void test_string_compare_insensitive_given_write_and_write(void){

  char *a = "write";

  char *b = "write";

  int cmp = strcmpInsensitive(a, b);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((cmp)), (

 ((void *)0)

 ), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_INT);

}





void test_loop(void)

{

  char str[] = "124 125 126";

  char *endptr = str;

  int val;



  val = loop(&endptr);

  UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_INT);

}



void test_loop_with_2(void)

{

  char str[] = "124 write 0x125 126";

  char *endptr = str;

  int val;



  val = loop(&endptr);

  UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_INT);

}



void test_loop_with_3(void)

{

  char str[] = "20x124 write 0x125 126";

  char *endptr = str;

  int val;



  val = loop(&endptr);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_INT);

}





void test_getNumber_given_write_expect_ERR(void)

{

  char *str = "wrITe";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(148), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given_write__0X123456_expect_ERR(void)

{

  char *str = "write\t0X123456\t";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(157), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((1193046)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(159), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(161), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given_write__0x123456_expect_ERR(void)

{

  char *str = "write\t0x123456\t";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(168), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((1193046)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(170), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(172), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given__0x123456_write_expect_ERR(void)

{

  char *str = "\t0x123456 write ";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((1193046)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(179), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(181), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(183), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given__0x123456_writ_expect_ERR(void)

{

  char *str = "\t0x123456 writ ";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((1193046)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(190), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(192), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given_123456_reaD_expect_ERR(void)

{

  char *str = "123456 reaD";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((123456)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(201), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(203), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(205), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given__1x123456_wrITe_00x123_expect_ERR(void)

{

  char *str = "\t1x123456 wrIte 00x123";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(212), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(214), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(216), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(218), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given_0x1_expect_1(void)

{

  char *str = "0x1";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(225), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(227), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given_20x1234_124_expect_ERR(void)

{

  char *str = "20x1234 124";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(234), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((124)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(236), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(238), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given_02x1234_expect_ERR(void)

{

  char *str = "02x1234\t";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(245), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(247), UNITY_DISPLAY_STYLE_INT);

}



void test_getNumber_given_write__0x1234_0x1_1_3expect_ERR(void)

{

  char *str = "write \t 0x1234 0x1 1 3 ";

  long val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(254), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((4660)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(256), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(258), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(260), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(262), UNITY_DISPLAY_STYLE_INT);

  val = getNumber(&str);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(264), UNITY_DISPLAY_STYLE_INT);

}

void test_loop_given_write__0x1234_0x1_1_3expect_ERR(void)

{

  char str[] = "write \t 0x1234 0x1 1 3 ";

  char *endptr = str;

  int val;



  val = loop(&endptr);

  UnityAssertEqualNumber((UNITY_INT)((4)), (UNITY_INT)((val)), (

 ((void *)0)

 ), (UNITY_UINT)(273), UNITY_DISPLAY_STYLE_INT);

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

 ), (UNITY_UINT)(285), UNITY_DISPLAY_STYLE_INT);

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

 ), (UNITY_UINT)(295), UNITY_DISPLAY_STYLE_INT);

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

 ), (UNITY_UINT)(305), UNITY_DISPLAY_STYLE_INT);

}
