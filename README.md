# gcc5_printf_check
GCC5 printf string format compilation time checking function


Using: 

WITH_CHECK(FUNC, FORMAT_STRING, ...);


Example: 

WITH_CHECK(printf, "[%d], [%s], [%d]\n", 1, 2, 3);


Output: 

throw "Wrong type of argument 2"

