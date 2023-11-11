#ifndef INTERFACE_H
#define INTERFACE_H

#include "Misc.h"
#include "Usuario.h"
#include "Postagem.h"
#include "Comentario.h"

int Mostrar_Tela_Inicio();
void Mostrar_Usuarios_EmMenu();
void Mostrar_Configs_Usuario();
void Mostrar_Postagem(S_Postagem* postagem);
void Mostrar_Postagens_EmMenu(S_ArrayPostagens* array);
void Mostrar_Comentarios_EmMenu(unsigned int id);
void Mostrar_Comentarios_EmPost(S_Postagem* postagem);
void Mostrar_Tela_Principal();
void Mostrar_Tela_UsuarioAtivo();
void Mostrar_Tela_Postagem(S_Postagem* postagem);
void Mostrar_Postagens_Curtidas();

#endif