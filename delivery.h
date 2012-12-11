#ifndef DELIVERY_H
#define DELIVERY_H

#include <stdlib.h>
#include <string.h>

struct alimento
{
	struct alimento *prox; // ponteiro para proxima comida/prato
	char *nome, *desc; // nome do produto e descricao do mesmo
	float preco; // preco em float
	char *foto; // imagem do produto
};
struct restaurantes
{
	struct restaurantes *prox; // ponteiro para proximo restaurante
	struct alimento *ali; // ponteiro para primeiro elemento da lista de alimentos do restaurante (vulgo cardapio)
	char *nome, *desc; // nome do restaurante e descricao do mesmo
	char *foto; // imagem do restaurante
};
struct categorias
{
	struct categorias *prox; // ponteiro para proxima categoria
	struct restaurantes *rest; // ponteiro para primeiro elemento da lista de restaurantes 
	char *nome; // nome da categoria
};
struct resultadoBusca {
	struct categorias* c;
	struct restaurantes* r;
	struct alimento* a;
};

struct alimento* createFood(struct alimento *root, char *nome, char *desc, float preco, char *foto)
{
	struct alimento *i;
	
	if (root) {
		i = root->prox;
		if (i) {
			while (i->prox)
				i = i->prox;

			i->prox = (struct alimento*) malloc(sizeof (struct alimento));
			i = i->prox;
		} else {
			root->prox = (struct alimento*) malloc(sizeof (struct alimento));
			i = root->prox;
		}
	} else {
		root = (struct alimento*) malloc(sizeof (struct alimento));
		i = root;
	}

	if (!i) {
		i->prox = 0;
		i->nome = nome;
		i->desc = desc;
		i->preco = preco;
		i->foto = foto;
	}

	return i;
}
struct restaurantes* createRestaurant(struct restaurantes *root, char *nome, char *desc, char *foto, struct alimento *ali)
{
	struct restaurantes *i;

	if (root) {
		i = root->prox;
		if (i) {
			while (i->prox)
				i = i->prox;

			i->prox = (struct restaurantes*) malloc(sizeof (struct restaurantes));
			i = i->prox;
		} else {
			root->prox = (struct restaurantes*) malloc(sizeof (struct restaurantes));
			i = root->prox;
		}
	} else {
		root = (struct restaurantes*) malloc(sizeof (struct restaurantes));
		i = root;
	}

	i->prox = 0;
	i->nome = nome;
	i->desc = desc;
	i->ali = ali;
	i->foto = foto;

	return i;
}
struct categorias* createCategory(struct categorias *root, char *nome, struct restaurantes *rest)
{
	struct categorias *i;

	if (root) {
		i = root->prox;
		if (i) {
			while (i->prox)
				i = i->prox;

			i->prox = (struct categorias*) malloc(sizeof (struct categorias));
			i = i->prox;
		} else {
			root->prox = (struct categorias*) malloc(sizeof (struct categorias));
			i = root->prox;
		}
	} else {
		root = (struct categorias*) malloc(sizeof (struct categorias));
		i = root;
	}

	i->prox = 0;
	i->nome = nome;
	i->rest = rest;

	return i;
}


void deleteFood(struct alimento *root)
{
	if (root->prox)
		deleteFood(root->prox);
	free(root);
}
void deleteRestaurant(struct restaurantes *root)
{
	if (root->prox)
		deleteRestaurant(root->prox);
	if (root->ali)
		deleteFood(root->ali);
	free(root);
}
void deleteCategory(struct categorias *root)
{
	if (root->prox)
		deleteCategory(root->prox);
	if (root->rest)
		deleteRestaurant(root->rest);
	free(root);
}

struct resultadoBusca busca( char * alvo, struct categorias * raiz ) {
	struct resultadoBusca ret;
	ret.r = 0;
	ret.a = 0;

	ret.c = raiz;
	while ( ret.c ) {
		if( strcmp(ret.c->nome, alvo) == 0 )
			return ret;
		
		if ( ret.c->rest ) {
			ret.r = ret.c->rest;
			while ( ret.r ) {
				if( strcmp(ret.r->nome , alvo) == 0 )
					return ret;

				if ( ret.r->ali ) {
					ret.a = ret.r->ali;
					while ( ret.a ){
						if( strcmp(ret.a->nome , alvo) == 0 )
							return ret;
						ret.a = ret.a->prox;
					}
				}
				ret.r = ret.r->prox;
			}
		}
		ret.c = ret.c->prox;
	}

	ret.r = 0;
	ret.c = 0;
	ret.a = 0;

	return ret;
}

#endif