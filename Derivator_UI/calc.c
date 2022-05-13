#include <stdio.h>		/* sprdoublef */
#include <stdlib.h>
#define INVALID		-0x7fffffff

char *skipspace(char *p);
double getnum(char **pp, int priority);

char *skipspace(char *p)
{
	for (; *p == ' '; p++) { }	/* 스페이스를 건너 뛴다 */
	return p;
}

double getnum(char **pp, int priority)
{
	char *p = *pp;
	double i = INVALID, j;
	p = skipspace(p);

	/* 단항 연산자 */
	if (*p == '+') {
		p = skipspace(p + 1);
		i = getnum(&p, 0);
	} else if (*p == '-') {
		p = skipspace(p + 1);
		i = getnum(&p, 0);
		if (i != INVALID) {
			i = - i;
		}
	} else if (*p == '(') {	/* 괄호 */
		p = skipspace(p + 1);
		i = getnum(&p, 9);
		if (*p == ')') {
			p = skipspace(p + 1);
		} else {
			i = INVALID;
		}
	} else if ('0' <= *p && *p <= '9') { /* 수치 */
		i = strtod(p, &p);
	} else { /* 에러 */
		i = INVALID;
	}

	/* 2항연산자 */
	for (;;) {
		if (i == INVALID) {
			break;
		}
		p = skipspace(p);
		if (*p == '+' && priority > 2) {
			p = skipspace(p + 1);
			j = getnum(&p, 2);
			if (j != INVALID) {
				i += j;
			} else {
				i = INVALID;
			}
		} else if (*p == '-' && priority > 2) {
			p = skipspace(p + 1);
			j = getnum(&p, 2);
			if (j != INVALID) {
				i -= j;
			} else {
				i = INVALID;
			}
		} else if (*p == '*' && priority > 1) {
			p = skipspace(p + 1);
			j = getnum(&p, 1);
			if (j != INVALID) {
				i *= j;
			} else {
				i = INVALID;
			}
		} else if (*p == '/' && priority > 1) {
			p = skipspace(p + 1);
			j = getnum(&p, 1);
			if (j != INVALID && j != 0) {
				i /= j;
			} else {
				i = INVALID;
			}

		} else {
			break;
		}
	}
	p = skipspace(p);
	*pp = p;
	return i;
}
