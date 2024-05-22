# CC7711Projeto

## Filipe Bruhns Pio Pedroso  22.121.053-7
## Lucas Forge Freo  22.121.081-8
## Yuri Tierno Popic  22.121.046-1

### Descrição
O programa inicia configurando os motores, sensores de proximidade e LEDs do robô. Em seguida, entra em um loop principal onde realiza as seguintes operações:
Lê os valores dos sensores de proximidade e os armazena em um array.
Verifica se uma caixa móvel no ambiente de simulação se moveu além de um limite pré-definido.
Se a caixa se moveu, para os motores do robô, ativa todos os LEDs e encerra o programa.
Caso contrário, calcula a velocidade dos motores com base nos valores dos sensores de proximidade.
Atualiza as velocidades dos motores de acordo com os cálculos feitos.
Repete o processo até que o programa seja encerrado ou a caixa se mova.
