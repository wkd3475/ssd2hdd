#include <gtk/gtk.h>
#include <stdio.h>

#define RECOMMEND 1

GtkWidget *list_label_frame(GtkWidget *parent, gchar *label_text) {
	GtkWidget *hbox;
	GtkWidget *button;
	GtkWidget *label;

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(parent), hbox);

	button = gtk_check_button_new();
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);

	label = gtk_label_new(label_text);
	gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);

	gtk_widget_show(button);
	gtk_widget_show(label);
	
	return hbox;
}

void call_context(int argc, char* argv[], char filelist[][30], int len, int type) {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *label_information;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_border_width(GTK_CONTAINER (window), 10);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

	switch (type) {
		case RECOMMEND:
			label_information = gtk_label_new("The disk is full. It is recommended to move the folder to the SSD. Would you like to move if?");
			break;
		default:
			printf("something wrong...\n");
			return;
	}
	gtk_widget_show(label_information);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(vbox), label_information);

	gtk_container_add(GTK_CONTAINER(window), vbox);

	GtkWidget *box[len];

	for(int i=0; i<len; i++) {
		box[i] = list_label_frame(vbox, filelist[i]);
		gtk_widget_show(box[i]);
	}

	gtk_widget_show(vbox);

	gtk_widget_show(window);
	gtk_main();
}

int main(int argc, char* argv[]) {
	char filelist[][30] = {"/user/path", "/your/path"};
	int len = sizeof(filelist) / sizeof(filelist[0]);
	call_context(argc, argv, filelist, len, RECOMMEND);
	return 0;
}	
