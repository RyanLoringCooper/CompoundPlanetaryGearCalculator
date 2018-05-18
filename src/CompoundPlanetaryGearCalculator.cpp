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

static GearCalculator *getGearCalculator() {
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
    return new GearCalculator(maxTeeth, minTeeth, minPlanets, maxPlanets, minTeethSize, minDiameter, maxDiameter, diameterInterval);
}

static void runParallel(GtkWidget *widget, gpointer data) {
    GearCalculator *gc = getGearCalculator();
    gc->run(true);
    gc->printResults(std::cout);
    delete gc;
}

static void runSequential(GtkWidget *widget, gpointer data) {
    GearCalculator *gc = getGearCalculator();
    gc->run(false);
    gc->printResults(std::cout);
    delete gc;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "bin/UI.glade", NULL);
    GObject *window = gtk_builder_get_object(builder, "MainWindow");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GObject *parallel = gtk_builder_get_object(builder, "runParallelButton");
    g_signal_connect(parallel, "clicked", G_CALLBACK(runParallel), NULL);
    GObject *sequential = gtk_builder_get_object(builder, "runSequentialButton");
    g_signal_connect(sequential, "clicked", G_CALLBACK(runSequential), NULL);

    gtk_main();
	// GearCalculator gc;
	// gc.run();	
	// gc.printResults(std::cout);
	return 0;
}
