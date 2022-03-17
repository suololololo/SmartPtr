#ifndef SHARE_PTR_H__
#define SHARE_PTR_H__

#include "refCouter.h"
#include <utility>
// 引用计数
// RAII
template <typename T>
class SharePtr
{
public:
    // 提供给T的构造函数使用
    SharePtr(T *p ) : data(p)
    {
    }
    SharePtr(T &p) : data(new T(p))
    {
    }
    SharePtr(T &&p) : data(new T(p))
    {
    }

public:
    SharePtr() : data(new T())
    {
    }
    // 拷贝构造
    SharePtr(const SharePtr &other) : data(other.data), count(other.count)
    {
    }

    SharePtr(SharePtr &&other) : data(other.data), count(other.count)
    {
    }
    SharePtr &operator=(const SharePtr &other)
    {
        if (count.unique())
        {
            delete data;
        }
        data = other.data;
        count = other.count;
        return *this;
    }
    SharePtr &operator=(SharePtr &&other) noexcept
    {
        if (count.unique())
            delete data;
        count = std::move(other.count);
        data = other.data;
        other.data = nullptr;
        return *this;
    }

    T *operator->() const noexcept
    {
        return data;
    }

    T &operator*() const noexcept
    {
        return *data;
    }

    ~SharePtr()
    {
        if (count.unique())
        {
            delete data;
            data = nullptr;
        }
        
    }

    // 返回共享对象的数量
    int user_count()
    {
        if (count)
        {
            return count.count;
        }
        return 0;
    }

private:
    T *data;
    RefCounter count;
};

#endif