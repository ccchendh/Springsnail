#include <stdio.h>
#include <time.h>
#include <string.h>
#include "log.h"

static int level = LOG_INFO;
static int LOG_BUFFER_SIZE = 2048;
static const char* loglevels[] =
{
    "emerge!", "alert!", "critical!", "error!", "warn!", "notice:", "info:", "debug:"
};

//设置日志级别
void set_loglevel( int log_level )
{
    level = log_level;
}

//向标准输出打印日志
void log( int log_level,  const char* file_name, int line_num, const char* format, ... )
{
    if ( log_level > level )
    {
        return;
    }
    
    //设置时间并记录
    time_t tmp = time( NULL );//获取时间戳
    struct tm* cur_time = localtime( &tmp );//将时间戳转换成标准时间格式存储在struct tm里
    if ( ! cur_time )
    {
        return;
    }

    char arg_buffer[ LOG_BUFFER_SIZE ];
    memset( arg_buffer, '\0', LOG_BUFFER_SIZE );
    //按照format将struct tm内容打印
    strftime( arg_buffer, LOG_BUFFER_SIZE - 1, "[ %x %X ] ", cur_time );
    printf( "%s", arg_buffer );
    printf( "%s:%04d ", file_name, line_num );
    printf( "%s ", loglevels[ log_level - LOG_EMERG ] );

    //获取可变参数
    va_list arg_list;
    va_start( arg_list, format );
    memset( arg_buffer, '\0', LOG_BUFFER_SIZE );
    //与snprintf相同，区别是最后不是接受一个参数列表，而是接受va_list
    vsnprintf( arg_buffer, LOG_BUFFER_SIZE - 1, format, arg_list );
    printf( "%s\n", arg_buffer );
    fflush( stdout );
    va_end( arg_list );
}
