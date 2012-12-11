#include <gtk/gtk.h>
#include <string.h>

const char CATEGORIAS[] = "Categorias";
const char RESTAURANTES[] = "Restaurantes";
const char PRATOS[] = "Pratos";
const char* LISTA_CAT[] = { "Regional", "Italiana", "Chinesa", "Vegetariana", "", "Regional", "Italiana", "Chinesa", "Vegetariana", "" };
const char* LISTA_RES[] = { "Nome 1", "Nome 2", "Nome 3", "Nome 4", "Nome 5", "Nome 6", "Nome 7", "Nome 8", "Nome 9", "Nome 10" };

GtkWidget *vbox, *sobre, *confirm, *areaUtil, *lbusca, *entry1;
GtkWidget *exp_categoria = 0, *exp_restaurante = 0, *exp_pratos = 0;

void preenchePrato();
void preencheRestaurante();
void preencheConfirmacao();
void preencheCategoria();

int restaurantes = 0, pratos = 0, confirmar = 0;

void on_window_destroy(GtkObject *object, gpointer user_data)
{
	gtk_main_quit();
}
void on_sair_menu_item_activate(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

void on_categoria_clicked(GtkWidget *widget, gpointer data)
{
	char tmp[32] = "";
	strcpy(tmp, CATEGORIAS);
	strcat(tmp, " [");
	strcat(tmp, gtk_button_get_label(GTK_BUTTON(widget)));
	strcat(tmp, "]");
	gtk_expander_set_expanded(GTK_EXPANDER(exp_categoria), FALSE);
	gtk_expander_set_label(GTK_EXPANDER(exp_categoria), tmp);
	if (!restaurantes) {
		restaurantes = 1;
		preencheRestaurante();
	} else {
		gtk_expander_set_expanded(GTK_EXPANDER(exp_restaurante), TRUE);
		gtk_expander_set_expanded(GTK_EXPANDER(exp_pratos), FALSE);
	}
}

void on_restaurante_clicked(GtkWidget *widget, gpointer data)
{
	char tmp[32] = "";
	strcpy(tmp, RESTAURANTES);
	strcat(tmp, " [");
	strcat(tmp, gtk_button_get_label(GTK_BUTTON(widget)));
	strcat(tmp, "]");
	gtk_expander_set_expanded(GTK_EXPANDER(exp_restaurante), FALSE);
	gtk_expander_set_label(GTK_EXPANDER(exp_restaurante), tmp);
	if (!pratos) {
		pratos = 1;
		preenchePrato();
	} else {
		gtk_expander_set_expanded(GTK_EXPANDER(exp_restaurante), FALSE);
		gtk_expander_set_expanded(GTK_EXPANDER(exp_pratos), TRUE);
	}
}

void on_prato_clicked(GtkWidget *widget, gpointer data)
{
	char tmp[32] = "";
	strcpy(tmp, PRATOS);
	strcat(tmp, " [");
	strcat(tmp, gtk_label_get_text(GTK_LABEL(data)));
	strcat(tmp, "]");
	gtk_expander_set_expanded(GTK_EXPANDER(exp_pratos), FALSE);
	gtk_expander_set_label(GTK_EXPANDER(exp_pratos), tmp);
	if (!confirmar) {
		confirmar = 1;
		preencheConfirmacao();
	}	
}

void expandir(GtkExpander *widget, gpointer data)
{
	if (widget != exp_categoria)
		gtk_expander_set_expanded(exp_categoria, FALSE);
	if (widget != exp_pratos)
		gtk_expander_set_expanded(exp_pratos, FALSE);
	if (widget != exp_restaurante)
		gtk_expander_set_expanded(exp_restaurante, FALSE);
}

void on_voltar_clicked(GtkWidget *widget, gpointer data)
{

}

void on_finalizar_clicked(GtkWidget *widget, gpointer data)
{
	gtk_dialog_run(GTK_DIALOG(confirm));
	gtk_widget_hide(GTK_WIDGET(confirm));
}

void on_sobre_menu_item_activate(GtkWidget *widget, gpointer data)
{
	gtk_dialog_run(GTK_DIALOG(sobre));
	gtk_widget_hide(GTK_WIDGET(sobre));
}

void preencheCategoria ()
{
	exp_categoria = gtk_expander_new(CATEGORIAS);
	g_signal_connect(G_OBJECT(exp_categoria), "activate", G_CALLBACK(expandir), NULL);

	GtkWidget *tabela = gtk_table_new(2,5,TRUE);
	int i, j;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 5; j++) {
			GtkWidget *botao = gtk_button_new_with_label(LISTA_CAT[i*5+j]);
			g_signal_connect(G_OBJECT(botao), "clicked", G_CALLBACK(on_categoria_clicked), NULL);

			gtk_table_attach(GTK_TABLE(tabela), botao, j, j+1, i, i+1, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
		}

	gtk_container_add(GTK_CONTAINER(exp_categoria), tabela);
	gtk_box_pack_start(GTK_BOX(areaUtil), exp_categoria, TRUE, TRUE, 0);
	gtk_expander_set_expanded(GTK_EXPANDER(exp_categoria), TRUE);
	gtk_widget_show_all(exp_categoria);
}

void preencheRestaurante()
{
	exp_restaurante = gtk_expander_new(RESTAURANTES);
	g_signal_connect(G_OBJECT(exp_restaurante), "activate", G_CALLBACK(expandir), NULL);

	GtkWidget *tabela = gtk_table_new(5,2,TRUE);
	int i, j;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 2; j++) {
			GtkWidget *botao = gtk_button_new_with_label(LISTA_RES[i*2+j]);
			g_signal_connect(G_OBJECT(botao), "clicked", G_CALLBACK(on_restaurante_clicked), NULL);

			gtk_table_attach(GTK_TABLE(tabela), botao, j, j+1, i, i+1, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
		}

	gtk_container_add(GTK_CONTAINER(exp_restaurante), tabela);
	gtk_box_pack_start(GTK_BOX(areaUtil), exp_restaurante, TRUE, TRUE, 0);
	gtk_expander_set_expanded(GTK_EXPANDER(exp_restaurante), TRUE);
	gtk_widget_show_all(exp_restaurante);
}

void preenchePrato()
{
	exp_pratos = gtk_expander_new(PRATOS);
	g_signal_connect(G_OBJECT(exp_pratos), "activate", G_CALLBACK(expandir), NULL);

	GtkWidget *vdisplay = gtk_viewport_new(gtk_adjustment_new(200,200,200,0,0,0), gtk_adjustment_new(175,175,600,80,160,80));
	GtkWidget *tabela = gtk_table_new(2,3,TRUE);
	int i, j;
	char p[7] = "Prato A";
	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++) {
			p[6]++;

			GtkWidget *vbox1 = gtk_vbox_new(FALSE, 5);
			GtkWidget *nome = gtk_label_new(p);
			GtkWidget *preco = gtk_label_new("R$ 9000,01");
			GtkWidget *hbox = gtk_hbox_new(TRUE, 0);

			GtkWidget *botao1 = gtk_button_new_with_label("Detalhes");
			GtkWidget *botao = gtk_button_new_with_label("Selecionar");
			g_signal_connect(G_OBJECT(botao), "clicked", G_CALLBACK(on_prato_clicked), (gpointer) nome);

			gtk_box_pack_start(GTK_BOX(hbox), botao1, FALSE, FALSE, 0);
			gtk_box_pack_start(GTK_BOX(hbox), botao, FALSE, FALSE, 0);

			gtk_box_pack_start(GTK_BOX(vbox1), nome, FALSE, FALSE, 0);
			gtk_box_pack_start(GTK_BOX(vbox1), preco, FALSE, FALSE, 0);
			gtk_box_pack_start(GTK_BOX(vbox1), hbox, FALSE, FALSE, 0);

			gtk_table_attach(GTK_TABLE(tabela), vbox1, j, j+1, i, i+1, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
		}

	//gtk_container_add(GTK_CONTAINER(vdisplay), tabela);
	gtk_container_add(GTK_CONTAINER(exp_pratos), tabela);
	gtk_box_pack_start(GTK_BOX(areaUtil), exp_pratos, TRUE, TRUE, 0);
	gtk_expander_set_expanded(GTK_EXPANDER(exp_pratos), TRUE);
	gtk_widget_show_all(exp_pratos);
}

void preencheConfirmacao()
{
	GtkWidget *finalizar = gtk_button_new_with_label("Finalizar pedido");
	g_signal_connect(G_OBJECT(finalizar), "clicked", G_CALLBACK(on_finalizar_clicked), NULL);
	gtk_box_pack_start(GTK_BOX(areaUtil), finalizar, TRUE, TRUE, 0);
	gtk_widget_show_all(areaUtil);
}

int main(int argc, char const *argv[])
{
	GtkBuilder *builder;
	GtkWidget *window;

	
	gtk_init (&argc, &argv);
	
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "main.glade", NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
	gtk_widget_set_size_request(GTK_WIDGET(window), 500, 300);

	vbox = GTK_WIDGET (gtk_builder_get_object(builder, "vbox1"));
	sobre = GTK_WIDGET (gtk_builder_get_object(builder, "caixa_sobre"));
	confirm = GTK_WIDGET (gtk_builder_get_object(builder, "dialogo_confirm"));
	areaUtil = GTK_WIDGET (gtk_builder_get_object(builder, "AreaUtil"));
	gtk_builder_connect_signals (builder, NULL);	  

	g_object_unref (G_OBJECT (builder));

	preencheCategoria();

	gtk_widget_show_all (window);
	gtk_main ();
	return 0;
}