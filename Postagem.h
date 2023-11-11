#ifndef POSTAGEM_H
#define POSTAGEM_H

#include "Usuario.h"
#include "Comentario.h"
#include "Imagem.h"
#include "Misc.h"

typedef struct
{
    unsigned int Id;
    unsigned int Autor_Id;
    char Descrit[TEXTO_TAM];
    S_ArrayImagens Imagens;
    
    S_ArrayId QuemCurtiu;
    S_ArrayComentarios Comentarios;
} S_Postagem;

typedef struct 
{
    unsigned int Quantidade;
    S_Postagem* Postagens;
} S_ArrayPostagens;

unsigned int GerarId_Postagem(const S_ArrayPostagens* array);
void Alocar_Postagem(S_ArrayPostagens* array);
void Liberar_Postagens(S_ArrayPostagens* array);
void Liberar_Postagens_Profundo(S_ArrayPostagens* array);
void Desalocar_Postagem(S_ArrayPostagens* array);
void Adicionar_Postagem_NoArray(S_ArrayPostagens* array, const S_Postagem* postagem);
void Apagar_Post(S_ArrayPostagens* postagens, unsigned int post_id, S_ArrayUsuarios* usuarios);
void Editar_Post(S_ArrayPostagens* psotagens, S_Postagem* postagem);

void Postar(S_ArrayPostagens* array, unsigned int id_autor);
void Comentar(S_ArrayUsuarios* array, S_Postagem* postagem, unsigned int id_autor);
void Recomentar(S_Postagem* postagem, unsigned int id_autor);
void Descomentar(S_ArrayUsuarios* array, S_Postagem* postagem, unsigned int id_autor);

S_Postagem* Achar_Postagem_PorId(const S_ArrayPostagens* array, unsigned int id_postagem);
S_ArrayPostagens Achar_Postagens_DoUsuario(S_ArrayPostagens* array, unsigned int id_usuario);
void VerPostagem(const S_Postagem* postagem, const S_ArrayUsuarios* array);

void Curtir_Postagem(S_ArrayUsuarios* array, S_Postagem* postagem, unsigned int id_usuario);
void Descurtir_Postagem(S_ArrayUsuarios* array, S_Postagem* postagem, unsigned int id_usuario);
void Mostrar_Curtidas(const S_ArrayUsuarios* array, const S_Postagem* postagem);
bool VerificarCurtida_Postagem(const S_Postagem* postagem, unsigned int id_usuario);

void SalvarArquivo_Postagens(const S_ArrayPostagens* array, char* caminho_arquivo);
void CarregarArquivo_Postagens(S_ArrayPostagens* array, char* caminho_arquivo);

#endif