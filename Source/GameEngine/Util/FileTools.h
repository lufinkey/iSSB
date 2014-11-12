
#include "ArrayList.h"
#include "String.h"

#pragma once

namespace GameEngine
{
	class FileTools
	{
	public:
		static ArrayList<String> getFoldersInDirectory(const String&directory, bool hidden=true);
		static ArrayList<String> getFilesInDirectory(const String&directory, bool hidden=true);
		static unsigned int totalFilesInDirectory(const String&directory, bool hidden=true);
		static bool directoryContainsFiles(const String&directory, bool hidden=true);
	
		static bool createFile(const String&path);
		static bool createDirectory(const String&directory);
#ifndef _WIN32
		static bool createSymbolicLink(const String&srcPath, const String&dstPath);
#endif
		static bool copyFile(const String&src, const String&dest);
		static bool copyFolder(const String&src, const String&dest);
		static bool fileExists(const String&path);
		static bool folderExists(const String&path);
		static bool pathIsFolder(const String&path);
		static bool pathIsFile(const String&path);
#ifndef _WIN32
		static bool expandPath(const String&path, String&dest);
#endif
		static bool deleteFromFilesystem(const String&path);
		static bool rename(const String&oldFile, const String&newFile);
		static bool loadFileIntoString(const String&path, String&str);
		static bool writeStringToFile(const String&path, const String&content);
		static bool appendStringToFile(const String&path, const String&content);
	};
}
