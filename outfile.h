my_bool outfile_remove_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *outfile_remove(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void outfile_remove_deinit(UDF_INIT *initid);

my_bool outfile_read_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *outfile_read(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void outfile_read_deinit(UDF_INIT *initid);

my_bool outfile_write_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *outfile_write(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void outfile_write_deinit(UDF_INIT *initid);

char* concat(const char* str1, const char* str2)
{
    char* res;
    asprintf(&res, "%s%s", str1, str2);
    return res;
}

char * read_outfile(char * path)  
{  
    int fd;
    char buf[8];
	char *result="";
    /* open, read, and display the message from the FIFO */
    fd = open(path, O_RDONLY);
    while( read(fd, buf, sizeof(buf)) > 0){
		result = concat(result,buf);
		memset(buf, 0, sizeof(buf));
	}
    //printf("Received: %s\n", buf);
    close(fd);
	
    return result; 
}  

int write_outfile(char * path, char * msg)  
{  
    	
	FILE* file = fopen(path, "a+");
	if (file == 0) {
		return 0;
	}
    fputs(msg, file);
    fclose(file);
	return 1;
}
int create_outfile(char * path)
{
	/* create the FIFO (named pipe) */
    return mkoutfile(path, 0660);
}
int remove_outfile(char *path)
{
	/* remove the FIFO */
    return unlink(path);
}
