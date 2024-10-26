//
// Binary file operations: Read, write, get file size, set position
//
// Author:	Kim Einar Larsen
// Email:	kim.developer@gmail.com
// Github:	https://github.com/kimlar
// Copyright (c) 2024 Kim Einar Larsen. All rights reserved.
//
// 
// NOTE: Memory allocation is done on the user side. Not inside here.
// NOTE: If you are using text_file_get_size(..) to get the size to allocate memory,
//       then you don't need to add +1 in the size when allocating memory,
//       otherwise remember to add +1 like this: text = malloc(size + 1);
//       when dealing with strings (null terminated).
//
// TODO: Make this also to work with C++.
// 
// 
// Example of using binary_file.h
//
//		#include "binary_file.h"
//		...
//		str filename = "newbin.bin";
//		binary_file file = binary_file_openfor_write_new(filename);
//		if (file == NULL)
//		{
//			printf("Error: Failed to open binary file for writing\n");
//			exit(1); // Exit to OS
//		}
//		
//		byte* mydata = "DEADBEEF";
//		binary_file_write_byte(mydata, sizeof(mydata), file);
//		
//		i32 list[4] = { 1, 2, 3, 4 };
//		binary_file_write_elements(list, sizeof(i32), 4, file);
//		
//		binary_file_close(file);
//
// 
// Example of writing different data types
//
//		#include "binary_file.h"
//		...
//		str filename = "newbin.bin";
//		binary_file file = binary_file_openfor_write_new(filename);
//		if (file == NULL)
//		{
//			printf("Error: Failed to open binary file for writing\n");
//			exit(1); // Exit to OS
//		}
//		
//		i8 mydata1 = 65;
//		i16 mydata2 = 66;
//		i32 mydata3 = 67;
//		i64 mydata4 = 68;
//		u8 mydata5 = 69;
//		u16 mydata6 = 70;
//		u32 mydata7 = 71;
//		u64 mydata8 = 72;
//		binary_file_write_i8(&mydata1, file);
//		binary_file_write_i16(&mydata2, file);
//		binary_file_write_i32(&mydata3, file);
//		binary_file_write_i64(&mydata4, file);
//		binary_file_write_u8(&mydata5, file);
//		binary_file_write_u16(&mydata6, file);
//		binary_file_write_u32(&mydata7, file);
//		binary_file_write_u64(&mydata8, file);
//		
//		binary_file_close(file);
//
// 
// Example of reading different data types
// 
//		str filename = "newbin.bin";
//		binary_file file = binary_file_openfor_read(filename);
//		if (file == NULL)
//		{
//			printf("Error: Failed to open binary file for reading\n");
//			exit(1); // Exit to OS
//		}
//		
//		i8 mydata1 = 0;
//		i16 mydata2 = 0;
//		i32 mydata3 = 0;
//		i64 mydata4 = 0;
//		u8 mydata5 = 0;
//		u16 mydata6 = 0;
//		u32 mydata7 = 0;
//		u64 mydata8 = 0;
//		binary_file_read_i8(&mydata1, file);
//		binary_file_read_i16(&mydata2, file);
//		binary_file_read_i32(&mydata3, file);
//		binary_file_read_i64(&mydata4, file);
//		binary_file_read_u8(&mydata5, file);
//		binary_file_read_u16(&mydata6, file);
//		binary_file_read_u32(&mydata7, file);
//		binary_file_read_u64(&mydata8, file);
//		
//		binary_file_close(file);
// 
//
// Example of reading bytes from a file
// 
//		str filename = "newbin.bin";
//		binary_file file = binary_file_openfor_read(filename);
//		if (file == NULL)
//		{
//			printf("Error: Failed to open binary file for reading\n");
//			exit(1); // Exit to OS
//		}
//		
//		char* text = malloc(30);
//		binary_file_read_byte(text, 30, file);
//		free(text);
//		binary_file_close(file);
//
// 
// Example of reading elements from a file
// 
//		// Wrote 4 elements before like this:
//		//		i32 list[4] = { 1, 2, 3, 4 };
//		//		binary_file_write_elements(list, sizeof(i32), 4, file);
//		
//		str filename = "newbin.bin";
//		binary_file file = binary_file_openfor_read(filename);
//		if (file == NULL)
//		{
//			printf("Error: Failed to open binary file for reading\n");
//			exit(1); // Exit to OS
//		}
//		
//		i32 list[4] = { 0, 0, 0, 0 };
//		binary_file_read_elements(list, sizeof(i32), 4, file);
//		
//		for (int i = 0; i < 4; i++)
//			printf("%d\n", list[i]);
//		
//		binary_file_close(file);
//
// 
// Example of reading bools from a file
//
//		binary_file file = binary_file_openfor_read("newbin.bin");
//		if (file == NULL)
//		{
//			printf("Error: Failed to open binary file for reading\n");
//			exit(1); // Exit to OS
//		}
//		
//		bool myvalue1 = false;
//		bool myvalue2 = false;
//		binary_file_read_bool(&myvalue1, file);
//		binary_file_read_bool(&myvalue2, file);
//		printf("%d = %s\n", myvalue1, myvalue1 ? "true" : "false");
//		printf("%d = %s\n", myvalue2, myvalue2 ? "true" : "false");
//		
//		binary_file_close(file);
// 
// 

#pragma once

//
// C includes
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//
// Data types
//
typedef char				 i8;
typedef short				i16;
typedef int					i32;
typedef long long			i64;
typedef unsigned char		 u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long	u64;
typedef float				f32;
typedef double				f64;
typedef unsigned char	   byte;
typedef unsigned char*		str;

//
// File types
//
typedef FILE*		binary_file;
typedef i64			  file_size;

//
// Prototypes: Text file
//
binary_file binary_file_openfor_write_new(str filename);
binary_file binary_file_openfor_write_append(str filename);
binary_file binary_file_openfor_read(str filename);
file_size binary_file_get_size(str filename);
bool binary_file_write_i8(i8* data, binary_file file);
bool binary_file_write_i16(i16* data, binary_file file);
bool binary_file_write_i32(i32* data, binary_file file);
bool binary_file_write_i64(i64* data, binary_file file);
bool binary_file_write_u8(u8* data, binary_file file);
bool binary_file_write_u16(u16* data, binary_file file);
bool binary_file_write_u32(u32* data, binary_file file);
bool binary_file_write_u64(u64* data, binary_file file);
bool binary_file_write_f32(f32* data, binary_file file);
bool binary_file_write_f64(f64* data, binary_file file);
bool binary_file_write_bool(bool* data, binary_file file);
bool binary_file_write_byte(byte* data, i64 size, binary_file file);
bool binary_file_write_str(str text, binary_file file);
bool binary_file_write_elements(void* data, i64 size, i64 count, binary_file file);
bool binary_file_read_i8(i8* data, binary_file file);
bool binary_file_read_i16(i16* data, binary_file file);
bool binary_file_read_i32(i32* data, binary_file file);
bool binary_file_read_i64(i64* data, binary_file file);
bool binary_file_read_u8(u8* data, binary_file file);
bool binary_file_read_u16(u16* data, binary_file file);
bool binary_file_read_u32(u32* data, binary_file file);
bool binary_file_read_u64(u64* data, binary_file file);
bool binary_file_read_f32(f32* data, binary_file file);
bool binary_file_read_f64(f64* data, binary_file file);
bool binary_file_read_bool(bool* data, binary_file file);
bool binary_file_read_byte(byte* data, i64 size, binary_file file);
bool binary_file_read_str(str text, i64 size, binary_file file);
bool binary_file_read_elements(void* data, i64 size, i64 count, binary_file file);
bool binary_file_set_position_begin(binary_file file);
bool binary_file_set_position(file_size position, binary_file file);
bool binary_file_set_position_relative(file_size position, binary_file file);
bool binary_file_set_position_end(binary_file file);
file_size binary_file_get_position(binary_file file);
void binary_file_close(binary_file file);

//
// Implementations: Binary file
//

// Open a binary file for writing in truncate mode.
binary_file binary_file_openfor_write_new(str filename)
{
	// Create a binary file. Truncate the file if it already exists.
	binary_file file = fopen(filename, "wb");

	return file;
}
// Open a binary file for writing in append mode.
binary_file binary_file_openfor_write_append(str filename)
{
	// Open a binary file in append mode. Create if not exists.
	binary_file file = fopen(filename, "ab");

	return file;
}
// Open a binary file for reading in binary mode.
binary_file binary_file_openfor_read(str filename)
{
	// Read a binary file in binary mode. Returns NULL if the file does not exist.
	binary_file file = fopen(filename, "rb");

	return file;
}
// Get the size of a binary file. Note: This function returns -1 if the binary file is not found
file_size binary_file_get_size(str filename)
{
	binary_file file = binary_file_openfor_read(filename);
	if (file == NULL)
		return -1; // Return -1 if the binary file is not found

	if (_fseeki64(file, 0, SEEK_END) != 0)
		return -1; // Failure

	file_size data_size = _ftelli64(file);

	binary_file_close(file);

	return data_size; // Return the data size of the binary file
}
// Write 'i8' data to a binary file
bool binary_file_write_i8(i8* data, binary_file file)
{
	if (fwrite(data, sizeof(i8), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'i16' data to a binary file
bool binary_file_write_i16(i16* data, binary_file file)
{
	if (fwrite(data, sizeof(i16), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'i32' data to a binary file
bool binary_file_write_i32(i32* data, binary_file file)
{
	if (fwrite(data, sizeof(i32), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'i64' data to a binary file
bool binary_file_write_i64(i64* data, binary_file file)
{
	if (fwrite(data, sizeof(i64), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'u8' data to a binary file
bool binary_file_write_u8(u8* data, binary_file file)
{
	if (fwrite(data, sizeof(u8), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'u16' data to a binary file
bool binary_file_write_u16(u16* data, binary_file file)
{
	if (fwrite(data, sizeof(u16), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'u32' data to a binary file
bool binary_file_write_u32(u32* data, binary_file file)
{
	if (fwrite(data, sizeof(u32), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'u64' data to a binary file
bool binary_file_write_u64(u64* data, binary_file file)
{
	if (fwrite(data, sizeof(u64), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'f32' data to a binary file
bool binary_file_write_f32(f32* data, binary_file file)
{
	if (fwrite(data, sizeof(f32), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'f64' data to a binary file
bool binary_file_write_f64(f64* data, binary_file file)
{
	if (fwrite(data, sizeof(f64), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'bool' data to a binary file. Note this writes 'true' as '1' and 'false' as '0'. Not compacted.
bool binary_file_write_bool(bool* data, binary_file file)
{
	if (fwrite(data, sizeof(bool), 1, file) != 1)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'byte'(s) data to a binary file
bool binary_file_write_byte(byte* data, i64 size, binary_file file)
{
	if (fwrite(data, sizeof(byte), size, file) != size)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'str' data to a binary file
bool binary_file_write_str(str text, binary_file file)
{
	if (fwrite(text, sizeof(char), strlen(text), file) != strlen(text))
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Write 'elements'(s) data to a binary file (as typical fwrite())
bool binary_file_write_elements(void* data, i64 size, i64 count, binary_file file)
{
	if (fwrite(data, size, count, file) != count)
		return false; // Something went wrong while trying to write the data

	return true; // Success
}
// Read 'i8' data from a binary file
bool binary_file_read_i8(i8* data, binary_file file)
{
	if (fread(data, sizeof(i8), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'i16' data from a binary file
bool binary_file_read_i16(i16* data, binary_file file)
{
	if (fread(data, sizeof(i16), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'i32' data from a binary file
bool binary_file_read_i32(i32* data, binary_file file)
{
	if (fread(data, sizeof(i32), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'i64' data from a binary file
bool binary_file_read_i64(i64* data, binary_file file)
{
	if (fread(data, sizeof(i64), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'u8' data from a binary file
bool binary_file_read_u8(u8* data, binary_file file)
{
	if (fread(data, sizeof(u8), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'u16' data from a binary file
bool binary_file_read_u16(u16* data, binary_file file)
{
	if (fread(data, sizeof(u16), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'u32' data from a binary file
bool binary_file_read_u32(u32* data, binary_file file)
{
	if (fread(data, sizeof(u32), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'u64' data from a binary file
bool binary_file_read_u64(u64* data, binary_file file)
{
	if (fread(data, sizeof(u64), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'f32' data from a binary file
bool binary_file_read_f32(f32* data, binary_file file)
{
	if (fread(data, sizeof(f32), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'f64' data from a binary file
bool binary_file_read_f64(f64* data, binary_file file)
{
	if (fread(data, sizeof(f64), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'bool' data from a binary file. Note this reads 'true' as '1' and 'false' as '0'. Not compacted.
bool binary_file_read_bool(bool* data, binary_file file)
{
	if (fread(data, sizeof(bool), 1, file) != 1)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'byte'(s) data from a binary file
bool binary_file_read_byte(byte* data, i64 size, binary_file file)
{
	if (fread(data, sizeof(byte), size, file) != size)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Read 'str' data from a binary file
bool binary_file_read_str(str text, i64 size, binary_file file)
{
	// Read specified portion of the binary file into memory. Typically all of the file.
	size_t bytes = fread(text, sizeof(char), size, file);
	if (ferror(file) != 0)
		return false; // Error reading file
	
	text[bytes] = '\0';

	return true; // Success
}
// Read 'elements'(s) data from a binary file
bool binary_file_read_elements(void* data, i64 size, i64 count, binary_file file)
{
	if (fread(data, size, count, file) != count)
		return false; // Something went wrong while trying to read the data

	return true; // Success
}
// Seek to the beginning of a binary file
bool binary_file_set_position_begin(binary_file file)
{
	return (_fseeki64(file, 0, SEEK_SET) == 0); // Returns true if the seek returns 0 meaning that the seek was successful
}
// Seek to an absolute position in a binary file
bool binary_file_set_position(file_size position, binary_file file)
{
	return (_fseeki64(file, position, SEEK_SET) == 0); // Returns true if the seek returns 0 meaning that the seek was successful
}
// Seek to a relative position in a binary file
bool binary_file_set_position_relative(file_size position, binary_file file)
{
	return (_fseeki64(file, position, SEEK_CUR) == 0); // Returns true if the seek returns 0 meaning that the seek was successful
}
// Seek to the end of a binary file
bool binary_file_set_position_end(binary_file file)
{
	return (_fseeki64(file, 0, SEEK_END) == 0); // Note: the regular fseek() supports only file sizes up to 2GB. This _fseeki64() supports up to 8 Exabytes.
}
// Get the current position in a binary file
file_size binary_file_get_position(binary_file file)
{
	return _ftelli64(file);
}
// Close a binary file
void binary_file_close(binary_file file)
{
	fclose(file);
}
