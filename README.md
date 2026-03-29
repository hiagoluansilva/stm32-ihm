# STM32 IHM Soft Starter — Interface Homem-Máquina

🇧🇷 **Português** | 🇺🇸 [English](#english)

---

## Português

Interface Homem-Máquina para soft starter em STM32F4xx com máquina de estados, LCD I2C e botões de configuração.

### O que faz
- Implementa **máquina de estados** com 3 modos: principal, configuração e emergência
- Botões PC1/PC2/PC3 navegam entre telas e ajustam parâmetros
- **LCD via I2C** exibe status e valores configurados
- Parâmetros: `temp_sub` e `temp_des` (tempo de rampa)
- Clock configurado para **84 MHz**

### Máquina de estados
```
MAIN ←→ CONFIG ←→ EMERGENCY
  ↑                    ↓
  └────────────────────┘
```

### Periféricos
| Periférico | Função |
|---|---|
| PC1 | Botão navegação/incremento |
| PC2 | Botão decremento |
| PC3 | Botão confirmar/emergência |
| I2C | LCD 16×2 |

### Microcontrolador
STM32F4xx — 84 MHz — Atollic TrueSTUDIO

---

## English

Human-Machine Interface for a soft starter on STM32F4xx with state machine, I2C LCD, and configuration buttons.

### What it does
- Implements a **state machine** with 3 modes: main, configuration, and emergency
- Buttons PC1/PC2/PC3 navigate screens and adjust parameters
- **I2C LCD** displays status and configured values
- Parameters: `temp_sub` and `temp_des` (ramp time)
- Clock configured at **84 MHz**

### State machine
```
MAIN ←→ CONFIG ←→ EMERGENCY
  ↑                    ↓
  └────────────────────┘
```

### Peripherals
| Peripheral | Function |
|---|---|
| PC1 | Navigation/increment button |
| PC2 | Decrement button |
| PC3 | Confirm/emergency button |
| I2C | 16×2 LCD |

### MCU
STM32F4xx — 84 MHz — Atollic TrueSTUDIO
