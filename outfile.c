/*
Homepage: http://netkiller.github.io/
Author: netkiller<netkiller@msn.com>
*/
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "outfile.h"

/* ------------------------ outfile_write ----------------------------- */

my_bool out2file_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2)
  {
    strncpy(message, "two arguments must be supplied: outfile_write('pipename','message').", MYSQL_ERRMSG_SIZE);
    return 1;
  }

  args->arg_type[0]= STRING_RESULT;
    return 0;
}

char *out2file(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

	char *status;
  //asprintf(&status, "SAFENET_URL=%s, SAFENET_KEY=%s", safe_url, safe_key);
	if( write_outfile( args->args[0], args->args[1] ) == -1)
		status = "false";
	else
		status = "true";
  
	*length = strlen(status);
	return ((char *)status);
}

void out2file_deinit(UDF_INIT *initid)
{
   return;
}
