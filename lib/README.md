### 对库文件的修改
```c
/**
 * @brief  STR Exclusive (8 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 8 bit values
 */
uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
   uint32_t result=0;
  
   // __ASM volatile ("strexb %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   __ASM volatile ("strexb %0, %2, [%1]" : "=&r" (result) : "r" (addr), "r" (value) );
   return(result);
}

/**
 * @brief  STR Exclusive (16 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 16 bit values
 */
uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
   uint32_t result=0;
  
   // __ASM volatile ("strexh %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   __ASM volatile ("strexh %0, %2, [%1]" : "=&r" (result) : "r" (addr), "r" (value) );
   return(result);
}
```