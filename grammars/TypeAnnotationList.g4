grammar TypeAnnotationList;

typeAnnotationList : typeAnnotation*;
typeAnnotation : 
                'Enum' Id '{' commaSeparatedIdList '}' ';'
              | 'Int' Id ';'
              | 'Bool' Id ';';
commaSeparatedIdList : Id (',' Id)*;

Id : [a-zA-Z_][a-zA-Z0-9_]*;
WS : [ \t\r\n]+ -> skip;
