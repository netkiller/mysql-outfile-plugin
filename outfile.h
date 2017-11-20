my_bool out2file_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *out2file(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void out2file_deinit(UDF_INIT *initid);

char* concat(const char* str1, const char* str2)
{
    char* res;
    asprintf(&res, "%s%s", str1, str2);
    return res;
}
int write_outfile(char * path, char * msg)  
{  
    	
	FILE* file = fopen(path, "a+");
	if (file == 0) {
		return 0;
	}
	msg = concat(msg, "\r\n");
    	fputs(msg, file);
    	fclose(file);
	return 1;
}
