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

//make "vector<int> *result" and call gtk_main_quik()
static void ok_button_press_event(GtkWidget *widget, gpointer data);

static void callback(GtkWidget *widget, gpointer text);

//make checked button number list
static void checkbutton_callback(GtkWidget *widget, long int num);

//cancel : result = -1
static void cancel_event(GtkWidget *widget, gpointer data);


GtkWidget *list_label_frame(GtkWidget *parent, const char *label_text, long int num);

//call gui
vector<int> * printList(int argc, char* argv[], vector<pair<double,string>> const* list, int errorCode);