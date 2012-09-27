#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>

extern GtkBuilder * builder;
extern GtkWidget * window;
extern GtkWidget * t_srcfile;
extern GtkWidget * t_dstfile;
extern GtkWidget * t_haffile;
extern GtkWidget * c_srcfile;
extern GtkWidget * c_dstfile;
extern GtkWidget * c_haffile;
extern GtkWidget * b_zip;
extern GtkWidget * b_unzip;

void init_window();

#endif // INTERFACE_H
