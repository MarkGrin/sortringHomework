#ifndef HPP_FF395039B6BC4E71BFEF5F114494977E

#define HPP_FF395039B6BC4E71BFEF5F114494977E

template<typename T>
class Singleton {

    Singleton(const Singleton<T>& ) = delete;
    Singleton(Singleton<T>&& ) = delete;
    Singleton<T>& operator= (const Singleton<T>& ) = delete;
    Singleton<T>& operator= (Singleton<T>&& ) = delete;

    protected:
            Singleton() = default;

    public:
        static T& instance() {
            static T obj;
            return obj;
        }
};


#endif /* HPP_FF395039B6BC4E71BFEF5F114494977E */
