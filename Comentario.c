#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Comentario.h"
#include "Usuario.h"
#include "Misc.h"

unsigned int GerarId_Comentario(const S_ArrayComentarios* array)
{
    unsigned int ultimo_id = 0;
    for(int i = 0; i < array->Quantidade - 1; i++)
    {
        if(array->Comentarios[i].Id > ultimo_id)
            ultimo_id = array->Comentarios[i].Id;
    }
    return ultimo_id + 1;
}
void Alocar_Comentario(S_ArrayComentarios* array)
{
    (array->Quantidade)++;
    if(array->Quantidade == 1)
        array->Comentarios = (S_Comentario *) malloc(sizeof(S_Comentario));
    else
        array->Comentarios = (S_Comentario *) realloc(array->Comentarios, array->Quantidade * sizeof(S_Comentario));

    if(array->Comentarios == NULL)
        printf("ERRO: Alocagem de comentario");    
    return;
}
void Desalocar_Comentario(S_ArrayComentarios* array)
{
    if(array->Quantidade == 0)
        return;

    (array->Quantidade)--;
    if(array->Quantidade == 0)
        Liberar_Comentarios(array);
    else
    {
        array->Comentarios = (S_Comentario *) realloc(array->Comentarios, array->Quantidade * sizeof(S_Comentario));
        if(array->Comentarios == NULL)
            printf("ERRO: De-alocagem de comentario");    
    }
    return;
}
void Adicionar_Comentario_NoArray(S_ArrayComentarios* array, const S_Comentario* comentario)
{
    Alocar_Comentario(array);
    array->Comentarios[array->Quantidade-1] = *comentario;
    return;
}
void Apagar_Comentario(S_ArrayComentarios* array, int posicao_comentario)
{
    array->Comentarios[posicao_comentario] = array->Comentarios[array->Quantidade - 1];
    Desalocar_Comentario(array);
}
S_Comentario* Achar_Comentario(S_ArrayComentarios* array, int id_comentario)
{
    for (int i = 0; i < array->Quantidade; i++)
    {
        if(array->Comentarios[i].Id == id_comentario)
            return &array->Comentarios[i];
    }
    return NULL;
}
int Achar_Posicao_DoComentario(S_ArrayComentarios* array, unsigned int id_comentario)
{
    for (int i = 0; i < array->Quantidade; i++)
    {
        if(array->Comentarios[i].Id == id_comentario)
            return i;
    }
    return -1;
}
S_ArrayComentarios Achar_Comentarios_DoUsuario(const S_ArrayComentarios* array, unsigned int id_usuario)
{
    S_ArrayComentarios Saida = {0, NULL};

    for(int i = 0; i < array->Quantidade; i++)
    {
        S_Comentario* Comentario = &array->Comentarios[i];
        if(Verifica_Autoria(Comentario, id_usuario) == true)
            Adicionar_Comentario_NoArray(&Saida, Comentario);
    }
    
    return Saida;
}
void Liberar_Comentarios(S_ArrayComentarios* array)
{
    if(array->Comentarios != NULL)
        free(array->Comentarios);
    array->Comentarios = NULL;
    array->Quantidade = 0;
    return;
}
void Criar_Comentario(S_ArrayComentarios* array, unsigned int id_postagem, unsigned int id_autor)
{
    Alocar_Comentario(array);
    S_Comentario* NovoComentario = &array->Comentarios[array->Quantidade - 1];
    NovoComentario->Id = GerarId_Comentario(array);
    NovoComentario->Perfil_Id = id_autor;
    NovoComentario->Postagem_Id = id_postagem;

    printf(">> Escreva o seu comentario (maximo de 256 caracteres): \n");
    fgets(NovoComentario->Mensagem, TEXTO_TAM, stdin);
    Resolve_Fgets(NovoComentario->Mensagem);

    printf(">> Comentario Criado<<\n");
    return;
}
void Editar_Comentario(S_ArrayComentarios* array, S_Comentario* comentario)
{
    printf(">> Edite o seu comentario (maximo de 256 caracteres): \n");
    fgets(comentario->Mensagem, TEXTO_TAM, stdin);
    Resolve_Fgets(comentario->Mensagem);
    printf(">>> Comentario Editado <<<\n");
    return;
}
bool Verifica_Autoria(const S_Comentario* comentario, unsigned int id_usuario)
{
    return comentario->Perfil_Id == id_usuario;
}
void Imprime_Comentario(const S_Comentario* comentario, const S_ArrayUsuarios* usuarios)
{
    S_Usuario* Autor = Achar_Usuario_PorId(usuarios, comentario->Perfil_Id);
    printf(">>> Comentario #%06u <<<\n", comentario->Id);
    printf("Usuario %s #%06u comentou:\n", Autor->Nome, Autor->Id);
    printf("> %s <\n", comentario->Mensagem);
    return;
}
void Imprime_Comentarios(const S_ArrayComentarios* array, const S_ArrayUsuarios* usuarios)
{
    if(array->Quantidade < 1)
        printf(">>>> Nenhum Comentario Foi Feito Ainda<<<<\n");
    else
    {
        for(int i = 0; i < array->Quantidade; i++)
            Imprime_Comentario(&array->Comentarios[i], usuarios);
    }
    return;
}
bool Imprime_Comentarios_DoUsuario(const S_ArrayComentarios* array, const S_ArrayUsuarios* usuarios, unsigned int id_usuario)
{
    bool TemComentarios = false;
    if(array->Quantidade < 1)
    {
        printf(">>>> Nenhum Comentario Foi Feito Ainda<<<<\n");
        return false;
    }

    for(int i = 0; i < array->Quantidade; i++)
    {
        S_Comentario* Comentario = &array->Comentarios[i];
        if(Verifica_Autoria(Comentario, id_usuario) == true)
        {
            Imprime_Comentario(Comentario, usuarios);
            TemComentarios = true;
        }
    }
    
    if (TemComentarios == false)
    {
        printf(">>>> Nenhum Comentario Foi Feito Por Este Usuario <<<<\n");
        return false;
    }
    return true;
}