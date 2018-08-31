#ifndef MTOKENTYPE_H
#define MTOKENTYPE_H

/**
 * @brief Enum for describing the Type of a token generated by the lexer
 *
 */
enum MTokenType
{
    PRIORITIZER,        //Brackets (,),[,],{,}, ...
    OPERATOR,           //+, -, *, /, ^, %
    NUMBER,             //double
    VARIABLE,           //x, y, z, ...
    FUNCTION,           //f(x), sin, cos, tan, ....
    CONSTANT,           //pi, ...
    COMPARATOR,          //=,=<,>=, <, >, ...
    LINK,               //spezial function
    UNDEFINED           //undefined
};
#endif // MTOKENTYPE_H
