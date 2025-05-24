# S H I T O R I

## Visão Geral do Projeto
Este projeto foi desenvolvido para a cadeira de **Laboratórios de Informática 2**. Implementa um jogo de resolução de puzzles onde os jogadores devem seguir regras específicas para marcar e eliminar símbolos em uma grade.

Para regras detalhadas do jogo, consulte a descrição oficial do projeto: [Descrição do Projeto](https://eos.di.uminho.pt/~rui/projeto/enunciado.html).

## Autores
- **Guilherme Ferreira**
- **Tomás Ferreira**
- **Lucas Pinto**

## Funcionalidades
- Interface interativa no terminal (REPL)
- Visualização e manipulação do tabuleiro
- Validação das restrições do jogo
- Solucionador automático para dicas e resolução completa
- Funcionalidade de desfazer/refazer
- Possibilidade de salvar e carregar estados do jogo

## Instalação
Para compilar o projeto, certifique-se de que possui **GCC** instalado. Execute o seguinte comando:

```sh
make jogo
```

## Comandos
O jogo opera no estilo **REPL (Read-Eval-Print Loop)** e suporta(rá) os seguintes comandos:

| Comando | Descrição |
|---------|-------------|
| `g <ficheiro>` | Guarda o estado atual do jogo num ficheiro |
| `l <ficheiro>` | Carrega um estado do jogo de um ficheiro |
| `<coord>` | Seleciona uma coordenada (exemplo: `b2`) |
| `b <coord>` | Marca um símbolo como **branco** (maiúsculo) |
| `r <coord>` | Marca um símbolo como **removido** (`#`) |
| `v` | Verifica o estado atual do tabuleiro e aponta erros |
| `a` | Aplica todas as jogadas inferíveis |
| `A` | Aplica `a` repetidamente até que não ocorram mais alterações |
| `R` | Resolve o puzzle automaticamente |
| `d` | Desfaz a última jogada |
| `s` | Sai do jogo |

## Testes
O projeto inclui testes unitários utilizando **CUnit**. Para compilar e executar todos os testes, use:

```sh
make teste
```

Para verificar a cobertura de código, utilize:

```sh
make cobertura
```

## Qualidade do Código
- Compilado com flags estritas: `-Wall -Wextra -pedantic -fsanitize=address`
- Utiliza `lcov` para análise de cobertura
- Detecção de vazamento de memória com `valgrind`

## Formato do Ficheiro
Os estados do jogo são guardados num formato de texto simples:
```
L C  # L = linhas, C = colunas
ecadc
dcdec
bddce
cdeeb
accbb
```

