
#define _CRT_SECURE_NO_WARNINGS

#include "FileTools.h"
#include "../Output/Console.h"
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <fstream>

#if defined(__APPLE__)
	#include <copyfile.h>
	#include <unistd.h>
#elif defined(_WIN32)
	#include <windows.h>
	#include <WinBase.h>
	#include <direct.h>
#else
	#include <unistd.h>
#endif

namespace GameEngine
{
	ArrayList<String> FileTools::getFoldersInDirectory(const String&directory, bool hidden)
	{
		DIR*dir = opendir(directory);
		if(dir==NULL)
		{
			Console::WriteLine((String)"Error: directory \"" + directory + "\" does not exist!");
			return ArrayList<String>();
		}
	
		ArrayList<String> folders;
	
		if(dir!=NULL)
		{
			struct dirent *entry = readdir(dir);

			while (entry != NULL)
			{
				if(entry->d_type == DT_DIR)
				{
					String folderName = entry->d_name;
					if(!folderName.equals(".") && !folderName.equals(".."))
					{
						if(hidden || (!hidden && folderName.charAt(0)!='.'))
						{
							folders.add(entry->d_name);
						}
					}
				}
				entry = readdir(dir);
			}
			closedir(dir);
		}
	
		return folders;
	}

	ArrayList<String> FileTools::getFilesInDirectory(const String&directory, bool hidden)
	{
		DIR*dir = opendir(directory);
		if(dir==NULL)
		{
			Console::WriteLine((String)"Error: directory \"" + directory + "\" does not exist!");
			return ArrayList<String>();
		}
	
		struct dirent *entry = readdir(dir);
	
		ArrayList<String> files;
	
		while (entry != NULL)
		{
			if(entry->d_type == DT_REG)
			{
				String fileName = entry->d_name;
				if(!fileName.equals(".") && !fileName.equals(".."))
				{
					if(hidden || (!hidden && fileName.charAt(0)!='.'))
					{
						files.add(entry->d_name);
					}
				}
			}
		
			entry = readdir(dir);
		}
	
		closedir(dir);
	
		return files;
	}

	unsigned int FileTools::totalFilesInDirectory(const String&directory, bool hidden)
	{
		unsigned int total = 0;
	
		ArrayList<String> files = FileTools::getFilesInDirectory(directory, hidden);
		total += files.size();
		files.clear();
	
		ArrayList<String> folders = FileTools::getFoldersInDirectory(directory, hidden);
		for(int i=0; i<folders.size(); i++)
		{
			total += FileTools::totalFilesInDirectory(directory+'/'+folders.get(i), hidden);
		}
		return total;
	}

	bool FileTools::directoryContainsFiles(const String&directory, bool hidden)
	{
		DIR*dir = opendir(directory);
		if(dir==NULL)
		{
			return false;
		}
	
		struct dirent *entry = readdir(dir);
	
		while (entry != NULL)
		{
			String entryName = entry->d_name;
			if(!entryName.equals(".") && !entryName.equals(".."))
			{
				if(entry->d_type==DT_REG || entry->d_type==DT_LNK)
				{
					closedir(dir);
					return true;
				}
				else if(entry->d_type==DT_DIR)
				{
					bool contains = FileTools::directoryContainsFiles(directory+'/'+entryName, hidden);
					if(contains)
					{
						closedir(dir);
						return true;
					}
				}
			}
		
			entry = readdir(dir);
		}
		
		closedir(dir);
	
		return false;
	}

	bool FileTools::createFile(const String&path)
	{
		FILE*file = std::fopen(path, "a+");
		if(file==NULL)
		{
			return false;
		}
		std::fclose(file);
		return true;
	}

	bool FileTools::createDirectory(const String&directory)
	{
#if defined(_WIN32)
		int result = _mkdir(directory);
#else
		int result = mkdir(directory, 0755);
#endif
		if(result == 0)
		{
			return true;
		}
		return false;
	}

#ifndef _WIN32
	bool FileTools::createSymbolicLink(const String&srcPath, const String&dstPath)
	{
		if(!createFile(dstPath))
		{
			Console::WriteLine("Failed to create symbolic link: Unable to create file for writing");
			return false;
		}
		if(symlink(srcPath, dstPath)!=0)
		{
			String message = "Failed to create symbolic link: ";
			switch(errno)
			{
				default:
				message += "Unknown error";
				break;
			
				case EACCES:
				message += "Permission denied";
				break;
			
				case EEXIST:
				message += "File already exists";
				break;
			
				case EINVAL:
				message += "Invalid destination path";
				break;
			
				case EIO:
				message += "IO error";
				break;
			
				case ELOOP:
				message += "Loop error";
				break;
			
				case ENAMETOOLONG:
				message += "Destination path name too long";
				break;
			
				case ENOENT:
				if(dstPath.length()==0)
				{
					message += "Destination path is an empty string";
				}
				else
				{
					message += "Destination path does not name an existing file";
				}
				break;
			
				case ENOSPC:
				message += "No available space on disk";
				break;
			
				case ENOTDIR:
				message += "Prefix of destination path is not a directory";
				break;
			
				case EROFS:
				message += "Destination path cannot reside in a read-only system";
				break;
			}
			Console::WriteLine(message);
			return false;
		}
		return true;
	}
#endif

	bool FileTools::copyFile(const String&src, const String&dest)
	{
#if defined(__APPLE__)
		copyfile_state_t state = copyfile_state_alloc();
		int result = copyfile(src, dest, state, COPYFILE_ALL);
		if(result<0)
		{
			String message = "Error: FileTools::copyFile(const String&, const String&): ";
			switch(errno)
			{
				default:
				message += "Unknown Error";
				break;
			
				case EINVAL:
				message += "Invalid argument";
				break;
			
				case ENOMEM:
				message += "Not enough memory";
				break;
			
				case ENOTSUP:
				message += "The source file was not a directory, symbolic link, or regular file";
				break;
			
				case ECANCELED:
				message += "Copy was cancelled by the callback";
				break;
			}
			Console::WriteLine(message);
			copyfile_state_free(state);
			return false;
		}
		copyfile_state_free(state);
		return true;
#elif defined(_WIN32)
		BOOL result = CopyFileW(src.wstring().c_str(), dest.wstring().c_str(), TRUE);
		if(result == 0)
		{
			Console::WriteLine("Error: FileTools::copyFile(const String&, const String&): Unable to copy file");
			return false;
		}
		return true;
#else
		size_t len = 0;
		char buffer[BUFSIZ] = {'\0'};
		FILE* in = std::fopen(src, "rb");
		FILE* out = std::fopen(dest,"wb");

		if(in == NULL || out == NULL)
		{
			Console::WriteLine("Error: FileTools::copyFile(const String&, const String&): Unable to copy file");
			return false;
		}
		while((len = std::fread( buffer, BUFSIZ, 1, in)) > 0)
		{
			std::fwrite(buffer, BUFSIZ, 1, out);
		}

		std::fclose(in);
		std::fclose(out);
		return true;
#endif
	}

	bool FileTools::copyFolder(const String&src, const String&dest)
	{
		FileTools::createDirectory(dest);
	
		bool success = true;
	
		ArrayList<String> files = FileTools::getFilesInDirectory(src, true);
		for(int i=0; i<files.size(); i++)
		{
			String&file = files.get(i);
			String srcFile = src+'/'+file;
			String dstFile = dest+'/'+file;
			bool copied = FileTools::copyFile(srcFile, dstFile);
			if(!copied)
			{
				Console::WriteLine((String)"Error: FileTools::copyFolder(const String&, const String&), failed to copy file \"" + srcFile
								   + "\" to \"" + dstFile + "\"");
				success = false;
			}
		}
	
		ArrayList<String> folders = FileTools::getFoldersInDirectory(src, true);
		for(int i=0; i<folders.size(); i++)
		{
			String&folder = folders.get(i);
			String srcFolder = src+'/'+folder;
			String dstFolder = dest+'/'+folder;
			bool copied = FileTools::copyFolder(srcFolder, dstFolder);
			if(!copied)
			{
				success = false;
			}
		}
	
		return success;
	}

	bool FileTools::fileExists(const String&path)
	{
		FILE*file = std::fopen(path, "r");
		if(file==NULL)
		{
			return false;
		}
		std::fclose(file);
		return true;
	}

	bool FileTools::folderExists(const String&path)
	{
		DIR*dir = opendir(path);
		if(dir==NULL)
		{
			if(errno == ENOENT || errno == ENOTDIR)
			{
				return false;
			}
			return true;
		}
		closedir(dir);
		return true;
	}

	bool FileTools::pathIsFolder(const String&path)
	{
		struct stat s;
		if(stat(path, &s)==0)
		{
			if((s.st_mode&S_IFMT) == S_IFDIR)
			{
				return true;
			}
		}
		else
		{
			if(errno == EACCES)
			{
				Console::WriteLine((String)"Error: FileTools::pathIsFolder(const String&): Access denied: " + path);
			}
		}
		return false;
	}

	bool FileTools::pathIsFile(const String&path)
	{
		struct stat s;
		if(stat(path, &s)==0)
		{
			if((s.st_mode&S_IFMT) == S_IFREG)
			{
				return true;
			}
		}
		else
		{
			if(errno == EACCES)
			{
				Console::WriteLine((String)"Error: FileTools::pathIsFile(const String&): Access denied: " + path);
			}
		}
		return false;
	}

#ifndef _WIN32
	bool FileTools::expandPath(const String& path, String& dest)
	{
		char* buffer = (char*)malloc(PATH_MAX);
		if(realpath(path, buffer)==NULL)
		{
			free(buffer);
			dest = "";
			String message;
			switch(errno)
			{
				default:
				message = "Unknown error";
				break;
			
				case EACCES:
				message = "Access denied";
				break;
			
				case EINVAL:
				message = "Path is NULL";
				break;
			
				case EIO:
				message = "I/O error";
				break;
			
				case ELOOP:
				message = "Too many symbolic links";
				break;
			
				case ENAMETOOLONG:
				message = "Path is too long";
				break;
			
				case ENOENT:
				message = "File does not exist";
				break;
			
				case ENOTDIR:
				message = "Path prefix is not a directory";
				break;
			}
			Console::WriteLine((String)"Error: FileTools::expandPath(const String&, String&): " + message + ": " + path);
			return false;
		}
		dest = buffer;
		free(buffer);
		return true;
	}
#endif

	bool FileTools::deleteFromFilesystem(const String&path)
	{
		int result = remove(path);
		if(result==0)
		{
			return true;
		}
		return false;
	}

	bool FileTools::rename(const String&oldFile, const String&newFile)
	{
		int result = std::rename(oldFile, newFile);
		if(result==0)
		{
			return true;
		}
		return false;
	}

	bool FileTools::loadFileIntoString(const String&path, String&str)
	{
		FILE*file = std::fopen(path, "r");
		if(file==NULL)
		{
			return false;
		}
		std::fseek(file, 0, SEEK_END);
		int total = ftell(file);
		std::fseek(file, 0, SEEK_SET);
		
		char*fileText = new char[total+1];
		fileText[total] = '\0';
		
		std::fread(fileText, 1, total+1, file);
		str = fileText;
		
		std::fclose(file);
		delete[] fileText;
		return true;
	}

	bool FileTools::writeStringToFile(const String&path, const String&content)
	{
		FILE*file = std::fopen(path, "w");
		if(file==NULL)
		{
			return false;
		}
		
		std::fwrite((const char*)content, 1, content.length(), file);
		
		std::fclose(file);
		return true;
	}

	bool FileTools::appendStringToFile(const String&path, const String&content)
	{
		FILE*file = std::fopen(path, "a+");
		if(file==NULL)
		{
			return false;
		}
		std::fseek(file,0,SEEK_END);
		std::fwrite((const char*)content, 1, content.length(), file);
		
		std::fclose(file);
		return true;
	}
}

