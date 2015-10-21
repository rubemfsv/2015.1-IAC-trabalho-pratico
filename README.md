<p align="center">
Universidade Federal de Alagoas</br>
Instituto de Computação</br>
Disciplina: Introdução à Computação</br>
Semestre letivo: 2015.1</br>
Professor: André Lage Freita</br>
</p>



# 2015.1-IAC-trabalho-pratico

# Identificação

* Página do repositório do trabalho ([link GitHub](https://github.com/rubemfsv/2015.1-IAC-trabalho-pratico))

* Discente 1
	* Nome: Rubem Ferreira Santos Vasconcelos 
	* Matrícula: 15111988
* Discente 2
	* Nome: Vanessa Soares Vieira
	* Matrícula: 15112025


### Contextualização.

Cada computador executa diversas tarefas “ao mesmo tempo”, isso quer dizer que ele executa diversos processos, e esses são, de fato, as tarefas que estão em execução quase que simultaneamente - algumas delas ocorrem em plano de fundo, sem que o usuário note. Como abstração feita para o próprio usuário, é impossível perceber que os processos não estão sendo executados sincronicamente por serem realizados eu um período de tempo infinitamente curto.

Frequentemente, quando um processo está em execução, ele pode consumir bastante memória volátil do sistema, este é o caso dos processos que são abstraídos para o usuário (como o simples ato de abrir um arquivo, que faz executar, em plano de fundo diversos processos até ser realizada a tarefa), que estão rodando por “trás” e consumindo a memória RAM. Quando muitas tarefas estão ocorrendo “simultaneamente”, há uma queda no desempenho da unidade central de processamento (UCP), e ocorre um retardo durante a execução dos programas - além de desperdício de memória. 

Para realização efetiva do trabalho prático, fez-se necessária a duplicação de um processo utilizando-se como recurso a função fork() (linha 22 do código-fonte), a mesma só pode ser executada em sistemas UNIX (ex.: o sistema operacional Linux). A fim de obter um maior e mais completo entendimento de como a função ocorre, utiliza-se o nome "pai" para o principal processo, que se multiplica em dois, criando um novo processo idêntico ao processo pai (mudando apenas seu número de identificação) denominado "filho".



### Objetivo

Este trabalho visa a investigação da utilização da unidade central de processamento e da memória pela execução dos processos, com isso, há uma melhor compreensão de dois dos principais recursos de um computador, que varia de um para o outro a depender, sobretudo, da arquitetura do computador, da quantidade de processadores e do tamanho da memória volátil (quantidade de Gigabytes da memória RAM). 

Foi então necessário verificar o uso e desempenho da UCP a partir da criação de um processo filho (utilizando-se da função fork()) e o monitoramento do mesmo. Para isso, se é observado a porcentagem do uso da UCP, a cada segundo, através da execução de um código de uso intenso da unidade central (linhas 47, 48 e 49 do código-fonte). Quando executado, de maneira análoga, um código de uso intenso de UCP e memória, pôde-se analisar a utilização dos recursos da memória e da UCP (linhas 50 a 53 do código) durante cada segundo desse processo (resultado em Kilobytes e em porcentagem, respectivamente), se vê uma progressão gradativa. 



### Conclusões Iniciais

O programa escrito em C cria, executa e coleta dados do processo filho, e o mesmo é identificado através de um número “pid” (identificador do processo), que é o valor retornado da função fork(). Quando o pid é igual a zero, se está executando o código do processo filho (linhas 46 a 57). Como mencionado anteriormente, para cada caso de argumento (argv) – cpu e cpu-mem, há a execução de um for infinito (um for sem argumentos definidos) para que haja uso intenso da UCP e um for infinito que aloca 10 bytes de memória em cada volta do loop, para haver o uso intenso tanto da UCP quanto da memória. 

Há, no processo pai, a coleta dos dados com o auxílio da função getrusage() (linha 35), que retorna valores do uso dos componentes do computador, estes valores são salvos em uma struct rusage (linha 19). Para acessar os dados em questão (Kilobytes, no caso da memória e porcentagem, no caso da UCP), guardou-se em dois vetores com 10 espaços os valores obtidos na struct (linhas 36, 37 e 38). Ao término dos 10 segundos de execução, o processo filho foi matado (linha 45) e foi impresso na tela todos os dados de memória e UCP de cada segundo e a soma de todos esses dados (linhas 59 a 63).



### Conclusões Finais

O objetivo do programa foi atingido com sucesso, pois além de compilar e executar cada caso de teste predefinido, foi possível inferir, a partir dos resultados apresentados nos gráficos abaixo, que o uso de memória foi o mesmo a cada segundo (e o total foi a soma de todos esses valores, ou seja, dez vezes o uso do primeiro segundo) e o uso da unidade central de processamento foi aumentando gradativamente. O valor em porcentagem da UCP pode parecer pequeno, isso porquê o processo filho foi forçado a parar após 10 segundos, ou seja, em um curto período de tempo o uso da UCP saiu de aproximadamente 0% até aproximadamente 21%, se o processo executasse por mais tempo é possível concluir que ao atingir 100%, ou até antes, o computador travaria.

Os recursos de uma máquina são escassos, mas de extrema importância, a memória RAM é um periférico que funciona como memória temporária (ou volátil), o processador a utiliza para guardar dados enquanto o processo estiver executando, quando o computador é desligado, aquela informação já foi volatizada, ou seja, perdida. Quando salvo em um arquivo, os dados de um programa alocam o mesmo em algum espaço da memória permanente (HD, memória flash ou SSD). No caso do programa deste trabalho prático, há somente o uso da memória RAM. Quando há o uso intenso da UCP e da memória, sem a restrição do tempo, o computador também travaria.



### Utilização Intensa da UCP e Memória

#### UCP

![UCP graph](http://imageshack.com/a/img910/6858/jkgdyQ.png)

* Código do gráfico da UCP Cque foi realizado em Julia:

```julia
plot(x=1:10, y=[0.28, 0.55, 0.83, 10.16, 10.39, 10.66, 10.94, 20.21, 20.47, 20.73],
Geom.point, Geom.line,
Guide.xlabel("Tempo em segundos"), Guide.ylabel("Uso da UCP (em porcentagem)"),
Guide.title("Processo da UCP"))
```

#### Memória

![memory graph](http://imageshack.com/a/img911/5458/Y4Pps1.png)

* Código do gráfico da memória que foi realizado em Julia:

```julia
plot(x=1:10, y=[532480, 532480*2, 532480*3, 532480*4, 532480*5, 532480*6, 532480*7, 532480*8, 532480*9, 532480*10],
Geom.point, Geom.line,
Guide.xlabel("Tempo em segundos"), Guide.ylabel("Uso da memória (em Kilobytes)"),
Guide.title("Processo da Memória"))
```

