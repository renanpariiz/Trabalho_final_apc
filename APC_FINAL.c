#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


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
void relatorio_sexo();
void relatorio_idade();
int n_linhas();
void excluir_pessoa();
void cria_arq();
void confere();



//FUNÇÃO PRINCIPAL QUE RECEBE AS OUTRAS
int main() {
  int numero_menu,num_dia,num_mes,digito;
  cria_arq();
  while(1){
    menu_de_opcoes();
    scanf("%d", &numero_menu);
   if (numero_menu == 1) { // O QUE ESTA FORA DE COMENTARIO AINDA N FUNCIONA.
       validacao_cpf();
       cadastro_nome();
       cadastro_sexo();
       do{
       num_dia = cadastro_dia();
       num_mes = cadastro_mes();
       digito = cadastro_ano(num_dia,num_mes);
       }while(digito != 1);
        valid_uf();
    } else if (numero_menu == 2) {
      consulta();
    } else if (numero_menu == 3) {
      listagem_cidade();
    } else if (numero_menu == 4){
      relatorio_idade();
      relatorio_sexo();
    }else if (numero_menu == 5){
      excluir_pessoa();
    } else if (numero_menu == 6){
      exit(0);
    }else{
        printf("\nNumero invalido, por favor insira novamente.\n");
    }
  }
  printf("Programa encerrado.\n");

  return 0;
}
//FIM FUNÇÃO PRINCIPAL


//MENU DE INTERAÇÃO COM O USUARIO
void menu_de_opcoes() {

  printf("                          ---------------------------------------------------------------\n");
  printf("                                      Sistema de Gestao de Beneficio Social\n");
  printf("                          ---------------------------------------------------------------\n");
  printf("\n1) Cadastrar Pessoa\n");
  printf("2) Consultar Pessoa\n");
  printf("3) Listar pessoas por Cidade\n");
  printf("4) Gerar relatorio\n");
  printf("5) Excluir Pessoa\n");
  printf("6) Encerrar Programa\n");
  printf("\nResposta : ");
}
//FIM MENU DE INTERAÇÃO


//FUNÇÃO QUE LIMPA BUFFER
void limpar_buffer() {
  char chare;
  while ((chare = getchar()) != '\n' && chare != EOF)
    ;
}
// FIM FUNÇÃO QUE LIMPA BUFFER

//FUNÇÃO QUE CONSULTA OS USUARIOS A PARTIR DE SEU CPF
void consulta() {
  char cepefi[MAX_CPF], cpf_arq[MAX_CPF],nome_arq[MAX_NOME],data_arq[MAX_DATA],cidade_arq[50],uf_arq[3],sexo_arq[20];
  FILE *arq;
  int x=0;
  arq = fopen("INFOO.txt", "r");
  if (arq == NULL) {
    printf("Erro no arquivo, por favor tente novamente\n");
    return;
  }
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
              fscanf(arq,"%[^\n]\n",cidade_arq);
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

       if(x == 0){
         printf("CPF nao cadastrado ou invalido, por favor tente novamente\n");
          }
    }while(x!=1);
    fclose(arq); // fechar arquivo
}
// FIM FUNCAO CONSULTA


typedef struct{
    char nome[100];
    char cpf[MAX_CPF];
    char sexo[20];
    char data[13];
    char uf[4];
    char cidade_arq[40];
}PESSOA;



//FUNCAO QUE VALIDA E CADASTRA O NOME
void cadastro_nome() {
  FILE *arq;
  char nome[MAX_NOME];
  int result, x=0,i,a,b;
  int digitos,verificador=0;


            while(x<digitos || b>a){
                // limpar_buffer();

                printf("\nDigite o nome que devera ser cadastrado\n");
                scanf(" %[^\n]s", nome);

                digitos = strlen(nome);
                a = isalpha(nome);
                b = isspace(nome);
                    for(i=0;i<digitos;i++){
                        if(isalpha(nome[i]) != 0){
                            x++;
                        }else if(isspace(nome[i]) != 0){
                            x++;

                        }else{
                            x = 0;
                        }
                    }
                            if(x<digitos){
                                printf("\nNome invalido, o programa so aceita letras, por favor tente novamente.\n");

                            }





            }

                            if ( x >= digitos) {
                                arq = fopen("INFOO.txt", "a");
                                    if (arq == NULL) {
                                        printf("Erro no arquivo, por favor tente novamente\n");
                                        return;
                                    }
                                fprintf(arq,"%s",nome);
                                fprintf(arq, ",");
                                printf("\nNome cadastrado\n");
                                fclose(arq);


                            } else{
                                arq = fopen("INFOO.txt", "a");
                                            if (arq == NULL) {
                                                printf("\nErro no arquivo, por favor tente novamente\n");
                                                return;
                                            }
                                printf("\nVoce inseriu algum digito invalido, por favor tente novamente\n");
                                fclose(arq);

                            }

}
//FIM FUNCAO CADASTRO NOME

//FUNCAO QUE VALIDA E CADASTRA O SEXO
void cadastro_sexo() {
  FILE *arq;
  char resposta[1];
  int result;
  int x,a,verificador=0;


    printf("\nDigite o numero que corresponde ao sexo\n");
    printf("1-Masculino\n");
    printf("2-Feminino\n");
    printf("Resposta: ");

        while(verificador == 0)
        {

            scanf(" %[^\n]s", resposta);
                if(strcmp(resposta,"1")== 0){
                    arq = fopen("INFOO.txt","a");
                        if(arq== NULL){
                            printf("Erro.\n");
                        }
                    verificador++;

                    fprintf(arq, "Masculino");
                    fprintf(arq, ",");
                    printf("\nSexo cadastrado\n");
                    fclose(arq);
                    break;

                }else if(strcmp(resposta,"2")==0){

                    arq = fopen("INFOO.txt","a");
                        if(arq== NULL){
                            printf("Erro.\n");
                        }
                    verificador++;

                    fprintf(arq, "Feminino");
                    fprintf(arq, ",");
                    printf("\nSexo cadastrado\n");
                    fclose(arq);
                    break;
                }

                    if(verificador < 1){
                        printf("\nDigito invalido.\n");
                        printf("Digite apenas os digitos 1-> Masculino e 2-> Feminino.\n");
                    }


        }


}
//FIM FUNCAO CADASTRO SEXO

//FUNCAO QUE LE O DIA
int cadastro_dia() {
  int dia, x;

  do {
    printf("\nInsira o DIA da sua data de nascimento\n");
    scanf("%d", &dia);
    if (dia > 0 && dia < 32) {
      x = 1;
      printf("\nDia cadastrado\n");
    } else {
      printf("\nDia invalido, por favor insira novamente\n");
      x = 0;
    }
  } while (x != 1);
  return dia;
}
//FIM FUNCAO DIA

//FUNÇÃO QUE LE O MES
int cadastro_mes() {
  int mes, x;

  do {
    printf("\nPor favor insira o MES de sua data de nascimento\n");
    scanf("%d", &mes);
    if (mes > 0 && mes < 13) {
      printf("\nMes cadastrado\n");
      x = 1;
    } else {
      printf("\nMes invalido\n");
      x = 0;
    }
  } while (x != 1);
  return mes;
}
//FIM FUNÇAO MES

//FUNÇAO QUE VALIDA E CADASTRA A DATA
int cadastro_ano(int num_dia, int num_mes) {
  FILE *arq;
  int ano, x;
  arq = fopen("INFOO.txt", "a");
  if (arq == NULL) {
    printf("Erro no arquivo, por favor tente novamente\n");
  }
            printf("\nPor favor insira o ANO de sua data de nascimento\n");
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
                            printf("\nData cadastrada\n");
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
                                printf("\nData cadastrada\n");
                                fclose(arq);
                        } else if ((num_mes == 2 && num_dia < 29 && num_dia > 0)) {
                            x= 1;
                            fprintf(arq, "%d", num_dia);
                            fprintf(arq, "/");
                            fprintf(arq, "%d", num_mes);
                            fprintf(arq, "/");
                            fprintf(arq, "%d", ano);
                            fprintf(arq,",");
                            printf("\nData cadastrada\n");
                            fclose(arq);
                        } else if ((num_mes == 2 && ano % 4 == 0 && num_dia < 30 && num_dia > 0)) {
                            x = 1;
                            fprintf(arq, "%d", num_dia);
                            fprintf(arq, "/");
                            fprintf(arq, "%d", num_mes);
                            fprintf(arq, "/");
                            fprintf(arq, "%d", ano);
                            fprintf(arq,",");
                            printf("\nData cadastrada\n");
                            fclose(arq);
                        } else {
                            printf("\nData invalida, por favor tente novamente");
                            x = 2;
                            fclose(arq);
                        }
                }
                                if (x == 1) {
                                    return 1;
                                } else {
                                    printf("\nVocê digitou algum dado incorreto, por favor faça a operacao novamente\n");
                                    return 0;
                                }
    }




//INICIO VALIDA CPF
int validacao_cpf() {
    FILE *arq;

    PESSOA p;
  char cpf[16];
  int x, i,y, num[11], soma, soma_2, verf_1, verf_2, verificador_1, verificador_2,
      num_final[11];
  soma = 0;

        do {
            printf("\nDigite o CPF:\n");
            printf("EXEMPLO: 02225127895\n");
            printf("Digite apenas os numeros\n\n");
            scanf(" %s", cpf);

            if (strlen(cpf) != 11 || strcmp(cpf, "00000000000") == 0 ||
                strcmp(cpf, "11111111111") == 0 || strcmp(cpf, "22222222222") == 0 ||
                strcmp(cpf, "33333333333") == 0 || strcmp(cpf, "44444444444") == 0 ||
                strcmp(cpf, "55555555555") == 0 || strcmp(cpf, "66666666666") == 0 ||
                strcmp(cpf, "77777777777") == 0 || strcmp(cpf, "88888888888") == 0 ||
                strcmp(cpf, "99999999999") == 0) {
                printf("\nCpf invalido, por favor tente novamente\n");
                x = 0;
            } else {
                //INICIO DO VALIDADOR DE CPF
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
                                    printf("\nCPF Invalido, tente novamente\n");
                                    x = 0;
                                }
                                //FIM VALIDADOR
                }
            //INICIO VERIFICAÇÃO SE O CPF ESTA PRESENTE OU NAO
            arq = fopen("INFOO.txt","r");
                if(arq == NULL){
                    printf("\nErro no arquivo, por favor tente novamente\n");
                    return;
                }

                    do
                    {
                        //leitura dos dados de dentro do arquivo,e armazenadas
                        fscanf(arq," %[^,],",p.cpf);
                        fscanf(arq," %[^,],",p.nome);
                        fscanf(arq," %[^,],",p.sexo);
                        fscanf(arq," %[^,],",p.data);
                        fscanf(arq," %[^,],",p.uf);
                        fscanf(arq," %[^\n]\n",p.cidade_arq);
                if(strcmp(p.cpf,cpf)==0){
                    printf("\nCPF ja cadastrado, por favor tente novamente\n");
                    x = 0;
                }
                    }while(!feof(arq));
                    //FIM VERIFICAÇÃO DO CPF JA EXISTENTE
                        fclose(arq);
        } while (x != 1);
        //CHAMADA DA FUNCAO PRA ESCRITA DENTRO DO ARQUIVO
            cadastro_cpf(cpf);
  return 0;
}
//FIM DA PARTE DO CPF



//INICIO FUNCAO QUE APENAS ESCREVE DENTRO DO AQUIVO
void cadastro_cpf(char cpf[]) {
  FILE *arq;
  int a;

  arq = fopen("INFOO.txt", "at");
  if (arq == NULL) {
    printf("\nErro no arquivo, por favor tente novamente\n");
  }else{
    // limpar_buffer();

    fprintf(arq,"%s",cpf);
    fprintf(arq, ",");
    printf("\nNumero de CPF cadastrado\n");

  }  fclose(arq);
}
//FIM FUNÇÃO


//FUNCAO QUE INFORMA QUANTAS LINHAS O ARQUIVP TEM
int n_linhas(){
    FILE *arq;
    int cont=0;
    arq = fopen("INFOO.txt","r");

    while(fscanf(arq," %*[^\n]")!= EOF){
        cont++;

    }

    fclose(arq);
    return cont;
}
// FIM FUNÇÃO ARQUIVO LINHAS


//FUNÇÃO QUE LISTA A PORCENTAGEM DE PESSOAS DE AMBOS OS SEXOS
void relatorio_sexo(){
    FILE *arq;
    int num,i,cont,num_total;
    float por_femeas,por_homens,num_femeas=0,num_homens=0;
    char sexo[13],cpf[MAX_CPF],nome[MAX_NOME],data[MAX_DATA],uf[3],cidade[40];
    num_total = 0;
    arq = fopen("INFOO.txt","r");
    if(arq == NULL){
        printf("Erro na abertura de arquivo\n");
        return;
    }
     cont = n_linhas();

        for(i=0;i<cont;i++){
            while(!feof(arq)){
                fscanf(arq,"%[^,],",cpf);
                fscanf(arq,"%[^,],",nome);
                fscanf(arq,"%[^,],",sexo);
                fscanf(arq,"%[^,],",data);
                fscanf(arq,"%[^,],",uf);
                fscanf(arq,"%[^\n]\n",cidade);

                if(strcmp(sexo, "Masculino")== 0){
                    num_homens++;
                    num_total = num_total + 1;
                }else if(strcmp(sexo, "Feminino")== 0){
                    num_femeas++;
                    num_total = num_total + 1;
                }
            }
        }
        fclose(arq);


        por_femeas = (num_femeas/num_total) * 100;
        por_homens = (num_homens/num_total) * 100;


        printf("\nPOR SEXO: \n");
        printf("\nMasculino: %.2f %%\n",por_homens);
        printf("\nFeminino: %.2f %%\n" ,por_femeas);
    }
//FIM FUNCAO QUE LISTA A PORCENTAGEM DOS SEXOS

//FUNCAO QUE LISTA A PORCENTAGEM POR IDADE
    void relatorio_idade(){
    FILE *arq;
    int ano_maquina,mes_maquina,dia_maquina,dia,mes,ano,idade;
    float qtd_pessoas=0,menos_16,menos_30,menos_50,menos_60,mais_60;
    float per_16,per_30,per_50,per_60_less,per_60_plus;
    time_t data_atual = time(NULL);
    struct tm *tm = localtime(&data_atual);
    char sexo[13],cpf[MAX_CPF],nome[MAX_NOME],uf[3],cidade[40],data[MAX_DATA];

    arq = fopen("INFOO.txt","r");
        if(arq == NULL){
            printf("Erro na abertura do aquivo\n");
            return;
        }
            while(!feof(arq)){
                fscanf(arq,"%[^,],",cpf);
                    //printf("%s\n",cpf);
                fscanf(arq,"%[^,],",nome);
                    //printf("%s\n",nome);
                fscanf(arq,"%[^,],",sexo);
                    //printf("%s\n",sexo);
                fscanf(arq,"%[^,],",data);
                    //printf("%s",data);
                fscanf(arq,"%[^,],",uf);
                    //printf("%s\n",uf);
                fscanf(arq,"%[^\n]\n",cidade);
                    //printf("%s\n",cidade);

                sscanf(data,"%d/%d/%d", &dia,&mes,&ano);
                //printf("%d %d %d \n",dia, mes, ano);






                 ano_maquina = tm->tm_year + 1900;
                 //printf("%d\n",ano_maquina);

                 mes_maquina = tm->tm_mon + 1;
                 //printf("%d\n",mes_maquina);

                 dia_maquina = tm->tm_mday;
                 //printf("%d\n",dia_maquina);



                 idade = ano_maquina - ano;

                    if(mes > mes_maquina || mes == mes_maquina && dia > dia_maquina){

                        idade--;
                    }




                        if (idade > -1 && idade < 16){
                            menos_16++;
                             qtd_pessoas++;
                        }else if (idade > 15 && idade < 30){
                            menos_30++;
                             qtd_pessoas++;
                        }else if (idade > 29 && idade < 50){
                            menos_50++;
                             qtd_pessoas++;
                        }else if (idade > 49 && idade < 61){
                            menos_60++;
                             qtd_pessoas++;
                        }else if (idade > 60){
                            mais_60++;
                             qtd_pessoas++;
                        }


            }
                 fclose(arq);

                    per_16 = (menos_16/qtd_pessoas) *100 ;

                    per_30 = (menos_30/qtd_pessoas) *100 ;

                    per_50 = (menos_50/qtd_pessoas) *100 ;

                    per_60_less = (menos_60/qtd_pessoas) *100 ;

                    per_60_plus = (mais_60/qtd_pessoas) *100 ;



                     printf("\n-------------------------------------\n");
                     printf("      Total de Pessoas Beneficiadas : \n");
                     printf("-------------------------------------\n");


                    printf("\nPOR IDADE: \n");
                    printf("\n0 a 15 anos : %.2f %%\n",per_16);
                    printf("\n16 a 29 anos : %.2f %%\n",per_30);
                    printf("\n30 a 49 anos : %.2f %%\n",per_50);
                    printf("\n50 a 60 anos : %.2f %%\n",per_60_less);
                    printf("\nAcima de 60 anos : %.2f %%\n",per_60_plus);









    }
//FIM FUNCAO QUE LISTA A PORCENTAGEM POR IDADE







//FUNCAO QUE EXCLUI A PESSOA DO ARQUIVO PELO CPF
void excluir_pessoa(){
    FILE *arq;
    FILE *arq2;
    char sexo[13],cpf[MAX_CPF],nome[MAX_NOME],data[MAX_DATA],uf[3],cidade[40],cpf_cancelado[MAX_CPF];
    char nome_saida[MAX_NOME];
    int verificador=0;
    int resposta;

    arq = fopen("INFOO.txt","r");

            if(arq == NULL){
                printf("\nAinda nao ha nenhum CPF cadastrado, por favor cadastre pelo menos um para usar esse item.\n");
                printf("\nSe o erro persistir entre em contato com o suporte -> 4002-8922.\n");
                return;
            }
                printf("\nDigite o CPF da pessoa que deseja excluir.\n");
                printf("\nMODELO: 444.444.444-44\n");
                printf("\nDigite apenas os numeros\n");
                printf("\nResposta: ");
                scanf("%s",cpf_cancelado);
                    while(!feof(arq))
                    {
                        fscanf(arq,"%[^,],",cpf);
                        fscanf(arq,"%[^,],",nome);
                        fscanf(arq,"%[^,],",sexo);
                        fscanf(arq,"%[^,],",data);
                        fscanf(arq,"%[^,],",uf);
                        fscanf(arq,"%[^\n]\n",cidade);

                            if(strcmp(cpf,cpf_cancelado)==0){
                                verificador++;
                            }
                    }
                            fclose(arq);
                        //printf("%d",verificador);
        if(verificador==0){
            printf("\nCPF nao cadastrado, por favor tente cadastrar um antes de tentar remover uma pessoa.\n");
        }else{
                arq = fopen("INFOO.txt","r");
                    if(arq == NULL){
                        printf("Erro na abertura de arquivo\n");
                        return;
                    }

            while(!feof(arq))
            {
                fscanf(arq,"%[^,],",cpf);
                fscanf(arq,"%[^,],",nome);
                fscanf(arq,"%[^,],",sexo);
                fscanf(arq,"%[^,],",data);
                fscanf(arq,"%[^,],",uf);
                fscanf(arq,"%[^\n]\n",cidade);
                    /*if(strcmp(cpf,cpf_cancelado) == 0){
                        nome_saida = nome;
                    }*/

                    if(strcmp(cpf,cpf_cancelado)!= 0){
                        arq2 = fopen("ARQTEMP.txt","w");

                        fprintf(arq2,"%s",cpf);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",nome);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",sexo);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",data);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",uf);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",cidade);
                        fprintf(arq2,"\n");

                        fclose(arq2);
                    }
            }

            fclose(arq);

                printf("\nVOCE REALMENTE DESEJA EXCLUIR ESSE USUARIO?\n");
                //printf("%s",nome_saida);
                printf("\n1 - SIM\n");
                printf("2 - NAO\n");
                printf("\nRESPOSTA (Numero) : ");
                scanf("%d",&resposta);
                    if(resposta == 1){
                        remove("INFOO.txt");
                        rename("ARQTEMP.txt","INFOO.txt");
                        printf("\nIndividuo apagado com sucesso,ser quiser realizar outro servico selecione algum listado abaixo:\n");

                    }else{
                        remove("ARQTEMP.txt");
                        printf("\nOperacao encerrada, ser quiser realizar outro servico selecione algum listado abaixo:\n");
                    }
        }



}
//FIM FUNCAO QUE EXLCUI PESSOA DO ARQUIVO

//FUNCAO QUE VALIDA E CADASTRA A UF E A CIDADE
void valid_uf()
{
    FILE *arq;
    FILE *arq2;
    PESSOA P;
    int confirma=0,digitos,a,b,x,digitos_uf,i,tam_uf,tam_cidade,j;
    char cidade_input[40], uf_input[3];
    char uf[3], cidade[40],cidade_s[40],codigo[10];
    do
    {
        while(x != 1){
            printf("\nDigite a UF:\n");
            printf("Modelo: DF \n");
            scanf(" %[^\n]", uf_input);
            tam_uf = strlen(uf_input);
            for(j=0;j<=tam_uf+2;j++){
                uf[j] = toupper(uf[j]);
            }




                digitos_uf = strlen(uf_input);
                a = isalpha(uf_input);
                    for(i=0;i<digitos_uf;i++){
                        if(isalpha(uf_input[i]) != 0){
                            x = 1;
                        }else{
                            x = 0;

                        }
                    }

            printf("\nDigite a cidade:\n ");
            printf("Modelo: Brasilia\n");

            scanf(" %[^\n]", cidade_input);
            tam_cidade = strlen(cidade_input);
            for(j=0;j<1;j++){
                cidade_input[j] = toupper(cidade_input[j]);
            }



                digitos = strlen(cidade_input);
                b = isalpha(cidade_input);
                    for(i=0;i<digitos;i++){
                        if(isalpha(cidade_input[i]) != 0){
                            x = 1;
                        }else{
                            x = 0;
                        }
                    }
                if(x ==0){
                    printf("\nSo sao aceitas letras nesse campo, por favor tente novamente.\n");
                }

        }
        arq = fopen("UF.csv", "r");
        while(!feof(arq)){

                fscanf(arq,"%[^\t]\t",codigo);
                fscanf(arq,"%[^\t]\t",uf);
                fscanf(arq,"%[^\t]\t",cidade);
                fscanf(arq,"%[^\n]\n",cidade_s);


            if(strcmp(uf, uf_input) == 0 && strcmp(cidade, cidade_input) == 0 || strcmp(cidade_s,cidade_input) ==0){
                confirma++;
                break;
            }
        }
            fclose(arq);
                if(confirma == 0)
                {
                    //cidade nao encontrada
                    printf("\nCidade nao existe\n");
                    fclose(arq2);
                }

                else{
                    arq2 = fopen("INFOO.txt", "a");
                    printf("\nCidade Cadastrada\n");
                    // cidade encontrada
                    fprintf(arq2, "%s", uf_input);
                    fprintf(arq2,",");
                    fprintf(arq2,"%s",cidade_input);
                    fprintf(arq,"\n");
                    fclose(arq2);
                }
                    x = 0;

    }while(confirma == 0);


}
//FIM FUNCAO QUE VALIDA E CADASTRA UF E CIDADE


//FUNCAO QUE CRIA UM ARQUIVO NO COMECO DO ARQUIVO
void cria_arq(){
FILE *arq;

arq = fopen("INFOO.txt","a+");
//fprintf(arq,"04458425129,Renan Batista,Masculino,14/08/2003,DF,Brasilia");

fclose(arq);



}
//FIM FUNCAO QUE CRIA ARQUIVO INFOO TXT



//FUNCAO QUE LISTA TODOS OS NOMES DE UMA CIDADE EM ORDEM ALFABÉTICA
void listagem_cidade() { // lista todos os nomes da cidade por ordem crescente de nome
  FILE *arq;
  PESSOA p;
  char nome_cidade[40],uf[3],temp[MAX_NOME];
  int i=0,cont,j,k,min,verificador=0;
    arq = fopen("INFOO.txt","r");
        if(arq == NULL){
            printf("Erro na abertura de arquivo.\n");
            return;
        }

    cont = n_linhas();
    char array[cont][MAX_NOME];


    do{
            printf("\nInsira o nome da cidade que deseja ver os habitantes\n");
            printf("\Resposta: ");
            printf("No formato: Brasilia ou Brasília\n");
            scanf("%s",nome_cidade);
            printf("\nInsira a Unidade Federal da cidade desejada\n");
            printf("No Formato: DF.\n");
            scanf("%s",uf);



        do{
           //le o nome da cidade que sera procurada no arquivo
          //leitura dos dados de dentro do arquivo,e armazenadas
            fscanf(arq," %[^,],",p.cpf);
            fscanf(arq," %[^,],",p.nome);
            fscanf(arq," %[^,],",p.sexo);
            fscanf(arq," %[^,],",p.data);
            fscanf(arq," %[^,],",p.uf);
            fscanf(arq," %[^\n]\n",p.cidade_arq);
            /*printf("%s\n",p.cpf);
            printf("%s\n",p.nome);
            printf("%s\n",p.sexo);
            printf("%s\n",p.data);
            printf("%s\n",p.uf);
            printf("%s\n",p.cidade_arq);*/

                //armazena os nomes dentro de uma matriz
                if(strcmp(p.cidade_arq,nome_cidade)==0 && strcmp(p.uf,uf)== 0){
                   strcpy(array[i],p.nome);                 // Trava nessa linha, ele entra na condição mas nao aloca o p.nome para o arr
                    array[i][strlen(array[i]) + 1] = '\0';                 // \0 colocado para indicar o fim da string
                    i++;
                    verificador++;
                }

          }while(!feof(arq));


            if(verificador == 0){
                printf("\nDado invalido ou arquivo vazio, por favor insira os dados no formato espeficado ou cadastre alguem antes.\n ");
            }

    }while(verificador == 0);
        fclose(arq);


        //comeco da parte de ordenação i = vai ser o numero de nomes que a cidade possui
        //primeiro for para colocar o primeiro array

            for(j = 0;j< i - 1;j++){
                min = j;
                    for(k = j + 1; k < i; k++ ){   //segundo for que vai colocar o array seguinte
                        if(strcmp(array[k],array[min])<0){    //se a condição for verdadeira, a segunda string é maior
                            min = k;    // e o k vai ocupar a posição do min

                        }
                    }
                //verificação da variavel min, para nao copiar nomes iguais
                    if(min != j){
                    //copiando strings ja ordenadads
                        strcpy(temp,array[j]);
                         strcpy(array[j],array[min]);
                          strcpy(array[min],temp);
                    }

            }

        // nomes ordenados
            for(j = 0; j< i; j++){
                printf("%s\n",array[j]);
            }

}
//FIM FUNCAO QUE LISTA NOMES ALFABÉTICAS

//FUNCAO QUE CONFERE SE OS DADOS DO ARQUIVO SAO VÁLIDOS OU NAO  (APENAS UM CONCEITO AINDA NAO FOI FINALIZADA)
void confere(){
    FILE *arq;
    FILE *arq2;
    PESSOA p;
    int verificador = 0;


        arq = fopen("INFOO.txt","r");
            if(arq==NULL){
                printf("Erro na abertura do arquivo.\n");

            }


        while(!feof)
        {

            fscanf(arq," %[^,],",p.cpf);
            fscanf(arq," %[^,],",p.nome);
            fscanf(arq," %[^,],",p.sexo);
            fscanf(arq," %[^,],",p.data);
            fscanf(arq," %[^,],",p.uf);
            fscanf(arq," %[^\n]\n",p.cidade_arq);

                if(strlen(p.cpf) != 11 || (strlen(p.sexo) != 9  || strlen(p.sexo) != 8) ||  strlen(p.data) < 8  || strlen(p.data) > 11 ||  srtlen(p.uf) != 2 || srtlen(p.cidade_arq) < 28 || srtlen(p.cidade_arq) < 3){
                    verificador++;

                }else{
                    arq = fopen("temp.txt","w+");
                        fprintf(arq2,"%s",p.cpf);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",p.nome);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",p.sexo);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",p.data);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",p.uf);
                        fprintf(arq2,",");
                        fprintf(arq2,"%s",p.cidade_arq);
                        fprintf(arq2,"\n");
                    fclose(arq2);
                }


        }
        fclose(arq);



            if(verificador != 0){
                remove("INFOO.txt");
                rename("temp.txt","INFOO.txt");
            }else{
                remove("temp.txt");

            }

}
//FIM FUNCAO
