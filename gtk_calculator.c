/*
CSCE 155E - GUI Programming with GTK
A GTK Tutorial:
  http://developer.gnome.org/gtk-tutorial/2.90/
The GTK API:
  http://developer.gnome.org/gtk/2.24/index.html
*/

#include <stdlib.h> 
/* Introduce types and prototypes of GTK+ for the compiler. */ 
#include <gtk/gtk.h>  

/**
 * This helper function takes a GTK Entry (textbox) 
 * widget and parses its contents converting it to a
 * double value
 */
double getInput(GtkWidget *input) {
  double x = 0.0;
  const gchar *input_text;
  input_text = gtk_entry_get_text (GTK_ENTRY (input));
  x = atof(input_text);
  return x;
}

/*
 * Declare the two input and one output widgets as global 
 * so that functions have access to them.  Note: globals 
 * are generally bad and should not be used; there are better
 * solutions, but for demonstration purposes we have declared
 * them global
 */
GtkWidget *inputA;
GtkWidget *inputB;
GtkWidget *output;

/**
 * Callback to be used for the add button.  Takes the two
 * inputs, adds them, and places the result in the output
 * text box.
 */
void add(GtkWidget *widget,
         gpointer   data)
{
  double a = getInput(inputA);
  double b = getInput(inputB);
  double c = a + b;
  g_print ("Adding %f and %f = %f\n", a, b, c);
  char *output_text;
  output_text = (char *) malloc(20 * sizeof(char));
  sprintf(output_text, "%.4f", c); 
  gtk_entry_set_text(GTK_ENTRY(output), output_text);
}

/**
 * Callback to be used for the subtraction button.  Takes the two
 * inputs, subtracts them, and places the result in the output
 * text box.
 */
void sub(GtkWidget *widget,
         gpointer   data )
{
  double a = getInput(inputA);
  double b = getInput(inputB);
  double c = a - b;
  g_print ("Subtracting %f and %f = %f\n", a, b, c);
  char *output_text;
  output_text = (char *) malloc(20 * sizeof(char));
  sprintf(output_text, "%.4f", c);
  gtk_entry_set_text(GTK_ENTRY(output), output_text);
}

/**
 * Callback to be used for the multiplication button.  Takes the two
 * inputs, multiplies them, and places the result in the output
 * text box.
 */
void mul(GtkWidget *widget,
         gpointer   data )
{
  double a = getInput(inputA);
  double b = getInput(inputB);
  double c = a * b;
  g_print ("Multiplying %f and %f = %f\n", a, b, c);
  char *output_text;
  output_text = (char *) malloc(20 * sizeof(char));
  sprintf(output_text, "%.4f", c);
  gtk_entry_set_text(GTK_ENTRY(output), output_text);
}

//TODO: place your division callback function here

int main(int argc, char** argv) {    

  /* declare pointers to all of the widgets */
  //the main window widget
  GtkWidget *window;

  //the button widgets
  GtkWidget *subButton;
  GtkWidget *mulButton;
  GtkWidget *addButton;
  //TODO: create a widget pointer for the div button

  //the layout widgets: the horizontal box and the two columns
  GtkWidget *hbox;
  GtkWidget *col1;
  GtkWidget *col2;

  /* Initialize the GTK+ library. */   
  gtk_init(&argc, &argv);    

  /* create a new window and set its attributes */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width(GTK_CONTAINER (window), 10);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  col1 = gtk_vbox_new(FALSE, 0);
  col2 = gtk_vbox_new(FALSE, 0);
  hbox = gtk_hbox_new(FALSE, 0);

  //add the single horizontal box to the main window
  gtk_container_add(GTK_CONTAINER(window), hbox);

  //add the two vertical boxes to the horizontal box
  gtk_container_add(GTK_CONTAINER(hbox), col1); 
  gtk_container_add(GTK_CONTAINER(hbox), col2);

  //make sure all the boxes are visible
  gtk_widget_show(hbox);
  gtk_widget_show(col1);
  gtk_widget_show(col2); 

  //create a label and add it to the first column
  GtkWidget *label1 = gtk_label_new("CSCE 155E");
  gtk_box_pack_start(GTK_BOX(col1), label1, FALSE, FALSE, 0);
  gtk_widget_show(label1);

  //create another label and add it to the second column
  GtkWidget *label2 = gtk_label_new("Calculator!");
  gtk_label_set_markup(GTK_LABEL(label2), "<span fgcolor=\"blue\" font_weight=\"bold\">Calculator!</span>");
  gtk_box_pack_start(GTK_BOX(col2), label2, FALSE, FALSE, 0);
  gtk_widget_show(label2);

  /* create the two input text boxes, adding them to the first column */
  inputA = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(inputA), "0");
  gtk_box_pack_start (GTK_BOX(col1), inputA, TRUE, TRUE, 0);
  gtk_widget_show(inputA);

  inputB = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(inputB), "0");
  gtk_box_pack_start (GTK_BOX(col1), inputB, TRUE, TRUE, 0);
  gtk_widget_show(inputB);

  /* create the output text entry, make it non-editable */
  output = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(output), "0");
  gtk_editable_set_editable(GTK_EDITABLE(output), FALSE);
  gtk_widget_show(output);
  //add it to the first column
  gtk_box_pack_start(GTK_BOX(col1), output, TRUE, TRUE, 0);

  //create the add button and add it to the second column
  addButton = gtk_button_new_with_label("+");
  gtk_box_pack_start(GTK_BOX(col2), addButton, TRUE, TRUE, 0);
  gtk_widget_show(addButton);

  //create the subtract button and add it to the second column
  subButton = gtk_button_new_with_label("-");
  gtk_widget_show(subButton);
  gtk_box_pack_start(GTK_BOX(col2), subButton, TRUE, TRUE, 0);

  //create the multiply button and add it to the second column
  mulButton = gtk_button_new_with_label("*");
  gtk_widget_show(mulButton);
  gtk_box_pack_start(GTK_BOX(col2), mulButton, TRUE, TRUE, 0);

  //TODO: create the division button and add it to the second column

  /* register callbacks by binding a particular function to a
     particular event (in this case, the "clicked" event) to a particular
     Button widget
   */
  g_signal_connect(addButton, "clicked", G_CALLBACK(add), NULL);
  g_signal_connect(subButton, "clicked", G_CALLBACK(sub), NULL);
  g_signal_connect(mulButton, "clicked", G_CALLBACK(mul), NULL);

  //TODO: register your division function with your divide button

  gtk_widget_show(window);

  /* Start the main event loop. */   
  g_print("main: calling gtk_main\n");   
  gtk_main();    

  return EXIT_SUCCESS; 
}  

