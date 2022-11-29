#include <gtk/gtk.h>

#include "pinging.h"

static void ping_on_click(GtkWidget *widget, gpointer data)
{
  GtkButton *button = (GtkButton *) widget;
  double res = measure_get();
  char ping_str[50];
  sprintf(ping_str, "GET ping: %lfms", res * 666);
  gtk_button_set_label(button, ping_str);
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "GET Pinger");
  gtk_window_set_default_size(GTK_WINDOW(window), 256, 256);

  button = gtk_button_new_with_label("GET Ping");
  g_signal_connect(button, "clicked", G_CALLBACK(ping_on_click), NULL);
  gtk_window_set_child(GTK_WINDOW(window), button);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc,
         char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.pinger", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
