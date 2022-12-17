#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <malloc.h>

static int	ft_count_digits(int num)
{
    int	dig;
    int	count;

    count = 0;
    if (num < 0)
    {
        num = (num + 1) * -1;
        if (num + 1 > 0)
            num += 1;
    }
    while (num > 0)
    {
        dig = num % 10;
        num = num / 10;
        count++;
    }
    return (count);
}

static int	ft_pow(int n, int p)
{
    int	num;

    num = 1;
    while (p > 0)
    {
        num *= n;
        p--;
    }
    return (num);
}

static int	ft_digit(int *n, int count)
{
    int		d;
    int		digit;

    d = ft_pow(10, (count - 1));
    digit = (*n / d) * -1;
    if (digit < 0)
        digit *= -1;
    *n = *n % d;
    return (digit);
}

static char	*ft_imalloc(int count, int n)
{
    char	*s;

    if (count == 0)
    {
        s = (char *)malloc(2);
        if (s == NULL)
            return (NULL);
        s[0] = '0';
    }
    else
    {
        if (n < 0)
        {
            s = (char *)malloc(count + 2);
            if (s == NULL)
                return (NULL);
            s[0] = '-';
        }
        else
        {
            s = (char *)malloc(count + 1);
        }
    }
    return (s);
}

char	*ft_itoa(int n)
{
    int		count;
    char	*s;
    int		i;

    count = ft_count_digits(n);
    s = ft_imalloc(count, n);
    if (s == NULL)
        return (NULL);
    if (n > 0)
        i = 0;
    else
        i = 1;
    while (count > 0)
    {
        s[i] = ft_digit(&n, count) + 48;
        i++;
        count --;
    }
    s[i] = '\0';
    return (s);
}

size_t	ft_strlen(const char *str)
{
    size_t	length;

    length = 0;
    while (str[length])
    {
        length++;
    }
    return (length);
}

void	*ft_memset(void *str, int c, size_t n)
{
    size_t		count;
    void		*str_cp;

    str_cp = str;
    count = 0;
    while (count < n)
    {
        *(char *) str_cp = c;
        str_cp++;
        count++;
    }
    return (str);
}

void	*ft_calloc(size_t nitems, size_t size)
{
    void			*p;

    if (size && SIZE_MAX / size < nitems)
        return (NULL);
    p = malloc(nitems * size);
    if (p == NULL)
        return (NULL);
    p = ft_memset(p, 0, (nitems * size));
    return (p);
}

char *decToHex(size_t val)
{
    size_t quotient;
    size_t temp;
    int i;
    char *hexadecimalNumber;

    quotient = val;
    if (quotient < 0)
        quotient *= -1;
    i = 16;
    hexadecimalNumber = (char *)malloc(17);
    hexadecimalNumber = ft_memset(hexadecimalNumber, 48, 17);

    printf("quotient: %d\n", quotient);
    while(quotient!=0) {
        temp = quotient % 16;
        //To convert integer into character
        if( temp < 10)
            temp =temp + 48;
        else
            temp = temp + 55;
        hexadecimalNumber[i--]= temp;
        quotient = quotient / 16;
    }
    hexadecimalNumber[17] = '\0';
    return (hexadecimalNumber);
}

int convertDecimalToOctal(int decimalNumber) {
    int octalNumber = 0, i = 1;

    while (decimalNumber != 0) {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }
}

void ft_type(char type, va_list args)

{
    void  *val;
    char c;
    char *str;

    if (type == 'i')
    {
        val = va_arg(args, int);
        val = ft_itoa(val);
    } else if (type == 'd')
        val = ft_itoa((int)va_arg(args, double));
    else if (type == 's')
        val = va_arg(args, char *);
    else if (type == 'c')
    {
        c = (char)va_arg(args, int);
        str = (char *)malloc(2);
        if (!str)
            return ;
        str[0] = c;
        str[1] = '\0';
        val = str;
    }
    else if (type == '%')
        val = "%";
    else if (type == 'p' || type == 'X')
    {
        val = decToHex((size_t)va_arg(args, void *));
        write(1, "0x", 2);
        while(*(char *)val == '0')
            val++;
    }
    else if (type == 'u')
    {
        val = va_arg(args, int);
        if ((int)val < 0)
            val = (int)val * -1;
        val = ft_itoa(val);
    }
    else
        return ;
    write(1, val, ft_strlen(val));
}

int ft_printf(const char *str, ...)
{
    va_list args;

    va_start(args, str);
    if (str == NULL)
        return (0);
    while (*str != '\0')
    {
        if (*str == '%')
        {
            str++;
            ft_type(*str, args);
        }
        else
        {
            write(1, str, 1);
        }
        str++;
    }
}

int main() {

    char *str;
    str = (char *)malloc(2);
    ft_printf("my age is %i\n", -23);
    ft_printf("my age is %u\n", -23);
    ft_printf("my name is %s\n", "Christina");
    ft_printf("my first char is %c  %%\n", 'C');
    ft_printf("the decimal point: %d\n", 10.50);
    printf("the pointer: %d\n", str);
    printf("the address of the pointer: %p\n", str);
    ft_printf("the pointer: %p\n", str);
    ft_printf("the hex number: %X\n", 11);


    return 0;
}
