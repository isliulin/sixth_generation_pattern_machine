#ifndef APP_DEBUG_H
#define APP_DEBUG_H


#define DEBUG_LEVEL     0       //������Ϣ��ӡ

/*----------------------------------------------------------------------------*/
#if (DEBUG_LEVEL > 0)
#define     UsrLog(...)     printf(__VA_ARGS__);                \
                            //printf("\r\n");                   \
                              
#else
#define     UsrLog(...)   
#endif 
                            
                            
#if (DEBUG_LEVEL > 1)

#define     ErrLog(...)     printf("ERROR: ");                  \
                            printf(__VA_ARGS__);                \
                            //printf("\r\n");                   \
                              
#else
#define     ErrLog(...)   
#endif 
                            
                            
#if (DEBUG_LEVEL > 2)                         
#define     DbgLog(...)     printf("DEBUG: ");                  \
                            printf(__VA_ARGS__);                \
                            //printf("\r\n");                   \
                              
#else
#define     DbgLog(...)                                         \
                              
#endif

/*----------------------------------------------------------------------------*/













#endif /* APP_DEBUG_H */
