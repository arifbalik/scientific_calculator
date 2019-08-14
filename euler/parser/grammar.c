/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
#include <assert.h>
/************ Begin %include sections from the grammar ************************/
#line 1 "euler/parser/grammar.y"

#include <assert.h>
#include "tokenizer.h"
#line 33 "euler/parser/grammar.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    ParseCTX_*         As ParseARG_ except for %extra_context
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYNTOKEN           Number of terminal symbols
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
**    YY_MIN_REDUCE      Minimum value for reduce actions
**    YY_MAX_REDUCE      Maximum value for reduce actions
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 26
#define YYACTIONTYPE unsigned char
#define YYWILDCARD 19
#define ParseTOKENTYPE  double 
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ersl_t *euler ;
#define ParseARG_PDECL , ersl_t *euler 
#define ParseARG_PARAM ,euler 
#define ParseARG_FETCH  ersl_t *euler =yypParser->euler ;
#define ParseARG_STORE yypParser->euler =euler ;
#define ParseCTX_SDECL
#define ParseCTX_PDECL
#define ParseCTX_PARAM
#define ParseCTX_FETCH
#define ParseCTX_STORE
#define YYNSTATE             43
#define YYNRULE              23
#define YYNTOKEN             22
#define YY_MAX_SHIFT         42
#define YY_MIN_SHIFTREDUCE   43
#define YY_MAX_SHIFTREDUCE   65
#define YY_ERROR_ACTION      66
#define YY_ACCEPT_ACTION     67
#define YY_NO_ACTION         68
#define YY_MIN_REDUCE        69
#define YY_MAX_REDUCE        91
/************* End control #defines *******************************************/
#define YY_NLOOKAHEAD ((int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])))

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X.
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (344)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    67,   32,   40,   29,   31,   41,   29,   83,   83,   83,
 /*    10 */    83,   83,    9,    7,    5,   22,    6,   33,   83,   29,
 /*    20 */    83,   78,   78,   78,   78,   78,   78,   78,   78,   78,
 /*    30 */    78,   34,   78,   29,   78,   82,   82,   82,   82,   82,
 /*    40 */    82,   82,   82,   82,   82,   35,   82,   29,   82,   84,
 /*    50 */    84,   84,   84,   84,    9,    7,    5,   22,    6,   23,
 /*    60 */    84,   29,   84,   85,   85,   85,   85,   85,   85,   85,
 /*    70 */    85,   85,    6,   24,   85,   29,   85,   91,   91,   91,
 /*    80 */    91,   91,   91,   91,   91,   91,   91,   25,   91,   29,
 /*    90 */    91,   90,   90,   90,   90,   90,   90,   90,   90,   90,
 /*   100 */    90,   26,   90,   29,   90,   89,   89,   89,   89,   89,
 /*   110 */    89,   89,   89,   89,   89,   19,   89,   29,   89,   88,
 /*   120 */    88,   88,   88,   88,   88,   88,   88,   88,    6,   27,
 /*   130 */    88,   29,   88,   87,   87,   87,   87,   87,   87,   87,
 /*   140 */    87,   87,   87,   18,   87,   29,   87,   86,   86,   86,
 /*   150 */    86,   86,   86,   86,   86,   86,    6,   36,   86,   29,
 /*   160 */    86,   81,   81,   81,   81,   81,    9,    7,    5,   22,
 /*   170 */     6,   15,   81,   29,   81,   80,   80,   80,   80,   80,
 /*   180 */     9,    7,    5,   22,    6,   37,   80,   29,   80,   79,
 /*   190 */    79,   79,   79,   79,   79,   79,   79,   79,   79,   70,
 /*   200 */    79,   39,   79,   77,   77,   77,   77,   77,   77,   77,
 /*   210 */    77,   77,   77,   16,   77,   69,   77,   76,   76,   76,
 /*   220 */    76,   76,   76,   76,   76,   76,   76,   68,   76,   68,
 /*   230 */    76,   14,    3,   38,   13,   11,    9,    7,    5,   22,
 /*   240 */     6,   68,   17,   14,    3,   38,   13,   11,    9,    7,
 /*   250 */     5,   22,    6,   12,    4,   68,   42,   13,   11,    9,
 /*   260 */     7,    5,   22,    6,   68,   75,   68,   75,   13,   11,
 /*   270 */     9,    7,    5,   22,    6,   68,   73,   68,   73,   13,
 /*   280 */    11,    9,    7,    5,   22,    6,   68,   74,   68,   74,
 /*   290 */    13,   11,    9,    7,    5,   22,    6,   68,   72,   68,
 /*   300 */    72,   13,   11,    9,    7,    5,   22,    6,   68,   71,
 /*   310 */    68,   71,   20,   21,   68,   28,   30,   68,   68,    2,
 /*   320 */     8,   10,   68,   68,   20,   21,   68,   28,   30,   68,
 /*   330 */    68,    1,    8,   10,   68,   68,   68,   68,   68,   68,
 /*   340 */    68,   68,   68,    1,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    22,   23,   24,   25,   23,   24,   25,    7,    8,    9,
 /*    10 */    10,   11,   12,   13,   14,   15,   16,   23,   18,   25,
 /*    20 */    20,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    30 */    16,   23,   18,   25,   20,    7,    8,    9,   10,   11,
 /*    40 */    12,   13,   14,   15,   16,   23,   18,   25,   20,    7,
 /*    50 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   23,
 /*    60 */    18,   25,   20,    7,    8,    9,   10,   11,   12,   13,
 /*    70 */    14,   15,   16,   23,   18,   25,   20,    7,    8,    9,
 /*    80 */    10,   11,   12,   13,   14,   15,   16,   23,   18,   25,
 /*    90 */    20,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   100 */    16,   23,   18,   25,   20,    7,    8,    9,   10,   11,
 /*   110 */    12,   13,   14,   15,   16,   23,   18,   25,   20,    7,
 /*   120 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   23,
 /*   130 */    18,   25,   20,    7,    8,    9,   10,   11,   12,   13,
 /*   140 */    14,   15,   16,   23,   18,   25,   20,    7,    8,    9,
 /*   150 */    10,   11,   12,   13,   14,   15,   16,   23,   18,   25,
 /*   160 */    20,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   170 */    16,   23,   18,   25,   20,    7,    8,    9,   10,   11,
 /*   180 */    12,   13,   14,   15,   16,   23,   18,   25,   20,    7,
 /*   190 */     8,    9,   10,   11,   12,   13,   14,   15,   16,    0,
 /*   200 */    18,   20,   20,    7,    8,    9,   10,   11,   12,   13,
 /*   210 */    14,   15,   16,   18,   18,    0,   20,    7,    8,    9,
 /*   220 */    10,   11,   12,   13,   14,   15,   16,   26,   18,   26,
 /*   230 */    20,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   240 */    16,   26,   18,    7,    8,    9,   10,   11,   12,   13,
 /*   250 */    14,   15,   16,    7,    8,   26,   20,   10,   11,   12,
 /*   260 */    13,   14,   15,   16,   26,   18,   26,   20,   10,   11,
 /*   270 */    12,   13,   14,   15,   16,   26,   18,   26,   20,   10,
 /*   280 */    11,   12,   13,   14,   15,   16,   26,   18,   26,   20,
 /*   290 */    10,   11,   12,   13,   14,   15,   16,   26,   18,   26,
 /*   300 */    20,   10,   11,   12,   13,   14,   15,   16,   26,   18,
 /*   310 */    26,   20,    2,    3,   26,    5,    6,   26,   26,    9,
 /*   320 */    10,   11,   26,   26,    2,    3,   26,    5,    6,   26,
 /*   330 */    26,   21,   10,   11,   26,   26,   26,   26,   26,   26,
 /*   340 */    26,   26,   26,   21,   26,   26,   26,
};
#define YY_SHIFT_COUNT    (42)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (322)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   310,  310,  322,  322,  322,  322,  322,  322,  322,  322,
 /*    10 */   322,  322,  322,  322,  322,    0,   14,   28,   42,   56,
 /*    20 */    70,   84,   98,  112,  126,  140,  154,  168,  182,  196,
 /*    30 */   210,  224,  236,  247,  258,  269,  280,  291,  246,  199,
 /*    40 */   181,  195,  215,
};
#define YY_REDUCE_COUNT (14)
#define YY_REDUCE_MIN   (-22)
#define YY_REDUCE_MAX   (162)
static const short yy_reduce_ofst[] = {
 /*     0 */   -22,  -19,   -6,    8,   22,   36,   50,   64,   78,   92,
 /*    10 */   106,  120,  134,  148,  162,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */    66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
 /*    10 */    66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
 /*    20 */    66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
 /*    30 */    66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
 /*    40 */    66,   66,   66,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.
** If a construct like the following:
**
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  ParseARG_SDECL                /* A place to hold %extra_argument */
  ParseCTX_SDECL                /* A place to hold %extra_context */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
  yyStackEntry *yystackEnd;            /* Last entry in the stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/*
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#if defined(YYCOVERAGE) || !defined(NDEBUG)
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = {
  /*    0 */ "$",
  /*    1 */ "EQ",
  /*    2 */ "INT",
  /*    3 */ "FLOAT",
  /*    4 */ "UNKNOWN",
  /*    5 */ "CONST",
  /*    6 */ "LETTER",
  /*    7 */ "AND",
  /*    8 */ "OR",
  /*    9 */ "NOT",
  /*   10 */ "PLUS",
  /*   11 */ "MINUS",
  /*   12 */ "MULT",
  /*   13 */ "DIV",
  /*   14 */ "MOD",
  /*   15 */ "FACT",
  /*   16 */ "EXP",
  /*   17 */ "LAPREN",
  /*   18 */ "RPAREN",
  /*   19 */ "ANY",
  /*   20 */ "EOQ",
  /*   21 */ "LPAREN",
  /*   22 */ "query",
  /*   23 */ "elar",
  /*   24 */ "boolean",
  /*   25 */ "number",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "query ::= elar EOQ",
 /*   1 */ "query ::= boolean EOQ",
 /*   2 */ "boolean ::= elar AND elar",
 /*   3 */ "boolean ::= elar NOT AND elar",
 /*   4 */ "boolean ::= elar OR elar",
 /*   5 */ "boolean ::= elar NOT OR elar",
 /*   6 */ "boolean ::= NOT elar",
 /*   7 */ "elar ::= LETTER",
 /*   8 */ "elar ::= number",
 /*   9 */ "elar ::= LPAREN boolean RPAREN",
 /*  10 */ "elar ::= CONST",
 /*  11 */ "elar ::= MINUS elar",
 /*  12 */ "elar ::= PLUS elar",
 /*  13 */ "elar ::= LPAREN elar RPAREN",
 /*  14 */ "elar ::= elar PLUS elar",
 /*  15 */ "elar ::= elar MINUS elar",
 /*  16 */ "elar ::= elar MULT elar",
 /*  17 */ "elar ::= elar DIV elar",
 /*  18 */ "elar ::= elar EXP elar",
 /*  19 */ "elar ::= elar MOD elar",
 /*  20 */ "elar ::= elar FACT",
 /*  21 */ "number ::= FLOAT",
 /*  22 */ "number ::= INT",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0;
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void ParseInit(void *yypRawParser ParseCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  ParseCTX_STORE
#ifdef YYTRACKMAXSTACKDEPTH
  yypParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  yypParser->yytos = NULL;
  yypParser->yystack = NULL;
  yypParser->yystksz = 0;
  if( yyGrowStack(yypParser) ){
    yypParser->yystack = &yypParser->yystk0;
    yypParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  yypParser->yytos = yypParser->yystack;
  yypParser->yystack[0].stateno = 0;
  yypParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  yypParser->yystackEnd = &yypParser->yystack[YYSTACKDEPTH-1];
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/*
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
yyParser yypParser[sizeof(yyParser)];

void *ParseAlloc(ParseCTX_PDECL){

   printf("size of yyparser %ld\n", sizeof(yyParser) );
   ParseCTX_STORE
   ParseInit(yypParser ParseCTX_PARAM);

  return (void*)yypParser;
}
#endif /* Parse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH
  ParseCTX_FETCH
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
      /* Default NON-TERMINAL Destructor */
    case 22: /* query */
    case 23: /* elar */
    case 24: /* boolean */
    case 25: /* number */
{
#line 22 "euler/parser/grammar.y"

        euler->type = euler->type;

#line 591 "euler/parser/grammar.c"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void ParseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/*
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseFree(
  void *p                    /* The parser to be deleted */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  ParseFinalize(p);
  //(*freeProc)(p);
}
#endif /* Parse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/* This array of booleans keeps track of the parser statement
** coverage.  The element yycoverage[X][Y] is set when the parser
** is in state X and has a lookahead token Y.  In a well-tested
** systems, every element of this matrix should end up being set.
*/
#if defined(YYCOVERAGE)
static unsigned char yycoverage[YYNSTATE][YYNTOKEN];
#endif

/*
** Write into out a description of every state/lookahead combination that
**
**   (1)  has not been used by the parser, and
**   (2)  is not a syntax error.
**
** Return the number of missed state/lookahead combinations.
*/
#if defined(YYCOVERAGE)
int ParseCoverage(FILE *out){
  int stateno, iLookAhead, i;
  int nMissed = 0;
  for(stateno=0; stateno<YYNSTATE; stateno++){
    i = yy_shift_ofst[stateno];
    for(iLookAhead=0; iLookAhead<YYNTOKEN; iLookAhead++){
      if( yy_lookahead[i+iLookAhead]!=iLookAhead ) continue;
      if( yycoverage[stateno][iLookAhead]==0 ) nMissed++;
      if( out ){
        fprintf(out,"State %d lookahead %s %s\n", stateno,
                yyTokenName[iLookAhead],
                yycoverage[stateno][iLookAhead] ? "ok" : "missed");
      }
    }
  }
  return nMissed;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_shift_action(
  YYCODETYPE iLookAhead,    /* The look-ahead token */
  YYACTIONTYPE stateno      /* Current state number */
){
  int i;

  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 );
    /* assert( i+YYNTOKEN<=(int)YY_NLOOKAHEAD ); */
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    if( i>=YY_NLOOKAHEAD || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if(
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          j<(int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])) &&
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      assert( i>=0 && i<sizeof(yy_action)/sizeof(yy_action[0]) );
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_reduce_action(
  YYACTIONTYPE stateno,     /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   ParseARG_FETCH
   ParseCTX_FETCH
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
#line 9 "euler/parser/grammar.y"
printf("stack_overflow\n");
#line 815 "euler/parser/grammar.c"
/******** End %stack_overflow code ********************************************/
   ParseARG_STORE /* Suppress warning about unused %extra_argument var */
   ParseCTX_STORE
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState, const char *zTag){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%s%s '%s', go to state %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%s%s '%s', pending reduce %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState - YY_MIN_REDUCE);
    }
  }
}
#else
# define yyTraceShift(X,Y,Z)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  YYACTIONTYPE yyNewState,      /* The new state to shift in */
  YYCODETYPE yyMajor,           /* The major token to shift in */
  ParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* For rule J, yyRuleInfoLhs[J] contains the symbol on the left-hand side
** of that rule */
static const YYCODETYPE yyRuleInfoLhs[] = {
    22,  /* (0) query ::= elar EOQ */
    22,  /* (1) query ::= boolean EOQ */
    24,  /* (2) boolean ::= elar AND elar */
    24,  /* (3) boolean ::= elar NOT AND elar */
    24,  /* (4) boolean ::= elar OR elar */
    24,  /* (5) boolean ::= elar NOT OR elar */
    24,  /* (6) boolean ::= NOT elar */
    23,  /* (7) elar ::= LETTER */
    23,  /* (8) elar ::= number */
    23,  /* (9) elar ::= LPAREN boolean RPAREN */
    23,  /* (10) elar ::= CONST */
    23,  /* (11) elar ::= MINUS elar */
    23,  /* (12) elar ::= PLUS elar */
    23,  /* (13) elar ::= LPAREN elar RPAREN */
    23,  /* (14) elar ::= elar PLUS elar */
    23,  /* (15) elar ::= elar MINUS elar */
    23,  /* (16) elar ::= elar MULT elar */
    23,  /* (17) elar ::= elar DIV elar */
    23,  /* (18) elar ::= elar EXP elar */
    23,  /* (19) elar ::= elar MOD elar */
    23,  /* (20) elar ::= elar FACT */
    25,  /* (21) number ::= FLOAT */
    25,  /* (22) number ::= INT */
};

/* For rule J, yyRuleInfoNRhs[J] contains the negative of the number
** of symbols on the right-hand side of that rule. */
static const signed char yyRuleInfoNRhs[] = {
   -2,  /* (0) query ::= elar EOQ */
   -2,  /* (1) query ::= boolean EOQ */
   -3,  /* (2) boolean ::= elar AND elar */
   -4,  /* (3) boolean ::= elar NOT AND elar */
   -3,  /* (4) boolean ::= elar OR elar */
   -4,  /* (5) boolean ::= elar NOT OR elar */
   -2,  /* (6) boolean ::= NOT elar */
   -1,  /* (7) elar ::= LETTER */
   -1,  /* (8) elar ::= number */
   -3,  /* (9) elar ::= LPAREN boolean RPAREN */
   -1,  /* (10) elar ::= CONST */
   -2,  /* (11) elar ::= MINUS elar */
   -2,  /* (12) elar ::= PLUS elar */
   -3,  /* (13) elar ::= LPAREN elar RPAREN */
   -3,  /* (14) elar ::= elar PLUS elar */
   -3,  /* (15) elar ::= elar MINUS elar */
   -3,  /* (16) elar ::= elar MULT elar */
   -3,  /* (17) elar ::= elar DIV elar */
   -3,  /* (18) elar ::= elar EXP elar */
   -3,  /* (19) elar ::= elar MOD elar */
   -2,  /* (20) elar ::= elar FACT */
   -1,  /* (21) number ::= FLOAT */
   -1,  /* (22) number ::= INT */
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
**
** The yyLookahead and yyLookaheadToken parameters provide reduce actions
** access to the lookahead token (if any).  The yyLookahead will be YYNOCODE
** if the lookahead token has already been consumed.  As this procedure is
** only called from one place, optimizing compilers will in-line it, which
** means that the extra parameters have no performance impact.
*/
static YYACTIONTYPE yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  ParseTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  ParseCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  YYACTIONTYPE yyact;             /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfoNRhs[yyruleno];
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s], go to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno], yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s].\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno]);
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfoNRhs[yyruleno]==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      /* The call to yyStackOverflow() above pops the stack until it is
      ** empty, causing the main parser loop to exit.  So the return value
      ** is never used and does not matter. */
      return 0;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        /* The call to yyStackOverflow() above pops the stack until it is
        ** empty, causing the main parser loop to exit.  So the return value
        ** is never used and does not matter. */
        return 0;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* query ::= elar EOQ */
#line 29 "euler/parser/grammar.y"
{
        euler->resultn.fraction = yymsp[-1].minor.yy0;
        euler->type = FRACTION;
}
#line 1030 "euler/parser/grammar.c"
        break;
      case 1: /* query ::= boolean EOQ */
#line 34 "euler/parser/grammar.y"
{
        euler->resultn.fraction = yymsp[-1].minor.yy0;
        euler->type = BINARY;
}
#line 1038 "euler/parser/grammar.c"
        break;
      case 2: /* boolean ::= elar AND elar */
#line 40 "euler/parser/grammar.y"
{ yylhsminor.yy0 = (int)yymsp[-2].minor.yy0 & (int)yymsp[0].minor.yy0; }
#line 1043 "euler/parser/grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 3: /* boolean ::= elar NOT AND elar */
#line 41 "euler/parser/grammar.y"
{ yylhsminor.yy0 = ~((int)yymsp[-3].minor.yy0 & (int)yymsp[0].minor.yy0); }
#line 1049 "euler/parser/grammar.c"
  yymsp[-3].minor.yy0 = yylhsminor.yy0;
        break;
      case 4: /* boolean ::= elar OR elar */
#line 42 "euler/parser/grammar.y"
{ yylhsminor.yy0 = (int)yymsp[-2].minor.yy0 | (int)yymsp[0].minor.yy0; }
#line 1055 "euler/parser/grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 5: /* boolean ::= elar NOT OR elar */
#line 43 "euler/parser/grammar.y"
{ yylhsminor.yy0 = ~((int)yymsp[-3].minor.yy0 | (int)yymsp[0].minor.yy0); }
#line 1061 "euler/parser/grammar.c"
  yymsp[-3].minor.yy0 = yylhsminor.yy0;
        break;
      case 6: /* boolean ::= NOT elar */
#line 44 "euler/parser/grammar.y"
{ yymsp[-1].minor.yy0 =  ~(int)yymsp[0].minor.yy0; }
#line 1067 "euler/parser/grammar.c"
        break;
      case 7: /* elar ::= LETTER */
#line 49 "euler/parser/grammar.y"
{ yymsp[0].minor.yy0 = 1; }
#line 1072 "euler/parser/grammar.c"
        break;
      case 8: /* elar ::= number */
      case 10: /* elar ::= CONST */ yytestcase(yyruleno==10);
      case 21: /* number ::= FLOAT */ yytestcase(yyruleno==21);
      case 22: /* number ::= INT */ yytestcase(yyruleno==22);
#line 50 "euler/parser/grammar.y"
{ yylhsminor.yy0 = yymsp[0].minor.yy0;       }
#line 1080 "euler/parser/grammar.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 9: /* elar ::= LPAREN boolean RPAREN */
      case 13: /* elar ::= LPAREN elar RPAREN */ yytestcase(yyruleno==13);
#line 51 "euler/parser/grammar.y"
{ yymsp[-2].minor.yy0 = yymsp[-1].minor.yy0;       }
#line 1087 "euler/parser/grammar.c"
        break;
      case 11: /* elar ::= MINUS elar */
#line 53 "euler/parser/grammar.y"
{ yymsp[-1].minor.yy0 = -yymsp[0].minor.yy0;      }
#line 1092 "euler/parser/grammar.c"
        break;
      case 12: /* elar ::= PLUS elar */
#line 54 "euler/parser/grammar.y"
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;       }
#line 1097 "euler/parser/grammar.c"
        break;
      case 14: /* elar ::= elar PLUS elar */
#line 56 "euler/parser/grammar.y"
{ yylhsminor.yy0 = yymsp[-2].minor.yy0 + yymsp[0].minor.yy0;   }
#line 1102 "euler/parser/grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 15: /* elar ::= elar MINUS elar */
#line 57 "euler/parser/grammar.y"
{ yylhsminor.yy0 = yymsp[-2].minor.yy0 - yymsp[0].minor.yy0;   }
#line 1108 "euler/parser/grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 16: /* elar ::= elar MULT elar */
#line 58 "euler/parser/grammar.y"
{ yylhsminor.yy0 = yymsp[-2].minor.yy0 * yymsp[0].minor.yy0;   }
#line 1114 "euler/parser/grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 17: /* elar ::= elar DIV elar */
#line 59 "euler/parser/grammar.y"
{ yylhsminor.yy0 = (yymsp[0].minor.yy0 != 0) ? (yymsp[-2].minor.yy0 / yymsp[0].minor.yy0) : (euler->status = MTHE); }
#line 1120 "euler/parser/grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 18: /* elar ::= elar EXP elar */
#line 60 "euler/parser/grammar.y"
{ yylhsminor.yy0=yymsp[-2].minor.yy0; for(uint8_t i = 1; i < yymsp[0].minor.yy0; i++) yylhsminor.yy0 *= yymsp[-2].minor.yy0; }
#line 1126 "euler/parser/grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 19: /* elar ::= elar MOD elar */
#line 61 "euler/parser/grammar.y"
{ yylhsminor.yy0 = fmod(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1132 "euler/parser/grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 20: /* elar ::= elar FACT */
#line 62 "euler/parser/grammar.y"
{ yylhsminor.yy0 = 1; for(uint8_t i = yymsp[-1].minor.yy0; i > 0; i--) yylhsminor.yy0 *= i; }
#line 1138 "euler/parser/grammar.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      default:
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfoLhs)/sizeof(yyRuleInfoLhs[0]) );
  yygoto = yyRuleInfoLhs[yyruleno];
  yysize = yyRuleInfoNRhs[yyruleno];
  yyact = yy_find_reduce_action(yymsp[yysize].stateno,(YYCODETYPE)yygoto);

  /* There are no SHIFTREDUCE actions on nonterminals because the table
  ** generator has simplified them to pure REDUCE actions. */
  assert( !(yyact>YY_MAX_SHIFT && yyact<=YY_MAX_SHIFTREDUCE) );

  /* It is not possible for a REDUCE to be followed by an error */
  assert( yyact!=YY_ERROR_ACTION );

  yymsp += yysize+1;
  yypParser->yytos = yymsp;
  yymsp->stateno = (YYACTIONTYPE)yyact;
  yymsp->major = (YYCODETYPE)yygoto;
  yyTraceShift(yypParser, yyact, "... then shift");
  return yyact;
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
#line 10 "euler/parser/grammar.y"
printf("parser failed\n");
#line 1185 "euler/parser/grammar.c"
/************ End %parse_failure code *****************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  ParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
/************ End %syntax_error code ******************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
/*********** End %parse_accept code *******************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  YYACTIONTYPE yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser = (yyParser*)yyp;  /* The parser */
  ParseCTX_FETCH
  ParseARG_STORE

  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif

  yyact = yypParser->yytos->stateno;
#ifndef NDEBUG
  if( yyTraceFILE ){
    if( yyact < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    assert( yyact==yypParser->yytos->stateno );
    yyact = yy_find_shift_action((YYCODETYPE)yymajor,yyact);
    if( yyact >= YY_MIN_REDUCE ){
      yyact = yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,
                        yyminor ParseCTX_PARAM);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,(YYCODETYPE)yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      break;
    }else if( yyact==YY_ACCEPT_ACTION ){
      yypParser->yytos--;
      yy_accept(yypParser);
      return;
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) > YY_MAX_SHIFTREDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
      if( yymajor==YYNOCODE ) break;
      yyact = yypParser->yytos->stateno;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      break;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      break;
#endif
    }
  }while( yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}

/*
** Return the fallback token corresponding to canonical token iToken, or
** 0 if iToken has no fallback.
*/
int ParseFallback(int iToken){
#ifdef YYFALLBACK
  if( iToken<(int)(sizeof(yyFallback)/sizeof(yyFallback[0])) ){
    return yyFallback[iToken];
  }
#else
  (void)iToken;
#endif
  return 0;
}
