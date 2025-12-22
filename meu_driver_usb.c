#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include "meu_driver.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ana Alicy");
MODULE_DESCRIPTION("Driver USB simples");

// Tabela de dispositivos suportados
/*
static struct usb_device_id tabela_ids[] = {
    { USB_DEVICE(0x23a9, 0xef18) },   // SEU pendrive
    
        { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, 0x06, 0x50) },
        
    { }
};
*/
static const struct usb_device_id tabela_ids[] = {
    { USB_DEVICE(ID_VENDOR, ID_PRODUCT) },   // usa os #defines do .h
    { }                                      // entrada terminadora
};
MODULE_DEVICE_TABLE(usb, tabela_ids);


MODULE_DEVICE_TABLE(usb, tabela_ids);

// Função chamada quando o dispositivo é conectado
static int meu_probe(struct usb_interface *interface,
                     const struct usb_device_id *id)
{
    printk(KERN_INFO "[USB] Dispositivo conectado: VID=%04X PID=%04X\n",
           id->idVendor, id->idProduct);

    return 0;
}

// Função chamada quando o dispositivo é removido
static void meu_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "[USB] Dispositivo removido!\n");
}

// Estrutura do driver USB
static struct usb_driver meu_usb_driver = {
    .name = "meu_usb_driver",
    .probe = meu_probe,
    .disconnect = meu_disconnect,
    .id_table = tabela_ids,
};

// Funções init/exit (FORMA 1 — usb_register)
static int __init meu_usb_init(void)
{
    printk(KERN_INFO "Driver USB carregado\n");
    return usb_register(&meu_usb_driver);
}

static void __exit meu_usb_exit(void)
{
    printk(KERN_INFO "Driver USB descarregado\n");
    usb_deregister(&meu_usb_driver);
}

module_init(meu_usb_init);
module_exit(meu_usb_exit);
