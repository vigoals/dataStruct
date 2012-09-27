#include <stdlib.h>
#include <gtk/gtk.h>
#include "interface.h"

int main (int argc, char *argv[])
{
	gtk_init(&argc,&argv);

	init_window();

	gtk_main();
	return 0;
}
