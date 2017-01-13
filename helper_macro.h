#pragma once

#define DECLARE_SINGLETON(TYPE)				\
private:                                    \
    TYPE();                                 \
    virtual ~TYPE();                    	\
    static TYPE *s_instance;                \
public:                                     \
static TYPE *GetInstance()			        \
{                                           \
    if (s_instance == nullptr)              \
        s_instance = new TYPE();            \
    return s_instance;                      \
}                                           \
static void DestroyInstance()				\
{                                           \
    if (s_instance != nullptr)              \
    {                                       \
        delete s_instance;                  \
        s_instance = nullptr;               \
    }                                       \
}                                           \

#define DEFINE_SINGLETON(TYPE)				\
    TYPE *TYPE::s_instance = nullptr;
