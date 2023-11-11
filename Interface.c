#include "Interface.h"

S_ArrayUsuarios Usuarios = {0, NULL};
S_ArrayPostagens Postagens = {0, NULL};
S_Usuario* Usuario_Logado = NULL;
S_Usuario* Usuario_Ativo = NULL;

void Mostrar_Postagens_Curtidas()
{
    S_ArrayPostagens Curtidas = {0, NULL};
    for(int i = 0; i < Usuario_Ativo->PostagensCurtidas.Quantidade; i++)
        Adicionar_Postagem_NoArray(&Curtidas, Achar_Postagem_PorId(&Postagens, Usuario_Ativo->PostagensCurtidas.Id[i]));

    Mostrar_Postagens_EmMenu(&Curtidas);
    Liberar_Postagens(&Curtidas);
    return;
}

int Mostrar_Tela_Inicio()
{
    int Escolha = 0;
    
    do
    {
        printf("[1] Logar\n");
        printf("[2] Cadastrar\n");
        printf("[3] Listar Usuarios\n");
        printf("[0] Sair\n");
        
        printf(">> ");
        scanf("%d", &Escolha);
        getchar();
        
        switch (Escolha)
        {
        case 0:
            return 1;
        case 1:
            Usuario_Ativo = Usuario_Logado = Logar_Usuario(&Usuarios);
            if(Usuario_Logado != NULL)
                Mostrar_Tela_Principal();
            break;
        case 2:
            Cadastrar_NovoUsuario(&Usuarios);
            break;
        case 3:
            printf("[1] Por Nome\n");
            printf("[2] Por Email\n");
            printf("[0] Por Id\n");
            
            scanf("%d", &Escolha);
            getchar();
            
            Ordenar_Usuarios(&Usuarios, (E_OrdenarPor) Escolha);
            Mostrar_Usuarios(&Usuarios);
            break;
        }
    } while(1);
}
void Mostrar_Comentarios_EmPost(S_Postagem* postagem)
{
    int Escolha = 0;
    unsigned int Id = 0;
    printf("[1] Todos\n");
    printf("[2] Seus\n");
    printf("[3] Autor\n");
    if(Usuario_Ativo->Id != Usuario_Logado->Id)
    {
        printf("[4] Usuario Ativo <%s #%06u>\n",
                Usuario_Ativo->Nome,
                Usuario_Ativo->Id);
    }
    printf("[5] Usuario Especifico\n");
    printf("[0] Cancelar\n");
    
    printf(">> ");
    scanf("%d", &Escolha);
    getchar();

    switch (Escolha)
    {
    case 0:
        break;
    case 1:
        Imprime_Comentarios(&postagem->Comentarios, &Usuarios);
        break;
    case 2:
        Imprime_Comentarios_DoUsuario(&postagem->Comentarios, &Usuarios, Usuario_Logado->Id);
        break;
    case 3:
        Imprime_Comentarios_DoUsuario(&postagem->Comentarios, &Usuarios, postagem->Autor_Id);
        break;
    case 4:
        Imprime_Comentarios_DoUsuario(&postagem->Comentarios, &Usuarios, Usuario_Ativo->Id);
        break;
    case 5:
        printf("Id do usuario: ");
        scanf("%u", &Id);
        getchar();
        Imprime_Comentarios_DoUsuario(&postagem->Comentarios, &Usuarios, Id);
        break;
    }
}
void Mostrar_Tela_Postagem(S_Postagem* postagem)
{
    int Escolha = 0;
    do
    {
        printf("[1] Curtir\n");
        printf("[2] Descurtir\n");
        printf("[3] Ver Quem Curtiu\n");
        printf("------------------------\n");
        printf("[4] Comentar\n");
        printf("[5] Ver Comentarios\n");
        if(postagem->Autor_Id == Usuario_Logado->Id)
        {
            printf("[6] Editar Comentario\n");
            printf("[7] Apagar Comentario\n");
            printf("------------------------\n");
            printf("[8] Editar Postagem\n");
            printf("[9] Apagar Postagem\n");
        }
        printf("------------------------\n");
        printf("[0] Concluir\n");
        
        printf(">> ");
        scanf("%d", &Escolha);
        getchar();

        switch (Escolha)
        {
        case 0:
            return;
        case 1:
            Curtir_Postagem(&Usuarios, postagem, Usuario_Logado->Id);
            break;
        case 2:
            Descurtir_Postagem(&Usuarios, postagem, Usuario_Logado->Id);
            break;
        case 3:
            Mostrar_Curtidas(&Usuarios, postagem);
            break;
        case 4:
            Comentar(&Usuarios, postagem, Usuario_Logado->Id);
            break;
        case 5:
            Mostrar_Comentarios_EmPost(postagem);
            break;
        case 8:
            if(postagem->Autor_Id == Usuario_Logado->Id)
                Editar_Post(&Postagens, postagem);
            break;
        case 7:
            if(postagem->Autor_Id == Usuario_Logado->Id)
            {
                Imprime_Comentarios_DoUsuario(&postagem->Comentarios, &Usuarios, Usuario_Logado->Id);
                Descomentar(&Usuarios, postagem, Usuario_Logado->Id);
            }
            break;
        case 9:
            if(postagem->Autor_Id == Usuario_Logado->Id)
            {
                Apagar_Post(&Postagens, postagem->Id, &Usuarios);
                printf(">>> Postagem apagada! <<<\n");
            }
            return;
        case 6:
            if(postagem->Autor_Id == Usuario_Logado->Id)
            {
                Imprime_Comentarios_DoUsuario(&postagem->Comentarios, &Usuarios, Usuario_Logado->Id);
                Recomentar(postagem, Usuario_Logado->Id);
            }
            break;
        }
    } while (1);
}
void Mostrar_Postagem(S_Postagem* postagem)
{
    if(postagem == NULL)
    {
        printf(">> Postagem Nao Encontrado <<\n");
        return;
    }
    VerPostagem(postagem, &Usuarios);
    Mostrar_Tela_Postagem(postagem);
    return;
}
void Mostrar_Usuarios_EmMenu(S_ArrayUsuarios* array)
{
    int Escolha = 0, Indice_atual = 0;
    do
    {
        S_Usuario* Usuario_atual = &array->Usuarios[Indice_atual];
        printf("> Id #%06u \n", Usuario_atual->Id);
        printf("> Nome: %s \n", Usuario_atual->Nome);
        printf("> Email: %s \n", Usuario_atual->Email);
        printf("\"%s\"\n", Usuario_atual->Bio);

        printf("[1] Anterior\n");
        printf("[2] Proximo\n");
        printf("[3] Ver Mais\n");
        printf("[0] Cancelar\n");

        printf(">> ");
        scanf("%d", &Escolha);
        getchar();

        switch (Escolha)
        {
        case 1:
            Indice_atual = Indice_atual == 0 ? array->Quantidade - 1 : Indice_atual - 1;
            break;
        case 2:
            Indice_atual = Indice_atual == array->Quantidade - 1 ? 0 : Indice_atual + 1;
            break;
        case 3:
            if(Usuario_atual->Id == Usuario_Logado->Id)
                return;
            Usuario_Ativo = Usuario_atual;
            Mostrar_Tela_UsuarioAtivo();
            break;
        case 0:
            return;
        }
        
    } while (1);
}
void Mostrar_Postagens_EmMenu(S_ArrayPostagens* array)
{
    int Escolha = 0, Indice_atual = 0;
    if(array->Quantidade < 1)
    {
        printf(">>>> Este Perfil Nao Possui Nenhum postagem <<<<\n");
        return;
    }
    do
    {
        S_Postagem* Postagem_Atual = &array->Postagens[Indice_atual];
        S_Usuario* Postagem_Autor = Achar_Usuario_PorId(&Usuarios, Postagem_Atual->Autor_Id);
        printf("<><><><><><><><><><><><><><><><><><><><><><><><>\n");
        printf("> #%06u\n", Postagem_Atual->Id);
        printf("> Postada por %s #%06u\n", Postagem_Autor->Nome, Postagem_Autor->Id);
        printf("\"%.32s\"\n", Postagem_Atual->Descrit);
        printf("<><><><><><><><><><><><><><><><><><><><><><><><>\n");

        printf("[1] Anterior\n");
        printf("[2] Proxima\n");
        printf("[3] Ver Mais\n");
        printf("[0] Cancelar\n");

        printf(">> ");
        scanf("%d", &Escolha);
        getchar();

        switch (Escolha)
        {
        case 1:
            Indice_atual = Indice_atual == 0 ? array->Quantidade - 1 : Indice_atual - 1;
            break;
        case 2:
            Indice_atual = Indice_atual == array->Quantidade - 1 ? 0 : Indice_atual + 1;
            break;
        case 3:
            Mostrar_Postagem(Postagem_Atual);
            break;
        case 0:
            return;
        }
        
    } while (1);
}
void Mostrar_Configs_Usuario()
{
    int Escolha = 0;
    do
    {
        Mostrar_Usuario(Usuario_Logado);
        printf("[1] Alterar Nome\n");
        printf("[2] Alterar Email\n");
        printf("[3] Alterar Senha\n");
        printf("[4] Alterar Bio\n");
        printf("[0] Concluir\n");
        
        printf(">> ");
        scanf("%d", &Escolha);
        getchar();

        switch (Escolha)
        {
        case 0:
            return;
        case 1:
            Alterar_Nome_Usuario(Usuario_Logado);
            break;
        case 2:
            Alterar_Email_Usuario(Usuario_Logado);
            break;
        case 3:
            Alterar_Senha_Usuario(Usuario_Logado);
            break;
        case 4:
            Alterar_Bio_Usuario(Usuario_Logado);
            break;
        }
    } while (1);
}
void Mostrar_Tela_Principal()
{
    S_ArrayPostagens Posts_DoUsuario = {0, NULL};
    S_ArrayUsuarios Busca_Usuarios = {0, NULL};
    char Busca_Buffer[NOME_TAM];
    do
    {
        int Escolha = 0;
        Mostrar_Usuario(Usuario_Logado);
        printf("[1] Nova Postagem\n");
        printf("[2] Ver Postagem \n");
        printf("[3] Ver Postagens Deste Perfil \n");
        printf("[4] Ver Todas As Postagens\n");
        printf("[5] Ver Postagens Curtidas\n");
        printf("-------------------------------\n");
        printf("[6] Buscar Perfil\n");
        printf("[7] Ver Todos Os Perfis\n");
        printf("[8] Estatisticas Deste Perfil\n");
        printf("[9] Alterar Perfil\n");
        printf("-------------------------------\n");
        printf("[0] Deslogar\n");
        
        printf(">> ");
        scanf("%d", &Escolha);
        getchar();
        
        switch (Escolha)
        {
        case 0:
            Deslogar_Usuario(&Usuario_Ativo);
            Deslogar_Usuario(&Usuario_Logado);
            return;
        case 1:
            Postar(&Postagens, Usuario_Ativo->Id);
            do
            {
                Upload_Imagem(&Postagens.Postagens[Postagens.Quantidade-1].Imagens);
                printf(">> Adicionar outra imagem? <1 para sim, 0 para nao>: \n");
            
                scanf("%d", &Escolha);
                getchar();
            } while (Escolha != 0); 
            break;
        case 2:
            printf(">> ID da postagem: ");
            
            scanf("%d", &Escolha);
            getchar();
            
            Mostrar_Postagem(Achar_Postagem_PorId(&Postagens, Escolha));
            break;
        case 3:
            Posts_DoUsuario = Achar_Postagens_DoUsuario(&Postagens, Usuario_Logado->Id);
            Mostrar_Postagens_EmMenu(&Posts_DoUsuario);
            Liberar_Postagens(&Posts_DoUsuario);
            break;
        case 4:
            Mostrar_Postagens_EmMenu(&Postagens);
            break;
        case 5:
            Mostrar_Postagens_Curtidas();
            break;
        case 6:
            printf(">> Buscar por? <1 para nome, 2 para email, 0 cancelar>: ");
            
            scanf("%d", &Escolha);
            getchar();

            if(Escolha == 0) break;
            printf(">> Escreva parte do %s: ", Escolha == 1 ? "nome" : "email");
            fgets(Busca_Buffer, NOME_TAM, stdin);
            Resolve_Fgets(Busca_Buffer);

            Busca_Usuarios = Escolha == 1 ? Buscar_Usuarios_PorNome(&Usuarios, Busca_Buffer) : Buscar_Usuarios_PorEmail(&Usuarios, Busca_Buffer);
            if(Busca_Usuarios.Quantidade == 0)
            {
                printf(">>>> Usuario nao encontrado! <<<<\n");
            }
            else Mostrar_Usuarios_EmMenu(&Busca_Usuarios);
            Liberar_Usuarios(&Busca_Usuarios);
            break;
        case 7:
            printf("[1] Por Nome\n");
            printf("[2] Por Email\n");
            printf("[0] Por Id\n");
            
            scanf("%d", &Escolha);
            getchar();
            
            Ordenar_Usuarios(&Usuarios, (E_OrdenarPor) Escolha);
            Mostrar_Usuarios_EmMenu(&Usuarios);
            break;
        case 8:
            Mostrar_Usuario(Usuario_Logado);
            break;
        case 9:
            Mostrar_Configs_Usuario();
            break;
        }
    } while (1);
}
void Mostrar_Tela_UsuarioAtivo()
{
    S_ArrayPostagens Posts_DoUsuario = {0, NULL};
    do
    {
        int Escolha = 0;
        Mostrar_Usuario(Usuario_Ativo);
        printf("[1] Ver Postagens Deste Perfil \n");
        printf("[2] Ver Postagens Curtidas Por Este Perfil\n");
        printf("[3] Estatisticas Do Perfil\n");
        printf("[0] Voltar\n");
        
        printf(">> ");
        scanf("%d", &Escolha);
        getchar();
        
        switch (Escolha)
        {
        case 0:
            Usuario_Ativo = Usuario_Logado;
            return;
        case 1:
            Posts_DoUsuario = Achar_Postagens_DoUsuario(&Postagens, Usuario_Ativo->Id);
            Mostrar_Postagens_EmMenu(&Posts_DoUsuario);
            Liberar_Postagens(&Posts_DoUsuario);
            break;
        case 2:
            Mostrar_Postagens_Curtidas();
            return;
        case 3:
            Mostrar_Usuario(Usuario_Ativo);
            break;
        }
    } while (1);
}