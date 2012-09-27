#include <gtk/gtk.h>
#include "interface.h"
#include "signal.h"

GtkBuilder * builder;
GtkWidget * window;
GtkWidget * t_srcfile;
GtkWidget * t_dstfile;
GtkWidget * t_haffile;
GtkWidget * c_srcfile;
GtkWidget * c_dstfile;
GtkWidget * c_haffile;
GtkWidget * b_zip;
GtkWidget * b_unzip;

static GtkBuilder* gtk_load_glade(gchar* filename)
{
	GtkBuilder *gb;
	GError * gerror=NULL;

	//新建一个GtkBuider对象
	gb=gtk_builder_new();
	//载入文件，失败则返回NULL
	if(!gtk_builder_add_from_file(gb,filename,&gerror)) return NULL;
	//连接文件中包含的所有信号
	gtk_builder_connect_signals(gb,NULL);

	//返回GtkBuilder对象供后面操作使用
	return gb;
}

void init_window()
{
	builder=gtk_load_glade("dataStruct.glade");
	window=GTK_WIDGET(gtk_builder_get_object(builder,"window"));
	t_srcfile=GTK_WIDGET(gtk_builder_get_object(builder,"t_srcfile"));
	t_dstfile=GTK_WIDGET(gtk_builder_get_object(builder,"t_dstfile"));
	t_haffile=GTK_WIDGET(gtk_builder_get_object(builder,"t_haffile"));
	c_srcfile=GTK_WIDGET(gtk_builder_get_object(builder,"c_srcfile"));
	c_dstfile=GTK_WIDGET(gtk_builder_get_object(builder,"c_dstfile"));
	c_haffile=GTK_WIDGET(gtk_builder_get_object(builder,"c_haffile"));
	b_zip=GTK_WIDGET(gtk_builder_get_object(builder,"b_zip"));
	b_unzip=GTK_WIDGET(gtk_builder_get_object(builder,"b_unzip"));
	//gtk_widget_show(t_srcfile);
	gtk_widget_show(window);
}

