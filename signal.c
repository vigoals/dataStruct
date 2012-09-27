#include <gtk/gtk.h>
#include "signal.h"
#include "interface.h"
#include "haf.h"
//#include "test.h"

G_MODULE_EXPORT void w_s_destroy(GtkObject* widget, gpointer user_data)
{
	gtk_main_quit();
}

G_MODULE_EXPORT void csf_s_changed(GtkObject* widget, gpointer user_data)
{
	char * filename=NULL;

	filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(c_srcfile));
	//printf("filename:%s\n",filename);
	gtk_entry_set_text(GTK_ENTRY(t_srcfile),filename);
}

G_MODULE_EXPORT void cdf_s_changed(GtkObject* widget, gpointer user_data)
{
	char * filename=NULL;

	filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(c_dstfile));
	//printf("filename:%s\n",filename);
	gtk_entry_set_text(GTK_ENTRY(t_dstfile),filename);
}

G_MODULE_EXPORT void chf_s_changed(GtkObject* widget, gpointer user_data)
{
	char * filename=NULL;

	filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(c_haffile));
	//printf("filename:%s\n",filename);
	gtk_entry_set_text(GTK_ENTRY(t_haffile),filename);
}

G_MODULE_EXPORT void bz_clicked(GtkObject* widget, gpointer user_data)
{
	int k;
	char * fn_src;
	char * fn_huf;
	char * fn_dst;

	fn_src=gtk_entry_get_text(GTK_ENTRY(t_srcfile));
	fn_huf=gtk_entry_get_text(GTK_ENTRY(t_haffile));
	fn_dst=gtk_entry_get_text(GTK_ENTRY(t_dstfile));

	if ( (k=zip(fn_src,fn_huf,fn_dst)) < 0 )
		myperror(k);

	//if ( (k=test(fn_src,fn_huf,fn_dst)) < 0 )
	//	myperror(k);
}

G_MODULE_EXPORT void bu_clicked(GtkObject* widget, gpointer user_data)
{
	int k;
	char * fn_src;
	char * fn_huf;
	char * fn_dst;

	fn_src=gtk_entry_get_text(GTK_ENTRY(t_srcfile));
	fn_huf=gtk_entry_get_text(GTK_ENTRY(t_haffile));
	fn_dst=gtk_entry_get_text(GTK_ENTRY(t_dstfile));

	if ( (k=unzip(fn_src,fn_huf,fn_dst)) < 0 )
		myperror(k);
}
