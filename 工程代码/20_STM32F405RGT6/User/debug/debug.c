#include "debug.h"

void DEBUG_Init(void){
	
	__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
	
}


/***************** 发送字符串 **********************/
void Usart_SendString(uint8_t *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit(&huart3,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
  
}
//重定向c库函数printf到串口DEBUG_USART,重定向后可以使用printf函数
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到串口DEBUG_USART */
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}

//重定向c库函数scanf到串口DEBUG_USART,重定向后可以使用scanf、getchar函数
int fgetc(FILE *f)
{
		
	int ch;
	while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_RXNE) == RESET);
	__HAL_UART_CLEAR_OREFLAG(&huart3);
	HAL_UART_Receive(&huart3, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}
