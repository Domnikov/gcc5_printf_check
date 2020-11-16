#include "printf_check.hpp"

#include <cstdio>
#include <string>

int main()
{
    const char s[] = "Hello";
    WITH_CHECK(printf, "Strings:\n");
    WITH_CHECK(printf, "\t[%10s]\n\t[%-10s]\n\t[%*s]\n\t[%-10.*s]\n\t[%-*.*s]\n", s, std::string("Hello").c_str(), 10, s, 4, s, 10, 4, s);
    WITH_CHECK(printf, "Characters:\t%c %%\n", 65);
    WITH_CHECK(printf, "Integers\n");
    WITH_CHECK(printf, "Decimal:\t%i %d %.6i %i %.0i %+i %i\n", 1, 2, 3, 0, 0, 4, -4);
    WITH_CHECK(printf, "Hexadecimal:\t%x %x %X %#x\n", 5u, 10u, 10u, 6u);
    WITH_CHECK(printf, "Octal:\t%o %#o %#o\n", 10u, 10u, 4u);
    WITH_CHECK(printf, "Floating point\n");
    WITH_CHECK(printf, "Rounding:\t%f %.0f %.32f\n", 1.5, 1.5, 1.3);
    WITH_CHECK(printf, "Padding:\t%05.2f %.2f %5.2f\n", 1.5, 1.5, 1.5);
    WITH_CHECK(printf, "Scientific:\t%E %e\n", 1.5, 1.5);
    WITH_CHECK(printf, "Hexadecimal:\t%a %A\n", 1.5, 1.5);
    WITH_CHECK(printf, "Special values:\t0/0=%g 1/0=%g\n", 0.0/0.0, 1.0/0.0);
    WITH_CHECK(printf, "Variable width control:\n");
    WITH_CHECK(printf, "right-justified variable width: '%*c'\n", 5, 'x');
    WITH_CHECK(printf, "left-justified variable width : '%*c'\n", -5, 'x');

    WITH_CHECK(printf, std::string().c_str());

    return 0;
}
