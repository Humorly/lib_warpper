#pragma once

#ifndef __H_LIB_WARPPER_H__
#define __H_LIB_WARPPER_H__

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif // _WIN32

#include <string>
#include <cassert>
#include <functional>

#include <typeinfo>
#include <iostream>

namespace wstd
{
	class lib_warpper
	{
	public:
		// 打开库文件
		lib_warpper(std::string str_lib) 
		{
#ifdef _WIN32
			win_handle_ = LoadLibraryA(std::string(str_lib + ".dll").c_str());
			assert(win_handle_);
#else
			handle_ = dlopen(std::string(str_lib + ".so").c_str(), RTLD_LAZY);
			assert(handle_);

			dlerror();
#endif // _WIN32
		}

		// 移除对应库文件
		virtual ~lib_warpper() 
		{
#ifdef _WIN32
			if (nullptr != win_handle_) 
				FreeLibrary(win_handle_);
#else
			if (nullptr != handle_) 
				dlclose(handle_);
#endif // _WIN32	
		}

		template <class ret_type>
		ret_type * get_function(std::string str_func)
		{
			std::cout << typeid(ret_type *).name() << std::endl;

#ifdef _WIN32
			return (reinterpret_cast<ret_type *>(GetProcAddress(win_handle_, str_func.c_str())));
#else
			return (reinterpret_cast<ret_type *>(dlsym(handle_, str_func.c_str())));
#endif // _WIN32	
		}

	private:
		// 维持句柄
#ifdef _WIN32
		HMODULE win_handle_ = nullptr;
#else
		void * handle_ = nullptr;
#endif 
	};
}

#endif