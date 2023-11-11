#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Usuario.h"
#include "Misc.h"

void Alocar_Usuario(S_ArrayUsuarios* array)
{
    (array->Quantidade)++;
    if(array->Quantidade == 1)
        array->Usuarios = (S_Usuario *) malloc(sizeof(S_Usuario));
    else
        array->Usuarios = (S_Usuario *) realloc(array->Usuarios, array->Quantidade * sizeof(S_Usuario));

    if(array->Usuarios == NULL)
        printf("ERRO: Alocagem de usuario");    
    return;
}
void Liberar_Usuarios(S_ArrayUsuarios* array)
{
    if(array->Usuarios != NULL)
        free(array->Usuarios);
    array->Usuarios = NULL;
    array->Quantidade = 0;
    return;
}
void Liberar_Usuarios_Profundo(S_ArrayUsuarios* array)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        Liberar_ArrayId(&array->Usuarios[i].PostagensComentadas);
        Liberar_ArrayId(&array->Usuarios[i].PostagensCurtidas);
    }
    if(array->Usuarios != NULL)
        free(array->Usuarios);
    array->Usuarios = NULL;
    array->Quantidade = 0;
    return;
}
void Adicionar_Usuario_NoArray(S_ArrayUsuarios* array, const S_Usuario* novo_usuario)
{
    Alocar_Usuario(array);
    array->Usuarios[array->Quantidade-1] = *novo_usuario;
}

S_Usuario* Logar_Usuario(const S_ArrayUsuarios* array)
{
    int Escolha = 0;
    char Email_Busca[NOME_TAM];
    char Senha_Busca[SENHA_TAM];
    S_Usuario* Encontrado;

    do
    {
        Encontrado = NULL;
        
        printf("[1] Logar com o ID\n");
        printf("[2] Logar com o Email\n");
        printf("[0] Cancelar\n");

        printf(">> ");
        scanf("%d", &Escolha);
        getchar();

        switch (Escolha)
        {
        case 0:
            return NULL;
        case 1:
            printf(">> Digite o ID: ");
            scanf("%d", &Escolha);
            getchar();
            Encontrado = Achar_Usuario_PorId(array, (unsigned int) Escolha);
            break;
        case 2:
            printf(">> Digite o email (Completo): ");
            fgets(Email_Busca, NOME_TAM, stdin);
            Resolve_Fgets(Email_Busca);
            Encontrado = Achar_Usuario_PorEmail(array, Email_Busca);
            break;
        default:
            continue;
        }

        printf(">> Digite a senha: ");
        fgets(Senha_Busca, SENHA_TAM, stdin);
        Resolve_Fgets(Senha_Busca);


        if(Encontrado == NULL)
        {
            printf("Email/ID invalido!\n");
            continue;
        }
        else if(strcmp(Encontrado->Senha, Senha_Busca) != 0)
        {
            printf("Senha invalida para esse usuario!!\n");
            continue;
        }
        else
        {
            printf("Logado como %s #%04u\n", Encontrado->Nome, Encontrado->Id);
            return Encontrado;
        }
    } while (1);
}
S_Usuario* Achar_Usuario_PorEmail(const S_ArrayUsuarios* array, char* email)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        if(strcmp(array->Usuarios[i].Email, email) == 0)
            return &array->Usuarios[i];
    }
    return NULL;
}
S_Usuario* Achar_Usuario_PorId(const S_ArrayUsuarios* array, unsigned int id)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        if(array->Usuarios[i].Id == id)
            return &array->Usuarios[i];
    }
    return NULL;
}
void Deslogar_Usuario(S_Usuario** usuario)
{
    *usuario = NULL;
}
void Alterar_Senha_Usuario(S_Usuario* usuario)
{
    char Senha_Antiga[SENHA_TAM];
    char Senha_Nova[SENHA_TAM];
    
    printf(">> Digite a senha atual: ");
    fgets(Senha_Antiga, SENHA_TAM, stdin);
    Resolve_Fgets(Senha_Antiga);

    if(strcmp(usuario->Senha, Senha_Antiga) != 0)
    {
        printf("A senha digitada esta incorreta!\n");
        return;
    }

    printf(">> Digite a nova senha: ");
    fgets(Senha_Nova, SENHA_TAM, stdin);
    Resolve_Fgets(Senha_Nova);

    strcpy(usuario->Senha, Senha_Nova);
    printf(">> Senha alterada com sucesso! <<\n");
    return;
}
void Alterar_Nome_Usuario(S_Usuario* usuario)
{
    printf(">> Digite o novo nome: ");
    fgets(usuario->Nome, NOME_TAM, stdin);
    Resolve_Fgets(usuario->Nome);

    printf(">> Nome alterado com sucesso! <<\n");
    return;
}
void Alterar_Email_Usuario(S_Usuario* usuario)
{
    char Senha_Confirma[SENHA_TAM];
    
    printf(">> Digite a senha atual: ");
    fgets(Senha_Confirma, SENHA_TAM, stdin);
    Resolve_Fgets(Senha_Confirma);

    if(strcmp(usuario->Senha, Senha_Confirma) != 0)
    {
        printf("A senha digitada esta incorreta!\n");
        return;
    }

    printf(">> Digite o novo email: ");
    fgets(usuario->Email, NOME_TAM, stdin);
    Resolve_Fgets(usuario->Email);

    printf(">> Email alterado com sucesso! <<\n");
    return;
}
void Alterar_Bio_Usuario(S_Usuario* usuario)
{
    printf(">> Escreva uma breve descricao sua: ");
    fgets(usuario->Bio, NOME_TAM, stdin);
    Resolve_Fgets(usuario->Bio);

    printf(">> Sua Bio foi atualizada com sucesso! <<\n");
    return;
}

int Checar_Usuario_CurtiuPost(const S_Usuario* usuario, unsigned int post_id)
{
    for(int i = 0; i < usuario->PostagensCurtidas.Quantidade; i++)
    {
        if(usuario->PostagensCurtidas.Id[i] == post_id)
            return i;
    }
    return -1;
}
int Checar_Usuario_Comentou(const S_Usuario* usuario, unsigned int post_id)
{
    for(int i = 0; i < usuario->PostagensComentadas.Quantidade; i++)
    {
        if(usuario->PostagensComentadas.Id[i] == post_id)
            return i;
    }
    return -1;
}
bool Verifica_Email_Existe(const S_ArrayUsuarios* array, const char* email)
{
    for(int i = 0; i < array->Quantidade - 1; i++)
    {
        if(strcmp(array->Usuarios[i].Email, email) == 0)
            return false;
    }
    return true;
}
bool Verifica_Email_Valido(const char* email)
{
    int Tamanho_Email = strlen(email);
    for(int i = 0; i < Tamanho_Email; i++)
    {
        if(email[i] != '@') continue;

        for(i; i < Tamanho_Email; i++)
        {
            if(email[i] != '.') continue;

            if(i < Tamanho_Email - 2 && email[i + 1] != ' ')
                return true;
        }
    }
    return false;
}
void Cadastrar_NovoUsuario(S_ArrayUsuarios* array)
{
    Alocar_Usuario(array);
    S_Usuario* UsuarioNovo = &(array->Usuarios[array->Quantidade - 1]);
    UsuarioNovo->Id = array->Quantidade;
    UsuarioNovo->PostagensCurtidas = (S_ArrayId) {0, NULL};
    UsuarioNovo->PostagensComentadas = (S_ArrayId) {0, NULL};

    printf(">> Digite o nome do usuario: ");
    fgets(UsuarioNovo->Nome, NOME_TAM, stdin);
    Resolve_Fgets(UsuarioNovo->Nome);

    do
    {
        printf(">> Digite o email do usuario: ");
        fgets(UsuarioNovo->Email, NOME_TAM, stdin);
        Resolve_Fgets(UsuarioNovo->Email);

        if(Verifica_Email_Valido(UsuarioNovo->Email) == false)
            printf(">>> Email fornecido e invalido! <<<\n");
        else if (Verifica_Email_Existe(array, UsuarioNovo->Email) == false)
            printf(">>> Este email ja esta em uso! <<<\n");
        else break;
    }
    while (1);
    

    printf(">> Digite a senha do usuario: ");
    fgets(UsuarioNovo->Senha, SENHA_TAM, stdin);
    Resolve_Fgets(UsuarioNovo->Senha);

    printf(">> Digite uma bio para o usuario: ");
    fgets(UsuarioNovo->Bio, NOME_TAM, stdin);
    Resolve_Fgets(UsuarioNovo->Bio);

    printf(">> Cadastro concluido <<\n");
}
void Mostrar_Usuario(const S_Usuario* usuario)
{
    printf(">>> Usuario #%06u <<<\n", usuario->Id);
    printf("> Nome: %s \n", usuario->Nome);
    printf("> Email: %s \n", usuario->Email);
    printf("> Bio: %s \n", usuario->Bio);
    printf("> Posts Curtidos: %u \n", usuario->PostagensCurtidas.Quantidade);
    printf("> Comentarios Feitos: %u \n", usuario->PostagensComentadas.Quantidade);
}
void Mostrar_Usuario_EmTabela(const S_Usuario* usuario)
{
    printf("| %06u | %-16.16s | %-37.37s | %-38.38s |\n",
        usuario->Id, usuario->Nome, usuario->Email, usuario->Bio);
}
void Mostrar_Usuarios(const S_ArrayUsuarios* array)
{
    if(array->Quantidade == 0)
    {
        printf(">>> Nenhum Usuario Encontrado! <<<\n");
        return;
    }
    
    printf("#--------#------------------#---------------------------------------#----------------------------------------#\n");
    printf("|   ID   |       Nome       |                 Email                 |                 Status                 |\n");
    printf("#========#==================#=======================================#========================================#\n");
    for(int i = 0; i < array->Quantidade; i++)
        Mostrar_Usuario_EmTabela(&(array->Usuarios[i]));
    printf("#--------#------------------#---------------------------------------#----------------------------------------#\n");
}

void SalvarArquivo_Usuarios(const S_ArrayUsuarios* array, char* caminho_arquivo)
{
    FILE* Arquivo = fopen(caminho_arquivo, "wb");
    if(Arquivo == NULL)
    {
        printf("ERRO: Abertura de arquivo");
        return;
    }
    
    fwrite(&(array->Quantidade), sizeof(unsigned int), 1, Arquivo);
    fwrite(array->Usuarios, sizeof(S_Usuario), array->Quantidade, Arquivo);
    for(int i = 0; i < array->Quantidade; i++)
    {
        fwrite(array->Usuarios[i].PostagensCurtidas.Id,
                sizeof(unsigned int),
                array->Usuarios[i].PostagensCurtidas.Quantidade,
                Arquivo);
        fwrite(array->Usuarios[i].PostagensComentadas.Id,
                sizeof(unsigned int),
                array->Usuarios[i].PostagensComentadas.Quantidade,
                Arquivo);
    }
    
    fclose(Arquivo);
    return;
}

void CarregarArquivo_Usuarios(S_ArrayUsuarios* array, char* caminho_arquivo)
{
    FILE* Arquivo = fopen(caminho_arquivo, "rb");

    if(Arquivo == NULL)
    {
        printf(">>> Arquivo de usuarios (users.bin) nao encontrado! <<\n");
        printf(">>> Um novo arquivo sera criado ao final do programa <<\n");
        return;
    }
    
    fread(&(array->Quantidade), sizeof(unsigned int), 1, Arquivo);
    array->Usuarios = (S_Usuario*) malloc(array->Quantidade * sizeof(S_Usuario));
    fread(array->Usuarios, sizeof(S_Usuario), array->Quantidade, Arquivo);
    for(int i = 0; i < array->Quantidade; i++)
    {
        S_Usuario* Usuario = &array->Usuarios[i];
        Usuario->PostagensCurtidas.Id = (unsigned int *) malloc(Usuario->PostagensCurtidas.Quantidade * sizeof(unsigned int));
        fread(Usuario->PostagensCurtidas.Id,
                sizeof(unsigned int),
                Usuario->PostagensCurtidas.Quantidade,
                Arquivo);
        if(Usuario->PostagensCurtidas.Quantidade == 0)
            Usuario->PostagensCurtidas.Id = NULL;
        
        Usuario->PostagensComentadas.Id = (unsigned int *) malloc(Usuario->PostagensComentadas.Quantidade * sizeof(unsigned int));
        fread(Usuario->PostagensComentadas.Id,
                sizeof(unsigned int),
                Usuario->PostagensComentadas.Quantidade,
                Arquivo);
        if(Usuario->PostagensComentadas.Quantidade == 0)
            Usuario->PostagensComentadas.Id = NULL;
    }
    
    fclose(Arquivo);
    return;
}

S_ArrayUsuarios Buscar_Usuarios_PorEmail(const S_ArrayUsuarios* array, char* email)
{
    S_ArrayUsuarios Usuarios_Encontrados = {0, NULL};
    for(int i = 0; i < array->Quantidade; i++)
    {
        if(AcharParte_NaFrase(array->Usuarios[i].Email, email))
            Adicionar_Usuario_NoArray(&Usuarios_Encontrados, &array->Usuarios[i]);
    }
    return Usuarios_Encontrados;
}
S_ArrayUsuarios Buscar_Usuarios_PorNome(const S_ArrayUsuarios* array, char* nome)
{
    S_ArrayUsuarios Usuarios_Encontrados = {0, NULL};
    for(int i = 0; i < array->Quantidade; i++)
    {
        if(AcharParte_NaFrase(array->Usuarios[i].Nome, nome))
            Adicionar_Usuario_NoArray(&Usuarios_Encontrados, &array->Usuarios[i]);
    }
    return Usuarios_Encontrados;
}

bool Encontra_Usuario_NaLista(const S_ArrayUsuarios* array, S_Usuario* usuario)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        if(array->Usuarios[i].Id == usuario->Id)
            return true;
    }
    return false;
}
void Ordenar_Usuarios(S_ArrayUsuarios* array, E_OrdenarPor tipo_ordenacao)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        S_Usuario Buffer;
        bool Resultado_Cheque;

        for(int j = i; j < array->Quantidade; j++)
        {
            switch (tipo_ordenacao)
            {
            case Ordena_Nome:
                Resultado_Cheque = Compara_Frases(array->Usuarios[j].Nome, array->Usuarios[i].Nome);
                break;
            case Ordena_Email:
                Resultado_Cheque = Compara_Frases(array->Usuarios[j].Email, array->Usuarios[i].Email);
                break;
            case Ordena_Id:
                Resultado_Cheque = array->Usuarios[j].Id < array->Usuarios[i].Id;
            }

            if(Resultado_Cheque == true)
            {
                Buffer = array->Usuarios[i];
                array->Usuarios[i] = array->Usuarios[j];
                array->Usuarios[j] = Buffer;
            }
        } 
    }
    return;
}