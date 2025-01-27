module.exports = grammar({
  name: 'custom_lang',

  rules: {
    program: $ => repeat(choice(
      $.block,
      $.procedure,
      $.function
    )),

    block: $ => repeat($.expression),

    function: $ => seq(
      'FUNCTION', $.identifier,
      optional(seq(
        '(', 
        sepBy(',', seq(optional(choice('BYREF', 'BYVAL')), $.identifier, ':', $.data_type)),
        ')'
      )),
      'RETURNS', $.data_type,
      $.block,
      'ENDPROCEDURE'
    ),

    procedure: $ => seq(
      'PROCEDURE', $.identifier,
      optional(seq(
        '(', 
        sepBy(',', seq(optional(choice('BYREF', 'BYVAL')), $.identifier, ':', $.data_type)),
        ')'
      )),
      $.block,
      'ENDPROCEDURE'
    ),

    expression: $ => choice(
      $.evaluation_expression,
      $.declare_statement,
      seq('CONSTANT', $.identifier, '=', choice($.integer, $.real, $.boolean, $.char, $.string))
    ),

    declare_statement: $ => seq(
      'DECLARE', sepBy(',', $.identifier), ':', optional(seq('ARRAY', '[', $.evaluation_expression, ':', $.evaluation_expression, ']', 'OF')), $.data_type
    ),

    data_type: $ => choice(
      'L_INTEGER', 'L_REAL', 'L_BOOLEAN', 'L_CHAR', 'L_STRING', $.identifier
    ),

    identifier: $ => /[a-zA-Z_][a-zA-Z0-9_]*/,
    integer: $ => /-?\d+/,
    real: $ => /-?\d+\.\d+/,
    boolean: $ => choice('TRUE', 'FALSE'),
    char: $ => /'[^']'/,
    string: $ => /"[^"]*"/
  }
});

function sepBy(sep, rule) {
  return optional(seq(rule, repeat(seq(sep, rule))));
}

