/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "language/parser.yy"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ast.hh"

extern int yylex();
extern int yylineno;
void yyerror(const char* s);

// Root of our AST
Spec* astRoot = nullptr;

// Helper variables for building the AST
std::vector<std::unique_ptr<Decl>> globals;
std::vector<std::unique_ptr<Init>> inits;
std::vector<std::unique_ptr<APIFuncDecl>> functions;
std::vector<std::unique_ptr<API>> apis;


#line 93 "build/parser.tab.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 4,             /* STRING_LITERAL  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_TRUE = 6,                       /* TRUE  */
  YYSYMBOL_FALSE = 7,                      /* FALSE  */
  YYSYMBOL_COLON = 8,                      /* COLON  */
  YYSYMBOL_ARROW = 9,                      /* ARROW  */
  YYSYMBOL_BIG_ARROW = 10,                 /* BIG_ARROW  */
  YYSYMBOL_SEMICOLON = 11,                 /* SEMICOLON  */
  YYSYMBOL_LPAREN = 12,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 13,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 14,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 15,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 16,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 17,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_EQUALS = 19,                    /* EQUALS  */
  YYSYMBOL_LT = 20,                        /* LT  */
  YYSYMBOL_GT = 21,                        /* GT  */
  YYSYMBOL_PRECONDITION = 22,              /* PRECONDITION  */
  YYSYMBOL_CALL = 23,                      /* CALL  */
  YYSYMBOL_POSTCONDITION = 24,             /* POSTCONDITION  */
  YYSYMBOL_TYPE_STRING = 25,               /* TYPE_STRING  */
  YYSYMBOL_TYPE_INT = 26,                  /* TYPE_INT  */
  YYSYMBOL_TYPE_BOOL = 27,                 /* TYPE_BOOL  */
  YYSYMBOL_TYPE_VOID = 28,                 /* TYPE_VOID  */
  YYSYMBOL_TYPE_MAP = 29,                  /* TYPE_MAP  */
  YYSYMBOL_TYPE_SET = 30,                  /* TYPE_SET  */
  YYSYMBOL_TYPE_TUPLE = 31,                /* TYPE_TUPLE  */
  YYSYMBOL_NIL = 32,                       /* NIL  */
  YYSYMBOL_OK = 33,                        /* OK  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_program = 35,                   /* program  */
  YYSYMBOL_declarations = 36,              /* declarations  */
  YYSYMBOL_init = 37,                      /* init  */
  YYSYMBOL_global_decl = 38,               /* global_decl  */
  YYSYMBOL_func_decl = 39,                 /* func_decl  */
  YYSYMBOL_type_list = 40,                 /* type_list  */
  YYSYMBOL_type_exprs = 41,                /* type_exprs  */
  YYSYMBOL_type_expr = 42,                 /* type_expr  */
  YYSYMBOL_api_block = 43,                 /* api_block  */
  YYSYMBOL_precondition = 44,              /* precondition  */
  YYSYMBOL_api_call = 45,                  /* api_call  */
  YYSYMBOL_postcondition = 46,             /* postcondition  */
  YYSYMBOL_expr = 47,                      /* expr  */
  YYSYMBOL_exprs = 48,                     /* exprs  */
  YYSYMBOL_mappings = 49,                  /* mappings  */
  YYSYMBOL_var = 50,                       /* var  */
  YYSYMBOL_func_call = 51,                 /* func_call  */
  YYSYMBOL_response_code = 52              /* response_code  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   96

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  47
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  95

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    76,    76,    84,    87,    90,    93,    96,   100,   106,
     113,   132,   136,   143,   147,   154,   155,   156,   157,   158,
     161,   164,   171,   182,   183,   186,   195,   207,   208,   212,
     213,   214,   215,   216,   217,   218,   222,   226,   241,   242,
     249,   253,   260,   264,   270,   274,   279,   286
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "STRING_LITERAL", "NUMBER", "TRUE", "FALSE", "COLON", "ARROW",
  "BIG_ARROW", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "COMMA", "EQUALS", "LT", "GT", "PRECONDITION",
  "CALL", "POSTCONDITION", "TYPE_STRING", "TYPE_INT", "TYPE_BOOL",
  "TYPE_VOID", "TYPE_MAP", "TYPE_SET", "TYPE_TUPLE", "NIL", "OK",
  "$accept", "program", "declarations", "init", "global_decl", "func_decl",
  "type_list", "type_exprs", "type_expr", "api_block", "precondition",
  "api_call", "postcondition", "expr", "exprs", "mappings", "var",
  "func_call", "response_code", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-37)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-12)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -37,    14,    12,   -37,     8,    22,    28,    35,   -37,    48,
     -37,   -37,   -37,    37,    15,   -37,   -37,   -37,   -37,    27,
      44,    45,    39,    53,    34,    54,   -37,   -37,   -37,   -37,
      37,    37,    65,   -37,   -37,   -37,   -37,    37,     0,     0,
       0,     0,    63,    56,     6,    68,    32,   -37,    17,   -37,
     -11,    73,   -37,    66,    62,    40,   -37,   -37,    82,    78,
     -37,   -37,    41,   -37,   -37,    37,   -37,   -37,    65,    37,
       0,   -37,     0,   -37,    54,    77,    37,   -37,   -37,    79,
     -37,    69,   -37,    80,   -37,    37,   -37,    58,   -37,   -37,
      42,   -37,    86,    81,   -37
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       7,     0,     2,     1,     0,     0,     0,     0,     6,     0,
       5,     3,     4,     0,     0,    15,    16,    17,    18,     0,
       0,     0,    10,     9,     0,    44,    30,    31,    32,    33,
       0,     0,     0,    39,     8,    29,    34,    24,     0,     0,
       0,     0,     0,     0,     0,    40,     0,    40,     0,    44,
       0,     0,    23,     0,     0,     0,    13,    12,     0,     0,
      22,    46,     0,    38,    37,     0,    36,    35,     0,     0,
       0,    20,     0,    21,     0,     0,    28,    45,    41,     0,
      42,     0,    14,     0,    27,     0,    19,     0,    43,    47,
       0,    26,     0,     0,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -36,   -37,
     -37,   -37,   -37,   -13,   -23,   -37,   -31,    38,   -37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     5,     6,     7,    22,    55,    23,     8,
      24,    43,    60,    47,    46,    50,    35,    36,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      34,    51,    53,    54,    56,    57,    67,    68,    48,    25,
      26,    27,    28,    29,     3,     4,     9,    45,    30,    61,
      31,    62,    32,    37,    52,    15,    16,    17,    18,    19,
      20,    21,    66,    10,    81,    65,    82,    79,    33,    11,
      25,    26,    27,    28,    29,    64,    12,    38,    41,    30,
      65,    31,    78,    32,    77,    91,    80,    42,    72,    65,
      92,    73,   -11,    84,    39,    40,    44,    13,    49,    33,
      14,    58,    88,    15,    16,    17,    18,    19,    20,    21,
      59,    63,    69,    71,    70,    74,    76,    83,    85,    93,
      86,    89,    87,     0,    94,     0,    75
};

static const yytype_int8 yycheck[] =
{
      13,    32,    38,    39,    40,    41,    17,    18,    31,     3,
       4,     5,     6,     7,     0,     3,     8,    30,    12,    13,
      14,    44,    16,     8,    37,    25,    26,    27,    28,    29,
      30,    31,    15,    11,    70,    18,    72,    68,    32,    11,
       3,     4,     5,     6,     7,    13,    11,    20,     9,    12,
      18,    14,    65,    16,    13,    13,    69,    23,    18,    18,
      18,    21,     9,    76,    20,    20,    12,    19,     3,    32,
      22,     8,    85,    25,    26,    27,    28,    29,    30,    31,
      24,    13,     9,    21,    18,     3,     8,    10,     9,     3,
      21,    33,    12,    -1,    13,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    35,    36,     0,     3,    37,    38,    39,    43,     8,
      11,    11,    11,    19,    22,    25,    26,    27,    28,    29,
      30,    31,    40,    42,    44,     3,     4,     5,     6,     7,
      12,    14,    16,    32,    47,    50,    51,     8,    20,    20,
      20,     9,    23,    45,    12,    47,    48,    47,    48,     3,
      49,    50,    47,    42,    42,    41,    42,    42,     8,    24,
      46,    13,    48,    13,    13,    18,    15,    17,    18,     9,
      18,    21,    18,    21,     3,    51,     8,    13,    47,    50,
      47,    42,    42,    10,    47,     9,    21,    12,    47,    33,
      52,    13,    18,     3,    13
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    36,    36,    36,    37,    38,
      39,    40,    40,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    43,    44,    44,    45,    45,    46,    46,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      48,    48,    49,    49,    50,    51,    51,    52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     3,     3,     2,     0,     4,     3,
       3,     1,     3,     1,     3,     1,     1,     1,     1,     6,
       4,     4,     5,     3,     2,     9,     7,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     1,
       1,     3,     3,     5,     1,     4,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declarations  */
#line 76 "language/parser.yy"
                 { 
        astRoot = new Spec(std::move(globals), std::move(inits), 
                           std::move(functions), std::move(apis));
        (yyval.spec) = astRoot;
    }
#line 1462 "build/parser.tab.cc"
    break;

  case 3: /* declarations: declarations global_decl SEMICOLON  */
#line 84 "language/parser.yy"
                                       {
        globals.push_back(std::unique_ptr<Decl>((yyvsp[-1].decl)));
    }
#line 1470 "build/parser.tab.cc"
    break;

  case 4: /* declarations: declarations func_decl SEMICOLON  */
#line 87 "language/parser.yy"
                                       {
        functions.push_back(std::unique_ptr<APIFuncDecl>((yyvsp[-1].funcDecl)));
    }
#line 1478 "build/parser.tab.cc"
    break;

  case 5: /* declarations: declarations init SEMICOLON  */
#line 90 "language/parser.yy"
                                  {
        inits.push_back(std::unique_ptr<Init>((yyvsp[-1].init)));
    }
#line 1486 "build/parser.tab.cc"
    break;

  case 6: /* declarations: declarations api_block  */
#line 93 "language/parser.yy"
                             {
        apis.push_back(std::unique_ptr<API>((yyvsp[0].api)));
    }
#line 1494 "build/parser.tab.cc"
    break;

  case 7: /* declarations: %empty  */
#line 96 "language/parser.yy"
                  {}
#line 1500 "build/parser.tab.cc"
    break;

  case 8: /* init: IDENTIFIER COLON EQUALS expr  */
#line 100 "language/parser.yy"
                                 {
        (yyval.init) = new Init(*(yyvsp[-3].stringVal), std::unique_ptr<Expr>((yyvsp[0].expr)));
    }
#line 1508 "build/parser.tab.cc"
    break;

  case 9: /* global_decl: IDENTIFIER COLON type_expr  */
#line 106 "language/parser.yy"
                               {
        (yyval.decl) = new Decl(*(yyvsp[-2].stringVal), std::unique_ptr<TypeExpr>((yyvsp[0].typeExpr)));
        delete (yyvsp[-2].stringVal);
    }
#line 1517 "build/parser.tab.cc"
    break;

  case 10: /* func_decl: IDENTIFIER COLON type_list  */
#line 113 "language/parser.yy"
                               {
        // For now, default HTTP response code to OK_200
        // std::vector<std::unique_ptr<TypeExpr>> returnTypes;
        std::unique_ptr<TypeExpr> returnType;

        // The last type in the list is the return type
        if (!(yyvsp[0].typeList)->empty()) {
            returnType = std::move((yyvsp[0].typeList)->back());
            (yyvsp[0].typeList)->pop_back();
        }
        
        (yyval.funcDecl) = new APIFuncDecl(*(yyvsp[-2].stringVal), std::move(*(yyvsp[0].typeList)), 
                          std::make_pair(HTTPResponseCode::OK_200, std::move(returnType)));
        delete (yyvsp[-2].stringVal);
        delete (yyvsp[0].typeList);
    }
#line 1538 "build/parser.tab.cc"
    break;

  case 11: /* type_list: type_expr  */
#line 132 "language/parser.yy"
              {
        (yyval.typeList) = new std::vector<std::unique_ptr<TypeExpr>>();
        (yyval.typeList)->push_back(std::unique_ptr<TypeExpr>((yyvsp[0].typeExpr)));
    }
#line 1547 "build/parser.tab.cc"
    break;

  case 12: /* type_list: type_list ARROW type_expr  */
#line 136 "language/parser.yy"
                                {
        (yyvsp[-2].typeList)->push_back(std::unique_ptr<TypeExpr>((yyvsp[0].typeExpr)));
        (yyval.typeList) = (yyvsp[-2].typeList);
    }
#line 1556 "build/parser.tab.cc"
    break;

  case 13: /* type_exprs: type_expr  */
#line 143 "language/parser.yy"
              {
        (yyval.typeList) = new std::vector<std::unique_ptr<TypeExpr>>();
        (yyval.typeList)->push_back(std::unique_ptr<TypeExpr>((yyvsp[0].typeExpr)));
    }
#line 1565 "build/parser.tab.cc"
    break;

  case 14: /* type_exprs: type_exprs COMMA type_expr  */
#line 147 "language/parser.yy"
                                 {
        (yyvsp[-2].typeList)->push_back(std::unique_ptr<TypeExpr>((yyvsp[0].typeExpr)));
        (yyval.typeList) = (yyvsp[-2].typeList);
    }
#line 1574 "build/parser.tab.cc"
    break;

  case 15: /* type_expr: TYPE_STRING  */
#line 154 "language/parser.yy"
                { (yyval.typeExpr) = new TypeConst("string"); }
#line 1580 "build/parser.tab.cc"
    break;

  case 16: /* type_expr: TYPE_INT  */
#line 155 "language/parser.yy"
                { (yyval.typeExpr) = new TypeConst("int"); }
#line 1586 "build/parser.tab.cc"
    break;

  case 17: /* type_expr: TYPE_BOOL  */
#line 156 "language/parser.yy"
                { (yyval.typeExpr) = new TypeConst("bool"); }
#line 1592 "build/parser.tab.cc"
    break;

  case 18: /* type_expr: TYPE_VOID  */
#line 157 "language/parser.yy"
                { (yyval.typeExpr) = new TypeConst("void"); }
#line 1598 "build/parser.tab.cc"
    break;

  case 19: /* type_expr: TYPE_MAP LT type_expr COMMA type_expr GT  */
#line 158 "language/parser.yy"
                                               {
        (yyval.typeExpr) = new MapType(std::unique_ptr<TypeExpr>((yyvsp[-3].typeExpr)), std::unique_ptr<TypeExpr>((yyvsp[-1].typeExpr)));
    }
#line 1606 "build/parser.tab.cc"
    break;

  case 20: /* type_expr: TYPE_SET LT type_expr GT  */
#line 161 "language/parser.yy"
                               {
        (yyval.typeExpr) = new SetType(std::unique_ptr<TypeExpr>((yyvsp[-1].typeExpr)));
    }
#line 1614 "build/parser.tab.cc"
    break;

  case 21: /* type_expr: TYPE_TUPLE LT type_exprs GT  */
#line 164 "language/parser.yy"
                                  {
        (yyval.typeExpr) = new TupleType(std::move(*(yyvsp[-1].typeList)));
        delete (yyvsp[-1].typeList);
    }
#line 1623 "build/parser.tab.cc"
    break;

  case 22: /* api_block: IDENTIFIER COLON precondition api_call postcondition  */
#line 171 "language/parser.yy"
                                                              {
             (yyval.api) = new API(
             std::string(*(yyvsp[-4].stringVal)),
             std::unique_ptr<Expr>((yyvsp[-2].expr)),
             std::unique_ptr<APIcall>((yyvsp[-1].apiCall)),
                std::unique_ptr<Expr>((yyvsp[0].expr))
             );
         }
#line 1636 "build/parser.tab.cc"
    break;

  case 23: /* precondition: PRECONDITION COLON expr  */
#line 182 "language/parser.yy"
                            { (yyval.expr) = (yyvsp[0].expr); }
#line 1642 "build/parser.tab.cc"
    break;

  case 24: /* precondition: PRECONDITION COLON  */
#line 183 "language/parser.yy"
                          { (yyval.expr) = new Bool(true); }
#line 1648 "build/parser.tab.cc"
    break;

  case 25: /* api_call: CALL COLON func_call BIG_ARROW LPAREN response_code COMMA IDENTIFIER RPAREN  */
#line 186 "language/parser.yy"
                                                                                {
        auto funcCall = (yyvsp[-6].funcCall);
        auto responseVar = new Var(*(yyvsp[-1].stringVal));
        
        (yyval.apiCall) = new APIcall(
            std::unique_ptr<FuncCall>(funcCall),
            Response((yyvsp[-3].httpCode), std::unique_ptr<Expr>(responseVar))
        );
    }
#line 1662 "build/parser.tab.cc"
    break;

  case 26: /* api_call: CALL COLON func_call BIG_ARROW LPAREN response_code RPAREN  */
#line 195 "language/parser.yy"
                                                                 {
        auto funcCall = (yyvsp[-4].funcCall);
        auto responseVar = new Var("dummy");
        
        (yyval.apiCall) = new APIcall(
            std::unique_ptr<FuncCall>(funcCall),
            Response((yyvsp[-1].httpCode), std::unique_ptr<Expr>(responseVar))
        );
    }
#line 1676 "build/parser.tab.cc"
    break;

  case 27: /* postcondition: POSTCONDITION COLON expr  */
#line 207 "language/parser.yy"
                             { (yyval.expr) = (yyvsp[0].expr); }
#line 1682 "build/parser.tab.cc"
    break;

  case 28: /* postcondition: POSTCONDITION COLON  */
#line 208 "language/parser.yy"
                           { (yyval.expr) = new Bool(true); }
#line 1688 "build/parser.tab.cc"
    break;

  case 29: /* expr: var  */
#line 212 "language/parser.yy"
        { (yyval.expr) = (yyvsp[0].var); }
#line 1694 "build/parser.tab.cc"
    break;

  case 30: /* expr: STRING_LITERAL  */
#line 213 "language/parser.yy"
                     { (yyval.expr) = new String(*(yyvsp[0].stringVal)); delete (yyvsp[0].stringVal); }
#line 1700 "build/parser.tab.cc"
    break;

  case 31: /* expr: NUMBER  */
#line 214 "language/parser.yy"
             { (yyval.expr) = new Num((yyvsp[0].intVal)); }
#line 1706 "build/parser.tab.cc"
    break;

  case 32: /* expr: TRUE  */
#line 215 "language/parser.yy"
           { (yyval.expr) = new Bool(true); }
#line 1712 "build/parser.tab.cc"
    break;

  case 33: /* expr: FALSE  */
#line 216 "language/parser.yy"
            { (yyval.expr) = new Bool(false); }
#line 1718 "build/parser.tab.cc"
    break;

  case 34: /* expr: func_call  */
#line 217 "language/parser.yy"
                { (yyval.expr) = (yyvsp[0].funcCall); }
#line 1724 "build/parser.tab.cc"
    break;

  case 35: /* expr: LBRACKET mappings RBRACKET  */
#line 218 "language/parser.yy"
                                 {
        (yyval.expr) = new Map(std::move(*(yyvsp[-1].mappings)));
        delete (yyvsp[-1].mappings);
    }
#line 1733 "build/parser.tab.cc"
    break;

  case 36: /* expr: LBRACE exprs RBRACE  */
#line 222 "language/parser.yy"
                          {
        (yyval.expr) = new Set(std::move(*(yyvsp[-1].exprList)));
        delete (yyvsp[-1].exprList);
    }
#line 1742 "build/parser.tab.cc"
    break;

  case 37: /* expr: LPAREN exprs RPAREN  */
#line 226 "language/parser.yy"
                          {
        (yyval.expr) = new Tuple(std::move(*(yyvsp[-1].exprList)));
        delete (yyvsp[-1].exprList);
    }
#line 1751 "build/parser.tab.cc"
    break;

  case 38: /* expr: LPAREN expr RPAREN  */
#line 241 "language/parser.yy"
                         { (yyval.expr) = (yyvsp[-1].expr); }
#line 1757 "build/parser.tab.cc"
    break;

  case 39: /* expr: NIL  */
#line 242 "language/parser.yy"
          {
        // Represent NIL as a special variable
        (yyval.expr) = new Var("NIL");
    }
#line 1766 "build/parser.tab.cc"
    break;

  case 40: /* exprs: expr  */
#line 249 "language/parser.yy"
         {
        (yyval.exprList) = new std::vector<std::unique_ptr<Expr>>();
        (yyval.exprList)->push_back(std::unique_ptr<Expr>((yyvsp[0].expr)));
    }
#line 1775 "build/parser.tab.cc"
    break;

  case 41: /* exprs: exprs COMMA expr  */
#line 253 "language/parser.yy"
                       {
        (yyvsp[-2].exprList)->push_back(std::unique_ptr<Expr>((yyvsp[0].expr)));
        (yyval.exprList) = (yyvsp[-2].exprList);
    }
#line 1784 "build/parser.tab.cc"
    break;

  case 42: /* mappings: var ARROW expr  */
#line 260 "language/parser.yy"
                       {
        (yyval.mappings) = new std::vector<std::pair<std::unique_ptr<Var>, std::unique_ptr<Expr>>>();
        (yyval.mappings)->push_back(std::make_pair(std::unique_ptr<Var>((yyvsp[-2].var)), std::unique_ptr<Expr>((yyvsp[0].expr))));
        }
#line 1793 "build/parser.tab.cc"
    break;

  case 43: /* mappings: mappings COMMA var ARROW expr  */
#line 264 "language/parser.yy"
                                    {
        (yyvsp[-4].mappings)->push_back(std::make_pair(std::unique_ptr<Var>((yyvsp[-2].var)), std::unique_ptr<Expr>((yyvsp[0].expr))));
        (yyval.mappings) = (yyvsp[-4].mappings);
        }
#line 1802 "build/parser.tab.cc"
    break;

  case 44: /* var: IDENTIFIER  */
#line 270 "language/parser.yy"
               { (yyval.var) = new Var(*(yyvsp[0].stringVal)); delete (yyvsp[0].stringVal); }
#line 1808 "build/parser.tab.cc"
    break;

  case 45: /* func_call: IDENTIFIER LPAREN exprs RPAREN  */
#line 274 "language/parser.yy"
                                   {
        (yyval.funcCall) = new FuncCall(*(yyvsp[-3].stringVal), std::move(*(yyvsp[-1].exprList)));
        delete (yyvsp[-3].stringVal);
        delete (yyvsp[-1].exprList);
    }
#line 1818 "build/parser.tab.cc"
    break;

  case 46: /* func_call: IDENTIFIER LPAREN RPAREN  */
#line 279 "language/parser.yy"
                               {
        (yyval.funcCall) = new FuncCall(*(yyvsp[-2].stringVal), std::vector<std::unique_ptr<Expr>>());
        delete (yyvsp[-2].stringVal);
    }
#line 1827 "build/parser.tab.cc"
    break;

  case 47: /* response_code: OK  */
#line 286 "language/parser.yy"
       { (yyval.httpCode) = HTTPResponseCode::OK_200; }
#line 1833 "build/parser.tab.cc"
    break;


#line 1837 "build/parser.tab.cc"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 289 "language/parser.yy"


void yyerror(const char* s) {
    std::cerr << "Error (line " << yylineno << "): " << s << std::endl;
}
