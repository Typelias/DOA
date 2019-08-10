#pragma once

namespace search
{
template <typename Iter, typename T>
Iter BinarySearch(Iter begin, Iter end, T target)
{
    if (end >= begin)
    {
        Iter mid = begin + (end - begin) / 2;
        if (*mid == target)
            return mid;
        if (*mid > target)
            return BinarySearch(begin, mid - 1, target);
        return BinarySearch(mid + 1, end, target);
    }
    return end;
}
} // namespace search
