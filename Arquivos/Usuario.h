#ifndef USUARIO_H
#define USUARIO_H

#include "Misc.h"

typedef struct
{
    unsigned int Id;
    char Nome[NOME_TAM];
    char Email[NOME_TAM];
    char Senha[SENHA_TAM];
    char Bio[NOME_TAM];

    S_ArrayId PostagensCurtidas;
    S_ArrayId PostagensComentadas;
} S_Usuario;

typedef struct
{
    unsigned int Quantidade;
    S_Usuario* Usuarios;
} S_ArrayUsuarios;

void Alocar_Usuario(S_ArrayUsuarios* array);
void Liberar_Usuarios(S_ArrayUsuarios* array);
void Liberar_Usuarios_Profundo(S_ArrayUsuarios* array);
void Adicionar_Usuario_NoArray(S_ArrayUsuarios* array, const S_Usuario* novo_usuario);

S_Usuario* Logar_Usuario(const S_ArrayUsuarios* array);
S_Usuario* Achar_Usuario_PorEmail(const S_ArrayUsuarios* array, char* email);
S_Usuario* Achar_Usuario_PorId(const S_ArrayUsuarios* array, unsigned int id);
void Deslogar_Usuario(S_Usuario** usuario);

void Alterar_Senha_Usuario(S_Usuario* usuario);
void Alterar_Nome_Usuario(S_Usuario* usuario);
void Alterar_Email_Usuario(S_Usuario* usuario);
void Alterar_Bio_Usuario(S_Usuario* usuario);

void Cadastrar_NovoUsuario(S_ArrayUsuarios* array);
bool Verifica_Email_Existe(const S_ArrayUsuarios* array, const char* email);
bool Verifica_Email_Valido(const char* email);
void Mostrar_Usuario(const S_Usuario* usuario);
void Mostrar_Usuario_EmTabela(const S_Usuario* usuario);
void Mostrar_Usuarios(const S_ArrayUsuarios* array);

int Checar_Usuario_CurtiuPost(const S_Usuario* usuario, unsigned int post_id);
int Checar_Usuario_Comentou(const S_Usuario* usuario, unsigned int post_id);

S_ArrayUsuarios Buscar_Usuarios_PorEmail(const S_ArrayUsuarios* array, char* email);
S_ArrayUsuarios Buscar_Usuarios_PorNome(const S_ArrayUsuarios* array, char* nome);
void Ordenar_Usuarios(S_ArrayUsuarios* array, E_OrdenarPor tipo_ordenacao);

void SalvarArquivo_Usuarios(const S_ArrayUsuarios* array, char* caminho_arquivo);
void CarregarArquivo_Usuarios(S_ArrayUsuarios* array, char* caminho_arquivo);
#endif
