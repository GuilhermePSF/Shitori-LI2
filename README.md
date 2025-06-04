# S H I T O R I

## Visão Geral do Projeto
Este projeto foi desenvolvido para a cadeira de **Laboratórios de Informática 2**. Implementa um jogo de resolução de puzzles onde os jogadores devem seguir regras específicas para marcar e eliminar símbolos em uma grade.

Para regras detalhadas do jogo, consulte a descrição oficial do projeto: [Descrição do Projeto](https://eos.di.uminho.pt/~rui/projeto/enunciado.html).

## Autores
- **Guilherme Ferreira**
- **Tomás Ferreira**
- **Lucas Pinto**

## Funcionalidades
- Interface interativa via terminal (REPL)
- Criação de puzzles aleatórios (`G <tamanho>`)
- Carregamento e gravação de puzzles a partir de ficheiros
- Visualização do tabuleiro
- Validação de jogadas e restrições
- Dicas automáticas com jogadas inferidas
- Resolução automática (com e sem visualização passo a passo)
- Suporte a desfazer (`d`) jogadas e repor o estado original (`D`)
- Verificação de vitória e fim de jogo com mensagem de parabéns
- Mensagens coloridas para melhor legibilidade

## Instalação
Para compilar o projeto, certifique-se que tem o **GCC** instalado. Execute o seguinte comando:

```sh
make jogo
```

## Comandos
O jogo opera no estilo **REPL (Read-Eval-Print Loop)** e suporta(rá) os seguintes comandos:

| Comando       | Descrição                                                                 |
|---------------|---------------------------------------------------------------------------|
| `?`           | Mostra novamente a lista de comandos                                       |
| `G <tamanho>` | Gera um novo tabuleiro aleatório com o tamanho especificado (1 a 26)      |
| `l <ficheiro>`| Carrega um tabuleiro a partir de um ficheiro                              |
| `g <ficheiro>`| Guarda o estado atual do jogo num ficheiro                                |
| `b <coord>`   | Marca a célula em `<coord>` como **branco** (maiúscula)             |
| `r <coord>`   | Marca a célula em `<coord>` como **riscado** (`#`)                       |
| `v`           | Verifica se as restrições do tabuleiro estão satisfeitas                  |
| `a`           | Aplica todas as jogadas inferíveis                                        |
| `A`           | Repete o comando `a` até não haver mais alterações                        |
| `R`           | Tenta resolver o puzzle automaticamente                                   |
| `P`           | Apresenta o processo de resolução passo a passo                           |
| `t`           | Aplica técnicas iniciais de resolução                                     |
| `S`           | Resolve o tabuleiro com força bruta (backtracking)                        |
| `d [<coord>]` | Desfaz a última jogada ou até à jogada numa coordenada específica         |
| `D`           | Restaura o tabuleiro ao estado original (carregado ou gerado)             |
| `s`           | Sai do jogo                                                               |


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

