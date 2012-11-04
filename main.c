#include <gtk/gtk.h>

// Variaveis globais
GtkWidget *vbox;
GtkWidget *viewport;
GtkWidget *sobre;
int pedido_feito = 0;
/* ---------- */

// Assinatura das funcoes
        // Listagens
        void listar_restaurantes(int voltou);
        void listar_cardapios();

        // Auxiliares
        void limpar_viewport();
        void mostrar_finalizar();
        void sair();

/* ---------- */

// Callbacks

void
on_window_destroy(GtkObject *object, 
        gpointer user_data)
{
        sair();
}

void
on_sair_menu_item_activate(GtkWidget *widget,
        gpointer data)
{
        sair();
}

void 
on_restaurante_clicked( GtkWidget *widget,
        gpointer   data )
{
        listar_cardapios();
}

void 
on_voltar_clicked( GtkWidget *widget, 
        gpointer data)
{
        listar_restaurantes(1);
}

void 
on_finalizar_clicked(GtkWidget *widget,
        gpointer data)
{
        g_print("Ir para finalizar");
}

void
on_sobre_menu_item_activate(GtkWidget *widget,
        gpointer data)
{
        gtk_dialog_run(GTK_DIALOG(sobre));
        gtk_widget_hide(GTK_WIDGET(sobre));
}

/* ---------- */

void 
limpar_viewport()
{
        GtkWidget *filho_antigo;

        filho_antigo = gtk_bin_get_child(GTK_BIN(viewport));
        if (filho_antigo != NULL)
                gtk_widget_destroy(filho_antigo);
}

void 
sair()
{
        gtk_main_quit();
}

void 
mostrar_finalizar()
{
        GtkWidget *finalizar;
        finalizar = gtk_button_new_with_label("Finalizar pedido");
        g_signal_connect(finalizar, "clicked", G_CALLBACK(on_finalizar_clicked), NULL);

        gtk_box_pack_start(GTK_BOX(vbox), finalizar, FALSE, FALSE, 0);
        gtk_widget_show_all(GTK_WIDGET(vbox));

        pedido_feito = 1;
}


void listar_restaurantes(int voltou)
{
        limpar_viewport();

        GtkWidget *tabela;
        tabela = gtk_table_new(3, 2, TRUE);
        gtk_table_set_row_spacings(GTK_TABLE(tabela), 5);
        gtk_table_set_col_spacings(GTK_TABLE(tabela), 5);

        GtkWidget *restaurante, *imagem, *nome, *categorias, *botao;

        int b, c, i;

        for (i = 0; i < 6; ++i)
        {
                restaurante = gtk_vbox_new(FALSE, 0);

                imagem = gtk_label_new("imagem");
                nome = gtk_label_new("Restaurante");
                categorias = gtk_label_new("categoria");
                botao = gtk_button_new_with_label("Ver pratos");

                gtk_box_pack_start(GTK_BOX(restaurante), imagem, FALSE, FALSE, 0);
                gtk_box_pack_start(GTK_BOX(restaurante), nome, FALSE, FALSE, 0);
                gtk_box_pack_start(GTK_BOX(restaurante), categorias, FALSE, FALSE, 0);
                gtk_box_pack_start(GTK_BOX(restaurante), botao, FALSE, FALSE, 0);

                g_signal_connect(botao, "clicked", G_CALLBACK(on_restaurante_clicked), NULL);

                b = (i%3);
                c = i/3;
                gtk_table_attach_defaults (GTK_TABLE(tabela), restaurante, b, b+1, c, c+1);
        }

        gtk_container_add(GTK_CONTAINER(viewport), tabela);

        if (voltou == 1 && pedido_feito == 0)
                mostrar_finalizar();

        gtk_widget_show_all(tabela);
}

void listar_cardapios()
{
        limpar_viewport();

        GtkWidget *tabela;
        tabela = gtk_table_new(3, 3, TRUE);
        gtk_table_set_row_spacings(GTK_TABLE(tabela), 5);
        gtk_table_set_col_spacings(GTK_TABLE(tabela), 5);

        GtkWidget *prato, *imagem, *nome, *preco, *botao, *voltar;

        GtkVBox *caixa_botao;
        caixa_botao = gtk_vbox_new(TRUE, 0);

        voltar = gtk_button_new_with_label("< Voltar");
        gtk_button_set_relief(GTK_BUTTON(voltar), GTK_RELIEF_NONE);
        g_signal_connect(voltar, "clicked", G_CALLBACK(on_voltar_clicked), NULL);

        gtk_box_pack_start(GTK_BOX(caixa_botao), voltar, TRUE, FALSE, 0);

        gtk_table_attach_defaults(GTK_TABLE(tabela), GTK_WIDGET(caixa_botao), 0, 1, 0, 1);

        int b, c, i;
        for (i = 1; i < 9; ++i)
        {
                prato = gtk_vbox_new(FALSE, 0);

                imagem = gtk_label_new("imagem");
                nome = gtk_label_new("nome");
                preco = gtk_label_new("R$ 12, 00");
                botao = gtk_toggle_button_new_with_label("Incluir");

                gtk_box_pack_start(GTK_BOX(prato), imagem, FALSE, FALSE, 0);
                gtk_box_pack_start(GTK_BOX(prato), nome, FALSE, FALSE, 0);
                gtk_box_pack_start(GTK_BOX(prato), preco, FALSE, FALSE, 0);
                gtk_box_pack_start(GTK_BOX(prato), botao, FALSE, FALSE, 0);


                b = (i%3);
                c = i/3;
                gtk_table_attach_defaults (GTK_TABLE(tabela), prato, b, b+1, c, c+1);
        }

        gtk_container_add(GTK_CONTAINER(viewport), tabela);
        gtk_widget_show_all(tabela);
}

int
main (int argc, char *argv[])
{
        GtkBuilder *builder;
        GtkWidget *window;

        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "main.glade", NULL);

        window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
        gtk_widget_set_size_request(GTK_WIDGET(window), 500, 300);

        viewport = GTK_WIDGET (gtk_builder_get_object (builder, "viewport"));
        vbox = GTK_WIDGET (gtk_builder_get_object(builder, "vbox1"));
        sobre = GTK_WIDGET (gtk_builder_get_object(builder, "caixa_sobre"));
        gtk_builder_connect_signals (builder, NULL);          


        g_object_unref (G_OBJECT (builder));

        // Listando Restaurantes
        listar_restaurantes(0);
        
        gtk_widget_show_all (window);       
        gtk_main ();
        
        return 0;
}