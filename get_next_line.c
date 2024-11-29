#include "get_next_line.h"

/**
 * ft_strdup
 * Creates a duplicate of the given string `src`.
 * Dynamically allocates memory for the duplicate.
 * 
 * @param src: The source string to duplicate.
 * @return: A pointer to the newly allocated duplicate string.
 */
char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;
	int		len;

	len = 0;
	while (src[len])
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * get_next_line
 * Reads a line from the given file descriptor `fd`.
 * Uses a static buffer to efficiently read data in chunks.
 * Handles dynamic memory allocation for lines of arbitrary length.
 * 
 * @param fd: The file descriptor to read from.
 * @return: A pointer to the next line read, or NULL on EOF or error.
 */
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_read = 0;
	static int	buffer_pos = 0;
	char		*line;
	int			line_len;
	int			start_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	line_len = 0;
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break;
		}
		start_pos = buffer_pos;
		while (buffer_pos < buffer_read && buffer[buffer_pos] != '\n')
			buffer_pos++;
		int segment_len = buffer_pos - start_pos;
		char *new_line = (char *)malloc(line_len + segment_len + 2);
		if (!new_line)
			return (NULL);
		if (line)
		{
			int j = 0;
			while (j < line_len)
			{
				new_line[j] = line[j];
				j++;
			}
			free(line);
		}
		int k = 0;
		while (k < segment_len)
		{
			new_line[line_len + k] = buffer[start_pos + k];
			k++;
		}
		line_len += segment_len;
		new_line[line_len] = '\0';
		line = new_line;
		if (buffer_pos < buffer_read && buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			break;
		}
	}
	if (!line || line_len == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/*
int main()
{
    int fd = open("./txt.txt", O_RDONLY);
    char *line;
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
*/
