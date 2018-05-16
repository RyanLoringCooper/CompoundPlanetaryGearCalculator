#include <iostream>
#include <cmath>
#include <vector>
#include <mutex>
#include <thread>
#include <gtk/gtk.h>
#include "GearSet.h"
#include "ValidSet.h"
#include "GearCalculator.h"

GtkBuilder *builder;

static void run(GtkWidget *widget, gpointer data) {
	GtkEntry *minTeethEntry = (GtkEntry *) gtk_builder_get_object(builder, "minTeethEntry");
    const gchar *minTeethStr = gtk_entry_get_text(minTeethEntry);
	std::cout << minTeethStr << std::endl;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "bin/UI.glade", NULL);
    GObject *window = gtk_builder_get_object(builder, "MainWindow");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GObject *button = gtk_builder_get_object(builder, "runButton");
    g_signal_connect(button, "clicked", G_CALLBACK(run), NULL);

    gtk_main();
	// GearCalculator gc;
	// gc.run();	
	// gc.printResults(std::cout);
	return 0;
}
