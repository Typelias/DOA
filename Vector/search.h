namespace search
{
    template<typename Iter>
    Iter linearSearch(Iter begin, Iter end, int target)
    {
        for(Iter i = begin; i!=end; i++)
            if(*i == target)
                return i;
        return end; 
    }  
    template<typename Iter, typename T>
    Iter binarySearch(Iter begin, Iter end, T target)
    {
        if(end >= begin)
        {
            Iter mid = begin + (end - begin) / 2;
            if(*mid == target)
                return mid;
            if(*mid > target)
                return binarySearch(begin, mid-1, target);
            return binarySearch(mid+1, end, target);
        }
        return end;
    }

}