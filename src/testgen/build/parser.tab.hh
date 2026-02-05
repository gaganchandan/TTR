/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_PARSER_TAB_HH_INCLUDED
# define YY_YY_BUILD_PARSER_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING_LITERAL = 259,          /* STRING_LITERAL  */
    NUMBER = 260,                  /* NUMBER  */
    TRUE = 261,                    /* TRUE  */
    FALSE = 262,                   /* FALSE  */
    COLON = 263,                   /* COLON  */
    ARROW = 264,                   /* ARROW  */
    BIG_ARROW = 265,               /* BIG_ARROW  */
    SEMICOLON = 266,               /* SEMICOLON  */
    LPAREN = 267,                  /* LPAREN  */
    RPAREN = 268,                  /* RPAREN  */
    LBRACE = 269,                  /* LBRACE  */
    RBRACE = 270,                  /* RBRACE  */
    LBRACKET = 271,                /* LBRACKET  */
    RBRACKET = 272,                /* RBRACKET  */
    COMMA = 273,                   /* COMMA  */
    EQUALS = 274,                  /* EQUALS  */
    LT = 275,                      /* LT  */
    GT = 276,                      /* GT  */
    PRECONDITION = 277,            /* PRECONDITION  */
    CALL = 278,                    /* CALL  */
    POSTCONDITION = 279,           /* POSTCONDITION  */
    TYPE_STRING = 280,             /* TYPE_STRING  */
    TYPE_INT = 281,                /* TYPE_INT  */
    TYPE_BOOL = 282,               /* TYPE_BOOL  */
    TYPE_VOID = 283,               /* TYPE_VOID  */
    TYPE_MAP = 284,                /* TYPE_MAP  */
    TYPE_SET = 285,                /* TYPE_SET  */
    TYPE_TUPLE = 286,              /* TYPE_TUPLE  */
    NIL = 287,                     /* NIL  */
    OK = 288                       /* OK  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "language/parser.yy"

    int intVal;
    std::string* stringVal;
    TypeExpr* typeExpr;
    Expr* expr;
    Var* var;
    FuncCall* funcCall;
    APIcall* apiCall;
    std::vector<std::unique_ptr<Expr>>* exprList;
    std::vector<std::unique_ptr<TypeExpr>>* typeList;
    std::vector<std::pair<std::unique_ptr<Var>, std::unique_ptr<Expr>>>* mappings;
    Decl* decl;
    APIFuncDecl* funcDecl;
    Init* init;
    Spec* spec;
    API* api;
    HTTPResponseCode httpCode;

#line 116 "build/parser.tab.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_HH_INCLUDED  */
