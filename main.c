#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000

struct node
{
  char operator;
  struct node *left;
  struct node *right;
};

// Declaração de funções
void writeExpression();
void readExpression();
void inOrder(struct node *root);
void freeTree(struct node *root);

int main()
{
  // operadores de precedência menor: +, -
  // operadores de precedência maior: *, /
  // por padrão, o nó raiz é o símbolo "|"

  // Os operadores de precedência menor são alocados à esquerda do nó raiz
  // Os operadores de precedência maior são alocados à direita do nó raiz

  // Exemplo de execução:
  // Input: 5 + 5 * 10 / 2 - 10
  // Saída: - + | * /

  writeExpression();
  readExpression();

  return 0;
}

void readExpression()
{
  FILE *filePointer;
  char expression[MAXCHAR];

  filePointer = fopen("./expression.txt", "r");

  // lê expressão salva na variável "expression"
  if (fgets(expression, MAXCHAR, filePointer) != NULL)
  {
    printf("Expressão: %s", expression);
  }
  else
  {
    printf("Erro ao ler o arquivo");
  }

  fclose(filePointer);

  struct node *root = NULL;

  root = malloc(sizeof(struct node));
  root->operator= '|'; // nó raiz padrão
  root->left = NULL;
  root->right = NULL;

  for (int i = 0; i < strlen(expression); i++)
  {
    if (expression[i] == '+' || expression[i] == '-')
    {
      struct node *newNode = malloc(sizeof(struct node));

      newNode->operator= expression[i];
      newNode->right = NULL;
      newNode->left = NULL;

      // encontra o último nó a esquerda
      struct node *current = root;
      while (current->left != NULL)
      {
        current = current->left;
      }

      current->left = newNode;
    }
    else if (expression[i] == '*' || expression[i] == '/')
    {
      struct node *newNode = malloc(sizeof(struct node));

      newNode->operator= expression[i];
      newNode->right = NULL;
      newNode->left = NULL;

      // encontra o último nó a direita
      struct node *current = root;
      while (current->right != NULL)
      {
        current = current->right;
      }

      current->right = newNode;
    }
  }

  printf("Nó raiz padrão: %c \n", root->operator);

  printf("Ordem de precedência dos operadores (menor | maior): \n");
  inOrder(root);
  printf("\n");

  // libera memória alocada
  freeTree(root);
}

void writeExpression()
{
  FILE *filePointer;
  char expression[MAXCHAR];
  int index;

  filePointer = fopen("./expression.txt", "w");

  printf("Digite uma expressão aritmética: ");
  fgets(expression, MAXCHAR, stdin);

  for (index = 0; index < strlen(expression); index++)
  {
    // salva a expressão no arquivo, caractere por caractere
    fputc(expression[index], filePointer);
  }

  fclose(filePointer);
}

void inOrder(struct node *root)
{
  if (root != NULL)
  {
    inOrder(root->left);
    printf("%c ", root->operator);
    inOrder(root->right);
  }
}

void freeTree(struct node *root)
{
  if (root != NULL)
  {
    freeTree(root->left);
    freeTree(root->right);
    free(root);
  }
}