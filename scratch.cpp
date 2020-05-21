#include <vector>
#include <iostream>

template<typename T1, typename T2>
T1 out(T1 x, T2 y)
{
  return x - y;
}

template <typename T1>
T1 out2(T1 x)
{ return x - 1; }

template<auto Func, typename T1, typename T2=void>
struct FWrap2
{
    auto operator()(T1 x, T2 y, const int size) const
    {
       // using res_type = typename std::result_of<Func(Args...)>::type;
        std::vector<T1> out_array;
        for (int i = 0; i < size; i++)
        {
            out_array.push_back(Func(x, y));
        }
        return out_array;
    }
};

template<auto Func, typename T1>
struct FWrap2<Func, T1>
{
    auto operator()(T1 x, const int size) const
    {
        std::vector<T1> out_array;
        for (int i = 0; i < size; i++)
        {
            out_array.push_back(Func(x));
        }
        return out_array;
    }
};

int main()
{
    //FWrap<out<int>> wrap;
    FWrap2<out<double, double>, double, double> wrap;
    FWrap2<out2<int>, int> wrap2;
    auto z = wrap(5, 2, 8);
    auto t = wrap2(5, 10);
    for (const auto& c:t)
    {
        std::cout << c;
    };
}