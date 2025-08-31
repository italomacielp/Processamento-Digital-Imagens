# MANIPULANDO PIXELS DE UMA IMAGEM
## Objetivo
A partir das coordenadas mencionadas pelo o usuário, substituir os pixels selecionados por pixels negativos com o cálculo: <br/>
**pixel atual = 255 - valor do pixel atual** <br/>
Sendo assim, se a imagem for colorida deve-se realizar esse cálculo para as faixas de cores RGB.
## Passos
Foi utilizado o **CMake** para facilitar o processo de compilação e execução, para isso é necessário realizar os seguintes comandos no diretório build.
- make: (Gera os arquivos compilados e demais arquivos de configuração como MAKEFILE)
- ./resources: (Executa o programa)
- make clean: (Exclui os arquivos executáveis e compilados)
## Recursos Adicionais
Foi adicionado tratamento de exceções para quando o usuário selecionar um ponto que não esteja na imagem, evitando possíveis de erros de segmentação. Como também foi criada uma classe para fins de organização dos pontos.


