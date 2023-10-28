# SSL-Estimator

## Componentes do grupo:
21001 - Luckwu
21413 - Horie

## Projeto de Decodificação e Estimativa de Informações do Programa SSL-Vision

### Descrição do Conceito
O objetivo deste projeto é criar um sistema capaz de receber mensagens via UDP do programa SSL-Vision, que contém informações da visão da categoria Small Size League da RoboCup. Através da decodificação dessas mensagens, o sistema irá extrair dados cruciais sobre a posição e estimar a velocidade dos objetos (robôs e bola) no campo de jogo. Esses dados serão processados e disponibilizados para uso em estratégias de controle e tomada de decisões dos robôs da RoboIME.

### Função
O sistema terá as seguintes funções principais:
1. Receber mensagens UDP do programa SSL-Vision.
2. Decodificar as mensagens para extrair informações sobre a visão do campo.
3. Estimar a posição e velocidade dos objetos, como robôs e a bola, com base nos dados da visão.
4. Possivelmente, fornecer uma interface de usuário para monitorar as informações da visão em tempo real.

### Motivação
A motivação por trás deste projeto é melhorar o desempenho e a eficácia da visão da equipe de robôs do Instituto Militar de Engenharia (RoboIME) na categoria Small Size League da RoboCup. O acesso a informações precisas e atualizadas sobre a posição e velocidade dos objetos no campo é fundamental para o sucesso da equipe. Isso irá permitir aprimorar o desempenho no jogo.

Este projeto é essencial para iniciar um novo código mais rápido e eficiente em substituição ao atual código.



# Instalação
### grSim
Primeiro vamos instalar o grSim, o qual é necessário para simular a visão fornecida pela competição. Basta seguir o tutorial do link: https://github.com/RoboCup-SSL/grSim/blob/master/INSTALL.md <br />
### Qt
Para instalar use o tutorial: https://www.youtube.com/watch?v=mVKdomkl5Uk <br />
E para fazer um primeiro "Hello, world" basta seguir o tutorial: https://www.youtube.com/watch?v=sjApF6qnyUI&ab_channel=ProgrammingKnowledge <br />

![diagrama de classes](docs/img/ssl_project.png?raw=true "diagrama de classes")
![fluxograma visao](docs/img/MultiObjectFilterFlowChart.png?raw=false "fluxograma visao")
![fluxograma kalman](docs/img/kalmanSteps.png?raw=false "fluxograma kalman")
