#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <mysql/mysql.h>
#include <string.h>

#define HOST "localhost"
#define USER "root"
#define PASS "2004"
#define DB "sistema_de_estoque"
//Para usar cls ou clear fazer consulta de OS(Linux ou Windows)
// comando pra compilação -> "gcc -o exe script.c -lmysqlclient"

void imprime_tabela(MYSQL *conexao);// Fazer poka-yoke para caso a solicitação não de certo
void insere_produto();
void totaliza_compra();
void atualiza_produto(MYSQL *conexao, char coluna[], char novo_valor[], char id[]);// Fazer poka-yoke caso não exista algo
void checa_produto(MYSQL *conexao, char produto[]);// Fazer poka-yoke caso a query não de resultado

void main()
{
   setlocale(LC_ALL, "Portuguese");// seta o idioma como português

   MYSQL conexao;// variável para uso da biblioteca
   bool resultado;
   mysql_init(&conexao);// inicia a variável como 'objeto' de conexão com o banco de dados
   resultado = mysql_real_connect(&conexao, HOST, USER, PASS, DB, 0, NULL, 0);//conecta ao banco de dados e retorna o resultado
   if(!resultado)// testa o resultado
   {
      printf("Erro na conexão.\n");
      return;
   }
   imprime_tabela(&conexao);
   atualiza_produto(&conexao, "nome", "Tijolo", "1");

   mysql_close(&conexao);// encerra conexão com o banco de dados
   return;
}

void imprime_tabela(MYSQL *conexao)
{
   MYSQL_ROW linhas;
   MYSQL_RES *resultado;
   MYSQL_FIELD *campos;
   int iterador;
   mysql_query(conexao, "SELECT * FROM produtos;");// Faz a query
   resultado = mysql_store_result(conexao);// recebe o resultado da query(caso ela não exista -> 0)
   if(resultado)// se tivere resultado
   {
      /*
      campos = mysql_fetch_field(resultado);// recebe uma estrutura com as colunas
      for(iterador = 0; iterador < mysql_num_fields(resultado); iterador++)
      {
         printf("%s ", (campos[iterador]).name);// imprime o nome das colunas
      }
      printf("\n");
      */
     printf("+------+-----------------+----------+------+\n");
     printf("|  ID  |     Nome        |  Preço   | Qunt |\n");//imprime os nomes das colunas "manualmente"(acima tem o método automático)
     printf("+------+-----------------+----------+------+\n");
      while ((linhas = mysql_fetch_row(resultado)) != NULL)
      {// enquanto retornar registro(linhas)
         iterador = 0;
         printf("| %4s ", linhas[iterador]);//id
         iterador++;
         printf("| %-15s ", linhas[iterador]);//nome
         iterador++;
         printf("| R$%6s ", linhas[iterador]);//preco
         iterador++;
         printf("| %4s |", linhas[iterador]);//quantidade

         /*
         for(iterador = 0; iterador < mysql_num_fields(resultado); iterador++)
         {//conta até o número de colunas, ou seja, imprime a linha inteira
            printf("%s\t", linhas[iterador]);
         }
         */
         printf("\n");//próxima linha
         
      }
      printf("+------+-----------------+----------+------+\n");
   }
   mysql_free_result(resultado);// limpa a variável de resultado
   return;
}

void checa_produto(MYSQL *conexao, char produto[])//TERMINAR
{
   int tamanho = (strlen(produto) + strlen("SELECT * FROM produtos WHERE id = "));
   char query[tamanho];// não pode ser declarada com tamanho e valor ao mesmo tempo. ex.: 'char var[4] = "Vitor"'
   char select[] = "SELECT * FROM produtos WHERE id = ";
   MYSQL_RES *res;//para armazenar o resultado da query
   MYSQL_ROW linha;
   strncpy(query, select, strlen(select));// copia para a "string" select em "query"
   strcat(query, produto);// concatena as strings

   mysql_query(conexao, query);// faz query
   res = mysql_store_result(conexao);//recebe(do histórico) o resultado da query
   linha = mysql_fetch_row(res);

   printf("+------+-----------------+----------+------+\n");
   printf("|  ID  |     Nome        |  Preço   | Qunt |\n");//imprime os nomes das colunas "manualmente"
   printf("+------+-----------------+----------+------+\n");
   int iterador = 0;
   printf("| %4s ", linha[iterador]);//id
   iterador++;
   printf("| %-15s ", linha[iterador]);//nome
   iterador++;
   printf("| R$%6s ", linha[iterador]);//preco
   iterador++;
   printf("| %4s |", linha[iterador]);//quantidade
   printf("\n+------+-----------------+----------+------+\n");
   return;
}

void atualiza_produto(MYSQL *conexao, char coluna[], char novo_valor[], char id[])
{
   int tamanho = strlen("UPDATE produtos SET  = '' WHERE id = '';") + strlen(coluna) + strlen(novo_valor) + strlen(id);
   char query[tamanho];
   char update0[] = "UPDATE produtos SET ";
   char update1[] = " = '";
   char update2[] = "' WHERE id = '";
   char update3[] = "';";

   strncpy(query, update0, strlen(update0));
   strcat(query, coluna);
   strcat(query, update1);
   strcat(query, novo_valor);
   strcat(query, update2);
   strcat(query, id);
   strcat(query, update3);
   printf("%s\n", query);

   mysql_query(conexao, query);
   return;
}

void insere_produto()
{
   
}