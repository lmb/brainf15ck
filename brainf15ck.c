#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static const char* load(const char* filename, size_t* length);

static int is_loop_op(char opcode)
{
	switch (opcode) {
		case '[': return 1;
		case ']': return -1;
		default:  return 0;
	}
}

static void execute(const char* program, size_t length)
{
	const char* end = program + length;
	const char* pc = program;

	uint8_t  memory[1024] = {0};
	uint8_t* ptr = memory;

	int n;

	while (program <= pc && pc < end) {
		switch (*pc) {
			case '>': ++ptr; break;
			case '<': --ptr; break;
			case '+': *ptr += 1; break;
			case '-': *ptr -= 1; break;
			case '.': putchar((char)*ptr); break;
			case ',': *ptr = getchar(); break;
			case '[':
				if (!*ptr) for (n = 1; n != 0; n += is_loop_op(*(++pc)));
				break;
			case ']':
				for (n = 1; n != 0; n -= is_loop_op(*(--pc)));
				continue;
			default: break;
		}

		pc++;
	}
}

int main(int argc, const char** argv)
{
	const char* program = NULL;
	size_t length = 0;

	if (argc < 2) {
		printf("Please specify source file.\n");
		return 1;
	}

	program = load(argv[1], &length);

	if (program == NULL) {
		return 1;
	}

	execute(program, length);
	free((void*)program);

	return 0;
}

static const char* load(const char* filename, size_t* length)
{
	int fd;
	struct stat stat;
	char* contents = NULL;

	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		printf("Could not open source\n");
		return NULL;
	}

	if (fstat(fd, &stat) != 0) {
		printf("fstat failed\n");
		goto error;
	}

	if (stat.st_size == 0) {
		printf("File is empty\n");
		goto error;
	}

	contents = malloc(stat.st_size);

	if (contents == NULL) {
		printf("Could not allocate memory\n");
		goto error;
	}

	if (read(fd, contents, stat.st_size) == -1) {
		printf("Could not read full file\n");
		goto error;
	}

	close(fd);

	*length = stat.st_size;
	return contents;

	error:
	close(fd);
	free(contents);
	return NULL;
}
