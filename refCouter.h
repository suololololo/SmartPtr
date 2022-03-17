#ifndef REF_COUNTER_H__
#define REF_COUNTER_H__
class RefCounter
{
public:
    RefCounter() : count(new int(1))
    {
    }
    RefCounter(const RefCounter &other) : count(other.count)
    {
        (*count)++;
    }

    RefCounter(const RefCounter &&other) : count(other.count)
    {
        other.count == nullptr;
    }

    RefCounter &operator=(const RefCounter &other)
    {
        // 自身引用计数减少
        try_delease();
        count = other.count;
        (*count)++;
        return *this;
    }
    RefCounter &operator=(RefCounter &&other)
    {
        try_delease();
        count = other.count;
        (*count)++;
        other.count = nullptr;
        return *this;
    }

    ~RefCounter()
    {
        try_delease();
        count = nullptr;
    }
    bool unique()
    {
        return (*count) == 1;
    }

private:
    void try_delease()
    {
        if (count)
        {
            (*count)--;
            if (*count == 0)
            {
                delete count;
                count = nullptr;
            }
        }
    }

private:
    int *count;
};

#endif