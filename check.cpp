#include <gtk/gtk.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <utility>
#include <stdlib.h>
//#include "PreviewFilesssdToHdd.h"

#define RECOMMEND 1
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 700
#define WIDGET_HEIGHT 40
#define WIDGET_WIDTH 20
#define LIST_NUM 10

using namespace std;

typedef struct data{
	GtkWidget *check_button_list[LIST_NUM];
	vector<int> *result;
} Data;

static void ok_button_prees_event(GtkWidget *widget, gpointer data);
static void callback(GtkWidget *widget, gpointer text);
static void checkbutton_callback(GtkWidget *widget, gpointer text);
GtkWidget *list_label_frame(GtkWidget *parent, const char *label_text, GtkWidget *checkbutton);
vector<int> * printList(int argc, char* argv[], vector<pair<double,string>> const* list, int errorCode, double rate);

int main(int argc, char* argv[]) {
	double a[5] = {1,2,3,4,5};
	string x[5] = {"/path/path", "hi", "hello", "why", "mundf"};
	vector<pair<double,string>> list;
	vector<int> *b = new vector<int>;
	for(int i=0; i<5; i++) {
		list.push_back(make_pair(a[i], x[i]));
	}
	b = printList(argc, argv, &list, RECOMMEND, 0.02);
	printf("hello\n");
	for(int i=0; i<b->size(); i++) {
		printf("%d : %d\n", i, b->at(i));
	}
	return 0;
}

static void ok_button_press_event(GtkWidget *widget, gpointer data) {
	Data * d = (Data *) data;
	
	for(int i=0; i<LIST_NUM; i++) {
		if(GTK_TOGGLE_BUTTON(&d->check_button_list[i])->active) {
			d->result->push_back(i);
		}
	}
	gtk_main_quit();
}

static void callback(GtkWidget *widget, gpointer text) {
	g_print("hello~~~ %s was pressed\n", (char *) text);
}

static void checkbutton_callback(GtkWidget *widget, gpointer text) {
	if(GTK_TOGGLE_BUTTON(widget)->active) {
		g_print("%s : activated\n", (char *) text);
	} else {
		g_print("%s : not activated\n", (char *) text);
	}
}

GtkWidget *list_label_frame(GtkWidget *parent, const char *label_text, GtkWidget **checkbutton) {
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

	printf("button address : %p\n", button);
	**checkbutton = *button;
	printf("checkbutton address : %p\n", *checkbutton);
	
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
	Data data;
	for(int i=0; i<sizeof(data.check_button_list) / sizeof(GtkWidget *); i++) {
		data.check_button_list[i] = (GtkWidget*)malloc(sizeof(GtkWidget));
	}
	data.result = new vector<int>;
	printf("data.check_button_list address : %p\n", data.check_button_list);

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
				printf("data.check_button_list[%d] address: %p\n", i, &data.check_button_list[i]);
				hbox[i] = list_label_frame(vbox, pathlist[i].c_str(), &data.check_button_list[i]);
				gtk_widget_show(hbox[i]);
			}

			hbox_button = gtk_hbox_new(FALSE, 0);
			button_cancel = gtk_button_new_with_label("cancel");
			button_ok = gtk_button_new_with_label("ok");

			g_signal_connect(button_ok, "clicked", G_CALLBACK(ok_button_press_event), (gpointer) &data);
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
			a = data.result;
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

