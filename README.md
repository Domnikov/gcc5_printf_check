# gcc5_printf_check
Compilation time checking printf string format and arguments checking.


Using: 

WITH_CHECK(FUNC, FORMAT_STRING, ...);


Example: 

WITH_CHECK(printf, "[%d], [%s], [%d]\n", 1, 2, 3);


Output: 

throw "Wrong type of argument 2"

