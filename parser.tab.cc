// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 27 "parser.yy"

   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <string>
   	
   #include "scanner.hh"

#undef yylex
#define yylex IPL::Parser::scanner.yylex
#define YYDEBUG 1

string fname;
std::map<string,abstract_astnode*> ast;
extern SymbTab gst;
SymbTab *st;
SymbTabEntry* currFunc;
extern datatype createVoidStarType();
std::string currStruct;
extern std::map<string,datatype> predefined;
int LOCAL_OFFSET = 0;
int PARAM_OFFSET = 12;
bool struct_declaration = false;


#line 72 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.yy"
namespace IPL {
#line 165 "parser.tab.cc"

  /// Build a parser object.
  Parser::Parser (Scanner  &scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_struct_specifier: // struct_specifier
      case symbol_kind::S_function_definition: // function_definition
      case symbol_kind::S_compound_statement: // compound_statement
        value.copy< abstract_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_expression: // assignment_expression
        value.copy< assignE_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_statement: // assignment_statement
        value.copy< assignS_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< declaration_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.copy< declaration_list_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarator_arr: // declarator_arr
      case symbol_kind::S_declarator: // declarator
        value.copy< declarator_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarator_list: // declarator_list
        value.copy< declarator_list_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_postfix_expression: // postfix_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.copy< exp_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fun_declarator: // fun_declarator
        value.copy< fun_declarator_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_procedure_call: // procedure_call
      case symbol_kind::S_expression_list: // expression_list
        value.copy< funcall_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_operator: // unary_operator
        value.copy< op_unary_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.copy< parameter_declaration_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.copy< parameter_list_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< seq_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
        value.copy< statement_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INT_CONSTANT: // INT_CONSTANT
      case symbol_kind::S_FLOAT_CONSTANT: // FLOAT_CONSTANT
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_specifier: // type_specifier
        value.copy< type_specifier_class* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_struct_specifier: // struct_specifier
      case symbol_kind::S_function_definition: // function_definition
      case symbol_kind::S_compound_statement: // compound_statement
        value.move< abstract_astnode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_assignment_expression: // assignment_expression
        value.move< assignE_astnode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_assignment_statement: // assignment_statement
        value.move< assignS_astnode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< declaration_class* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.move< declaration_list_class* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_declarator_arr: // declarator_arr
      case symbol_kind::S_declarator: // declarator
        value.move< declarator_class* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_declarator_list: // declarator_list
        value.move< declarator_list_class* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_postfix_expression: // postfix_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.move< exp_astnode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_fun_declarator: // fun_declarator
        value.move< fun_declarator_class* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_procedure_call: // procedure_call
      case symbol_kind::S_expression_list: // expression_list
        value.move< funcall_astnode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_unary_operator: // unary_operator
        value.move< op_unary_astnode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.move< parameter_declaration_class* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< parameter_list_class* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< seq_astnode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
        value.move< statement_astnode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INT_CONSTANT: // INT_CONSTANT
      case symbol_kind::S_FLOAT_CONSTANT: // FLOAT_CONSTANT
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_specifier: // type_specifier
        value.move< type_specifier_class* > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_struct_specifier: // struct_specifier
      case symbol_kind::S_function_definition: // function_definition
      case symbol_kind::S_compound_statement: // compound_statement
        value.YY_MOVE_OR_COPY< abstract_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_expression: // assignment_expression
        value.YY_MOVE_OR_COPY< assignE_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_statement: // assignment_statement
        value.YY_MOVE_OR_COPY< assignS_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< declaration_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.YY_MOVE_OR_COPY< declaration_list_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarator_arr: // declarator_arr
      case symbol_kind::S_declarator: // declarator
        value.YY_MOVE_OR_COPY< declarator_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarator_list: // declarator_list
        value.YY_MOVE_OR_COPY< declarator_list_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_postfix_expression: // postfix_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.YY_MOVE_OR_COPY< exp_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fun_declarator: // fun_declarator
        value.YY_MOVE_OR_COPY< fun_declarator_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_procedure_call: // procedure_call
      case symbol_kind::S_expression_list: // expression_list
        value.YY_MOVE_OR_COPY< funcall_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_operator: // unary_operator
        value.YY_MOVE_OR_COPY< op_unary_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.YY_MOVE_OR_COPY< parameter_declaration_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.YY_MOVE_OR_COPY< parameter_list_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.YY_MOVE_OR_COPY< seq_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
        value.YY_MOVE_OR_COPY< statement_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INT_CONSTANT: // INT_CONSTANT
      case symbol_kind::S_FLOAT_CONSTANT: // FLOAT_CONSTANT
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_specifier: // type_specifier
        value.YY_MOVE_OR_COPY< type_specifier_class* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_struct_specifier: // struct_specifier
      case symbol_kind::S_function_definition: // function_definition
      case symbol_kind::S_compound_statement: // compound_statement
        value.move< abstract_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_expression: // assignment_expression
        value.move< assignE_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_statement: // assignment_statement
        value.move< assignS_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< declaration_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.move< declaration_list_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarator_arr: // declarator_arr
      case symbol_kind::S_declarator: // declarator
        value.move< declarator_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarator_list: // declarator_list
        value.move< declarator_list_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_postfix_expression: // postfix_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.move< exp_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fun_declarator: // fun_declarator
        value.move< fun_declarator_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_procedure_call: // procedure_call
      case symbol_kind::S_expression_list: // expression_list
        value.move< funcall_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_operator: // unary_operator
        value.move< op_unary_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.move< parameter_declaration_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< parameter_list_class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< seq_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
        value.move< statement_astnode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INT_CONSTANT: // INT_CONSTANT
      case symbol_kind::S_FLOAT_CONSTANT: // FLOAT_CONSTANT
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_specifier: // type_specifier
        value.move< type_specifier_class* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_struct_specifier: // struct_specifier
      case symbol_kind::S_function_definition: // function_definition
      case symbol_kind::S_compound_statement: // compound_statement
        value.copy< abstract_astnode* > (that.value);
        break;

      case symbol_kind::S_assignment_expression: // assignment_expression
        value.copy< assignE_astnode* > (that.value);
        break;

      case symbol_kind::S_assignment_statement: // assignment_statement
        value.copy< assignS_astnode* > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< declaration_class* > (that.value);
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.copy< declaration_list_class* > (that.value);
        break;

      case symbol_kind::S_declarator_arr: // declarator_arr
      case symbol_kind::S_declarator: // declarator
        value.copy< declarator_class* > (that.value);
        break;

      case symbol_kind::S_declarator_list: // declarator_list
        value.copy< declarator_list_class* > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_postfix_expression: // postfix_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.copy< exp_astnode* > (that.value);
        break;

      case symbol_kind::S_fun_declarator: // fun_declarator
        value.copy< fun_declarator_class* > (that.value);
        break;

      case symbol_kind::S_procedure_call: // procedure_call
      case symbol_kind::S_expression_list: // expression_list
        value.copy< funcall_astnode* > (that.value);
        break;

      case symbol_kind::S_unary_operator: // unary_operator
        value.copy< op_unary_astnode* > (that.value);
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.copy< parameter_declaration_class* > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.copy< parameter_list_class* > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< seq_astnode* > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
        value.copy< statement_astnode* > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INT_CONSTANT: // INT_CONSTANT
      case symbol_kind::S_FLOAT_CONSTANT: // FLOAT_CONSTANT
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_type_specifier: // type_specifier
        value.copy< type_specifier_class* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_struct_specifier: // struct_specifier
      case symbol_kind::S_function_definition: // function_definition
      case symbol_kind::S_compound_statement: // compound_statement
        value.move< abstract_astnode* > (that.value);
        break;

      case symbol_kind::S_assignment_expression: // assignment_expression
        value.move< assignE_astnode* > (that.value);
        break;

      case symbol_kind::S_assignment_statement: // assignment_statement
        value.move< assignS_astnode* > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< declaration_class* > (that.value);
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        value.move< declaration_list_class* > (that.value);
        break;

      case symbol_kind::S_declarator_arr: // declarator_arr
      case symbol_kind::S_declarator: // declarator
        value.move< declarator_class* > (that.value);
        break;

      case symbol_kind::S_declarator_list: // declarator_list
        value.move< declarator_list_class* > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_postfix_expression: // postfix_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.move< exp_astnode* > (that.value);
        break;

      case symbol_kind::S_fun_declarator: // fun_declarator
        value.move< fun_declarator_class* > (that.value);
        break;

      case symbol_kind::S_procedure_call: // procedure_call
      case symbol_kind::S_expression_list: // expression_list
        value.move< funcall_astnode* > (that.value);
        break;

      case symbol_kind::S_unary_operator: // unary_operator
        value.move< op_unary_astnode* > (that.value);
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        value.move< parameter_declaration_class* > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< parameter_list_class* > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< seq_astnode* > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
        value.move< statement_astnode* > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INT_CONSTANT: // INT_CONSTANT
      case symbol_kind::S_FLOAT_CONSTANT: // FLOAT_CONSTANT
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_type_specifier: // type_specifier
        value.move< type_specifier_class* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        switch (yykind)
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
#line 19 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 928 "parser.tab.cc"
        break;

      case symbol_kind::S_INT_CONSTANT: // INT_CONSTANT
#line 20 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 934 "parser.tab.cc"
        break;

      case symbol_kind::S_FLOAT_CONSTANT: // FLOAT_CONSTANT
#line 21 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 940 "parser.tab.cc"
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
#line 22 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 946 "parser.tab.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_struct_specifier: // struct_specifier
      case symbol_kind::S_function_definition: // function_definition
      case symbol_kind::S_compound_statement: // compound_statement
        yylhs.value.emplace< abstract_astnode* > ();
        break;

      case symbol_kind::S_assignment_expression: // assignment_expression
        yylhs.value.emplace< assignE_astnode* > ();
        break;

      case symbol_kind::S_assignment_statement: // assignment_statement
        yylhs.value.emplace< assignS_astnode* > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< declaration_class* > ();
        break;

      case symbol_kind::S_declaration_list: // declaration_list
        yylhs.value.emplace< declaration_list_class* > ();
        break;

      case symbol_kind::S_declarator_arr: // declarator_arr
      case symbol_kind::S_declarator: // declarator
        yylhs.value.emplace< declarator_class* > ();
        break;

      case symbol_kind::S_declarator_list: // declarator_list
        yylhs.value.emplace< declarator_list_class* > ();
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_postfix_expression: // postfix_expression
      case symbol_kind::S_primary_expression: // primary_expression
        yylhs.value.emplace< exp_astnode* > ();
        break;

      case symbol_kind::S_fun_declarator: // fun_declarator
        yylhs.value.emplace< fun_declarator_class* > ();
        break;

      case symbol_kind::S_procedure_call: // procedure_call
      case symbol_kind::S_expression_list: // expression_list
        yylhs.value.emplace< funcall_astnode* > ();
        break;

      case symbol_kind::S_unary_operator: // unary_operator
        yylhs.value.emplace< op_unary_astnode* > ();
        break;

      case symbol_kind::S_parameter_declaration: // parameter_declaration
        yylhs.value.emplace< parameter_declaration_class* > ();
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        yylhs.value.emplace< parameter_list_class* > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
        yylhs.value.emplace< seq_astnode* > ();
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_selection_statement: // selection_statement
      case symbol_kind::S_iteration_statement: // iteration_statement
        yylhs.value.emplace< statement_astnode* > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INT_CONSTANT: // INT_CONSTANT
      case symbol_kind::S_FLOAT_CONSTANT: // FLOAT_CONSTANT
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_type_specifier: // type_specifier
        yylhs.value.emplace< type_specifier_class* > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // translation_unit: struct_specifier
#line 123 "parser.yy"
        {
		yylhs.value.as < abstract_astnode* > () = yystack_[0].value.as < abstract_astnode* > ();
	}
#line 1286 "parser.tab.cc"
    break;

  case 3: // translation_unit: function_definition
#line 126 "parser.yy"
                         { 
      ast.insert({fname, yystack_[0].value.as < abstract_astnode* > ()});
    }
#line 1294 "parser.tab.cc"
    break;

  case 4: // translation_unit: translation_unit struct_specifier
#line 129 "parser.yy"
    { yylhs.value.as < abstract_astnode* > () = yystack_[1].value.as < abstract_astnode* > (); }
#line 1300 "parser.tab.cc"
    break;

  case 5: // translation_unit: translation_unit function_definition
#line 131 "parser.yy"
    { 
      ast.insert({fname, yystack_[0].value.as < abstract_astnode* > ()});
    }
#line 1308 "parser.tab.cc"
    break;

  case 6: // $@1: %empty
#line 138 "parser.yy"
{
	  st = new SymbTab();
	  currStruct = "struct "+ yystack_[0].value.as < std::string > ();
	  if (gst.search("struct "+ yystack_[0].value.as < std::string > ()) != NULL && gst.search("struct "+ yystack_[0].value.as < std::string > ())->varfun == "struct")
	  {
		  error(yystack_[0].location, "\"" + currStruct + "\"" +  " has a previous definition");
		  
	  }
	  struct_declaration = true;
}
#line 1323 "parser.tab.cc"
    break;

  case 7: // struct_specifier: STRUCT IDENTIFIER $@1 '{' declaration_list '}' ';'
#line 149 "parser.yy"
{
	  struct_declaration = false;
	  currStruct = "";

	  gst.push("struct " + yystack_[5].value.as < std::string > (),
			   new SymbTabEntry("struct", "global", datatype(), (yystack_[2].value.as < declaration_list_class* > ()->offset), 0, st));
	  // push the local symbol table in the global one
}
#line 1336 "parser.tab.cc"
    break;

  case 8: // $@2: %empty
#line 161 "parser.yy"
    { 
	  if (yystack_[1].value.as < type_specifier_class* > ()->structname != "" && gst.search(yystack_[1].value.as < type_specifier_class* > ()->structname)== NULL) error(yystack_[1].location, "\""+ yystack_[1].value.as < type_specifier_class* > ()->structname + "\" " + "not declared");
	  fname = yystack_[0].value.as < fun_declarator_class* > ()->identifier;
      st = new SymbTab();	//create new local symbol table
      datatype dt = createtype(yystack_[1].value.as < type_specifier_class* > (), yystack_[0].value.as < fun_declarator_class* > ()->deref);
		                    // previous declaration error
      if(gst.search(yystack_[0].value.as < fun_declarator_class* > ()->identifier) !=NULL)
      {
        error(yystack_[0].location, "The function \"" + yystack_[0].value.as < fun_declarator_class* > ()->identifier + "\" has a previous definition");
        
      }   
      gst.push(yystack_[0].value.as < fun_declarator_class* > ()->identifier , new SymbTabEntry("fun","global",dt,0,0,st));	// push the local symbol table in the global one
	
      currFunc = gst.search(yystack_[0].value.as < fun_declarator_class* > ()->identifier);
      parameter_declaration_class* param;
      datatype data_type;
      int total_params_size = 0;			
      parameter_list_class* pl = yystack_[0].value.as < fun_declarator_class* > ()->param;
      if(pl!=NULL){
        for(int i=0;i<(int) (pl->param.size());++i)
        {
          total_params_size += ((pl->param)[i]->t).size();
        }
    
        int cumul = 0;
        for(int i=0; 
		i<(int) (pl->param.size());++i)
        {
		  param = (pl->param)[i];
		  data_type = param->t;
		  // struct is not defined
		  if (data_type.type == 3)
		  {
			  SymbTabEntry *temp = gst.search(data_type.structname);
			  if (temp == NULL || temp->varfun != "struct")
			  {
				  error(yystack_[0].location, "\"" + data_type.structname + "\" is not defined");
			  }
		  }
		  // void data type declaration error
		  if (data_type.type == 0 && data_type.deref == 0)
		  {
			error(yystack_[0].location, "Cannot declare the type of a parameter as  \"void\"");
		
		  }
		  if (st->search(param->identifier) != NULL)
		  {
			error(yystack_[0].location, "\"" + param->identifier + "\"  has a previous declaration");
		  }
          cumul += data_type.size();
		  st->push(param->identifier,
			// add the parameter entry into symbol table
			new SymbTabEntry("var", "param", data_type,
			data_type.size(),
			total_params_size + PARAM_OFFSET - cumul, // offset
			NULL));
        }
      }
    }
#line 1400 "parser.tab.cc"
    break;

  case 9: // function_definition: type_specifier fun_declarator $@2 compound_statement
#line 221 "parser.yy"
    {
		yylhs.value.as < abstract_astnode* > ()=yystack_[0].value.as < abstract_astnode* > ();  //When you remove the action in between remember to change $4 to $3
	}
#line 1408 "parser.tab.cc"
    break;

  case 10: // type_specifier: VOID
#line 227 "parser.yy"
         {
      yylhs.value.as < type_specifier_class* > () = new type_specifier_class(VOID_TYPE);
    }
#line 1416 "parser.tab.cc"
    break;

  case 11: // type_specifier: INT
#line 230 "parser.yy"
        {
      yylhs.value.as < type_specifier_class* > () = new type_specifier_class(INT_TYPE);
    }
#line 1424 "parser.tab.cc"
    break;

  case 12: // type_specifier: FLOAT
#line 233 "parser.yy"
          {
      yylhs.value.as < type_specifier_class* > () = new type_specifier_class(FLOAT_TYPE);
    }
#line 1432 "parser.tab.cc"
    break;

  case 13: // type_specifier: STRUCT IDENTIFIER
#line 236 "parser.yy"
                      {
      yylhs.value.as < type_specifier_class* > () = new type_specifier_class(STRUCT_TYPE, "struct "+ yystack_[0].value.as < std::string > ());
  }
#line 1440 "parser.tab.cc"
    break;

  case 14: // fun_declarator: IDENTIFIER '(' parameter_list ')'
#line 242 "parser.yy"
                                       {
      yylhs.value.as < fun_declarator_class* > () = new fun_declarator_class(yystack_[3].value.as < std::string > (),yystack_[1].value.as < parameter_list_class* > ());

    }
#line 1449 "parser.tab.cc"
    break;

  case 15: // fun_declarator: IDENTIFIER '(' ')'
#line 246 "parser.yy"
                       {
      yylhs.value.as < fun_declarator_class* > () = new fun_declarator_class(yystack_[2].value.as < std::string > ());
  }
#line 1457 "parser.tab.cc"
    break;

  case 16: // parameter_list: parameter_declaration
#line 253 "parser.yy"
    {
       yylhs.value.as < parameter_list_class* > () = new parameter_list_class();
	   yylhs.value.as < parameter_list_class* > ()->push(yystack_[0].value.as < parameter_declaration_class* > ());
    }
#line 1466 "parser.tab.cc"
    break;

  case 17: // parameter_list: parameter_list ',' parameter_declaration
#line 259 "parser.yy"
    { 
       yystack_[2].value.as < parameter_list_class* > ()->push(yystack_[0].value.as < parameter_declaration_class* > ());
	   yylhs.value.as < parameter_list_class* > () = yystack_[2].value.as < parameter_list_class* > ();	   		    
    }
#line 1475 "parser.tab.cc"
    break;

  case 18: // parameter_declaration: type_specifier declarator
#line 268 "parser.yy"
    {
      yylhs.value.as < parameter_declaration_class* > () = new parameter_declaration_class(yystack_[1].value.as < type_specifier_class* > (), yystack_[0].value.as < declarator_class* > ());
    }
#line 1483 "parser.tab.cc"
    break;

  case 19: // declarator_arr: IDENTIFIER
#line 277 "parser.yy"
               {
      yylhs.value.as < declarator_class* > ()= new declarator_class(yystack_[0].value.as < std::string > ());
    }
#line 1491 "parser.tab.cc"
    break;

  case 20: // declarator_arr: declarator_arr '[' INT_CONSTANT ']'
#line 281 "parser.yy"
        {
		
    if (stoi(yystack_[1].value.as < std::string > ()) < 0)
    {
    	error(yystack_[1].location, "Size of array is negative");
    }
		
		yystack_[3].value.as < declarator_class* > ()->add_array_index(stoi(yystack_[1].value.as < std::string > ()));		
		yylhs.value.as < declarator_class* > ()=yystack_[3].value.as < declarator_class* > ();  
  }
#line 1506 "parser.tab.cc"
    break;

  case 21: // declarator: declarator_arr
#line 296 "parser.yy"
                  {
   yylhs.value.as < declarator_class* > () = yystack_[0].value.as < declarator_class* > ();
}
#line 1514 "parser.tab.cc"
    break;

  case 22: // declarator: '*' declarator
#line 299 "parser.yy"
                         {
    	yystack_[0].value.as < declarator_class* > ()->addstar();
    	yylhs.value.as < declarator_class* > ()=yystack_[0].value.as < declarator_class* > ();
    }
#line 1523 "parser.tab.cc"
    break;

  case 23: // declaration_list: declaration
#line 307 "parser.yy"
        {
		
    	declarator_class* decl;
    	type_specifier_class* type = yystack_[0].value.as < declaration_class* > ()->type;
    	int curr_offset = LOCAL_OFFSET;
    	declarator_list_class* dl = yystack_[0].value.as < declaration_class* > ()->decl_list;
    	datatype dt;
		for(int i=0;i<(int)(dl->v.size());++i)
		{   
			decl = dl->v[i];
			dt = createtype(type, decl);
			// struct is not defined 
			if(dt.type == STRUCT_TYPE)
			{
				SymbTabEntry* temp = gst.search(dt.structname);
				if(dt.structname==currStruct && dt.deref ==0) {
					error(yystack_[0].location, "\"" + dt.structname + "\" is not defined");
				}

				if(dt.structname==currStruct && dt.deref !=0) {

				}
				else if(temp==NULL || (temp->varfun != "struct")) {
					
					error(yystack_[0].location, "\"" + dt.structname + "\"  is not defined");
				}	
			}
			// void data type declaration error
			if(dt.type==VOID_TYPE && dt.deref == 0)
			{
				error(yystack_[0].location,"Cannot declare variable of type \"void\"" );
			}
			// previous declaration error
			if(st->search(decl->identifier) !=NULL)
			{
				error(yystack_[0].location, "\"" + decl->identifier + "\" has a previous declaration");
			}

			if (!struct_declaration) curr_offset -= dt.size();
			st->push(decl->identifier,					// pushing in the local symbol table
				new SymbTabEntry("var","local",
					dt,
					dt.size(),
					curr_offset,
					NULL));
		    if (struct_declaration) curr_offset += dt.size();	
		}	
		
		yylhs.value.as < declaration_list_class* > () = new declaration_list_class();
		yylhs.value.as < declaration_list_class* > ()->offset=curr_offset;	
    }
#line 1579 "parser.tab.cc"
    break;

  case 24: // declaration_list: declaration_list declaration
#line 358 "parser.yy"
                                   {
		
    	declarator_class* decl;
    	type_specifier_class* type = yystack_[0].value.as < declaration_class* > ()->type;
    	int curr_offset = yystack_[1].value.as < declaration_list_class* > ()->offset;
    	declarator_list_class* dl = yystack_[0].value.as < declaration_class* > ()->decl_list;
    	datatype dt;

		for(int i=0;i<(int)(dl->v.size());++i)
		{
			decl = dl->v[i];
			dt = createtype(type, decl);
			if(dt.type == 3)
			{
				SymbTabEntry* temp = gst.search(dt.structname);
				if(dt.structname==currStruct && dt.deref ==0) {
					error(yystack_[0].location, "\"" + dt.structname + "\" is not defined");
				}
				if(dt.structname==currStruct && dt.deref !=0) {

				}
				else if(temp==NULL || (temp->varfun != "struct")) {

					error(yystack_[0].location, "\"" + dt.structname + "\" is not defined");
				}	
			}
			// void data type declaration error
			if(dt.type==VOID_TYPE && dt.deref == 0)
			{
				error(yystack_[0].location, "Cannot declare variable of type \"void\"");
			}
			// previous declaration error
			if(st->search(decl->identifier) !=NULL)
			{
				error(yystack_[0].location, "\"" + decl->identifier + "\" has a previous declaration");
				exit(1);
			}
			if (!struct_declaration) curr_offset -= dt.size();
			st->push(decl->identifier,					// pushing in the local symbol table
				new SymbTabEntry("var","local",
					dt,
					dt.size(),
					curr_offset,
					NULL));
		    if (struct_declaration) curr_offset += dt.size();	
		}
		yylhs.value.as < declaration_list_class* > () = new declaration_list_class();
		yylhs.value.as < declaration_list_class* > ()->offset=curr_offset;		
    }
#line 1633 "parser.tab.cc"
    break;

  case 25: // declaration: type_specifier declarator_list ';'
#line 410 "parser.yy"
                                          {
		yylhs.value.as < declaration_class* > () = new declaration_class(yystack_[2].value.as < type_specifier_class* > (), yystack_[1].value.as < declarator_list_class* > ());
	}
#line 1641 "parser.tab.cc"
    break;

  case 26: // declarator_list: declarator
#line 416 "parser.yy"
                   {
		yylhs.value.as < declarator_list_class* > () = new declarator_list_class();
		yylhs.value.as < declarator_list_class* > ()->push(yystack_[0].value.as < declarator_class* > ());
	}
#line 1650 "parser.tab.cc"
    break;

  case 27: // declarator_list: declarator_list ',' declarator
#line 421 "parser.yy"
        {
		yystack_[2].value.as < declarator_list_class* > ()->push(yystack_[0].value.as < declarator_class* > ());
		yylhs.value.as < declarator_list_class* > () = yystack_[2].value.as < declarator_list_class* > ();
	}
#line 1659 "parser.tab.cc"
    break;

  case 28: // compound_statement: '{' '}'
#line 428 "parser.yy"
                  {
		yylhs.value.as < abstract_astnode* > ()=new seq_astnode();
    }
#line 1667 "parser.tab.cc"
    break;

  case 29: // compound_statement: '{' statement_list '}'
#line 431 "parser.yy"
                                 {
		yylhs.value.as < abstract_astnode* > ()=yystack_[1].value.as < seq_astnode* > ();
	}
#line 1675 "parser.tab.cc"
    break;

  case 30: // compound_statement: '{' declaration_list '}'
#line 434 "parser.yy"
                                   {
		yylhs.value.as < abstract_astnode* > ()=new seq_astnode();
	}
#line 1683 "parser.tab.cc"
    break;

  case 31: // compound_statement: '{' declaration_list statement_list '}'
#line 438 "parser.yy"
                                              {
		yylhs.value.as < abstract_astnode* > ()=yystack_[1].value.as < seq_astnode* > ();
		
	}
#line 1692 "parser.tab.cc"
    break;

  case 32: // statement_list: statement
#line 446 "parser.yy"
                    {
		yylhs.value.as < seq_astnode* > ()=new seq_astnode();
		yylhs.value.as < seq_astnode* > ()->pushback(yystack_[0].value.as < statement_astnode* > ());

	}
#line 1702 "parser.tab.cc"
    break;

  case 33: // statement_list: statement_list statement
#line 451 "parser.yy"
                              {
		yylhs.value.as < seq_astnode* > ()=yystack_[1].value.as < seq_astnode* > ();
		yylhs.value.as < seq_astnode* > ()->pushback(yystack_[0].value.as < statement_astnode* > ());	
	}
#line 1711 "parser.tab.cc"
    break;

  case 34: // statement: ';'
#line 459 "parser.yy"
           {
		yylhs.value.as < statement_astnode* > () = new empty_astnode();
	  }
#line 1719 "parser.tab.cc"
    break;

  case 35: // statement: '{' statement_list '}'
#line 462 "parser.yy"
                              {
    	yylhs.value.as < statement_astnode* > ()=yystack_[1].value.as < seq_astnode* > ();
    }
#line 1727 "parser.tab.cc"
    break;

  case 36: // statement: selection_statement
#line 465 "parser.yy"
                            {
    	yylhs.value.as < statement_astnode* > ()=yystack_[0].value.as < statement_astnode* > ();
    }
#line 1735 "parser.tab.cc"
    break;

  case 37: // statement: iteration_statement
#line 468 "parser.yy"
                            {
    	yylhs.value.as < statement_astnode* > ()=yystack_[0].value.as < statement_astnode* > ();
    }
#line 1743 "parser.tab.cc"
    break;

  case 38: // statement: assignment_statement
#line 471 "parser.yy"
                            {
    	yylhs.value.as < statement_astnode* > ()=yystack_[0].value.as < assignS_astnode* > ();

     }
#line 1752 "parser.tab.cc"
    break;

  case 39: // statement: procedure_call
#line 476 "parser.yy"
                            {
		yylhs.value.as < statement_astnode* > () = new proccall_astnode(yystack_[0].value.as < funcall_astnode* > ());
	}
#line 1760 "parser.tab.cc"
    break;

  case 40: // statement: RETURN expression ';'
#line 479 "parser.yy"
                            {
		// check if the return type is correct
		if (!compatible(currFunc->type, yystack_[1].value.as < exp_astnode* > ()->data_type))
		{
			error(yystack_[1].location, "Incompatible type " + 
			yystack_[1].value.as < exp_astnode* > ()->data_type.sprint() + " returned, expected " +
			currFunc->type.sprint());

		}
		if (yystack_[1].value.as < exp_astnode* > ()->data_type.is_array)
		{
			if (yystack_[1].value.as < exp_astnode* > ()->data_type.array[0] == -1)
			{
				error(yystack_[1].location, "Function returns address of local variable");
			}
		}
		if (isIntType(yystack_[1].value.as < exp_astnode* > ()->data_type) && isFloatType(currFunc->type))
		{
			yystack_[1].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[1].value.as < exp_astnode* > ());
		}
		if (isIntType(currFunc->type) && isFloatType(yystack_[1].value.as < exp_astnode* > ()->data_type))
		{
			yystack_[1].value.as < exp_astnode* > () = new op_unary_astnode("TO_INT", yystack_[1].value.as < exp_astnode* > ());

		}
		yylhs.value.as < statement_astnode* > () = new return_astnode(yystack_[1].value.as < exp_astnode* > ());
	}
#line 1792 "parser.tab.cc"
    break;

  case 41: // assignment_expression: unary_expression '=' expression
#line 509 "parser.yy"
         {
		if (!(yystack_[2].value.as < exp_astnode* > ()->lvalue))
		{

			error(yystack_[2].location, "Left operand of assignment should have an lvalue"); 
		}
		else if (isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type)  && 
		         yystack_[0].value.as < exp_astnode* > ()->astnode_type== IntConstNode && 
				 yystack_[0].value.as < exp_astnode* > ()->int_val == 0)
		{
	
			yystack_[0].value.as < exp_astnode* > ()->data_type = createVoidStarType(); 
			//Special case of a NULL pointer. We are assuming that operationally, a NULL pointer of a type t* is for all purposes a void * with value 0;
			
		}

		else if (yystack_[2].value.as < exp_astnode* > ()->astnode_type==IdentifierNode && 
		         yystack_[2].value.as < exp_astnode* > ()->data_type.is_array &&
				 (st->search(yystack_[2].value.as < exp_astnode* > ()->idname()))->scope=="local"
				 )
		{
			error(yylhs.location, "Incompatible assignment when assigning to a constant l-value with type " +
			normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
			" from type " +
            normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint());
		}
		else if (!compatible(yystack_[2].value.as < exp_astnode* > ()->data_type, yystack_[0].value.as < exp_astnode* > ()->data_type, true))
		{

			error(yylhs.location, "Incompatible assignment when assigning to type " +
			normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
			" from type " +
            normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint());
		}

		else if (isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type) && isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_INT", yystack_[0].value.as < exp_astnode* > ());
		}
		else if (isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type) && isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type))
		{
			yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
		}
		yylhs.value.as < assignE_astnode* > () = new assignE_astnode(yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
		yylhs.value.as < assignE_astnode* > ()->data_type = yystack_[2].value.as < exp_astnode* > ()->data_type;
		yylhs.value.as < assignE_astnode* > ()->lvalue = false;
	 }
#line 1844 "parser.tab.cc"
    break;

  case 42: // assignment_statement: assignment_expression ';'
#line 562 "parser.yy"
{
		yylhs.value.as < assignS_astnode* > () = new assignS_astnode(yystack_[1].value.as < assignE_astnode* > ()->left, yystack_[1].value.as < assignE_astnode* > ()->right, yystack_[1].value.as < assignE_astnode* > ()->typecast);
		
}
#line 1853 "parser.tab.cc"
    break;

  case 43: // procedure_call: IDENTIFIER '(' ')' ';'
#line 569 "parser.yy"
{
		if (predefined.find(yystack_[3].value.as < std::string > ()) == predefined.end())
		{
			SymbTabEntry *temp = gst.search(yystack_[3].value.as < std::string > ());
			if (temp == NULL)
			{
				error(yylhs.location, "Procedure \"" + yystack_[3].value.as < std::string > () + "\"  not declared");
			}
			if (temp->varfun != "fun")
			{
				error(yylhs.location, "Called object \"" + yystack_[3].value.as < std::string > () + "\"  is not a procedure");
			}
			std::vector<pair<int, datatype>> v = temp->symbtab->getparameters();
			if (v.size() > 0)
			{
				error(yylhs.location, "Procedure \"" + yystack_[3].value.as < std::string > () + "\"  called with too few arguments");
			}
			// function call has no datatype
		}
		yylhs.value.as < funcall_astnode* > () = new funcall_astnode(new identifier_astnode(yystack_[3].value.as < std::string > ()));
		if (predefined.find(yystack_[3].value.as < std::string > ()) == predefined.end())
			yylhs.value.as < funcall_astnode* > ()->data_type = gst.search(yystack_[3].value.as < std::string > ())->type;
		else
			yylhs.value.as < funcall_astnode* > ()->data_type = predefined[yystack_[3].value.as < std::string > ()];
		yylhs.value.as < funcall_astnode* > ()->lvalue = false;
}
#line 1884 "parser.tab.cc"
    break;

  case 44: // procedure_call: IDENTIFIER '(' expression_list ')' ';'
#line 597 "parser.yy"
        {

		if (predefined.find(yystack_[4].value.as < std::string > ()) == predefined.end())
		{
			SymbTabEntry *temp = gst.search(yystack_[4].value.as < std::string > ());
			if (temp == NULL)
			{
				error(yylhs.location, "Procedure \"" + yystack_[4].value.as < std::string > () + "\"  not declared");
			}
			if (temp->varfun != "fun")
			{
				error(yylhs.location, "Called object \"" + yystack_[4].value.as < std::string > () + "\"  is not a procedure");
			}
			std::vector<pair<int, datatype>> v = temp->symbtab->getparameters();
			if (v.size() < yystack_[2].value.as < funcall_astnode* > ()->children.size())
			{
				error(yylhs.location, "Procedure \"" + yystack_[4].value.as < std::string > () + "\"  called with too many arguments");
			}
			if (v.size() > yystack_[2].value.as < funcall_astnode* > ()->children.size())
			{
				error(yylhs.location, "Procedure \"" + yystack_[4].value.as < std::string > () + "\"  called with too few arguments");
			}
			for (int i = 0; i < (int)v.size(); ++i)
			{
				if (isPointer(convert(v[i].second)) &&
					yystack_[2].value.as < funcall_astnode* > ()->children[i]->astnode_type == IntConstNode && yystack_[2].value.as < funcall_astnode* > ()->int_val == 0)
				{
					yystack_[2].value.as < funcall_astnode* > ()->data_type = createVoidStarType();
				}

				else if (!compatible(normalize(convert(v[i].second)), normalize(convert(yystack_[2].value.as < funcall_astnode* > ()->children[i]->data_type)), true))
				{
					error(yystack_[2].location, "Expected " +
								  normalize(convert(v[i].second)).sprint() +
								  " but argument is of type " +
								  normalize(convert(yystack_[2].value.as < funcall_astnode* > ()->children[i]->data_type)).sprint());
				}

				if (isIntType(yystack_[2].value.as < funcall_astnode* > ()->children[i]->data_type) && isFloatType(v[i].second))
				{
					yystack_[2].value.as < funcall_astnode* > ()->children[i] = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < funcall_astnode* > ()->children[i]);
				}
				else if (isFloatType(yystack_[2].value.as < funcall_astnode* > ()->children[i]->data_type) && isIntType(v[i].second))
				{
					yystack_[2].value.as < funcall_astnode* > ()->children[i] = new op_unary_astnode("TO_INT", yystack_[2].value.as < funcall_astnode* > ()->children[i]);
				}
			}
	};
	yystack_[2].value.as < funcall_astnode* > ()->setname(yystack_[4].value.as < std::string > ());
	yylhs.value.as < funcall_astnode* > () = yystack_[2].value.as < funcall_astnode* > ();
	if (predefined.find(yystack_[4].value.as < std::string > ()) == predefined.end())
		yylhs.value.as < funcall_astnode* > ()->data_type = gst.search(yystack_[4].value.as < std::string > ())->type;
	else
		yylhs.value.as < funcall_astnode* > ()->data_type = predefined[yystack_[4].value.as < std::string > ()];
	yylhs.value.as < funcall_astnode* > ()->lvalue = false;
	}
#line 1945 "parser.tab.cc"
    break;

  case 45: // expression: logical_and_expression
#line 656 "parser.yy"
        {
    	yylhs.value.as < exp_astnode* > ()=yystack_[0].value.as < exp_astnode* > ();
    }
#line 1953 "parser.tab.cc"
    break;

  case 46: // expression: expression OR_OP logical_and_expression
#line 659 "parser.yy"
                                              {
		  exp_astnode* arg1=yystack_[2].value.as < exp_astnode* > (), *arg3=yystack_[0].value.as < exp_astnode* > ();
		if (!isScalarOrPointerType(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)))
		 error(yystack_[2].location, "Invalid operand of ||, not scalar or pointer");
		else if (!isScalarOrPointerType(convert(yystack_[0].value.as < exp_astnode* > ()->data_type)))
		 error(yystack_[0].location, "Invalid operand of ||, not scalar or pointer");
	
    	yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("OR_OP", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
    	if(arg3->is_calculable || arg1->is_calculable)
		{
			yylhs.value.as < exp_astnode* > ()->is_calculable = true;
			yylhs.value.as < exp_astnode* > ()->int_val = (arg1->int_val) && (arg3->int_val);
		}
    	yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
    	yylhs.value.as < exp_astnode* > ()->lvalue = false;
   }
#line 1974 "parser.tab.cc"
    break;

  case 47: // logical_and_expression: equality_expression
#line 679 "parser.yy"
                            {
    	yylhs.value.as < exp_astnode* > ()=yystack_[0].value.as < exp_astnode* > ();
    }
#line 1982 "parser.tab.cc"
    break;

  case 48: // logical_and_expression: logical_and_expression AND_OP equality_expression
#line 683 "parser.yy"
  {
		exp_astnode *arg1 = yystack_[2].value.as < exp_astnode* > (), *arg3 = yystack_[0].value.as < exp_astnode* > ();
		if (!isScalarOrPointerType(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)))
		 error(yystack_[2].location, "Invalid operand of &&,  not scalar or pointer");
		else if (!isScalarOrPointerType(convert(yystack_[0].value.as < exp_astnode* > ()->data_type)))
		 error(yystack_[0].location, "Invalid operand of &&,  not scalar or pointer");

		yylhs.value.as < exp_astnode* > () = new op_binary_astnode("AND_OP", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
		if (arg3->is_calculable && arg1->is_calculable)
		{
			yylhs.value.as < exp_astnode* > ()->is_calculable = true;
			yylhs.value.as < exp_astnode* > ()->int_val = (arg1->int_val) && (arg3->int_val);
		}
		yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
  }
#line 2003 "parser.tab.cc"
    break;

  case 49: // equality_expression: relational_expression
#line 700 "parser.yy"
                          {
		yylhs.value.as < exp_astnode* > ()=yystack_[0].value.as < exp_astnode* > ();
	}
#line 2011 "parser.tab.cc"
    break;

  case 50: // equality_expression: equality_expression EQ_OP relational_expression
#line 703 "parser.yy"
                                                    {
		exp_astnode* arg1=yystack_[2].value.as < exp_astnode* > (), *arg3=yystack_[0].value.as < exp_astnode* > ();
		if(isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) && yystack_[0].value.as < exp_astnode* > ()->astnode_type== IntConstNode && yystack_[0].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[0].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

    	if(isPointer(yystack_[0].value.as < exp_astnode* > ()->data_type) && yystack_[2].value.as < exp_astnode* > ()->astnode_type== IntConstNode && yystack_[2].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[2].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}
        
		if (!isScalarOrPointerType(normalize(convert(yystack_[2].value.as < exp_astnode* > ()->data_type))) ||
			!isScalarOrPointerType(normalize(convert(yystack_[0].value.as < exp_astnode* > ()->data_type))) ||
			!compatible(yystack_[2].value.as < exp_astnode* > ()->data_type,yystack_[0].value.as < exp_astnode* > ()->data_type,true))
			error(yylhs.location, "Invalid operands types for binary ==, " +
			          normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
					  " and " +
					  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint());

    	if(isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{

			if(isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
				yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			if(isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("EQ_OP_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
		}
		else {
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("EQ_OP_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			if(arg3->is_calculable && arg1->is_calculable)
			{
				yylhs.value.as < exp_astnode* > ()->is_calculable = true;
				yylhs.value.as < exp_astnode* > ()->int_val = (arg1->int_val)==(arg3->int_val);
			}
		}
    	yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
    	yylhs.value.as < exp_astnode* > ()->lvalue = false;
    }
#line 2054 "parser.tab.cc"
    break;

  case 51: // equality_expression: equality_expression NE_OP relational_expression
#line 741 "parser.yy"
                                                          {
		if(isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) && yystack_[0].value.as < exp_astnode* > ()->is_calculable && yystack_[0].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[0].value.as < exp_astnode* > ()-> data_type = createVoidStarType();
    	}

    	if(isPointer(yystack_[0].value.as < exp_astnode* > ()->data_type) && yystack_[2].value.as < exp_astnode* > ()->is_calculable && yystack_[2].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[2].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

		if (!isScalarOrPointerType(normalize(convert(yystack_[2].value.as < exp_astnode* > ()->data_type))) ||
			!isScalarOrPointerType(normalize(convert(yystack_[0].value.as < exp_astnode* > ()->data_type))) ||
			!compatible(yystack_[2].value.as < exp_astnode* > ()->data_type,yystack_[0].value.as < exp_astnode* > ()->data_type,true))
		{
    		error(yylhs.location, "Invalid operands types for binary !=, " +
			          normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
					  " and " +
					  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint());  
		
		}
		if(isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			if(isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
				yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			if(isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("NE_OP_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
		}
		else {
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("NE_OP_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
		}
    	yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
		
	}
#line 2093 "parser.tab.cc"
    break;

  case 52: // relational_expression: additive_expression
#line 778 "parser.yy"
                         {
		yylhs.value.as < exp_astnode* > ()=yystack_[0].value.as < exp_astnode* > ();
	}
#line 2101 "parser.tab.cc"
    break;

  case 53: // relational_expression: relational_expression '<' additive_expression
#line 781 "parser.yy"
                                                    {
		exp_astnode* arg1=yystack_[2].value.as < exp_astnode* > (), *arg3=yystack_[0].value.as < exp_astnode* > ();

		if(isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) && yystack_[0].value.as < exp_astnode* > ()->is_calculable && yystack_[0].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[0].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

    	if(isPointer(yystack_[0].value.as < exp_astnode* > ()->data_type) && yystack_[2].value.as < exp_astnode* > ()->is_calculable && yystack_[2].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[2].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

    	if (!isScalarOrPointerType(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)) ||
			!isScalarOrPointerType(convert(yystack_[0].value.as < exp_astnode* > ()->data_type)) ||
			!compatible(normalize(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)),normalize(convert(yystack_[0].value.as < exp_astnode* > ()->data_type))))

		{
			error(yylhs.location, "Invalid operands types for binary < , " +
			          normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
					  " and " +
					  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint()); 					  
		}
		if(isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			if(isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
				yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			if(isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("LT_OP_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
		}
		else
		{
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("LT_OP_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			if(arg3->is_calculable && arg1->is_calculable)
			{
				yylhs.value.as < exp_astnode* > ()->is_calculable = true;
				yylhs.value.as < exp_astnode* > ()->int_val = (arg1->int_val)<(arg3->int_val);
			}
		}
		yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
   		yylhs.value.as < exp_astnode* > ()->lvalue = false;
   	}
#line 2147 "parser.tab.cc"
    break;

  case 54: // relational_expression: relational_expression '>' additive_expression
#line 822 "parser.yy"
                                                         {
		exp_astnode* arg1=yystack_[2].value.as < exp_astnode* > (), *arg3=yystack_[0].value.as < exp_astnode* > ();

		if(isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) && yystack_[0].value.as < exp_astnode* > ()->is_calculable && yystack_[0].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[0].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

    	if(isPointer(yystack_[0].value.as < exp_astnode* > ()->data_type) && yystack_[2].value.as < exp_astnode* > ()->is_calculable && yystack_[2].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[2].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

		
		if (!isScalarOrPointerType(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)) ||
			!isScalarOrPointerType(convert(yystack_[0].value.as < exp_astnode* > ()->data_type)) ||
			!compatible(normalize(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)),normalize(convert(yystack_[0].value.as < exp_astnode* > ()->data_type))))
		{
			error(yylhs.location, "Invalid operand types for binary > , " +
			          normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
					  " and " +
					  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint()); 					  
		}
		
		
		if(isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			if(isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
				yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			if(isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("GT_OP_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
		}
		else
		{
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("GT_OP_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			if(arg3->is_calculable && arg1->is_calculable)
			{
				yylhs.value.as < exp_astnode* > ()->is_calculable = true;
				yylhs.value.as < exp_astnode* > ()->int_val = (arg1->int_val)>(arg3->int_val);
			}
		}
		yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
	}
#line 2195 "parser.tab.cc"
    break;

  case 55: // relational_expression: relational_expression LE_OP additive_expression
#line 865 "parser.yy"
                                                           {
		exp_astnode* arg1=yystack_[2].value.as < exp_astnode* > (), *arg3=yystack_[0].value.as < exp_astnode* > ();
		if(isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) && yystack_[0].value.as < exp_astnode* > ()->is_calculable && yystack_[0].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[0].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

    	if(isPointer(yystack_[0].value.as < exp_astnode* > ()->data_type) && yystack_[2].value.as < exp_astnode* > ()->is_calculable && yystack_[2].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[2].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

		if (!isScalarOrPointerType(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)) ||
			!isScalarOrPointerType(convert(yystack_[0].value.as < exp_astnode* > ()->data_type)) ||
			!compatible(normalize(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)),normalize(convert(yystack_[0].value.as < exp_astnode* > ()->data_type))))
		
		{
			error(yylhs.location, "Invalid operand types for binary <= , " +
			          normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
					  " and " +
					  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint()); 					  
		}
		
		if(isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			if(isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
            	yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			if(isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("LE_OP_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
		}
		else
		{
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("LE_OP_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			if(arg3->is_calculable && arg1->is_calculable)
			{
				yylhs.value.as < exp_astnode* > ()->is_calculable = true;
				yylhs.value.as < exp_astnode* > ()->int_val = (arg1->int_val)<=(arg3->int_val);
			}
		}
		yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
	}
#line 2241 "parser.tab.cc"
    break;

  case 56: // relational_expression: relational_expression GE_OP additive_expression
#line 906 "parser.yy"
                                                      {
		exp_astnode* arg1=yystack_[2].value.as < exp_astnode* > (), *arg3=yystack_[0].value.as < exp_astnode* > ();

		if(isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) && yystack_[0].value.as < exp_astnode* > ()->is_calculable && yystack_[0].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[0].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

    	if(isPointer(yystack_[0].value.as < exp_astnode* > ()->data_type) && yystack_[2].value.as < exp_astnode* > ()->is_calculable && yystack_[2].value.as < exp_astnode* > ()->int_val==0) {
    		yystack_[2].value.as < exp_astnode* > ()->data_type = createVoidStarType();
    	}

    	
		if (!isScalarOrPointerType(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)) ||
			!isScalarOrPointerType(convert(yystack_[0].value.as < exp_astnode* > ()->data_type)) ||
			!compatible(normalize(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)),normalize(convert(yystack_[0].value.as < exp_astnode* > ()->data_type))))
			
		{
			error(yylhs.location, "Invalid operand types for binary >= , " +
			          normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
					  " and " +
					  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint()); 					  
		}
		
		
		if(isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			if(isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
            	yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			if(isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("GE_OP_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
		}
		else
		{
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("GE_OP_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			if(arg3->is_calculable && arg1->is_calculable)
			{
				yylhs.value.as < exp_astnode* > ()->is_calculable = true;
				yylhs.value.as < exp_astnode* > ()->int_val = (arg1->int_val)>=(arg3->int_val);
			}
		}
		yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
    	yylhs.value.as < exp_astnode* > ()->lvalue = false;
    }
#line 2290 "parser.tab.cc"
    break;

  case 57: // additive_expression: multiplicative_expression
#line 953 "parser.yy"
                             {
		yylhs.value.as < exp_astnode* > ()=yystack_[0].value.as < exp_astnode* > ();
	}
#line 2298 "parser.tab.cc"
    break;

  case 58: // additive_expression: additive_expression '+' multiplicative_expression
#line 957 "parser.yy"
        {
		if (isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) &&
			isPointer(yystack_[0].value.as < exp_astnode* > ()->data_type))
			error(yylhs.location, "Invalid operand types for binary + , " +
						  normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
						  " and " +
						  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint());

		else if ((isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) &&
			 isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type)) ||
			(isPointer(yystack_[0].value.as < exp_astnode* > ()->data_type) &&
			 isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type)))
		{
			yylhs.value.as < exp_astnode* > () = new op_binary_astnode("PLUS_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()->data_type = isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) ? yystack_[2].value.as < exp_astnode* > ()->data_type : yystack_[0].value.as < exp_astnode* > ()->data_type;
		}
		else if ((isArray(yystack_[2].value.as < exp_astnode* > ()->data_type) &&
			 isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type)) ||
			(isArray(yystack_[0].value.as < exp_astnode* > ()->data_type) &&
			 isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type)))
		{
			yylhs.value.as < exp_astnode* > () = new op_binary_astnode("PLUS_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()->data_type = isArray(yystack_[2].value.as < exp_astnode* > ()->data_type) ? convert(normalize(yystack_[2].value.as < exp_astnode* > ()->data_type)) : convert(normalize(yystack_[0].value.as < exp_astnode* > ()->data_type));
		}

		else
		{
            // none of the operands are pointers
			if (!(isIntOrFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) && isIntOrFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type)))
			
             error(yylhs.location, "Invalid operand types for binary + , " +
			          normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
					  " and " +
					  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint()); 

			if (isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
			{
				if (isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
                	yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			    if(isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				    yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
				yylhs.value.as < exp_astnode* > () = new op_binary_astnode("PLUS_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
				yylhs.value.as < exp_astnode* > ()->data_type = createtype(FLOAT_TYPE);
			}
			else
			{

				yylhs.value.as < exp_astnode* > () = new op_binary_astnode("PLUS_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
				yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
			}
		}
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
	}
#line 2356 "parser.tab.cc"
    break;

  case 59: // additive_expression: additive_expression '-' multiplicative_expression
#line 1010 "parser.yy"
                                                             {

		if (isPointer(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)) &&
			isPointer(convert(yystack_[0].value.as < exp_astnode* > ()->data_type)) &&
			compatible(normalize(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)), normalize(convert(yystack_[0].value.as < exp_astnode* > ()->data_type))))
		{
			yylhs.value.as < exp_astnode* > () = new op_binary_astnode("MINUS_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
		}
		else if (isArray(yystack_[2].value.as < exp_astnode* > ()->data_type) &&
				 isArray(yystack_[0].value.as < exp_astnode* > ()->data_type) &&
				 compatible(normalize(convert(yystack_[2].value.as < exp_astnode* > ()->data_type)), normalize(convert(yystack_[0].value.as < exp_astnode* > ()->data_type))))
			{
				yylhs.value.as < exp_astnode* > () = new op_binary_astnode("MINUS_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
				yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
			}
		else if (isPointer(yystack_[2].value.as < exp_astnode* > ()->data_type) &&
				 isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			yylhs.value.as < exp_astnode* > () = new op_binary_astnode("MINUS_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()->data_type = yystack_[2].value.as < exp_astnode* > ()->data_type;
		}
        else if (isArray(yystack_[2].value.as < exp_astnode* > ()->data_type) &&
				 isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			yylhs.value.as < exp_astnode* > () = new op_binary_astnode("MINUS_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()->data_type = normalize(convert(yystack_[2].value.as < exp_astnode* > ()->data_type));
		}
		else if (isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			if (isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
				yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			if (isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > () = new op_binary_astnode("MINUS_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()->data_type = createtype(FLOAT_TYPE);
		}
		else if (isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type) && isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			yylhs.value.as < exp_astnode* > () = new op_binary_astnode("MINUS_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
		}
		else
			error(yylhs.location, "Invalid operand types for binary - , " +
						  normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
						  " and " +
						  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint());
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
	}
#line 2410 "parser.tab.cc"
    break;

  case 60: // unary_expression: postfix_expression
#line 1062 "parser.yy"
                     {
		yylhs.value.as < exp_astnode* > ()=yystack_[0].value.as < exp_astnode* > ();
	}
#line 2418 "parser.tab.cc"
    break;

  case 61: // unary_expression: unary_operator unary_expression
#line 1065 "parser.yy"
                                           {
		exp_astnode* arg2=yystack_[0].value.as < exp_astnode* > ();
		yylhs.value.as < exp_astnode* > ()=new op_unary_astnode(yystack_[1].value.as < op_unary_astnode* > ()->getoperator(),yystack_[0].value.as < exp_astnode* > ());
		if(yystack_[1].value.as < op_unary_astnode* > ()->getoperator()=="DEREF") {
			if(!isDereferenceAllowed(yystack_[0].value.as < exp_astnode* > ()->data_type)) {
				error(yystack_[0].location, "Invalid operand type " +  arg2->data_type.sprint() + " of unary *");			}
			yylhs.value.as < exp_astnode* > ()->lvalue=true;
			yylhs.value.as < exp_astnode* > ()->data_type=extract_type(arg2->data_type, TYPE_DEREF);
		}
		else if(yystack_[1].value.as < op_unary_astnode* > ()->getoperator()=="ADDRESS") {
			if(!arg2->lvalue) {
				error(yystack_[0].location, "Operand of & should  have lvalue");	
				
			}

			yylhs.value.as < exp_astnode* > ()->lvalue = false;
			yylhs.value.as < exp_astnode* > ()->data_type = arg2->data_type;
			yylhs.value.as < exp_astnode* > ()->data_type.addpointer();

		}
		else if(yystack_[1].value.as < op_unary_astnode* > ()->getoperator()=="UMINUS")
		{

			if(!isIntOrFloatType(arg2->data_type)){
				error(yystack_[0].location, " Operand of unary - should be an int or float");
			}
			if(arg2->is_calculable)
			{
				yylhs.value.as < exp_astnode* > ()->is_calculable = true;
				if(yystack_[1].value.as < op_unary_astnode* > ()->getoperator()=="UMINUS")
				{
					yylhs.value.as < exp_astnode* > ()->int_val = -1*arg2->int_val ;
				}
				else
				{
					if(arg2->int_val !=0)
					{
						yylhs.value.as < exp_astnode* > ()->int_val = 0;
					}
					else
					{
						yylhs.value.as < exp_astnode* > ()->int_val = 1;
					}
				}
			}
			yylhs.value.as < exp_astnode* > ()->data_type = yystack_[0].value.as < exp_astnode* > ()->data_type;
		}
        else if (yystack_[1].value.as < op_unary_astnode* > ()->getoperator()=="NOT")
		{
			if(!isScalarOrPointerType(normalize(convert (arg2->data_type)))){
				error(yystack_[0].location, " Operand of NOT should be an int or float or pointer");
			}
			yylhs.value.as < exp_astnode* > ()->lvalue = false;
			yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);

		}
	}
#line 2480 "parser.tab.cc"
    break;

  case 62: // multiplicative_expression: unary_expression
#line 1126 "parser.yy"
                     {
		yylhs.value.as < exp_astnode* > ()=yystack_[0].value.as < exp_astnode* > ();
	}
#line 2488 "parser.tab.cc"
    break;

  case 63: // multiplicative_expression: multiplicative_expression '*' unary_expression
#line 1129 "parser.yy"
                                                         {
		exp_astnode* arg1=yystack_[2].value.as < exp_astnode* > (), *arg3=yystack_[0].value.as < exp_astnode* > ();
		if(!(isIntOrFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) && isIntOrFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type)))
		{
			error(yylhs.location, "Invalid operand types for binary * , " +
			          normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
					  " and " +
					  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint());
		}
		if(isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			if(isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
				yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			if(isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("MULT_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()->data_type = createtype(FLOAT_TYPE);
		}
		else
		{
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("MULT_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			if(arg3->is_calculable && arg1->is_calculable)
			{
				yylhs.value.as < exp_astnode* > ()->is_calculable = true;
				yylhs.value.as < exp_astnode* > ()->int_val = (arg1->int_val)*(arg3->int_val);
			}
			yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
		}
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
	}
#line 2523 "parser.tab.cc"
    break;

  case 64: // multiplicative_expression: multiplicative_expression '/' unary_expression
#line 1159 "parser.yy"
                                                         {
		exp_astnode* arg1=yystack_[2].value.as < exp_astnode* > (), *arg3=yystack_[0].value.as < exp_astnode* > ();
		if(!(isIntOrFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) && isIntOrFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type)))
		{
			error(yylhs.location, "Invalid operand types for binary / , " +
			          normalize(yystack_[2].value.as < exp_astnode* > ()->data_type).sprint() +
					  " and " +
					  normalize(yystack_[0].value.as < exp_astnode* > ()->data_type).sprint()); 
					  
		}
		if(isFloatType(yystack_[2].value.as < exp_astnode* > ()->data_type) || isFloatType(yystack_[0].value.as < exp_astnode* > ()->data_type))
		{
			if(isIntType(yystack_[2].value.as < exp_astnode* > ()->data_type))
            	yystack_[2].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[2].value.as < exp_astnode* > ());
			if(isIntType(yystack_[0].value.as < exp_astnode* > ()->data_type))
				yystack_[0].value.as < exp_astnode* > () = new op_unary_astnode("TO_FLOAT", yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("DIV_FLOAT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			yylhs.value.as < exp_astnode* > ()->data_type = createtype(FLOAT_TYPE);
		}
		else
		{
			yylhs.value.as < exp_astnode* > ()=new op_binary_astnode("DIV_INT", yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < exp_astnode* > ());
			if(arg3->is_calculable && arg1->is_calculable)
			{
				yylhs.value.as < exp_astnode* > ()->is_calculable = true;
				yylhs.value.as < exp_astnode* > ()->int_val = (arg1->int_val)*(arg3->int_val);
			}
			yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
		}
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
	}
#line 2559 "parser.tab.cc"
    break;

  case 65: // postfix_expression: primary_expression
#line 1196 "parser.yy"
                       {
        yylhs.value.as < exp_astnode* > ()=yystack_[0].value.as < exp_astnode* > ();
}
#line 2567 "parser.tab.cc"
    break;

  case 66: // postfix_expression: postfix_expression '[' expression ']'
#line 1200 "parser.yy"
  {

		exp_astnode *arg1 = yystack_[3].value.as < exp_astnode* > ();
		datatype expr_dt = yystack_[1].value.as < exp_astnode* > ()->data_type;
		if (!isIntType(expr_dt))
		{
			error(yystack_[1].location, "Array subscript is not an integer");
		}
		if (!yystack_[3].value.as < exp_astnode* > ()->data_type.is_array && yystack_[3].value.as < exp_astnode* > ()->data_type.deref == 0)
		{
			error(yystack_[3].location, "Subscripted value is neither array nor pointer");
		}
		yylhs.value.as < exp_astnode* > () = new arrayref_astnode(yystack_[3].value.as < exp_astnode* > (), yystack_[1].value.as < exp_astnode* > ());
		if (arg1->data_type.is_array)
		{
			yylhs.value.as < exp_astnode* > ()->data_type = extract_type(arg1->data_type, TYPE_ARRAY_REF);
		}
		else
		{
			yylhs.value.as < exp_astnode* > ()->data_type = arg1->data_type;
			yylhs.value.as < exp_astnode* > ()->data_type.deref--;
		}
		yylhs.value.as < exp_astnode* > ()->lvalue = true;
  }
#line 2596 "parser.tab.cc"
    break;

  case 67: // postfix_expression: IDENTIFIER '(' ')'
#line 1226 "parser.yy"
  {
		if (predefined.find(yystack_[2].value.as < std::string > ()) == predefined.end())
		{
			SymbTabEntry *temp = gst.search(yystack_[2].value.as < std::string > ());
			if (temp == NULL)
			{
				error(yylhs.location, "Function \"" + yystack_[2].value.as < std::string > () + "\"  not declared");
			}
			if (temp->varfun != "fun")
			{
				error(yylhs.location, "Called object \"" + yystack_[2].value.as < std::string > () + "\"  is not a function");
			}
			std::vector<pair<int, datatype>> v = temp->symbtab->getparameters();
			if (v.size() > 0)
			{
				error(yylhs.location, "Function \"" + yystack_[2].value.as < std::string > () + "\"  called with too few arguments");
			}
		}
		// function call has no datatype
		yylhs.value.as < exp_astnode* > () = new funcall_astnode(new identifier_astnode(yystack_[2].value.as < std::string > ()));
		if (predefined.find(yystack_[2].value.as < std::string > ()) == predefined.end())
			yylhs.value.as < exp_astnode* > ()->data_type = gst.search(yystack_[2].value.as < std::string > ())->type;
		else
			yylhs.value.as < exp_astnode* > ()->data_type = predefined[yystack_[2].value.as < std::string > ()];
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
  }
#line 2627 "parser.tab.cc"
    break;

  case 68: // postfix_expression: IDENTIFIER '(' expression_list ')'
#line 1253 "parser.yy"
        {
		if (predefined.find(yystack_[3].value.as < std::string > ()) == predefined.end())
		{
			SymbTabEntry *temp = gst.search(yystack_[3].value.as < std::string > ());
			if (temp == NULL)
			{
				error(yylhs.location, "Function \"" + yystack_[3].value.as < std::string > () + "\"  not declared");
			}
			if (temp->varfun != "fun")
			{
				error(yylhs.location, "Called object \"" + yystack_[3].value.as < std::string > () + "\"  is not a function");
			}
			std::vector<pair<int, datatype>> v = temp->symbtab->getparameters();
			if (v.size() < yystack_[1].value.as < funcall_astnode* > ()->children.size())
			{
				error(yylhs.location, "Function \"" + yystack_[3].value.as < std::string > () + "\"  called with too many arguments");
			}
			if (v.size() > yystack_[1].value.as < funcall_astnode* > ()->children.size())
			{   
				error(yylhs.location, "Function \"" + yystack_[3].value.as < std::string > () + "\"  called with too few arguments");
			}
			for (int i = 0; i < (int)v.size(); ++i)
			{   
				if (!compatible(normalize(convert(v[i].second)), normalize(convert(yystack_[1].value.as < funcall_astnode* > ()->children[i]->data_type)), true))
				{   
					error(yystack_[1].location, "Expected " +
					v[i].second.sprint() +
					" but argument is of type " +
					yystack_[1].value.as < funcall_astnode* > ()->children[i]->data_type.sprint());
				}
				if (isIntType( yystack_[1].value.as < funcall_astnode* > ()->children[i]->data_type) && isFloatType(v[i].second)) 
				{
					yystack_[1].value.as < funcall_astnode* > ()->children[i] = new op_unary_astnode("TO_FLOAT", yystack_[1].value.as < funcall_astnode* > ()->children[i]);
				}
				else if (isFloatType( yystack_[1].value.as < funcall_astnode* > ()->children[i]->data_type) && isIntType(v[i].second)) 
				{
					yystack_[1].value.as < funcall_astnode* > ()->children[i] = new op_unary_astnode("TO_INT", yystack_[1].value.as < funcall_astnode* > ()->children[i]);
				}
			}
		}
		yystack_[1].value.as < funcall_astnode* > ()->setname(yystack_[3].value.as < std::string > ());
		yylhs.value.as < exp_astnode* > () = yystack_[1].value.as < funcall_astnode* > ();
		if (predefined.find(yystack_[3].value.as < std::string > ()) == predefined.end())
			yylhs.value.as < exp_astnode* > ()->data_type = gst.search(yystack_[3].value.as < std::string > ())->type;
		else
			yylhs.value.as < exp_astnode* > ()->data_type = predefined[yystack_[3].value.as < std::string > ()];
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
	}
#line 2680 "parser.tab.cc"
    break;

  case 69: // postfix_expression: postfix_expression '.' IDENTIFIER
#line 1302 "parser.yy"
                                      {
		// check if data type of postfix exp is struct
		datatype tempdt = yystack_[2].value.as < exp_astnode* > ()->data_type;
		if (!isStructType(tempdt))
		{
			error(yystack_[2].location, "Left operand of \".\"  is not a  structure");
		}
		// if postfix's type is struct, check if it has member named identifier
		SymbTabEntry *temp = gst.search(tempdt.structname);
		SymbTab *struct_table = (temp -> symbtab);
		SymbTabEntry *identifier_entry = struct_table->search(yystack_[0].value.as < std::string > ());
		if (identifier_entry == NULL)
		{
			error(yystack_[2].location, "Struct \"" + tempdt.structname + "\" has no member named \"" + yystack_[0].value.as < std::string > () + "\"");
		}
		yylhs.value.as < exp_astnode* > () = new member_astnode(yystack_[2].value.as < exp_astnode* > (), new identifier_astnode(yystack_[0].value.as < std::string > ())); // Add in lex
		yylhs.value.as < exp_astnode* > ()->data_type = identifier_entry->type;
		yylhs.value.as < exp_astnode* > ()->lvalue = yystack_[2].value.as < exp_astnode* > ()->lvalue;
  }
#line 2704 "parser.tab.cc"
    break;

  case 70: // postfix_expression: postfix_expression PTR_OP IDENTIFIER
#line 1321 "parser.yy"
                                        {
		datatype left_dt = yystack_[2].value.as < exp_astnode* > ()->data_type;
		if (!isStructPointerType(convert(left_dt)))
		{
			error(yystack_[2].location, "Left operand of \"->\" is not a pointer to structure");
		}
		SymbTabEntry *temp = gst.search(left_dt.structname);
		SymbTab *struct_table = (temp->symbtab);
		SymbTabEntry *identifier_entry = struct_table->search(yystack_[0].value.as < std::string > ());
		if (identifier_entry == NULL)
		{
			error(yystack_[2].location, "Struct \"" + left_dt.structname + "\" has no member named " + yystack_[0].value.as < std::string > ());
		}
		yylhs.value.as < exp_astnode* > () = new arrow_astnode(yystack_[2].value.as < exp_astnode* > (), new identifier_astnode(yystack_[0].value.as < std::string > ())); // Add in lex
		yylhs.value.as < exp_astnode* > ()->data_type = identifier_entry->type;
		yylhs.value.as < exp_astnode* > ()->lvalue = true;
  }
#line 2726 "parser.tab.cc"
    break;

  case 71: // postfix_expression: postfix_expression INC_OP
#line 1338 "parser.yy"
                              {
    	exp_astnode* arg1=yystack_[1].value.as < exp_astnode* > ();
    	if(!(isScalarOrPointerType(yystack_[1].value.as < exp_astnode* > ()->data_type)))
    	{
    		error(yystack_[1].location, "Operand of \"++\" should be a int, float or pointer");
    	}
    	if(!yystack_[1].value.as < exp_astnode* > ()->lvalue)
    	{
    		error(yystack_[1].location, "Operand of \"++\" should have lvalue");
    	}							

		yylhs.value.as < exp_astnode* > ()=new op_unary_astnode("PP",yystack_[1].value.as < exp_astnode* > ());				// type checking for incop
		yylhs.value.as < exp_astnode* > ()->data_type = arg1->data_type;
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
	}
#line 2746 "parser.tab.cc"
    break;

  case 72: // primary_expression: IDENTIFIER
#line 1359 "parser.yy"
               {
		SymbTabEntry *temp = st->search(yystack_[0].value.as < std::string > ());
		if (temp == NULL)
		{
			error(yystack_[0].location, "Variable \"" +  yystack_[0].value.as < std::string > () + "\" not declared");
		}
		yylhs.value.as < exp_astnode* > () = new identifier_astnode(yystack_[0].value.as < std::string > ());
		yylhs.value.as < exp_astnode* > ()->data_type = temp->type;
		yylhs.value.as < exp_astnode* > ()->lvalue = true;
}
#line 2761 "parser.tab.cc"
    break;

  case 73: // primary_expression: INT_CONSTANT
#line 1370 "parser.yy"
                 {
		int arg1 = std::stoi(yystack_[0].value.as < std::string > ());
		yylhs.value.as < exp_astnode* > () = new intconst_astnode(std::stoi(yystack_[0].value.as < std::string > ())); // the values of these expressions are already stored through the constructor function
		yylhs.value.as < exp_astnode* > ()->astnode_type = IntConstNode;
		yylhs.value.as < exp_astnode* > ()->data_type = createtype(INT_TYPE);
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
		yylhs.value.as < exp_astnode* > ()->is_calculable = true;
		yylhs.value.as < exp_astnode* > ()->int_val = arg1;
  }
#line 2775 "parser.tab.cc"
    break;

  case 74: // primary_expression: FLOAT_CONSTANT
#line 1379 "parser.yy"
                   {
		yylhs.value.as < exp_astnode* > () = new floatconst_astnode(std::stof(yystack_[0].value.as < std::string > ()));
		yylhs.value.as < exp_astnode* > ()->data_type = createtype(FLOAT_TYPE);
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
  }
#line 2785 "parser.tab.cc"
    break;

  case 75: // primary_expression: STRING_LITERAL
#line 1384 "parser.yy"
                   {
		yylhs.value.as < exp_astnode* > () = new stringconst_astnode(yystack_[0].value.as < std::string > ()); // did not set the data type for primary_expression here
		yylhs.value.as < exp_astnode* > ()->lvalue = false;
		yylhs.value.as < exp_astnode* > ()->data_type = createtype(7);
  }
#line 2795 "parser.tab.cc"
    break;

  case 76: // primary_expression: '(' expression ')'
#line 1389 "parser.yy"
                        {
		yylhs.value.as < exp_astnode* > () = yystack_[1].value.as < exp_astnode* > ();
  }
#line 2803 "parser.tab.cc"
    break;

  case 77: // expression_list: expression
#line 1395 "parser.yy"
             {
    	yylhs.value.as < funcall_astnode* > ()=new funcall_astnode();
    	yylhs.value.as < funcall_astnode* > ()->pushback(yystack_[0].value.as < exp_astnode* > ());	
    }
#line 2812 "parser.tab.cc"
    break;

  case 78: // expression_list: expression_list ',' expression
#line 1399 "parser.yy"
                                     {
    	yylhs.value.as < funcall_astnode* > ()=yystack_[2].value.as < funcall_astnode* > ();
    	yylhs.value.as < funcall_astnode* > ()->pushback(yystack_[0].value.as < exp_astnode* > ());
    }
#line 2821 "parser.tab.cc"
    break;

  case 79: // unary_operator: '-'
#line 1406 "parser.yy"
      {
		yylhs.value.as < op_unary_astnode* > () = new op_unary_astnode("UMINUS");
	}
#line 2829 "parser.tab.cc"
    break;

  case 80: // unary_operator: '!'
#line 1409 "parser.yy"
        {
		yylhs.value.as < op_unary_astnode* > ()=new op_unary_astnode("NOT");
	}
#line 2837 "parser.tab.cc"
    break;

  case 81: // unary_operator: '&'
#line 1412 "parser.yy"
        {
		yylhs.value.as < op_unary_astnode* > ()=new op_unary_astnode("ADDRESS");					
	}
#line 2845 "parser.tab.cc"
    break;

  case 82: // unary_operator: '*'
#line 1415 "parser.yy"
       {
		yylhs.value.as < op_unary_astnode* > ()=new op_unary_astnode("DEREF");
	}
#line 2853 "parser.tab.cc"
    break;

  case 83: // selection_statement: IF '(' expression ')' statement ELSE statement
#line 1421 "parser.yy"
                                                {
	    if (!isScalarOrPointerType(yystack_[4].value.as < exp_astnode* > ()->data_type))
			error(yystack_[4].location, "The guard should be a int or float or a pointer");
    	yylhs.value.as < statement_astnode* > ()=new if_astnode(yystack_[4].value.as < exp_astnode* > (),yystack_[2].value.as < statement_astnode* > (),yystack_[0].value.as < statement_astnode* > ());
    }
#line 2863 "parser.tab.cc"
    break;

  case 84: // iteration_statement: WHILE '(' expression ')' statement
#line 1429 "parser.yy"
                                       {
		if (!isScalarOrPointerType(yystack_[2].value.as < exp_astnode* > ()->data_type))
			error(yystack_[2].location, "The guard should be a int or float or a pointer");
		yylhs.value.as < statement_astnode* > () = new while_astnode(yystack_[2].value.as < exp_astnode* > (), yystack_[0].value.as < statement_astnode* > ());
	}
#line 2873 "parser.tab.cc"
    break;

  case 85: // iteration_statement: FOR '(' assignment_expression ';' expression ';' assignment_expression ')' statement
#line 1434 "parser.yy"
                                                                                         {
	
	if (!isScalarOrPointerType(yystack_[4].value.as < exp_astnode* > ()->data_type))
		error(yystack_[4].location, "The guard should be a int or float or a pointer");
   yylhs.value.as < statement_astnode* > ()=new for_astnode(yystack_[6].value.as < assignE_astnode* > (),yystack_[4].value.as < exp_astnode* > (),yystack_[2].value.as < assignE_astnode* > (),yystack_[0].value.as < statement_astnode* > ());   
  }
#line 2884 "parser.tab.cc"
    break;


#line 2888 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char Parser::yypact_ninf_ = -79;

  const signed char Parser::yytable_ninf_ = -14;

  const short
  Parser::yypact_[] =
  {
      94,   -79,   -79,   -79,    -5,   113,   -79,   -79,    13,    17,
     -79,   -79,   -79,     5,   -79,    23,    91,    26,   119,    71,
     -79,    -3,    89,   -79,   134,   -79,    -3,    64,   -79,   -79,
     -79,    -3,    52,   -79,   -79,   119,    66,    70,    83,    93,
      97,   -79,   -79,   -79,    66,   302,   -79,   -79,   -79,   -79,
     -79,   -79,   170,   203,   -79,    95,   -79,   -79,   102,    22,
     -79,    66,   -79,   -79,   -79,    20,   129,   -79,   -79,   143,
     -79,   151,    -6,   144,    98,   130,   110,   -79,   116,    66,
      66,    66,     0,     9,   236,   -79,   269,   -79,   -79,   -79,
      66,    66,   177,   180,   -79,   -79,    -3,   -79,   -79,   176,
      37,    66,   -79,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    48,   172,    59,   173,   188,   111,
     -79,   -79,   -79,   188,    29,   -79,   -79,   -79,   -79,   -79,
     112,   144,    98,   130,   130,   110,   110,   110,   110,   116,
     116,   -79,   -79,   302,    66,   302,   -79,   175,    66,   -79,
     -79,   -79,    14,   191,   -79,   188,    66,   302,   184,   -79,
     302,   -79
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,    10,    11,    12,     0,     0,     2,     3,     0,     6,
       1,     4,     5,     0,     8,     0,     0,     0,     0,     0,
      15,     0,     0,    16,     0,     9,     0,     0,    23,    13,
      19,     0,    21,    18,    14,     0,     0,     0,     0,     0,
      72,    73,    74,    75,     0,     0,    28,    80,    34,    79,
      82,    81,     0,     0,    32,     0,    38,    39,     0,    60,
      65,     0,    36,    37,    26,     0,     0,    24,    22,     0,
      17,    72,     0,    45,    47,    49,    52,    62,    57,     0,
       0,     0,     0,     0,     0,    30,     0,    29,    33,    42,
       0,     0,     0,     0,    71,    61,     0,    25,     7,     0,
       0,     0,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    67,    77,     0,
      76,    35,    31,    41,     0,    70,    69,    27,    20,    67,
       0,    46,    48,    50,    51,    53,    55,    54,    56,    58,
      59,    63,    64,     0,     0,     0,    43,    68,     0,    66,
      68,    84,     0,     0,    44,    78,     0,     0,     0,    83,
       0,    85
  };

  const short
  Parser::yypgoto_[] =
  {
     -79,   -79,   198,   -79,   199,   -79,     7,   -79,   -79,   178,
     -79,   -22,   183,   -21,   -79,   -79,    40,   -52,   -78,   -79,
     -79,   -33,   114,   118,    76,    58,   -24,    78,   -79,   -79,
     122,   -79,   -79,   -79
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     5,     6,    15,     7,    17,    26,    14,    22,    23,
      32,    33,    27,    28,    65,    25,    53,    54,    55,    56,
      57,   118,    73,    74,    75,    76,    77,    78,    59,    60,
     119,    61,    62,    63
  };

  const short
  Parser::yytable_[] =
  {
      58,    88,   115,    72,    64,   101,    67,     8,     9,    68,
      30,    83,     8,    71,    41,    42,    43,    44,   117,   102,
     101,    58,    16,    21,    47,   101,    13,   120,    58,    58,
     -13,    67,    88,    31,    88,    49,    50,    95,    51,   156,
     101,    91,    21,    96,    18,    97,   114,    24,   116,   149,
      71,    41,    42,    43,    44,   129,    58,   123,   124,   101,
      58,    47,    58,    92,    93,    94,   143,     1,     2,     3,
     101,    69,    49,    50,   127,    51,    19,   145,   158,    71,
      41,    42,    43,    44,    29,    84,    66,    79,   141,   142,
      47,   151,    86,   153,     1,     2,     3,     1,     2,     3,
      80,    49,    50,    19,    51,   159,     4,    34,   161,    20,
      81,   152,    35,    10,    82,   155,     1,     2,     3,    58,
      89,    58,     1,     2,     3,     4,   104,   105,    90,   147,
     150,    19,    58,    58,   148,   148,    58,     1,     2,     3,
      36,    37,    38,    39,   110,   111,    19,    40,    41,    42,
      43,    44,   112,   113,    98,    45,    46,    99,    47,    48,
     106,   107,   108,   109,   135,   136,   137,   138,   100,    49,
      50,   103,    51,     1,     2,     3,    36,    37,    38,    39,
     133,   134,    19,    40,    41,    42,    43,    44,   139,   140,
     125,    45,    85,   126,    47,    48,   128,   144,   146,   101,
     154,   157,   160,    11,    12,    49,    50,    52,    51,    36,
      37,    38,    39,    70,     0,   131,    40,    41,    42,    43,
      44,   132,   130,     0,    45,    87,     0,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
       0,    51,    36,    37,    38,    39,     0,     0,     0,    40,
      41,    42,    43,    44,     0,     0,     0,    45,   121,     0,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,     0,    51,    36,    37,    38,    39,     0,
       0,     0,    40,    41,    42,    43,    44,     0,     0,     0,
      45,   122,     0,    47,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,     0,    51,    36,    37,
      38,    39,     0,     0,     0,    40,    41,    42,    43,    44,
       0,     0,     0,    45,     0,     0,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,     0,
      51
  };

  const short
  Parser::yycheck_[] =
  {
      24,    53,    80,    36,    26,    11,    27,     0,    13,    31,
      13,    44,     5,    13,    14,    15,    16,    17,    18,    25,
      11,    45,    17,    16,    24,    11,    13,    18,    52,    53,
      13,    52,    84,    36,    86,    35,    36,    61,    38,    25,
      11,    19,    35,    23,    21,    25,    79,    21,    81,    20,
      13,    14,    15,    16,    17,    18,    80,    90,    91,    11,
      84,    24,    86,    41,    42,    43,    18,     3,     4,     5,
      11,    19,    35,    36,    96,    38,    12,    18,   156,    13,
      14,    15,    16,    17,    13,    45,    22,    17,   112,   113,
      24,   143,    52,   145,     3,     4,     5,     3,     4,     5,
      17,    35,    36,    12,    38,   157,    12,    18,   160,    18,
      17,   144,    23,     0,    17,   148,     3,     4,     5,   143,
      25,   145,     3,     4,     5,    12,    28,    29,    26,    18,
      18,    12,   156,   157,    23,    23,   160,     3,     4,     5,
       6,     7,     8,     9,    34,    35,    12,    13,    14,    15,
      16,    17,    36,    37,    25,    21,    22,    14,    24,    25,
      30,    31,    32,    33,   106,   107,   108,   109,    17,    35,
      36,    27,    38,     3,     4,     5,     6,     7,     8,     9,
     104,   105,    12,    13,    14,    15,    16,    17,   110,   111,
      13,    21,    22,    13,    24,    25,    20,    25,    25,    11,
      25,    10,    18,     5,     5,    35,    36,    24,    38,     6,
       7,     8,     9,    35,    -1,   101,    13,    14,    15,    16,
      17,   103,   100,    -1,    21,    22,    -1,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      -1,    38,     6,     7,     8,     9,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    21,    22,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    -1,    38,     6,     7,     8,     9,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      21,    22,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    -1,    38,     6,     7,
       8,     9,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    21,    -1,    -1,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    -1,
      38
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,     4,     5,    12,    45,    46,    48,    50,    13,
       0,    46,    48,    13,    51,    47,    17,    49,    21,    12,
      18,    50,    52,    53,    21,    59,    50,    56,    57,    13,
      13,    36,    54,    55,    18,    23,     6,     7,     8,     9,
      13,    14,    15,    16,    17,    21,    22,    24,    25,    35,
      36,    38,    56,    60,    61,    62,    63,    64,    70,    72,
      73,    75,    76,    77,    55,    58,    22,    57,    55,    19,
      53,    13,    65,    66,    67,    68,    69,    70,    71,    17,
      17,    17,    17,    65,    60,    22,    60,    22,    61,    25,
      26,    19,    41,    42,    43,    70,    23,    25,    25,    14,
      17,    11,    25,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    65,    62,    65,    18,    65,    74,
      18,    22,    22,    65,    65,    13,    13,    55,    20,    18,
      74,    66,    67,    68,    68,    69,    69,    69,    69,    71,
      71,    70,    70,    18,    25,    18,    25,    18,    23,    20,
      18,    61,    65,    61,    25,    65,    25,    10,    62,    61,
      18,    61
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    44,    45,    45,    45,    45,    47,    46,    49,    48,
      50,    50,    50,    50,    51,    51,    52,    52,    53,    54,
      54,    55,    55,    56,    56,    57,    58,    58,    59,    59,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    62,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    67,    68,    68,    68,    68,    68,    69,    69,    69,
      70,    70,    71,    71,    71,    72,    72,    72,    72,    72,
      72,    72,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    75,    75,    76,    77,    77
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     0,     7,     0,     4,
       1,     1,     1,     2,     4,     3,     1,     3,     2,     1,
       4,     1,     2,     1,     2,     3,     1,     3,     2,     3,
       3,     4,     1,     2,     1,     3,     1,     1,     1,     1,
       3,     3,     2,     4,     5,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     2,     1,     3,     3,     1,     4,     3,     4,     3,
       3,     2,     1,     1,     1,     1,     3,     1,     3,     1,
       1,     1,     1,     7,     5,     9
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "VOID", "INT", "FLOAT",
  "RETURN", "WHILE", "FOR", "IF", "ELSE", "OR_OP", "STRUCT", "IDENTIFIER",
  "INT_CONSTANT", "FLOAT_CONSTANT", "STRING_LITERAL", "'('", "')'", "'['",
  "']'", "'{'", "'}'", "','", "'!'", "';'", "'='", "AND_OP", "EQ_OP",
  "NE_OP", "'<'", "LE_OP", "'>'", "GE_OP", "'+'", "'-'", "'*'", "'/'",
  "'&'", "USTAR", "UMINUS", "PTR_OP", "'.'", "INC_OP", "$accept",
  "translation_unit", "struct_specifier", "$@1", "function_definition",
  "$@2", "type_specifier", "fun_declarator", "parameter_list",
  "parameter_declaration", "declarator_arr", "declarator",
  "declaration_list", "declaration", "declarator_list",
  "compound_statement", "statement_list", "statement",
  "assignment_expression", "assignment_statement", "procedure_call",
  "expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression", "unary_expression",
  "multiplicative_expression", "postfix_expression", "primary_expression",
  "expression_list", "unary_operator", "selection_statement",
  "iteration_statement", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   122,   122,   126,   129,   130,   138,   137,   161,   160,
     227,   230,   233,   236,   242,   246,   252,   258,   267,   277,
     280,   296,   299,   306,   358,   410,   416,   420,   428,   431,
     434,   438,   446,   451,   459,   462,   465,   468,   471,   476,
     479,   508,   561,   568,   596,   655,   659,   679,   682,   700,
     703,   741,   778,   781,   822,   865,   906,   953,   956,  1010,
    1062,  1065,  1126,  1129,  1159,  1196,  1199,  1225,  1252,  1302,
    1321,  1338,  1359,  1370,  1379,  1384,  1389,  1395,  1399,  1406,
    1409,  1412,  1415,  1421,  1429,  1434
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,     2,     2,     2,    38,     2,
      17,    18,    36,    34,    23,    35,    42,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
      30,    26,    32,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    19,     2,    20,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,    22,     2,     2,     2,     2,
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
      15,    16,    27,    28,    29,    31,    33,    39,    40,    41,
      43
    };
    // Last valid token kind.
    const int code_max = 280;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "parser.yy"
} // IPL
#line 3399 "parser.tab.cc"

#line 1442 "parser.yy"

void 
IPL::Parser::error( const location_type &l, const std::string &err_message )
{
	std::cout << "Error at line " << l.begin.line << ": " << err_message << "\n";
//    std::cout << "Error at location " << l << ": " << err_message << "\n";
    exit(1);

}
