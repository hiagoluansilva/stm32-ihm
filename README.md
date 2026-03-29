# stm32-ihm

Interface Homem-Máquina (IHM) embarcada com LCD I2C, botões e comunicação USART no STM32F4xx.

## Descrição

Firmware de IHM embarcado para o soft starter, com display LCD 16×2 via I2C para exibição de status e parâmetros, botões físicos para navegação e configuração, e comunicação USART para integração com o sistema de controle.

## Hardware

- Microcontrolador: STM32F4xx
- Display: LCD 16×2 via I2C
- Comunicação: USART serial

## Funcionalidades

- Exibição de temperatura de subida e descida no LCD
- Navegação por menus com botões
- Modo de configuração e modo de operação
- Flag de emergência (`emerg`)
- Envio de parâmetros via USART

## Parâmetros

| Variável | Faixa | Descrição |
|----------|-------|-----------|
| `temp_sub` | 3–55 | Tempo de rampa de subida (s) |
| `temp_des` | 3–55 | Tempo de rampa de descida (s) |

## Estrutura

```
IHM/
├── Src/
│   ├── main.c
│   ├── i2c-lcd.c    # Driver LCD I2C
│   ├── i2c.c
│   ├── gpio.c
│   └── usart.c (gerado HAL)
├── Inc/
└── Drivers/
```

## IDE

Atollic TrueSTUDIO 9.3 / STM32CubeIDE

## Escola

Centro Tecnológico Liberato — Novo Hamburgo/RS
