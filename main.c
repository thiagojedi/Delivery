#include <gtk/gtk.h>


GtkWidget*
criar_janela()
{
        GtkWidget *window;
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);


        return window;
}

void
on_window_destroy(GtkObject *object, gpointer user_data)
{
        gtk_main_quit();
}

void cria_cardapio(GtkWidget* port)
{
        GtkWidget *filho_antigo;

        filho_antigo = gtk_bin_get_child(GTK_BIN(port));
        gtk_widget_destroy(filho_antigo);

        GtkWidget *tabela;
        tabela = gtk_table_new(3, 3, TRUE);
        gtk_table_set_row_spacings(GTK_TABLE(tabela), 5);
        gtk_table_set_col_spacings(GTK_TABLE(tabela), 5);

        GtkWidget *prato, *imagem, *nome, *preco, *botao;
        int b, c, i;

        for (i = 0; i < 9; ++i)
        {
                prato = gtk_vbox_new(FALSE, 0);

                imagem = gtk_label_new("imagem");
                nome = gtk_label_new("nome");
                preco = gtk_label_new("R$ 12, 00");
                botao = gtk_button_new_with_label("Incluir");
        
                gtk_box_pack_start(GTK_BOX(prato), imagem, FALSE, FALSE, 0);
                gtk_box_pack_start(GTK_BOX(prato), nome, FALSE, FALSE, 0);
                gtk_box_pack_start(GTK_BOX(prato), preco, FALSE, FALSE, 0);


                b = (i%3);
                c = i/3;
                gtk_table_attach_defaults (GTK_TABLE(tabela), prato, b, b+1, c, c+1);
        }

        gtk_container_add(GTK_CONTAINER(port), tabela);
}

int
main (int argc, char *argv[])
{
        GtkBuilder *builder;
        GtkWidget *window;
        GtkWidget *viewport;
        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "main.glade", NULL);

        window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
        viewport = GTK_WIDGET (gtk_builder_get_object (builder, "viewport"));
        gtk_builder_connect_signals (builder, NULL);          


        g_object_unref (G_OBJECT (builder));

        cria_cardapio(viewport);

        
        gtk_widget_show_all (window);       
        gtk_main ();
        
        return 0;
}