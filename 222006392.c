#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CPF 16
#define MAX_NOME 1001
#define MAX_DATA 11

void valid_uf();
void menu_de_opcoes();
void cadastro_cpf();
void limpar_buffer();
void consulta();
void listagem_cidade();
void cadastro_nome();
void cadastro_sexo();
int cadastro_dia();
int cadastro_mes();
int cadastro_ano();
int validacao_cpf();
void validacao_uf();
char validacao_uf_para_listar();

int main() {
  int numero_menu,num_dia,num_mes,digito;
  while(1){
    menu_de_opcoes();
    scanf("%d", &numero_menu);
   if (numero_menu == 1) { // O QUE ESTA FORA DE COMENTARIO AINDA N FUNCIONA.
       /*validacao_cpf();
       cadastro_nome();
       cadastro_sexo();
       do{
       num_dia = cadastro_dia();
       num_mes = cadastro_mes();
       digito = cadastro_ano(num_dia,num_mes);
       }while(digito != 1);*/
        valid_uf();
    } else if (numero_menu == 2) {
      consulta();
    } else if (numero_menu == 3) {
      listagem_cidade();
    } else if (numero_menu != 6){
      printf("Programa em construcao por favor va com calma\n");
      exit(0);
    }
  }
  printf("Programa encerrado.\n");

  return 0;
}

void menu_de_opcoes() {

  printf("1) Cadastrar Pessoa\n");
  printf("2) Consultar Pessoa\n");
  printf("3) Listar pessoas por Cidade\n");
  printf("4) Gerar relatorio\n");
  printf("5) Excluir Pessoa\n");
  printf("6) Encerrar Programa\n");
  printf("Resposta : ");
}

void limpar_buffer() {
  char chare;
  while ((chare = getchar()) != '\n' && chare != EOF)
    ;
}

void consulta() {
  char cepefi[MAX_CPF], cpf_arq[MAX_CPF],nome_arq[MAX_NOME],data_arq[MAX_DATA],cidade_arq[50],uf_arq[3],sexo_arq[20];
  FILE *arq;
  int x=0;
  arq = fopen("INFO.txt", "r");
  if (arq == NULL) {
    printf("Erro no arquivo, por favor tente novamente\n");
  }else{
    x=0;
    do{
    printf("Insira o CPF para consulta da pessoa:\n");
    scanf("%s", cepefi); // leitura do cpf
    //printf("%s\n",cepefi);
    while(feof(arq)==0){
      fscanf(arq,"%[^,],",cpf_arq);
      //printf("%s",cpf_arq);
      fscanf(arq,"%[^,],",nome_arq);
      // printf("%s",nome_arq);
      fscanf(arq,"%[^,],",sexo_arq);
      //printf("%s",sexo_arq);
      fscanf(arq,"%[^,],",data_arq);
      //printf("%s",data_arq);
      fscanf(arq,"%[^,],",uf_arq);
      //printf("%s",cidade_arq);
      fscanf(arq,"%[^,],",cidade_arq);
      //printf("%s",uf_arq);
      //printf("CPF: %s", cpf_arq); // mostrar o cpf e o resto dos dados da pessoa
    //printf("NOME: %s", nome_arq);
        if(strcmp(cepefi, cpf_arq) == 0){      // ve se o cpf esta presente no arquivo
          printf("CPF: %s\n", cepefi); // mostrar o cpf e o resto dos dados da pessoa
          printf("NOME: %s\n", nome_arq);
          printf("SEXO: %s\n",sexo_arq);
          printf("DATA DE NASCIMENTO: %s\n",data_arq );
          printf("UNIDADE FEDERAL: %s\n",uf_arq);
          printf("CIDADE: %s\n",cidade_arq);
          printf("\n");
          x = 1;
        }
      }
     fclose(arq); // fechar arquivo
       if(x == 0){
         printf("CPF nao cadastrado ou invalido, por favor tente novamente\n");
          }
    }while(x!=1);
  }
}

typedef struct{
    char nome[100];
    char cpf[MAX_CPF];
    char sexo[20];
    char data[13];
    char uf[4];
    char cidade_arq[40];
}PESSOA;

void listagem_cidade() { // lista todos os nomes da cidade por ordem crescente de nome
  FILE *arq;
  PESSOA p;
  int i=-1;
  char nome_cidade[40];
  arq = fopen("INFO.txt", "r");
  if (arq == NULL) {
    printf("Erro no arquivo, por favor tente novamente\n");
    return;
  }

  //le o nome da cidade que sera procurada no arquivo
    printf("Insira o nome da cidade que deseja ver os habitantes\n");
    scanf("%s",nome_cidade);
    do{
      //leitura dos dados de dentro do arquivo,e armazenadas
        fscanf(arq," %[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",p.cpf,p.nome,p.sexo,p.data,p.uf,p.cidade_arq);

        if(strcmp(p.cidade_arq,nome_cidade)==0){

        }
      }while(!feof(arq));
}

void cadastro_nome() {
  FILE *arq;
  char nome[MAX_NOME];
  int result, x;
  arq = fopen("INFO.txt", "at");
  if (arq == NULL) {
    printf("Erro no arquivo, por favor tente novamente\n");
  }else{
  // limpar_buffer();
  printf("Digite o nome que deverá ser cadastrado\n");
  scanf(" %[^\n]", nome);
  if (strlen(nome) != 0) {
    result = fputs(nome, arq);
    fprintf(arq, ",");
    printf("Nome cadastrado\n");
    if (result == EOF) {
      printf("Erro na gravacao\n");
    }
  } else {
    printf("Nome vazio, tente novamente\n");
  }
  fclose(arq);
}
}

void cadastro_sexo() {
  FILE *arq;
  int resposta;
  int result;
  int x;
  arq = fopen("INFO.txt", "at");
  if (arq == NULL) {
    printf("Erro no arquivo, por favor tente novamente\n");
  }else{
  do {
    printf("Digite o numero que corresponde ao sexo\n");
    printf("1-Masculino\n");
    printf("2-Feminino\n");
    scanf("%d", &resposta);
    if (resposta == 1) {
      fprintf(arq, "Masculino");
      fprintf(arq, ",");
      printf("Sexo cadastrado\n");
      x = 1;
      fclose(arq);
    } else if (resposta == 2) {
      fprintf(arq, "Feminino");
      fprintf(arq, ",");
      printf("Sexo cadastrado\n");
      x = 1;
      fclose(arq);
    } else {
      printf("Sexo invalido, tente novamente\n");
      x = 0;
    }
  } while (x != 1);
}
}


int cadastro_dia() {
  int dia, x;

  do {
    printf("Insira o DIA da sua data de nascimento\n");
    scanf("%d", &dia);
    if (dia > 0 && dia < 32) {
      x = 1;
      printf("Dia cadastrado\n");
    } else {
      printf("Dia invalido, por favor insira novamente\n");
      x = 0;
    }
  } while (x != 1);
  return dia;
}

int cadastro_mes() {
  int mes, x;

  do {
    printf("Por favor insira o MES de sua data de nascimento\n");
    scanf("%d", &mes);
    if (mes > 0 && mes < 13) {
      printf("Mes cadastrado\n");
      x = 1;
    } else {
      printf("Mes invalido\n");
      x = 0;
    }
  } while (x != 1);
  return mes;
}

int cadastro_ano(int num_dia, int num_mes) {
  FILE *arq;
  int ano, x;
  arq = fopen("INFO.txt", "at");
  if (arq == NULL) {
    printf("Erro no arquivo, por favor tente novamente\n");
  }else{
  printf("Por favor insira o ANO de sua data de nascimento\n");
  scanf("%d", &ano);
  if (num_mes > 0 && num_mes < 13 && num_dia > 0 && num_dia < 32 &&
      ano > 1903 && ano < 2024) {
    if ((num_mes == 1 || num_mes == 3 || num_mes == 5 || num_mes == 7 ||
         num_mes == 8 || num_mes == 10 || num_mes == 12) &&
        (num_dia > 0 && num_dia < 32)) {
      x = 1;
      fprintf(arq, "%d", num_dia);
      fprintf(arq, "/");
      fprintf(arq, "%d", num_mes);
      fprintf(arq, "/");
      fprintf(arq, "%d", ano);
      fprintf(arq,",");
      printf("Data cadastrada\n");
      fclose(arq);
    } else if ((num_mes == 4 || num_mes == 6 || num_mes == 9 ||
                num_mes == 11) &&
               (num_dia < 31 && num_dia > 0)) {
      x = 1;
      fprintf(arq, "%d", num_dia);
      fprintf(arq, "/");
      fprintf(arq, "%d", num_mes);
      fprintf(arq, "/");
      fprintf(arq, "%d", ano);
      fprintf(arq,",");
      printf("Data cadastrada\n");
      fclose(arq);
    } else if ((num_mes == 2 && num_dia < 29 && num_dia > 0)) {
      x = 1;
      fprintf(arq, "%d", num_dia);
      fprintf(arq, "/");
      fprintf(arq, "%d", num_mes);
      fprintf(arq, "/");
      fprintf(arq, "%d", ano);
      fprintf(arq,",");
      printf("Data cadastrada\n");
      fclose(arq);
    } else if ((num_mes == 2 && ano % 4 == 0 && num_dia < 30 && num_dia > 0)) {
      x = 1;
      fprintf(arq, "%d", num_dia);
      fprintf(arq, "/");
      fprintf(arq, "%d", num_mes);
      fprintf(arq, "/");
      fprintf(arq, "%d", ano);
      fprintf(arq,",");
      printf("Data cadastrada\n");
      fclose(arq);
    } else {
      printf("Data invalida, por favor tente novamente");
      x = 2;
      fclose(arq);
    }
  }
  if (x == 1) {
    return 1;
  } else {
    printf("Você digitou algum dado incorreto, por favor faça a operacao "
           "novamente\n");
    return 0;
  }
}
}

void valid_uf()
{
    FILE *arq = fopen("UF.csv", "r");
    FILE *arq2 = fopen("INFO.txt", "a");
    PESSOA P;
    int confirma=0;
    char nome_cidade[100], uf[3];
    char cidade_input[100], uf_input[3];
    do
    {
    printf("Digite a UF:\n");
    scanf(" %[^\n]", uf_input);

    printf("Digite a cidade:\n ");
    scanf(" %[^\n]", cidade_input);

    while(fscanf(arq, " %*[^;];%[^;];%*[^;];%[^\n]", uf, nome_cidade) == 2){
        if(strncmp(uf, uf_input, 2) == 0 && strcmp(nome_cidade, cidade_input) == 0){
            confirma++;
            break;
        }
    }
    fclose(arq);
    if(confirma == 0)
    {
        //cidade nao encontrada
        printf("Cidade nao encontrada, por favor tente novamente no formato do exemplo.\n");
    }
    else{
        printf("Cidade Encontrada\n");
        // cidade encontrada
        fprintf(arq2, "%s,%s\n", uf_input, cidade_input);
    }
    }while(confirma == 0);

    fclose(arq2);
}


int validacao_cpf() {
    FILE *arq;
  char cpf[16],cpf_arq[MAX_CPF],nome[MAX_NOME],sexo[20],data[11],uf[5],cidade[40];
  int x, i,y, num[11], soma, soma_2, verf_1, verf_2, verificador_1, verificador_2,
      num_final[11];
  soma = 0;
        do {
        printf("Digite o CPF:\n");
        printf("EXEMPLO: 444.444.444-44\n");
        printf("Digite apenas os numeros\n");
        scanf(" %s", cpf);

        if (strlen(cpf) != 11 || strcmp(cpf, "00000000000") == 0 ||
        strcmp(cpf, "11111111111") == 0 || strcmp(cpf, "22222222222") == 0 ||
        strcmp(cpf, "33333333333") == 0 || strcmp(cpf, "44444444444") == 0 ||
        strcmp(cpf, "55555555555") == 0 || strcmp(cpf, "66666666666") == 0 ||
        strcmp(cpf, "77777777777") == 0 || strcmp(cpf, "88888888888") == 0 ||
        strcmp(cpf, "99999999999") == 0) {
        printf("Cpf invalido, por favor tente novamente\n");
        x = 0;
        } else {
            for (i = 0; i < 11; i++) {
            num[i] = cpf[i];
            num_final[i] = num[i] - 48;
            }
        soma = (num_final[0] * 1) + (num_final[1] * 2) + (num_final[2] * 3) +
             (num_final[3] * 4) + (num_final[4] * 5) + (num_final[5] * 6) +
             (num_final[6] * 7) + (num_final[7] * 8) + (num_final[8] * 9);
        verf_1 = soma % 11;
        if (verf_1 == 10) {
        verificador_1 = 0;
        } else {
        verificador_1 = verf_1;
        }
        soma_2 = (num_final[0] * 0) + (num_final[1] * 1) + (num_final[2] * 2) +
               (num_final[3] * 3) + (num_final[4] * 4) + (num_final[5] * 5) +
               (num_final[6] * 6) + (num_final[7] * 7) + (num_final[8] * 8) +
               (verificador_1 * 9);
        verf_2 = soma_2 % 11;
        if (verf_2 == 10) {
        verificador_2 = 0;
        } else {
        verificador_2 = verf_2;
        }
        if (num_final[10] == verificador_2 && num_final[9] == verificador_1) {
        x = 1;
        } else {
          printf("CPF Invalido, tente novamente\n");
        x = 0;
        }
        }
        } while (x != 1);
            arq = fopen("INFO.txt","r");
            if(arq == NULL){
            return;
            }

        while(!feof(arq)){
            fscanf(arq,"%[^,],",cpf_arq);
            //printf("%s",cpf_arq);
            fscanf(arq,"%[^,],",nome);
            // printf("%s",nome_arq);
            fscanf(arq,"%[^,],",sexo);
            //printf("%s",sexo_arq);
            fscanf(arq,"%[^,],",data);
            //printf("%s",data_arq);
            fscanf(arq,"%[^,],",uf);
            //printf("%s",cidade_arq);
            fscanf(arq,"%[^\n],",cidade);
            if(strcmp(cpf_arq, cpf)== 0){
                //printf("%s\n",cpf);
                //printf("%s\n",cpf_arq);
                printf("CPF ja cadastrado, por favor tente novamente\n");
                return;
            }else{
                cadastro_cpf(cpf);
            }
        }


  return 0;
}




void cadastro_cpf(char cpf[]) {
  FILE *arq;
  int a;

  arq = fopen("INFO.txt", "at");
  if (arq == NULL) {
    printf("Erro no arquivo, por favor tente novamente\n");
  }else{
    // limpar_buffer();

    fprintf(arq,"%s",cpf);
    fprintf(arq, ",");
    printf("Numero de CPF cadastrado\n");

  }  fclose(arq);
}


char validacao_uf_para_listar() { // verificar se a UF é válida
  FILE *arq;
  int mes, confere_cidade = 0;
  char uf_arquivo[3],codigo_arquivo[8],nome_arquivo[40],nome_arquivo_s[40],uf[5],nome_cidade[40];
  arq = fopen("UF.csv", "r ");
  if (arq == NULL) {
    printf("Erro no arquivo, por favor tente novamente\n");
  }else{
  do{
    printf("Insira a UF da cidade\n");
    printf("Exemplo: DF\n");
    scanf("%s",uf);
    printf("Insira a sua CIDADE\n ");
    printf("Exemplo: Brasília\n");
    scanf("%s", nome_cidade);

    //printf("%s %s\n",uf,nome_cidade);

    // Removendo o caracter \n do final da string

    nome_cidade[strlen(nome_cidade)] = '\0'; //colocando o \0 por preucação
    uf[strlen(uf)] = '\0'; //colocando o \0 por preucação
    do{
      // Scan dos valores da UF e Cidade
      char temp[80]; // Armazenar temporariamente Nome_arquivo e  Nome_arquivo_s
      fscanf(arq,"%s",codigo_arquivo);
      fscanf(arq,"%s",uf_arquivo);
      fgets(temp, 80, arq);

      // Tratamento das strings
      // Flag de fim do nome
      int end = -1;
      for(int i=0; i<strlen(temp); i++){
        if (temp[i] == '\t' && end < 1){
          end = i;
        }
      }

      //Alocar o nome para a variavel nome_arquivo
      strncpy(nome_arquivo, temp+1, end); //Copiando para nome_arquivo o que esta na variavel temp deslocando por 1 posição(espaço em branco) até a posição end

      //Alocar o nome sem acento para a variavel nome_arquivo_s
      strncpy(nome_arquivo_s, temp+end+1, end*2); //Copiando a segunda metade da variavel temp a partir de end+1 até o dobro de end (fim do segundo nome)

      //Fechando as strings com \0
      nome_arquivo_s[end-1] = '\0';
      nome_arquivo[end-1] = '\0';



      if(strcmp(uf, uf_arquivo) == 0 && (strcmp(nome_arquivo_s, nome_cidade) == 0 || strcmp(nome_arquivo, nome_cidade) == 0)){
        //printf("UF E CIDADE CADASTRADAS\n");
        confere_cidade = 1;

      }
    }while(!feof(arq));
    fclose(arq);

    if(confere_cidade == 0){
    //printf("UF OU CIDADE INVALIDAS, POR FAVOR TENTE NOVAMENTE\n");

    }
  }while(confere_cidade != 1);
}
  return confere_cidade;
}

