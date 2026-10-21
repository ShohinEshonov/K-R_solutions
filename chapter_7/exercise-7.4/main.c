#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define LOCAL_FMT 100

void miniscanf(char *fmt, ...);

int main()
{
	int x;
	float f;
	char ch, str[100];
	unsigned int u;

	//some tests 
	printf("INT: d\n");
	miniscanf("%d", &x);
	printf("%d\n", x);
	
	printf("INT: i\n");
	miniscanf("%i", &x);
	printf("%i\n", x);

	printf("INT: x\n");
	miniscanf("%x", &x);
	printf("%x\n", x);

	printf("INT: o\n");
	miniscanf("%o", &x);
	printf("%o\n", x);
	
	printf("CHAR: c\n");
	miniscanf("%c", &ch);
	printf("%c\n", ch);

	printf("STRING: s\n");
	miniscanf("%s", str);
	printf("%s\n", str);

	printf("FLOAT: f\n");
	miniscanf("%f", &f);
	printf("%f\n", f);

	printf("UNSIGNED: u\n");
	miniscanf("%u", &u);
	printf("%u\n", u);

	
	int year, month, day;
	printf("DATE FORMAT: yy/mm/dd\n");
	miniscanf("%d/%d/%d", &year, &month, &day);
	printf("%d/%d/%d\n", year, month, day);

	printf("DATE FORMAT: Day: yy Month: mm Year: yy\n");
	miniscanf("Day: %d Month: %d Year: %d\n", &day, &month, &year);
	printf("Day: %d Month: %d Year: %d\n", day, month, year);	

}

void miniscanf(char *fmt, ...) 
{
	va_list ap;
	char *p;
	char new_fmt[LOCAL_FMT];
	int fmt_p = 0;
	
	int *ival;
	float *fval;
	unsigned *uval;
	char *chval, *sval;
	
	va_start(ap, fmt);
	for(p = fmt; *p; p++) {
		if(*p != '%') {
			new_fmt[fmt_p++] = *p;
			continue;
		}

		new_fmt[fmt_p++] = *p;
		while(*(++p) && !isalpha(*p))
			new_fmt[fmt_p++] = *p;
		new_fmt[fmt_p++] = *p;
		new_fmt[fmt_p] = '\0';
		switch(*p) 
		{
			case 'x':
			case 'o':
			case 'i':
			case 'd':
				ival = va_arg(ap, int *);
				scanf(new_fmt, ival);
				break;
			
			case 'u':
				uval = va_arg(ap, unsigned *);
				scanf(new_fmt, uval);
				break;

			case 'c':
				chval = va_arg(ap, char *);
				scanf(new_fmt, chval);
				break;

			case 's':
				sval = va_arg(ap, char *);
				scanf(new_fmt, sval);
				break;

			case 'f':
				fval =  va_arg(ap, float *);	
				scanf(new_fmt, fval);
				break;

			default:
				scanf(new_fmt);
				break;
		}
		fmt_p = 0;
	}
	va_end(ap);
}
