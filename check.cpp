#include "check.h"

static vector<int> *result = new vector<int>;

static int list[LIST_NUM] = {0, };

int main(int argc, char* argv[]) {
	double a[5] = {1,2,3,4,5};
	string x[5] = {"/path/path", "hi", "hello", "why", "mundf"};
	vector<pair<double,string>> list;
	vector<int> *b = new vector<int>;
	for(int i=0; i<5; i++) {
		list.push_back(make_pair(a[i], x[i]));
	}
	printList(argc, argv, &list, RECOMMEND);
	printf("<result>\n");
	//result == -1 => cancel
	for(int i=0; i<result->size(); i++) {
		printf("num %d : %d\n", i, result->at(i));
	}
	return 0;
}

vector<int> * printList(int argc, char* argv[], vector<pair<double,string>> const* list, int errorCode) {

	if(list->size()>10) {
		result->push_back(-1);
		return result;
	}

	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *label_information;
	GtkWidget *hbox_button;
	GtkWidget *button_cancel;
	GtkWidget *button_ok;

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
				hbox[i] = list_label_frame(vbox, pathlist[i].c_str(), i);
				gtk_widget_show(hbox[i]);
			}

			hbox_button = gtk_hbox_new(FALSE, 0);
			button_cancel = gtk_button_new_with_label("cancel");
			button_ok = gtk_button_new_with_label("ok");

			g_signal_connect(button_ok, "clicked", G_CALLBACK(ok_button_press_event), NULL);
			g_signal_connect(GTK_OBJECT(button_cancel), "clicked", G_CALLBACK(cancel_event), (gpointer) "cancel");

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
			result->push_back(-1);
			break;
		}
	}

	return result;
}

GtkWidget *list_label_frame(GtkWidget *parent, const char *label_text, long int num) {
	GtkWidget *hbox;
	GtkWidget *button;
	GtkWidget *label;
	GdkColor color;
	color.red = 0x0000;
	color.green = 0x0000;
	color.blue = 0x0000;
	
	hbox = gtk_hbox_new(FALSE, 0);
	gtk_widget_set_size_request(hbox, WINDOW_WIDTH, WIDGET_HEIGHT);
	gtk_container_add(GTK_CONTAINER(parent), hbox);

	button = gtk_check_button_new();
	g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(checkbutton_callback), (gpointer) num);
	gtk_widget_set_size_request(button, WIDGET_WIDTH, WIDGET_HEIGHT);
	gtk_container_add(GTK_CONTAINER(hbox), button);
	//gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
	
	label = gtk_label_new(label_text);
	gtk_widget_set_size_request(label, WINDOW_WIDTH-WIDGET_WIDTH, WIDGET_HEIGHT);
	//gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(hbox), label);

	gtk_widget_modify_bg(label, GTK_STATE_NORMAL, &color);

	gtk_widget_show(button);
	gtk_widget_show(label);
	
	return hbox;
}


static void ok_button_press_event(GtkWidget *widget, gpointer data) {
	for(int i=0; i<LIST_NUM; i++) {
		if(list[i]==1)
			result->push_back(i);
	}

	gtk_main_quit();
}

static void callback(GtkWidget *widget, gpointer text) {
	g_print("hello~~~ %s was pressed\n", (char *) text);
}

static void checkbutton_callback(GtkWidget *widget, long int num) {
	if(GTK_TOGGLE_BUTTON(widget)->active) {
		g_print("%ld : activated\n", num);
		list[num] = 1;
	} else {
		g_print("%ld : not activated\n", num);
		list[num] = 0;
	}
	printf("\n");
}

static void cancel_event(GtkWidget *widget, gpointer data) {
	result->push_back(-1);

	gtk_main_quit();
}

static void init_list() {
	result->clear();
	for(int i=0; i<LIST_NUM; i++) {
		list[i] = 0;
	}
}