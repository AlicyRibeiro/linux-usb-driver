# meu_driver_usb — USB Device Driver

Este diretório contém a implementação de um **driver USB** baseada na seção **5.3.3** do material  
*Técnicas de Programação para Sistemas Embarcados II*.

O objetivo desta prática é demonstrar como criar um **driver USB no espaço de kernel**, capaz de
reconhecer a conexão e desconexão de um dispositivo USB específico (ex.: pen drive), utilizando
os mecanismos fornecidos pelo subsistema USB do Linux.

---

###  Estrutura dos Arquivos

* meu_driver_usb/
* ├── Makefile
* ├── meu_driver.c
* └── meu_driver.h

---

##  Funcionalidades do Módulo

###  Registro de Driver USB

O driver é registrado no kernel utilizando a estrutura `struct usb_driver`, que associa:

- Nome do driver
- Lista de dispositivos suportados
- Funções de **probe** e **disconnect**

O registro e a remoção do driver são feitos através das funções:

- `usb_register()`
- `usb_deregister()`

---

###  Identificação do Dispositivo USB

O subsistema USB identifica dispositivos através de um par de identificadores:

- **idVendor** — identificador do fabricante
- **idProduct** — identificador do dispositivo

Esses IDs são obtidos com o comando:

```bash
lsusb
```

E definidos no arquivo meu_driver.h:

```bash
#define ID_VENDOR  0xXXXX
#define ID_PRODUCT 0xYYYY
```
Esses valores são usados para criar a tabela de dispositivos suportados pelo driver.

---

## Tabela de Dispositivos USB

O driver define uma lista de dispositivos compatíveis usando usb_device_id:

```bash
static struct usb_device_id usb_device_list[] = {
    { USB_DEVICE(ID_VENDOR, ID_PRODUCT) },
    { }
};

```
A macro MODULE_DEVICE_TABLE permite que o kernel carregue automaticamente o módulo quando um dispositivo compatível for conectado.

### Funções Probe e Disconnect

#### my_probe()
Executada automaticamente quando um dispositivo USB compatível é conectado.
Exibe no log o ID do dispositivo detectado.

#### my_disconnect()
Executada quando o dispositivo USB é removido da porta.

Essas funções permitem monitorar eventos de conexão e desconexão de dispositivos USB.
