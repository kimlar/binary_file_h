# binary_file_h
![alt text](https://github.com/kimlar/binary_file_h/blob/main/binary_file-code-example.png "Showing the code")

<br>

![alt text](https://github.com/kimlar/binary_file_h/blob/main/binary_file-running.png "Showing the code in action")

## Examples of using binary_file.h

### How to read elements from a binary file:
```c
#include "binary_file.h"
...
// Wrote 4 elements before like this:
//	i32 list[4] = { 1, 2, 3, 4 };
//	binary_file_write_elements(list, sizeof(i32), 4, file);

str filename = "newbin.bin";
binary_file file = binary_file_openfor_read(filename);
if (file == NULL)
{
	printf("Error: Failed to open binary file for reading\n");
	exit(1); // Exit to OS
}

i32 list[4] = { 0, 0, 0, 0 };
binary_file_read_elements(list, sizeof(i32), 4, file);

for(int i = 0; i < 4; i++)
	printf("%d\n", list[i]);

binary_file_close(file);
```

This is a drop-in file for any Windows C projects to quickly add a higher level binary file operation for reading and writing.
