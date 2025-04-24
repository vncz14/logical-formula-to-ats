grammar Formula;

formula
    : '(' formula ')'
    | formula '->' formula
    | '!' formula
    | formula '&' formula
    | formula '|' formula
    | 'true'
    | 'false'
    | predicates
    | 'O' formula
    | 'H' formula
    | formula 'S' formula
    | 'Y' formula
    ;

predicates
    : Id '>' term
    | Id '<' term
    | Id '=' term
    | Id '!=' term
    | Id '>=' term
    | Id '<=' term
    ;

term
    : Id
    | Int
    | Bool
    ;

Id
    : [a-zA-Z_][a-zA-Z0-9_]*
    ;

Int
    : [0-9]+
    ;

Bool
    : 'true'
    | 'false'
    ;

WS
    : [ \t\r\n]+ -> skip
    ;