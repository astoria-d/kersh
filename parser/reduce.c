
#include <stdio.h>

#include "idtbl.h"
#include "parser.h"
#include "reduce.h"
#include "code.h"


static void declaration_0(void) {
    struct code_block* cb;
    struct type_definition* decl;

    if (!get_decl_handled()) {
        cb = get_current_cb();
        decl = lookup_declaration();
        cb_add_declaration(cb, decl);
    }
    else {
        /*enum, struct are already there. reset the flag.*/
        set_decl_handled(0);
    }
}

static void declaration_1(void) {
    struct code_block* cb;
    struct type_definition* decl;

    if (!get_decl_handled()) {
        cb = get_current_cb();
        decl = lookup_declaration();
        cb_add_declaration(cb, decl);
    }
    else {
        /*enum, struct are already there. reset the flag.*/
        set_decl_handled(0);
    }
}

static void declarator_0(void) {
}

static void declarator_1(void) {
}

static void struct_or_union_specifier_0(void) {
    struct code_block* cb;
    struct type_definition* td;

    cb = get_current_cb();
    td = get_current_td();
    cb_close_struct_block(cb, td);
    exit_parse_stage();
}

static void struct_or_union_specifier_1(void) {
    struct code_block* cb;
    struct type_definition* td;

    cb = get_current_cb();
    td = get_current_td();
    cb_close_struct_block(cb, td);
    exit_parse_stage();
}

static void struct_or_union_specifier_2(void) {
    struct code_block* cb;
    struct type_definition* td;

    cb = get_current_cb();
    td = get_current_td();
//    cb_close_struct_block(cb, td);
    exit_parse_stage();
}

static void struct_declaration_0(void) {
    struct type_definition* td;
    struct type_definition* fld;

    td = get_current_td();
    fld = lookup_declaration();
    cb_add_struct_field(td, fld);
}

static void struct_declaration_1(void) {
    struct type_definition* td;
    struct type_definition* fld;

    td = get_current_td();
    fld = lookup_declaration();
    cb_add_struct_field(td, fld);
}

static void struct_declarator_0(void) {
}

static void enum_specifier_0(void) {
    struct code_block* cb;
    struct type_definition* td;

    cb = get_current_cb();
    td = get_current_td();
    cb_close_enum_block(cb, td);
    exit_parse_stage();
}

static void enum_specifier_1(void) {
    struct code_block* cb;
    struct type_definition* td;

    cb = get_current_cb();
    td = get_current_td();
    cb_close_enum_block(cb, td);
    exit_parse_stage();
}

static void enum_specifier_2(void) {
    struct code_block* cb;
    struct type_definition* td;

    cb = get_current_cb();
    td = get_current_td();
    cb_close_enum_block(cb, td);
    exit_parse_stage();
}

static void enum_specifier_3(void) {
    struct code_block* cb;
    struct type_definition* td;

    cb = get_current_cb();
    td = get_current_td();
    cb_close_enum_block(cb, td);
    exit_parse_stage();
}

static void enum_specifier_4(void) {
    exit_parse_stage();
}


static void emumerator_0(void) {
    int val = get_enum_index();
    struct type_definition* td;

    td = get_current_td();
    cb_add_enum_elm(&td->members, get_old_identifer(), val);
    set_enum_index(val + 1);
}

static void emumerator_1(void) {
    int val = get_const_val();
    struct type_definition* td;

    td = get_current_td();
    cb_add_enum_elm(&td->members, get_old_identifer(), val);
    set_enum_index(val + 1);
}

static void function_definition_0(void) {
    printf("func end.\n");
}

static void function_definition_1(void) {
    printf("func end.\n");
}

typedef void (*reduce_hander)(void);

reduce_hander reduce_hander_array [] = {
/*   0 null_index                               */ NULL,
/*   1 identifier_0                             */ NULL,
/*   2 indx_constant_0                          */ NULL,
/*   3 indx_constant_1                          */ NULL,
/*   4 indx_constant_2                          */ NULL,
/*   5 indx_integer_constant_0                  */ NULL,
/*   6 indx_integer_constant_1                  */ NULL,
/*   7 indx_integer_constant_2                  */ NULL,
/*   8 indx_emumeration_constant_0              */ NULL,
/*   9 indx_character_constant_0                */ NULL,
/*  10 indx_string_literal_0                    */ NULL,
/*  11 indx_primary_expression_0                */ NULL,
/*  12 indx_primary_expression_1                */ NULL,
/*  13 indx_primary_expression_2                */ NULL,
/*  14 indx_primary_expression_3                */ NULL,
/*  15 indx_postfix_expression_0                */ NULL,
/*  16 indx_postfix_expression_1                */ NULL,
/*  17 indx_postfix_expression_2                */ NULL,
/*  18 indx_postfix_expression_3                */ NULL,
/*  19 indx_postfix_expression_4                */ NULL,
/*  20 indx_postfix_expression_5                */ NULL,
/*  21 indx_postfix_expression_6                */ NULL,
/*  22 indx_postfix_expression_7                */ NULL,
/*  23 indx_postfix_expression_8                */ NULL,
/*  24 indx_postfix_expression_9                */ NULL,
/*  25 indx_argument_expression_list_0          */ NULL,
/*  26 indx_argument_expression_list_1          */ NULL,
/*  27 indx_unary_expression_0                  */ NULL,
/*  28 indx_unary_expression_1                  */ NULL,
/*  29 indx_unary_expression_2                  */ NULL,
/*  30 indx_unary_expression_3                  */ NULL,
/*  31 indx_unary_expression_4                  */ NULL,
/*  32 indx_unary_expression_5                  */ NULL,
/*  33 indx_unary_operator_0                    */ NULL,
/*  34 indx_unary_operator_1                    */ NULL,
/*  35 indx_unary_operator_2                    */ NULL,
/*  36 indx_unary_operator_3                    */ NULL,
/*  37 indx_unary_operator_4                    */ NULL,
/*  38 indx_unary_operator_5                    */ NULL,
/*  39 indx_cast_expression_0                   */ NULL,
/*  40 indx_cast_expression_1                   */ NULL,
/*  41 indx_multipricative_expression_0         */ NULL,
/*  42 indx_multipricative_expression_1         */ NULL,
/*  43 indx_multipricative_expression_2         */ NULL,
/*  44 indx_multipricative_expression_3         */ NULL,
/*  45 indx_additive_expression_0               */ NULL,
/*  46 indx_additive_expression_1               */ NULL,
/*  47 indx_additive_expression_2               */ NULL,
/*  48 indx_shift_expression_0                  */ NULL,
/*  49 indx_shift_expression_1                  */ NULL,
/*  50 indx_shift_expression_2                  */ NULL,
/*  51 indx_relational_expression_0             */ NULL,
/*  52 indx_relational_expression_1             */ NULL,
/*  53 indx_relational_expression_2             */ NULL,
/*  54 indx_relational_expression_3             */ NULL,
/*  55 indx_relational_expression_4             */ NULL,
/*  56 indx_equality_expression_0               */ NULL,
/*  57 indx_equality_expression_1               */ NULL,
/*  58 indx_equality_expression_2               */ NULL,
/*  59 indx_AND_expression_0                    */ NULL,
/*  60 indx_AND_expression_1                    */ NULL,
/*  61 indx_exclusive_OR_expression_0           */ NULL,
/*  62 indx_exclusive_OR_expression_1           */ NULL,
/*  63 indx_inclusive_OR_expression_0           */ NULL,
/*  64 indx_inclusive_OR_expression_1           */ NULL,
/*  65 indx_logical_AND_expression_0            */ NULL,
/*  66 indx_logical_AND_expression_1            */ NULL,
/*  67 indx_logical_OR_expression_0             */ NULL,
/*  68 indx_logical_OR_expression_1             */ NULL,
/*  69 indx_conditional_expression_0            */ NULL,
/*  70 indx_conditional_expression_1            */ NULL,
/*  71 indx_assignment_expression_0             */ NULL,
/*  72 indx_assignment_expression_1             */ NULL,
/*  73 indx_assignment_operator_0               */ NULL,
/*  74 indx_assignment_operator_1               */ NULL,
/*  75 indx_assignment_operator_2               */ NULL,
/*  76 indx_assignment_operator_3               */ NULL,
/*  77 indx_assignment_operator_4               */ NULL,
/*  78 indx_assignment_operator_5               */ NULL,
/*  79 indx_assignment_operator_6               */ NULL,
/*  80 indx_assignment_operator_7               */ NULL,
/*  81 indx_assignment_operator_8               */ NULL,
/*  82 indx_assignment_operator_9               */ NULL,
/*  83 indx_assignment_operator_10              */ NULL,
/*  84 indx_expression_0                        */ NULL,
/*  85 indx_expression_1                        */ NULL,
/*  86 indx_constant_expression_0               */ NULL,
/*  87 indx_declaration_0                       */ declaration_0,
/*  88 indx_declaration_1                       */ declaration_1,
/*  89 indx_declaration_specifiers_0            */ NULL,
/*  90 indx_declaration_specifiers_1            */ NULL,
/*  91 indx_declaration_specifiers_2            */ NULL,
/*  92 indx_declaration_specifiers_3            */ NULL,
/*  93 indx_declaration_specifiers_4            */ NULL,
/*  94 indx_declaration_specifiers_5            */ NULL,
/*  95 indx_declaration_specifiers_6            */ NULL,
/*  96 indx_declaration_specifiers_7            */ NULL,
/*  97 indx_init_declarator_list_0              */ NULL,
/*  98 indx_init_declarator_list_1              */ NULL,
/*  99 indx_init_declarator_0                   */ NULL,
/* 100 indx_init_declarator_1                   */ NULL,
/* 101 indx_storage_class_specifier_0           */ NULL,
/* 102 indx_storage_class_specifier_1           */ NULL,
/* 103 indx_storage_class_specifier_2           */ NULL,
/* 104 indx_storage_class_specifier_3           */ NULL,
/* 105 indx_storage_class_specifier_4           */ NULL,
/* 106 indx_type_specifier_0                    */ NULL,
/* 107 indx_type_specifier_1                    */ NULL,
/* 108 indx_type_specifier_2                    */ NULL,
/* 109 indx_type_specifier_3                    */ NULL,
/* 110 indx_type_specifier_4                    */ NULL,
/* 111 indx_type_specifier_5                    */ NULL,
/* 112 indx_type_specifier_6                    */ NULL,
/* 113 indx_type_specifier_7                    */ NULL,
/* 114 indx_type_specifier_8                    */ NULL,
/* 115 indx_type_specifier_9                    */ NULL,
/* 116 indx_struct_or_union_specifier_0         */ struct_or_union_specifier_0,
/* 117 indx_struct_or_union_specifier_1         */ struct_or_union_specifier_1,
/* 118 indx_struct_or_union_specifier_2         */ struct_or_union_specifier_2,
/* 119 indx_struct_or_union_0                   */ NULL,
/* 120 indx_struct_or_union_1                   */ NULL,
/* 121 indx_struct_declaration_list_0           */ NULL,
/* 122 indx_struct_declaration_list_1           */ NULL,
/* 123 indx_struct_declaration_0                */ struct_declaration_0,
/* 124 indx_struct_declaration_1                */ struct_declaration_1,
/* 125 indx_specifier_qualifier_list_0          */ NULL,
/* 126 indx_specifier_qualifier_list_1          */ NULL,
/* 127 indx_specifier_qualifier_list_2          */ NULL,
/* 128 indx_specifier_qualifier_list_3          */ NULL,
/* 129 indx_struct_declarator_list_0            */ NULL,
/* 130 indx_struct_declarator_list_1            */ NULL,
/* 131 indx_struct_declarator_0                 */ struct_declarator_0,
/* 132 indx_struct_declarator_1                 */ NULL,
/* 133 indx_struct_declarator_2                 */ NULL,
/* 134 indx_enum_specifier_0                    */ enum_specifier_0,
/* 135 indx_enum_specifier_1                    */ enum_specifier_1,
/* 136 indx_enum_specifier_2                    */ enum_specifier_2,
/* 137 indx_enum_specifier_3                    */ enum_specifier_3,
/* 138 indx_enum_specifier_4                    */ enum_specifier_4,
/* 139 indx_emumerator_list_0                   */ NULL,
/* 140 indx_emumerator_list_1                   */ NULL,
/* 141 indx_emumerator_0                        */ emumerator_0,
/* 142 indx_emumerator_1                        */ emumerator_1,
/* 143 indx_type_qualifier_0                    */ NULL,
/* 144 indx_type_qualifier_1                    */ NULL,
/* 145 indx_function_speficier_0                */ NULL,
/* 146 indx_declarator_0                        */ declarator_0,
/* 147 indx_declarator_1                        */ declarator_1,
/* 148 indx_direct_declarator_0                 */ NULL,
/* 149 indx_direct_declarator_1                 */ NULL,
/* 150 indx_direct_declarator_2                 */ NULL,
/* 151 indx_direct_declarator_3                 */ NULL,
/* 152 indx_direct_declarator_4                 */ NULL,
/* 153 indx_direct_declarator_5                 */ NULL,
/* 154 indx_direct_declarator_6                 */ NULL,
/* 155 indx_direct_declarator_7                 */ NULL,
/* 156 indx_direct_declarator_8                 */ NULL,
/* 157 indx_direct_declarator_9                 */ NULL,
/* 158 indx_direct_declarator_10                */ NULL,
/* 159 indx_direct_declarator_11                */ NULL,
/* 160 indx_direct_declarator_12                */ NULL,
/* 161 indx_direct_declarator_13                */ NULL,
/* 162 indx_pointer_0                           */ NULL,
/* 163 indx_pointer_1                           */ NULL,
/* 164 indx_pointer_2                           */ NULL,
/* 165 indx_pointer_3                           */ NULL,
/* 166 indx_type_qualifier_list_0               */ NULL,
/* 167 indx_type_qualifier_list_1               */ NULL,
/* 168 indx_parameter_type_list_0               */ NULL,
/* 169 indx_parameter_type_list_1               */ NULL,
/* 170 indx_parameter_list_0                    */ NULL,
/* 171 indx_parameter_list_1                    */ NULL,
/* 172 indx_parameter_declaration_0             */ NULL,
/* 173 indx_parameter_declaration_1             */ NULL,
/* 174 indx_parameter_declaration_2             */ NULL,
/* 175 indx_identifier_list_0                   */ NULL,
/* 176 indx_identifier_list_1                   */ NULL,
/* 177 indx_type_name_0                         */ NULL,
/* 178 indx_type_name_1                         */ NULL,
/* 179 indx_abstract_declarator_0               */ NULL,
/* 180 indx_abstract_declarator_1               */ NULL,
/* 181 indx_abstract_declarator_2               */ NULL,
/* 182 indx_direct_abstract_declarator_0        */ NULL,
/* 183 indx_direct_abstract_declarator_1        */ NULL,
/* 184 indx_direct_abstract_declarator_2        */ NULL,
/* 185 indx_direct_abstract_declarator_3        */ NULL,
/* 186 indx_direct_abstract_declarator_4        */ NULL,
/* 187 indx_direct_abstract_declarator_5        */ NULL,
/* 188 indx_direct_abstract_declarator_6        */ NULL,
/* 189 indx_direct_abstract_declarator_7        */ NULL,
/* 190 indx_direct_abstract_declarator_8        */ NULL,
/* 191 indx_direct_abstract_declarator_9        */ NULL,
/* 192 indx_direct_abstract_declarator_10       */ NULL,
/* 193 indx_direct_abstract_declarator_11       */ NULL,
/* 194 indx_direct_abstract_declarator_12       */ NULL,
/* 195 indx_direct_abstract_declarator_13       */ NULL,
/* 196 indx_direct_abstract_declarator_14       */ NULL,
/* 197 indx_direct_abstract_declarator_15       */ NULL,
/* 198 indx_direct_abstract_declarator_16       */ NULL,
/* 199 indx_direct_abstract_declarator_17       */ NULL,
/* 200 indx_direct_abstract_declarator_18       */ NULL,
/* 201 indx_direct_abstract_declarator_19       */ NULL,
/* 202 indx_direct_abstract_declarator_20       */ NULL,
/* 203 indx_typedef_name_0                      */ NULL,
/* 204 indx_initializer_0                       */ NULL,
/* 205 indx_initializer_1                       */ NULL,
/* 206 indx_initializer_2                       */ NULL,
/* 207 indx_initializer_list_0                  */ NULL,
/* 208 indx_initializer_list_1                  */ NULL,
/* 209 indx_initializer_list_2                  */ NULL,
/* 210 indx_initializer_list_3                  */ NULL,
/* 211 indx_designation_0                       */ NULL,
/* 212 indx_designator_list_0                   */ NULL,
/* 213 indx_designator_list_1                   */ NULL,
/* 214 indx_designator_0                        */ NULL,
/* 215 indx_designator_1                        */ NULL,
/* 216 indx_statement_0                         */ NULL,
/* 217 indx_statement_1                         */ NULL,
/* 218 indx_statement_2                         */ NULL,
/* 219 indx_statement_3                         */ NULL,
/* 220 indx_statement_4                         */ NULL,
/* 221 indx_statement_5                         */ NULL,
/* 222 indx_labeled_statement_0                 */ NULL,
/* 223 indx_labeled_statement_1                 */ NULL,
/* 224 indx_labeled_statement_2                 */ NULL,
/* 225 indx_compound_statement_0                */ NULL,
/* 226 indx_compound_statement_1                */ NULL,
/* 227 indx_block_item_list_0                   */ NULL,
/* 228 indx_block_item_list_1                   */ NULL,
/* 229 indx_block_item_0                        */ NULL,
/* 230 indx_block_item_1                        */ NULL,
/* 231 indx_expression_statement_0              */ NULL,
/* 232 indx_expression_statement_1              */ NULL,
/* 233 indx_selection_statement_0               */ NULL,
/* 234 indx_selection_statement_1               */ NULL,
/* 235 indx_selection_statement_2               */ NULL,
/* 236 indx_iteration_statement_0               */ NULL,
/* 237 indx_iteration_statement_1               */ NULL,
/* 238 indx_iteration_statement_2               */ NULL,
/* 239 indx_iteration_statement_3               */ NULL,
/* 240 indx_iteration_statement_4               */ NULL,
/* 241 indx_iteration_statement_5               */ NULL,
/* 242 indx_iteration_statement_6               */ NULL,
/* 243 indx_iteration_statement_7               */ NULL,
/* 244 indx_iteration_statement_8               */ NULL,
/* 245 indx_iteration_statement_9               */ NULL,
/* 246 indx_iteration_statement_10              */ NULL,
/* 247 indx_iteration_statement_11              */ NULL,
/* 248 indx_iteration_statement_12              */ NULL,
/* 249 indx_iteration_statement_13              */ NULL,
/* 250 indx_jump_statement_0                    */ NULL,
/* 251 indx_jump_statement_1                    */ NULL,
/* 252 indx_jump_statement_2                    */ NULL,
/* 253 indx_jump_statement_3                    */ NULL,
/* 254 indx_jump_statement_4                    */ NULL,
/* 255 indx_translation_unit_0                  */ NULL,
/* 256 indx_translation_unit_1                  */ NULL,
/* 257 indx_external_declaration_0              */ NULL,
/* 258 indx_external_declaration_1              */ NULL,
/* 259 indx_function_definition_0               */ function_definition_0,
/* 260 indx_function_definition_1               */ function_definition_1,
/* 261 indx_declaration_list_0                  */ NULL,
/* 262 indx_declaration_list_1                  */ NULL
};

void post_reduce_action(int rule_index) {
    if (reduce_hander_array[rule_index] != NULL) {
        (*reduce_hander_array[rule_index])();
    }
}

