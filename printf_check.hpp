#include <cstdint>
#include <type_traits>

#define WITH_CHECK(func, fmt, ...) \
    static_cast< \
        std::conditional_t< \
            decltype(erd_lib::is_constexpr_array(fmt)){} &&  \
            erd_lib::printf_check(fmt, decltype(erd_lib::unwrapper(__VA_ARGS__)){}) == 0,  \
                decltype(func( fmt, ##__VA_ARGS__)),  \
                decltype(func( fmt, ##__VA_ARGS__)) \
            > \
        > \
    (func(fmt, ##__VA_ARGS__))

namespace erd_lib
{
    namespace printf_check_impl
    {
        enum FORMAT_ERRORS
        {
            WRONG_FORMAT = -3,
            EXTRA_ARGUMENTS = -2,
            NOT_ENOUGH_ARGUMENTS = -1,
            NO_ERRORS = 0
        };

        constexpr int strncmp_ct(const char *s1, const char *s2, size_t n)
        {
          unsigned char u1 = 0x0, u2 = 0x0;

          while (n-- > 0)
            {
              u1 = (unsigned char) *s1++;
              u2 = (unsigned char) *s2++;
              if (u1 != u2)
            return u1 - u2;
              if (u1 == '\0')
            return 0;
            }
          return 0;
        }

        template <typename ... Args, std::enable_if_t<sizeof...(Args) == 0, int> = 0>
        constexpr int printf_check_impl(int, const char* fmt);


        template <typename First, typename ... Others>
        constexpr int printf_check_impl(int num, const char* fmt);


        template<typename ... Args, std::enable_if_t<sizeof...(Args) == 0, int> = 0>
        constexpr int parse_spec(int, const char*)
        {return 0;}


        template<typename First, typename ... Others>
        constexpr int parse_spec(int num, const char* fmt)
        {
            while(*fmt)
            {
                if     (strncmp_ct(fmt,  "c" , 1) == 0) { return std::is_convertible<First, const char   >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "lc" , 2) == 0) { return std::is_convertible<First, const wchar_t>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,  "s" , 1) == 0) { return (std::is_convertible<First, const char   *>{} || std::is_convertible<First, const unsigned char   *>{} ) ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "ls" , 2) == 0) { return std::is_convertible<First, const wchar_t*>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "i", 1) == 0) { return std::is_convertible<First, const int                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "hi", 2) == 0) { return std::is_convertible<First, const short                   >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "hhi", 3) == 0) { return std::is_convertible<First, const signed char             >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "li", 2) == 0) { return std::is_convertible<First, const long                    >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "lli", 3) == 0) { return std::is_convertible<First, const long long               >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "ji", 2) == 0) { return std::is_convertible<First, const intmax_t                >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "zi", 2) == 0) { return std::is_convertible<First, const std::make_signed<size_t>>{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "ti", 2) == 0) { return std::is_convertible<First, const std::ptrdiff_t          >{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "d", 1) == 0) { return std::is_convertible<First, const int                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "hd", 2) == 0) { return std::is_convertible<First, const short                   >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "hhd", 3) == 0) { return std::is_convertible<First, const signed char             >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "ld", 2) == 0) { return std::is_convertible<First, const long                    >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "lld", 3) == 0) { return std::is_convertible<First, const long long               >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "jd", 2) == 0) { return std::is_convertible<First, const intmax_t                >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "zd", 2) == 0) { return std::is_convertible<First, const std::make_signed<size_t>>{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "td", 2) == 0) { return std::is_convertible<First, const std::ptrdiff_t          >{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "o", 1) == 0) { return std::is_convertible<First, const unsigned int                      >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "ho", 2) == 0) { return std::is_convertible<First, const unsigned short                    >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "hho", 3) == 0) { return std::is_convertible<First, const unsigned char                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lo", 2) == 0) { return std::is_convertible<First, const unsigned long                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "llo", 3) == 0) { return std::is_convertible<First, const unsigned long long                >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "jo", 2) == 0) { return std::is_convertible<First, const uintmax_t                         >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "zo", 2) == 0) { return std::is_convertible<First, const size_t                            >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "to", 2) == 0) { return std::is_convertible<First, const std::make_unsigned<std::ptrdiff_t>>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "x", 1) == 0) { return std::is_convertible<First, const unsigned int                      >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "hx", 2) == 0) { return std::is_convertible<First, const unsigned short                    >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "hhx", 3) == 0) { return std::is_convertible<First, const unsigned char                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lx", 2) == 0) { return std::is_convertible<First, const unsigned long                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "llx", 3) == 0) { return std::is_convertible<First, const unsigned long long                >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "jx", 2) == 0) { return std::is_convertible<First, const uintmax_t                         >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "zx", 2) == 0) { return std::is_convertible<First, const size_t                            >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "tx", 2) == 0) { return std::is_convertible<First, const std::make_unsigned<std::ptrdiff_t>>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "X", 1) == 0) { return std::is_convertible<First, const unsigned int                      >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "hX", 2) == 0) { return std::is_convertible<First, const unsigned short                    >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "hhX", 3) == 0) { return std::is_convertible<First, const unsigned char                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lX", 2) == 0) { return std::is_convertible<First, const unsigned long                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "llX", 3) == 0) { return std::is_convertible<First, const unsigned long long                >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "jX", 2) == 0) { return std::is_convertible<First, const uintmax_t                         >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "zX", 2) == 0) { return std::is_convertible<First, const size_t                            >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "tX", 2) == 0) { return std::is_convertible<First, const std::make_unsigned<std::ptrdiff_t>>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "u", 1) == 0) { return std::is_convertible<First, const unsigned int                      >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "hu", 2) == 0) { return std::is_convertible<First, const unsigned short                    >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "hhu", 3) == 0) { return std::is_convertible<First, const unsigned char                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lu", 2) == 0) { return std::is_convertible<First, const unsigned long                     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "llu", 3) == 0) { return std::is_convertible<First, const unsigned long long                >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "ju", 2) == 0) { return std::is_convertible<First, const uintmax_t                         >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "zu", 2) == 0) { return std::is_convertible<First, const size_t                            >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "tu", 2) == 0) { return std::is_convertible<First, const std::make_unsigned<std::ptrdiff_t>>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "f", 1) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lf", 2) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "Lf", 2) == 0) { return std::is_convertible<First, const long double>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "F", 1) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lF", 2) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "LF", 2) == 0) { return std::is_convertible<First, const long double>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "e", 1) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "le", 2) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "Le", 2) == 0) { return std::is_convertible<First, const long double>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "E", 1) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lE", 2) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "LE", 2) == 0) { return std::is_convertible<First, const long double>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "a", 1) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "la", 2) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "La", 2) == 0) { return std::is_convertible<First, const long double>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "A", 1) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lA", 2) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "LA", 2) == 0) { return std::is_convertible<First, const long double>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "g", 1) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lg", 2) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "Lg", 2) == 0) { return std::is_convertible<First, const long double>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "G", 1) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "lG", 2) == 0) { return std::is_convertible<First, const double     >{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "LG", 2) == 0) { return std::is_convertible<First, const long double>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "n", 1) == 0) { return std::is_convertible<First, const int                     *>{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "hn", 2) == 0) { return std::is_convertible<First, const short                   *>{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "hhn", 3) == 0) { return std::is_convertible<First, const signed char             *>{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "ln", 2) == 0) { return std::is_convertible<First, const long                    *>{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt, "lln", 3) == 0) { return std::is_convertible<First, const long long               *>{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "jn", 2) == 0) { return std::is_convertible<First, const intmax_t                *>{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "zn", 2) == 0) { return std::is_convertible<First, const std::make_signed<size_t>*>{} ? printf_check_impl<Others...>(num, fmt) : num; }
                else if(strncmp_ct(fmt,  "tn", 2) == 0) { return std::is_convertible<First, const std::ptrdiff_t          *>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else if(strncmp_ct(fmt,   "p", 1) == 0) { return std::is_pointer<First>{} ? printf_check_impl<Others...>(num, fmt) : num; }

                else
                {
                    if(*fmt == '*')
                    {
                        if( !std::is_convertible<First, int>{}){return 1;}
                        else {return parse_spec<Others...>(num, ++fmt);}
                    }
                    else if( !(*fmt == '-' || *fmt == '+' || *fmt == '.' || *fmt == '#' || (*fmt >= '0' && *fmt <= '9')))
                    {
                        return WRONG_FORMAT;
                    }
                }


                fmt++;
            }
            return WRONG_FORMAT;
        }


        template <typename ... Args, std::enable_if_t<sizeof...(Args) == 0, int>>
        constexpr int printf_check_impl(int, const char* fmt)
        {
            for( ; *fmt != '\0'; fmt++)
            {
                if(*fmt == '%')
                {
                    if(*++fmt != '%')
                    {
                        return NOT_ENOUGH_ARGUMENTS;
                    }
                }
            }
            return 0;
        }

        template <typename First, typename ... Others>
        constexpr int printf_check_impl(int num, const char* fmt)
        {
            for( ; *fmt != '\0'; fmt++)
            {
                if(*fmt == '%')
                {
                    if(*++fmt != '%')
                    {
                        return parse_spec<First, Others...>(num+1, fmt);
                    }
                }
            }
            return EXTRA_ARGUMENTS;
        }


    }//namespace printf_check_impl

    template<typename ... Args> struct unwrap_args{};

    template<typename ... Args> unwrap_args<Args...> unwrapper(Args ...);


    template <typename U>        constexpr std::integral_constant<bool, false> is_constexpr_array(U);
    template <typename T, int N> constexpr std::integral_constant<bool, true > is_constexpr_array(T(&)[N]);


    template <typename ... Args>
    constexpr auto printf_check(const char* fmt, unwrap_args<Args ...>)
    {
        auto result = printf_check_impl::printf_check_impl<Args...>(0, fmt);
        (result == printf_check_impl::WRONG_FORMAT) ?
                    throw "Wrong format"
                  : 1;
        (result == printf_check_impl::EXTRA_ARGUMENTS) ?
                    throw "Extra arguments provided"
                  : 1;
        (result == printf_check_impl::NOT_ENOUGH_ARGUMENTS) ?
                    throw "Extra arguments required"
                  : 1;
        (result ==  1) ?
                    throw "Wrong type of argument 1"
                  : 1;
        (result ==  2) ?
                    throw "Wrong type of argument 2"
                  : 1;
        (result ==  3) ?
                    throw "Wrong type of argument 3"
                  : 1;
        (result ==  4) ?
                    throw "Wrong type of argument 4"
                  : 1;
        (result ==  5) ?
                    throw "Wrong type of argument 5"
                  : 1;
        (result ==  6) ?
                    throw "Wrong type of argument 6"
                  : 1;
        (result ==  7) ?
                    throw "Wrong type of argument 7"
                  : 1;
        (result ==  8) ?
                    throw "Wrong type of argument 8"
                  : 1;
        (result ==  9) ?
                    throw "Wrong type of argument 9"
                  : 1;
        (result == 10) ?
                    throw "Wrong type of argument 10"
                  : 1;
        (result !=  printf_check_impl::NO_ERRORS) ?
                    throw "One of arguments has wrong type"
                  : 1;

        return result;
    }

}//namespace erd_lib
