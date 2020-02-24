#include <sys/types.h>
#include <stdio.h>
#include <time.h>  
#include <stdlib.h>
#include <errno.h>

extern char *tzname[];  
 
void main()  
{  
     time_t now; 
     struct tm *sp; 
 
     (void) time( &now ); 
 
	char buf[26];
	(void) ctime_r(&now, buf, 26);

     printf("%s", buf); 	
	
	setenv("TZ","PST8PDT", 1);
 	
	int errno = 0;
     
	errno = localtime_r(&now, sp);
	
	//printf("%d\n", errno);
     
	printf("%d/%d/%02d %d:%02d %s\n", 
         sp->tm_mon + 1, sp->tm_mday, 
         sp->tm_year, sp->tm_hour, 
         sp->tm_min, tzname[sp->tm_isdst]); 
     exit(0);
} 