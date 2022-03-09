#pragma once

template <typename T> class Singleton
{
private:
	static T* ms_singleton;

public:
	Singleton()
	{
		int offset = (int)(T*)1 - (int)(Singleton <T>*) (T*) 1;
		ms_singleton = (T*)((int)this + offset);
	}

	virtual ~Singleton()
	{
		ms_singleton = 0;
	}

	__forceinline static T* instance()
	{
		if (!ms_singleton)
			ms_singleton = new T;
		return ms_singleton;
	}
};

template <typename T> T* Singleton <T>::ms_singleton = 0;