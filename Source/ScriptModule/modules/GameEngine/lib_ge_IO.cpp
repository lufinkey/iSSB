
#ifndef SMASHBROS_SCRIPT_DISABLE

#define _CRT_SECURE_NO_WARNINGS

#include "lib_GameEngine.h"

#include <stdio.h>
#include <cstdio>

namespace GameEngine
{
	static const byte IO_SEEK_SET = SEEK_SET;
	static const byte IO_SEEK_CUR = SEEK_CUR;
	static const byte IO_SEEK_END = SEEK_END;
	static const byte IO_FOPEN_MAX = FOPEN_MAX;

	size_t IO_fread(char*ptr, size_t size, size_t count, FILE*stream)
	{
		return std::fread((void*)ptr, size, count, stream);
	}
	size_t IO_fread(byte*ptr, size_t size, size_t count, FILE*stream)
	{
		return std::fread((void*)ptr, size, count, stream);
	}

	size_t IO_fwrite(const char * ptr, size_t size, size_t count, FILE * stream)
	{
		return std::fwrite((const void*)ptr, size, count, stream);
	}
	size_t IO_fwrite(const byte* ptr, size_t size, size_t count, FILE * stream)
	{
		return std::fwrite((const void*)ptr, size, count, stream);
	}

	byte* GameEngine_malloc(size_t size)
	{
		return (byte*)std::malloc(size);
	}

	byte* GameEngine_calloc(size_t count, size_t size)
	{
		return (byte*)std::calloc(count, size);
	}

	byte* GameEngine_realloc(byte*ptr, size_t newSize)
	{
		return (byte*)std::realloc((void*)ptr, newSize);
	}

	void GameEngine_free(byte*ptr)
	{
		std::free((void*)ptr);
	}
	

	chaiscript::ModulePtr load_module_GameEngine_IO()
	{
		chaiscript::Module* m_gameengine_io = new chaiscript::Module();

		//Console
		m_gameengine_io->add(chaiscript::fun((void(*)(const GameEngine::String&)) &GameEngine::Console::Write), "Console_Write");
		m_gameengine_io->add(chaiscript::fun((void(*)(const std::string&)) &GameEngine::Console::Write), "Console_Write");
		m_gameengine_io->add(chaiscript::fun((void(*)(const char*)) &GameEngine::Console::Write), "Console_Write");
		m_gameengine_io->add(chaiscript::fun((void(*)(const GameEngine::String&)) &GameEngine::Console::WriteLine), "Console_WriteLine");
		m_gameengine_io->add(chaiscript::fun((void(*)(const std::string&)) &GameEngine::Console::WriteLine), "Console_WriteLine");
		m_gameengine_io->add(chaiscript::fun((void(*)(const char*)) &GameEngine::Console::WriteLine), "Console_WriteLine");

		//file IO
		m_gameengine_io->add(chaiscript::user_type<FILE>(), "FILE");
		m_gameengine_io->add_global_const(chaiscript::const_var(GameEngine::IO_SEEK_SET), "IO_SEEK_SET");
		m_gameengine_io->add_global_const(chaiscript::const_var(GameEngine::IO_SEEK_CUR), "IO_SEEK_CUR");
		m_gameengine_io->add_global_const(chaiscript::const_var(GameEngine::IO_SEEK_END), "IO_SEEK_END");
		m_gameengine_io->add_global_const(chaiscript::const_var(GameEngine::IO_FOPEN_MAX), "IO_FOPEN_MAX");

		m_gameengine_io->add(chaiscript::fun((FILE*(*)(const char*,const char*)) &std::fopen), "IO_fopen");
		m_gameengine_io->add(chaiscript::fun(&std::fclose), "IO_fclose");
		m_gameengine_io->add(chaiscript::fun(&std::fgetc), "IO_fgetc");
		m_gameengine_io->add(chaiscript::fun(&std::fgets), "IO_fgets");
		m_gameengine_io->add(chaiscript::fun(&std::fputc), "IO_fputc");
		m_gameengine_io->add(chaiscript::fun(&std::fputs), "IO_fputs");
		m_gameengine_io->add(chaiscript::fun((size_t(*)(char*,size_t,size_t,FILE*)) &GameEngine::IO_fread), "IO_fread");
		m_gameengine_io->add(chaiscript::fun((size_t(*)(byte*,size_t,size_t,FILE*)) &GameEngine::IO_fread), "IO_fread");
		m_gameengine_io->add(chaiscript::fun((size_t(*)(const char*,size_t,size_t,FILE*)) &GameEngine::IO_fwrite), "IO_fwrite");
		m_gameengine_io->add(chaiscript::fun((size_t(*)(const byte*,size_t,size_t,FILE*)) &GameEngine::IO_fwrite), "IO_fwrite");
		m_gameengine_io->add(chaiscript::fun(&std::feof), "IO_feof");
		m_gameengine_io->add(chaiscript::fun(&std::freopen), "IO_freopen");
		m_gameengine_io->add(chaiscript::fun(&std::ferror), "IO_ferror");
		m_gameengine_io->add(chaiscript::fun(&std::ftell), "IO_ftell");
		m_gameengine_io->add(chaiscript::fun(&std::fseek), "IO_fseek");
		m_gameengine_io->add(chaiscript::fun(&std::fgetpos), "IO_fgetpos");
		m_gameengine_io->add(chaiscript::fun(&std::fsetpos), "IO_fsetpos");
		m_gameengine_io->add(chaiscript::fun(&std::fflush), "IO_fflush");
		//m_gameengine_io->add(chaiscript::fun(&std::fmemopen), "IO_fmemopen");
		//m_gameengine_io->add(chaiscript::fun(&std::fdopen), "IO_fdopen");
		m_gameengine_io->add(chaiscript::fun(&GameEngine_malloc), "malloc");
		m_gameengine_io->add(chaiscript::fun(&GameEngine_calloc), "calloc");
		m_gameengine_io->add(chaiscript::fun(&GameEngine_realloc), "realloc");
		m_gameengine_io->add(chaiscript::fun(&GameEngine_free), "free");

		return chaiscript::ModulePtr(m_gameengine_io);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
