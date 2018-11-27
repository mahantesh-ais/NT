/*This is the sample program to notify us for the file creation and file deletion takes place in “/tmp” directory*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main( )
{
	int length, i = 0;
	int fd;
	int wd;
        char buffer[EVENT_BUF_LEN];
	/*creating the INOTIFY instance*/
	fd = inotify_init();
	/*checking for error*/
	if ( fd < 0 ) {
		perror( "inotify_init" );
	}
	/*adding the “/tmp” directory into watch list. Here, the suggestion is to validate the existence of the directory before adding into monitoring list.*/
	wd = inotify_add_watch( fd, "/proc/29267/status", IN_DELETE | IN_DELETE_SELF);
       	/*read to determine the event change happens on “/tmp” directory. Actually this read blocks until the change event occurs*/ 
	length = read( fd, buffer, EVENT_BUF_LEN ); 
	printf("\nEvent triggered \n");
	/*checking for error*/
	if ( length < 0 ) {
		perror( "read" );
        }  

	/*actually read return the list of change events happens. Here, read the change event one by one and process it accordingly.*/
	while ( i < length ) {     
		printf("\n Reading the event list \n");
		struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
		if ( event->len ) {
				if ( event->mask & IN_DELETE_SELF ) {
					printf( "Directory %s deleted.\n", event->name );
				}
				else if ( event->mask & IN_DELETE) {
					printf( "Directory %s dleted.\n", event->name );
				}
		}
		i += EVENT_SIZE + event->len;
	}
	/*removing the “/tmp” directory from the watch list.*/
	inotify_rm_watch( fd, wd );

	/*closing the INOTIFY instance*/
	close( fd );
}
