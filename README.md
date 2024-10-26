# binary_file_h
![alt text](https://github.com/kimlar/binary_file_h/blob/main/binary_file-code-example.png "Showing the code")

<br>

![alt text](https://github.com/kimlar/binary_file_h/blob/main/binary_file-running.png "Showing the code in action")

## Examples of using text_file.h

### How to read a text file:
```c
#include "text_file.h"
...
str filename = "bigtextfile.txt";
text_file file = text_file_openfor_read(filename);
if (file == NULL)
{
	printf("Error: Failed to open item file\n");
	exit(1); // Exit to OS
}
i64 size = text_file_get_size(filename);
str text = malloc(size);
text_file_read_str(text, size, file);
printf("%s\n", text); // OUTPUT
free(text);
text_file_close(file);
```

This is a drop-in file for any Windows C projects to quickly add a higher level binary file operation for reading and writing.
