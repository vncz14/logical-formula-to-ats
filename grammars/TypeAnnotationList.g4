grammar TypeAnnotationList;

typeAnnotationList : typeAnnotation | typeAnnotation typeAnnotationList;
typeAnnotation : 
                'Enum' Id '{' commaSeparatedIdList '}' ';'
              | 'Int' Id ';'
              | 'Bool' Id ';';
commaSeparatedIdList : Id | Id ',' commaSeparatedIdList;

Id : [a-zA-Z_][a-zA-Z0-9_]*;
WS : [ \t\r\n]+ -> skip;
