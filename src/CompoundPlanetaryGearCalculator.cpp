#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <mutex>
#include <thread>
#include <gtk/gtk.h>
#include "GearSet.h"
#include "ValidSet.h"
#include "GearCalculator.h"

GtkBuilder *builder;

static const gchar *getEntryData(const char *entryName) {
	GtkEntry *entry = (GtkEntry *) gtk_builder_get_object(builder, entryName);
    return gtk_entry_get_text(entry);
}

static void run(GtkWidget *widget, gpointer data) {
    int minTeeth = atoi(getEntryData("minTeethEntry"));
    int maxTeeth = atoi(getEntryData("maxTeethEntry"));
    int minPlanets = atoi(getEntryData("minPlanetsEntry"));
    int maxPlanets = atoi(getEntryData("maxPlanetsEntry"));
    double minTeethSize = atof(getEntryData("minToothSizeEntry"));
    double minDiameter = atof(getEntryData("minDiameterEntry"));
    double maxDiameter = atof(getEntryData("maxDiameterEntry"));
    double diameterInterval = atof(getEntryData("diameterIntervalEntry"));
	std::cout << "minTeeth " << minTeeth << std::endl
        << "maxTeeth " << maxTeeth << std::endl
        << "minPlanets " << minPlanets << std::endl
        << "maxPlanets " << maxPlanets << std::endl
        << "minDiameter " << minDiameter << std::endl
        << "maxDiameter " << maxDiameter << std::endl
        << "diameterInterval " << diameterInterval << std::endl;
    GearCalculator gc(maxTeeth, minTeeth, minPlanets, maxPlanets, minTeethSize, minDiameter, maxDiameter, diameterInterval);
    gc.run();
    gc.printResults(std::cout);

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
