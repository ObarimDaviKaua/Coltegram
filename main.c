#include "Modulos/Interface.h"

#if __unix__

#define CAMINHO_USUARIOS "Data/users.bin"
#define CAMINHO_POSTS "Data/posts.bin"

#else

#define CAMINHO_USUARIOS "Data\\users.bin"
#define CAMINHO_POSTS "Data\\posts.bin"

#endif

extern S_ArrayUsuarios Usuarios;
extern S_ArrayPostagens Postagens;
extern S_Usuario* Usuario_Logado;
extern S_Usuario* Usuario_Ativo;

int main(int argc, char** argv)
{
    int Resultado = 0;
    CarregarArquivo_Usuarios(&Usuarios, CAMINHO_USUARIOS);
    CarregarArquivo_Postagens(&Postagens, CAMINHO_POSTS);
    while (1)
    {
        Limpar_Tela();
        if(Mostrar_Tela_Inicio() == 1)
        {
            Deslogar_Usuario(&Usuario_Logado);
            SalvarArquivo_Postagens(&Postagens, CAMINHO_POSTS);
            SalvarArquivo_Usuarios(&Usuarios, CAMINHO_USUARIOS);
            Liberar_Usuarios_Profundo(&Usuarios);
            Liberar_Postagens_Profundo(&Postagens);
            break;
        }
    }
    
    return 0;
}