// Courtesy of https://stackoverflow.com/questions/37421747/is-there-a-builtin-alternative-to-stdput-time-for-gcc-5
#pragma once

#include <iomanip>

#if __GNUC__ && __GNUC__ < 5
#include <ostream>

template<typename CharT>
struct _put_time
{
    const std::tm* time;
    const char* fmt;
};

template<typename CharT>
inline _put_time<CharT>
  put_time(const std::tm* time, const CharT* fmt)
{
    return {time, fmt};
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
  operator<<(std::basic_ostream<CharT, Traits>& os, _put_time<CharT> f)
{
    typedef typename std::ostreambuf_iterator<CharT, Traits> Iter;
    typedef std::time_put<CharT, Iter> TimePut;

    const CharT* const fmt_end = f.fmt + Traits::length(f.fmt);
    const TimePut& mp = std::use_facet<TimePut>(os.getloc());

    std::ios_base::iostate err = std::ios_base::goodbit;
    try
    {
        if (mp.put(Iter(os.rdbuf()), os, os.fill(), f.time, f.fmt, fmt_end).failed())
            err |= std::ios_base::badbit;
    }
    catch (...)
    {
        err |= std::ios_base::badbit;
    }

    if (err)
        os.setstate(err);

    return os;
}
#else
using std::put_time;
#endif
