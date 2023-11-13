#ifndef COMENTARIOS_H
#define COMENTARIOS_H

#include "Misc.h"
#include "Usuario.h"
#include <stdbool.h>

typedef struct
{
    unsigned int Id;
    unsigned int Perfil_Id;
    unsigned int Postagem_Id;
    char Mensagem[TEXTO_TAM];
} S_Comentario;

typedef struct 
{
    unsigned int Quantidade;
    S_Comentario *Comentarios;
} S_ArrayComentarios;

unsigned int GerarId_Comentario(const S_ArrayComentarios* array);
void Alocar_Comentario(S_ArrayComentarios* array);
void Desalocar_Comentario(S_ArrayComentarios* array);
void Criar_Comentario(S_ArrayComentarios* array, unsigned int id_postagem, unsigned int id_autor);
void Editar_Comentario(S_ArrayComentarios* array, S_Comentario* comentario);
void Apagar_Comentario(S_ArrayComentarios* array, int posicao_comentario);
void Liberar_Comentarios(S_ArrayComentarios* array);

bool Verifica_Autoria(const S_Comentario* comentario, unsigned int id_logado);
void Imprime_Comentario(const S_Comentario* comentario, const S_ArrayUsuarios* usuarios);
void Imprime_Comentarios(const S_ArrayComentarios* array, const S_ArrayUsuarios* usuarios);
bool Imprime_Comentarios_DoUsuario(const S_ArrayComentarios* array, const S_ArrayUsuarios* usuarios, unsigned int id_logado);

int Achar_Posicao_DoComentario(S_ArrayComentarios* array, unsigned int id_comentario);
S_Comentario* Achar_Comentario(S_ArrayComentarios* array, int id_comentario);
S_ArrayComentarios Achar_Comentarios_DoUsuario(const S_ArrayComentarios* array, unsigned int id_usuario);
#endif
