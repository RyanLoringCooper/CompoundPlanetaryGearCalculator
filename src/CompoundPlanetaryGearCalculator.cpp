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
	GtkEntry *minTeethEntry= gtk_builder_get_object(builder, "minTeethEntry");
    gchar *minTeethStr = gtk_entry_get_text(minTeethEntry);
	std::cout << minTeethStr << std::endl;
}

static void activate (GtkApplication *app, gpointer user_data) {
	// TODO need to pass args to gc
	GObject *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Compound Planetary Gear Calculator");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	GtkWidget *grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	GtkWidget *textBox = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), textBox, 0, 0, 1, 1);

	GTKWidget *runButton = gtk_button_new_with_label("Run");
	g_signal_connect(runButton, "clicked", g_CALLBACK(run), NULL);
	gtk_grid_attach(GTK_GRID(grid), runButton, 0, 1, 1, 1);

	gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "UI.glade");
    GObjectt *window = gtk_builder_get_object(builder, "MainWindow");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GObject *button = gtk_builder_get_object(builder, "runButton");
    g_signal_connect(button, "clicked", G_CALLBACK(run), NULL);

    gtk_main();
	// GearCalculator gc;
	// gc.run();	
	// gc.printResults(std::cout);
	return 0;
}
