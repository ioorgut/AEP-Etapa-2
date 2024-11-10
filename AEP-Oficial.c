//AEP - Etapa 2
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
// Var Globais //===========================================
	char nome[21][100];
	char senha[21][50];
	char op;
	int totuser;
// Procedimentos e Fun�oes//=========================================
	void menu();
	void arquivo(int tp);
	void inserir();
	void alterar();
	void excluir();
	void listar();
	void creditos();
	void classifica();
	char* criptografia (char *pal);
	char* des_criptografia (char *pal);
//==========================================================
void menu(){
	do{
		system("cls");
		printf("\n");
		printf("M E N U\n");
		printf("\n");
		printf("1 - Inserir \n");
		printf("2 - Alterar \n");
		printf("3 - Excluir \n");
		printf("4 - Listar \n");
		printf("5 - Creditos\n");
		printf("6 - Fim \n");
		printf("  Opcao: ");

		scanf("%c", &op);
		switch (op){
			case '1':
				inserir();
				break;
			case '2':
				alterar();
				break;
			case '3':
				excluir();
				break;
			case '4':
				listar();
				break;
			case '5':
				creditos();
		}
	} while(op != '6');
}
//================================================
void inserir(){
	char senha2[21];
	int p;
	
	system("cls");
	printf("\n");
	printf("I N S E R I R\n");
	do{
		printf("Nome do Usuario: ");
		scanf("%s", nome[totuser]);
	} while(strlen(nome[totuser]) <= 3);
	
    p = buscaUsuario(nome[totuser]);		

	if(p >= 0){
		printf("Usuario ja cadastrado!\n");
	} else {
		do{
			printf("          Senha: ");
			scanf("%s", senha[totuser]);	
		} while (senhaValida(senha[totuser]) == false);
	
		do{
			printf(" Repita a Senha: ");
			scanf("%s", senha2);
		} while (strcmp(senha[totuser], senha2) != 0);
	
		printf("\n");
		printf(" Usuario Adicionado  \n");
		printf("Pressione ENTER para voltar o MENU ");
		totuser++;
		classifica();
		getch();
		}
	arquivo(1);
}
//================================================
void alterar(){
    char senha2[20], parada[20];;
    int p;
	char temp[50];

    do{
        system("cls");
        printf("A L T E R A R   S E N H A\n");
		printf("Nome do Usuario: ");
        scanf("%s", &temp);

        p=buscaUsuario(temp);
        if(p==-1){
            printf("Usuario nao encontrado!\n");
            getch();
        }
    } while((p == -1) && (strlen(nome[totuser]) <= 3));

    do{
        printf("Nova senha: ");
        scanf("%s", senha[p]);
    } while(senhaValida(senha[p]) != true);

    do{
        printf("Repita a Senha: ");
        scanf("%s", senha2);
    } while(senhaValida(senha2) != true && strcmp(senha[p], senha2) != 0);
    
	arquivo(1);
}
//================================================
void excluir(){
    int x, p;
    char parada;
	char temp[50];

    do{
    	system("cls");
        printf("E X C L U I R\n");
        printf("Nome do Usuario: \n");
        scanf("%s", &temp);
        p = buscaUsuario(temp);

        if(p==-1){
            printf("Usuario nao encontrado!\n");
            getch();
        }
		
    }while((p == -1) && (strlen(nome[totuser]) <= 3));

	
    printf("Confirma exclusao? (S/N):  ");
    scanf(" %c", &parada);
    
    if(toupper(parada) == 'S'){
        for(x=p; x<=totuser; x++){
        	
            strcpy(nome[x], nome[x+1]);
            strcpy(senha[x], senha[x+1]);
            
        }
    totuser--;
    }
    
    arquivo(1);
}
//================================================
void listar (int tp){
	int x;
	
	system("cls");
	printf("---------------------------------------------------------\n");
	printf(" Usuario                        Senha\n");
	printf("---------------------------------------------------------\n");
	for(x=0; x<totuser; x++){
		printf("%s                        %s\n ", nome[x], criptografia(senha[x]));
	}
	printf("---------------------------------------------------------\n");
	printf("\n");
	printf("Pressione ENTER para voltar o MENU ");
	getch();
}
//================================================
void classifica(){
	char temp[50];
	int x, y;
	
	for(x=0; x < totuser - 1; x++){
		for(y = x + 1; y < totuser; y++){
			if(strcmp(nome[y], nome[x]) == -1){
				strcpy(temp, nome[x]);
				strcpy(nome[x], nome[y]);
				strcpy(nome[y], temp);
				
				strcpy(temp, senha[x]);
				strcpy(senha[x], senha[y]);
				strcpy(senha[y], temp);
			}
		}
	}
}
//================================================
void creditos(){
	system("cls"); 
	
    const char *mensagem = 
        "Programa desenvolvido pelos alunos Gustavo Cardoso, Joao Pedro de Oliveira, Vitor Hugo da Costa \n"
        "Agradecimentos especiais a Gabriel Campos Feiten, Guilherme Tamioso Bueno do Prado e Alexandre Moreno \n "
        "como projeto da AEP de engenharia de software 2024/Unicesumar.\n"
        "Requisitos: CRUD (create/read/update/delete) de users\n"
        "com criptografia dos dados salvos em arquivo texto.\n"
        "Possui funcionalidades como procedimentos, funções, passagem de parâmetros por valor e por referência,\n" 
        "variáveis gobais e locais, criptografia, vetores, arquivo texto e classificação.\n";
    
//Exibe o texto--------------------------------------
    while (*mensagem) {
        printf("%c", *mensagem);
        fflush(stdout);
        Sleep(25); 
        mensagem++;
    }

    printf("\n\nPressione ENTER para retornar ao menu...");
    getch(); 

    system("cls");
}
//================================================
char* criptografia (char *pal){
	static char temp[256];
    int x,c;
    temp[0]='\0';
    for (x=0;x < strlen(pal);x++){
        c=(int)pal[x];
        temp[x]=(char)(c+x+37);
    }
    temp[x]='\0';

    return temp;
}
//================================================
char* des_criptografia (char *pal){
	static char temp[256];
    int x,c;
    temp[0]='\0';
    for (x=0;x < strlen(pal);x++){
        c=(int)pal[x];
        temp[x]=(char)(c-x-37);
    }
    temp[x]='\0';

    return temp;
}
//================================================
int buscaUsuario(char chave[50]){
	int x;
	
	for(x = 0; x < totuser; x++){
		if(strcmp(chave, nome[x]) == 0){
			return x;
		}
	}
	return -1;
} 
//================================================
int senhaValida(char s[]){
	bool v1 = false, v2 = false, v3 = false, v4 = false, v5 = false;
	int i, tam;
	
	tam = strlen(s);

	if(tam >= 8 && tam <= 20){
		v1 = true;
		for(i=0; i<tam; i++){
			if(isupper(s[i])){
				v2 = true;
			} else if(islower(s[i])) {
				v3 = true;
			} else if(isdigit(s[i])){
				v4 = true;
			} else {
				v5 = true;
			}
		}
	}
	if(v1 && v2 && v3 && v4 && v5 == true){
		return true;
	} else {
		return false;
	}
}
//================================================
void arquivo(int tp){ //0 - leitura / 1 - gravacao
  	char linha[30], temp[30]; 
  	int x;
  	FILE *file; 
    file = fopen("users.txt", "r");
    	if (file != NULL && tp == 0) {
        	totuser=0;
        	x=0;
        	while (fgets(linha, sizeof(linha), file) != NULL && strlen(linha)>0) { 
          		linha[strlen(linha)-1]='\0'; 
          		
            	if (x%2==0){
              		totuser++; 
              		strcpy(nome[totuser-1], des_criptografia(linha));
              	} 
				else
              		strcpy(senha[totuser-1], des_criptografia(linha));
              		x++;
        	}
    	} 
		else {
      		file = fopen("users.txt", "w"); 
        	for (x=0;x<totuser;x++){ 
          		strcpy(temp,nome[x]); 
          		fprintf(file, "%s\n", criptografia(temp)); 
          		strcpy(temp,senha[x]); 
          		fprintf(file, "%s\n", criptografia(temp)); 
        	} 
   		}
    fclose(file);
}
//================================================
int main(){
	SetConsoleOutputCP(CP_UTF8);
	arquivo(0);
	menu();
	arquivo(1);
}


