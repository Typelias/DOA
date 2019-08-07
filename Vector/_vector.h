#pragma once

template<typename T, int N_Shifts = 1>
class _vector
{
public:
    _vector()
    {
        index = 0;
        _capacity = 10;
        _data = new T[_capacity];
    }

    _vector(int size, T data)
    {
        index = 0;
        _capacity =  size;
        _data = new T[_capacity];
        while (index != size)
        {
            push_back(data);
        }
        
    }
    _vector(T* begin, T*end)
    {
        index = 0;
        _capacity = 10;
        _data = new T[_capacity];
        while(begin != end)
        {
            push_back(*begin);
            begin++;
        }
    }
    //Copy assign
    _vector<T>& operator =(const _vector<T> & rhs)
    {
        delete[] _data;
        _data = rhs._data;
        index = rhs.index;
        _capacity = rhs._capacity;
        return *this;

    }
    //Move assign
    /*_vector<T>& operator =(_vector<T>&& rhs)
    {
        delete[] _data;
        _data = rhs._data;
        index = rhs.index;
        _capacity = rhs._capacity;
        rhs._data = nullptr;
        return *this;

    }*/
    ~_vector()
    {
        delete[] _data;
    }

    void push_back(const T& indata)
    {
        if(index == _capacity-1)
            resize();
        _data[index] = indata;
        index++;
    }

    T* begin()
    {
        return _data;
    }
    T* end()
    {
        return _data+index;
    }
    const T* begin() const
    {
        return _data;
    }
    const T* end() const
    {
        return _data+index;
    }
    int size() const
    {
        return index;
    }
    T & operator[] (int i)
    {
        return _data[i];
    }
    bool empty() const
    {
        return index == 0;
    }

    int capacity()const
    {
        return _capacity;
    }
    
private:
    void resize()
    {
        _capacity <<= N_Shifts;
        T* temp = new T[_capacity];
        std::copy(_data, _data + index, temp);
        delete[] _data;
        _data = temp;
    }
    int index;
    int _capacity;
    T* _data;
};