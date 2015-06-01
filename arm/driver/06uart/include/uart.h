#ifndef __UART_H__
#define __UART_H__

#define GPA0CON (*(volatile unsigned int *)(0x11400000 + 0x0000))

#define UART0_BASE 0x13800000

#define ULCON(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0000)) 
#define UCON(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0004)) 
#define UFCON(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0008)) 
#define UMCON(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x000C)) 
#define UTRSTAT(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0010)) 
#define UERSTAT(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0014)) 
#define UFSTAT(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0018)) 
#define UMSTAT(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x001C)) 
#define UTXH(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0020)) 
#define URXH(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0024)) 
#define UBRDIV(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0028)) 
#define UFRACVAL(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x002C)) 
#define UINTP(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0030)) 
#define UINTSP(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0034)) 
#define UINTM(n) 	(*(volatile unsigned int *)(UART0_BASE + 0x10000 * (n)+ 0x0038)) 

extern void uart_init(int no);
extern void uart_send(int no, char c);
extern char uart_recv(int no);

extern void uputchar(char c);
extern char ugetchar(void);
extern void _uputs(char *s);
extern char *ugets(char *s, int len);
extern void uputs(char *s);
extern int uprintf(const char *fmt, ...);

//UART 
// -----T-----   ---R--------
// -----R-----   ---T--------
// -----E-----   ---E--------
// -----CT----   ---RT-------
// -----RT----   ---CT-------
// AFC 硬件 软件
//
// CMOS/TTL(4412) 	RS232(PC uart)
// 1.8V/3.3V/5V  1
// 0V            0
// 4412(1.8v)--->升压--->TTL<--->3.3/5 Max232<--->RS232
// [-3V, -12V] 	 1
// [3V, 12V]	 0


#endif








