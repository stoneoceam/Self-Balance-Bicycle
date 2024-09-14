#include "debug.h"

void DEBUG_Init(void){
	
	__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
	
}


/***************** �����ַ��� **********************/
void Usart_SendString(uint8_t *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit(&huart3,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
  
}
//�ض���c�⺯��printf������DEBUG_USART,�ض�������ʹ��printf����
int fputc(int ch, FILE *f)
{
	/* ����һ���ֽ����ݵ�����DEBUG_USART */
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}

//�ض���c�⺯��scanf������DEBUG_USART,�ض�������ʹ��scanf��getchar����
int fgetc(FILE *f)
{
		
	int ch;
	while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_RXNE) == RESET);
	__HAL_UART_CLEAR_OREFLAG(&huart3);
	HAL_UART_Receive(&huart3, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}
