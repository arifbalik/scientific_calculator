#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "includes.h"

#define GETSV(bstr, estr) strndup(estr, bstr - estr)
#define GETFV(bstr, estr) atof(GETSV(bstr, estr))
#define GETIV(bstr, estr) atoi(GETSV(bstr, estr))

const char *YYCURSOR;
const char *exsp;
token_info tkn;

static int fch = 0; /* flag to indicate first variable name in the query line */

int lex(char *equery)
{
	const char *YYMARKER, *o1, *o2, *o3, *o4;

	if (YYCURSOR >= equery) {
		return EOL;
	}
	/*!stags:re2c format = 'const char *@@;'; */
	/*!re2c
	re2c:define:YYCTYPE = char;
	re2c:yyfill:enable = 0;

	int = [0-9]+;
	float = [0-9]+('.'[0-9]+)('e'[+-]?[0-9]+)? ;
	var = [A-Z]+;
	*/

	/*!re2c

	oct = [0-9]{1,3};
        dot = ".";

        @o1 int @o2 {
		sprintf(tkn.name, "%.*s%.*s",(int)(o2 - o1), o1);
            return INT;
        }


	float {
		//tkn.val = GETFV(YYCURSOR, exsp);
                return FLOAT;
	}
	var {
                //strcpy(tkn.name,GETSV(YYCURSOR, exsp));
		if(fch == 0){
			fch = 1;
			//strcpy(fvar, tkn.name);
		}
		return VAR;
	}


	"+" { return PLUS; }
	"-" { return MINUS;  }
	"*" { return MULT; }
	"/" { return DIV; }
	"=" { return EQ; }
	"(" { return LPAREN;}
	")" {return RPAREN;}
        "list" {return LIST; }
	"quit" {return QUIT;}
	*   { return QUIT; }


	"cos" {return COS;}
	"acos" {return ACOS;}
	"cosh" {return COSH;}

	"sin" {return SIN;}
	"asin" {return ASIN;}
	"sinh" {return SINH;}

	"tan" {return TAN;}
	"atan" {return ATAN;}
	"tanh" {return TANH;}

	"cot" {return COT;}


	"exp" {return EXP;}
	"log" {return LOG;}
	"ln" {return LN;}

	"pow" {return POW;}
	"sqrt" {return SQRT;}
	"cbrt" {return CBRT;}

	"ceil" {return CEIL;}
	"floor" {return FLOOR;}
	"mod" {return MOD;}

	"abs" {return ABS;}

	"," { return COMMA; }



	"pi" {return PI;}


	*/
}

int main()
{
	char *query = "125";
	char *equery;
	void *parser;
	int token = -3;
	char tk[30];

	//parser = ParseAlloc(malloc);

	equery = (char *)(((char *)query) + strlen(query));
	YYCURSOR = exsp = query;

	while (token != EOL) {
		token = lex(equery);
		sprintf(tk, "%d\n", token);
		switch (token) {
		case PI:
			puts("PI=3.14\n");
			break;
		case INT:
			sprintf(tk, "INT val=%f\n", atof(tkn.name));
			puts(tk);
			break;
		case EOL:
			//puts("EOL\n");
			break;
		default:
			puts("Error\n");
			break;
		}
		//puts(tk);
		//Parse(parser, token, *tkn);
		exsp = YYCURSOR;
	}
	fch = 0;
	tkn.val = 0;
	strcpy(tkn.name, " ");
	token = -3;

	//ParseFree(parser, free);
	return (0);
}
