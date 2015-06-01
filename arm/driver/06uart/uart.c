#include <common.h>
#include <uart.h>
#include <stdarg.h>

void uart_init(int no)
{
	switch(no){
		case 0:
			GPA0CON &= ~0xff;
			GPA0CON |= 0x22;
			break;
		case 1:
			GPA0CON &= ~(0xff << 16);
			GPA0CON |= 0x22 << 16;
			break;
		case 2:
		case 3:
		default:
			break;
	}

	//1.数据格式  8N1   选择串口的工作方式
	ULCON(no) = 3;
	UCON(no) = (1 << 2) | 1;
	//2.波特率    115200
	UBRDIV(no) = 53;
	UFRACVAL(no) = 4;
	//3.关闭afc
	UMCON(no) = 0;
	//4.关闭fifo
	UFCON(no) = 0;
	
	//	TR--/*->fifo-*/-->shirter------------->T
	//	RR<-/*--fifo<--*/-shirter<-------------R		
	//dma  irq  poll
}

void uart_send(int no, char c)
{
	UTXH(no) = c;
	while((UTRSTAT(no) & 2) == 0);//flags
}

char uart_recv(int no)
{
	while((UTRSTAT(no) & 1) == 0);
	return URXH(no) & 0xff;
}

void uputchar(char c)
{
	uart_send(0, c);
}

char ugetchar(void)
{
	return uart_recv(0);
}

// "helloworld\n" dfjsfdajdfjfdlkj
//kjfsdkjfkfdkjfd
void _uputs(char *s)
{
	while(*s){
		uputchar(*s);
		if(*s == '\n'){
			uputchar('\r');
		}
		s++;
	}
}

void uputs(char *s)
{
	_uputs(s);
	uputchar('\n');
	uputchar('\r');
}

char *ugets(char *buf, int max_len)
{
	char c;
	int len = 0;

	while(((c = ugetchar()) != '\r') && (len < max_len - 1)){
		buf[len++] = c;
		uputchar(c);
	}

	buf[len] = 0;

	uputchar('\r');
	uputchar('\n');

	return buf;
}

void itoa(unsigned int n, char *buf)
{

}

void xtoa(unsigned int n, char *buf)
{

}

//stdarg.h
//va_list
//va_start
//va_end
//va_arg
//uprintf("helloworld %d %c %x %s\n", 10, 'a', 0x400, "hihao");

int uprintf(const char *fmt, ...)
{
	va_list ap;
	int n;
	char *s;
	char buf[32];
	char c;

	va_start(ap, fmt);

	while(*fmt){
		if(*fmt == '%'){
			fmt++;
			switch(*fmt){
				case 'd':
					n = va_arg(ap, int);
					if(n < 0){
						uputchar('-');
						n = -n;
					}
					itoa(n, buf);
					_uputs(buf);
					break;
				case 'c':
					c = va_arg(ap, int);
					uputchar(c);
					break;
				case 's':
					s = va_arg(ap, char *);
					_uputs(s);
					break;
				case 'x':
					n = va_arg(ap, int);
					xtoa(n, buf);
					_uputs(buf);
					break;
				default:
					break;
			}
		}else{
			uputchar(*fmt);
			if(*fmt == '\n'){
				uputchar('\r');
			}
		}
		fmt++;
	}	

	va_end(ap);

	return 0;
}






