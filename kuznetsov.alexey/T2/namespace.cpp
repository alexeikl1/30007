#include "namespace.h"


namespace kuzn
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LabelCharIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data = "  ";
        std::getline(in >> DelimiterIO{ '\'' }, data, '\'');
        if (data[1] != '\0')
        {
            in.setstate(std::ios::failbit);
        }
        else
        {
            dest.ref = data[0];
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LongLongIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelimiterIO{ 'N' } >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, UnsLongLongIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelimiterIO{ 'D' } >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, KeyStringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ ':' }, dest.ref, ' ');
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data = "";
        if ((in >> KeyStringIO{ data }) && (data != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            bool flagkey1 = false, flagkey2 = false, flagkey3 = false;

            using sep = DelimiterIO;
            using chr = LabelCharIO;
            using ll = LongLongIO;
            using ull = UnsLongLongIO;
            using str = StringIO;

            in >> sep{ '(' };
            while (true) {
                if (flagkey1 && flagkey2 && flagkey3) break;
                std::string temp;
                char c;
                in >> c;
                if (!in) break;
                if (c == ':' && (in >> temp))
                {
                    if (temp == "key1")
                    {
                        in >> chr{ input.key1 };
                        flagkey1 = true;
                    }
                    else if (temp == "key2")
                    {
                        in >> sep{ '(' } >> sep{ ':' };
                        in >> ll{ input.key2.first } >> sep{ ':' } >> ull{ input.key2.second };
                        in >> sep{ ':' } >> sep{ ')' };
                        flagkey2 = true;
                    }
                    else if (temp == "key3")
                    {
                        in >> str{ input.key3 };
                        flagkey3 = true;
                    }
                }
            }
            in >> sep{ ':' } >> sep{ ')' };
        }

        if (in)
        {
            dest = input;
        }

        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:";
        out << "key1 '" << src.key1 << "'";
        out << ":key2 (:N " << std::fixed << std::setprecision(1) << src.key2.first;
        out << ":D " << std::fixed << std::setprecision(1) << src.key2.second << ":)";
        out << ":key3 \"" << src.key3 << "\"";
        out << ":)";
        return out;
    }

    iofmtguard::iofmtguard(std::basic_ios< char >& s) :
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {}

    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}