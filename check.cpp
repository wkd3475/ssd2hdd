#include <gtk/gtk.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <utility>
//#include "PreviewFilesssdToHdd.h"

#define RECOMMEND 1
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 700
#define WIDGET_HEIGHT 40
#define WIDGET_WIDTH 20

using namespace std;

static void callback(GtkWidget *widget, gpointer data);
GtkWidget *list_label_frame(GtkWidget *parent, const char *label_text, int num);
vector<int> * printList(int argc, char* argv[], vector<pair<double,string>> const* list, int errorCode, double rate);

static void callback(GtkWidget *widget, gpointer data) {
	g_print("hello~~~ %s was pressed\n", (char *) data);
}

static void checkbutton_callback(GtkWidget *widget, gpointer data) {
	if(GTK_TOGGLE_BUTTON(widget)->active) {
		g_print("%s : activated\n", (char *) data);
	} else {
		g_print("%s : not activated\n", (char *) data);
	}
}

GtkWidget *list_label_frame(GtkWidget *parent, const char *label_text) {
	GtkWidget *hbox;
	GtkWidget *button;
	GtkWidget *label;

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_widget_set_size_request(hbox, WINDOW_WIDTH, WIDGET_HEIGHT);
	gtk_container_add(GTK_CONTAINER(parent), hbox);

	button = gtk_check_button_new();
	g_signal_connect(button, "clicked", G_CALLBACK(checkbutton_callback), (gpointer) label_text);
	gtk_widget_set_size_request(button, WIDGET_WIDTH, WIDGET_HEIGHT);
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
	
	label = gtk_label_new(label_text);
	gtk_widget_set_size_request(label, WINDOW_WIDTH-WIDGET_WIDTH, WIDGET_HEIGHT);
	gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);

	gtk_widget_show(button);
	gtk_widget_show(label);
	
	return hbox;
}

vector<int> * printList(int argc, char* argv[], vector<pair<double,string>> const* list, int errorCode, double rate) {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *label_information;
	GtkWidget *hbox_button;
	GtkWidget *button_cancel;
	GtkWidget *button_ok;
	vector<int> *a = new vector<int>;
	vector<int> *num_list = new vector<int>;

	a->push_back(0);
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "SSD to HDD");

	gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(gtk_exit), NULL);
	gtk_signal_connect(GTK_OBJECT(window), "delete_event", GTK_SIGNAL_FUNC(gtk_exit), NULL);

	gtk_container_border_width(GTK_CONTAINER (window), 10);

	switch (errorCode) {
		case RECOMMEND:
		{
			label_information = gtk_label_new("The disk is full. It is recommended to move the folder to the SSD. Would you like to move if?");
			gtk_widget_show(label_information);

			vbox = gtk_vbox_new(FALSE, 0);
			gtk_container_add(GTK_CONTAINER(vbox), label_information);

			gtk_container_add(GTK_CONTAINER(window), vbox);

			string pathlist[10];
			int l = 0;
			for(vector<pair<double,string>>::const_iterator iter=list->begin(); iter!=list->end(); iter++) {
				pathlist[l] = (*iter).second;
				l += 1;
			}

			GtkWidget *hbox[l];

			for(int i=0; i<l; i++) {
				hbox[i] = list_label_frame(vbox, pathlist[i].c_str());
				gtk_widget_show(hbox[i]);
			}
			
			hbox_button = gtk_hbox_new(FALSE, 0);
			button_cancel = gtk_button_new_with_label("cancel");
			button_ok = gtk_button_new_with_label("ok");

			g_signal_connect(button_ok, "clicked", G_CALLBACK(callback), (gpointer) "ok");
			g_signal_connect(button_cancel, "clicked", G_CALLBACK(callback), (gpointer) "cancel");

			gtk_container_add(GTK_CONTAINER(hbox_button), button_cancel);
			gtk_container_add(GTK_CONTAINER(hbox_button), button_ok);
			gtk_container_add(GTK_CONTAINER(vbox), hbox_button);
			gtk_widget_show(hbox_button);
			gtk_widget_show(button_cancel);
			gtk_widget_show(button_ok);

			gtk_widget_show(vbox);

			gtk_widget_show(window);
			gtk_main();
			break;
		}
		default:
		{
			printf("something wrong...\n");
			a->push_back(-1);
			break;
		}

		return a;
	}

	gtk_container_add(GTK_CONTAINER(hbox_button), button_cancel);
	gtk_container_add(GTK_CONTAINER(hbox_button), button_ok);
	gtk_container_add(GTK_CONTAINER(vbox), hbox_button);
	gtk_widget_show(hbox_button);
	gtk_widget_show(button_cancel);
	gtk_widget_show(button_ok);

	gtk_widget_show(vbox);

	gtk_widget_show(window);
	gtk_main();
	return a;
}

int main(int argc, char* argv[]) {
	double a = 3, b = 2;
	string x = "/path/path";
	string y = "/your/path";
	vector<pair<double,string>> list;
	list.push_back(make_pair(a, x));
	list.push_back(make_pair(b, y));
	printList(argc, argv, &list, RECOMMEND, 0.02);
	return 0;
}	
