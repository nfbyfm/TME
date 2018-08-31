#include "lexer.h"



#define INIT_FUNCTIONS_START {

    Lexer::Lexer(QObject *parent) : QObject(parent)
    {
        initKeyWords();
    }

    Lexer::~Lexer()
    {
        keywords.clear();
        //qDeleteAll(keywords);   //only needed when List contains pointers
    }

    void Lexer::initKeyWords()
    {
        keywords.clear();
        keywords["sin"]         = MTokenType::FUNCTION;
        keywords["\\sin"]       = MTokenType::FUNCTION;
        keywords["cos"]         = MTokenType::FUNCTION;
        keywords["\\cos"]       = MTokenType::FUNCTION;
        keywords["tan"]         = MTokenType::FUNCTION;
        keywords["\\tan"]       = MTokenType::FUNCTION;

        keywords["abs"]       = MTokenType::FUNCTION;
        keywords["\\abs"]       = MTokenType::FUNCTION;

        keywords["alpha"]       = MTokenType::VARIABLE;
        keywords["\\alpha"]       = MTokenType::VARIABLE;
        keywords["beta"]       = MTokenType::VARIABLE;
        keywords["\\beta"]       = MTokenType::VARIABLE;
        keywords["gamma"]       = MTokenType::VARIABLE;
        keywords["\\gamma"]       = MTokenType::VARIABLE;
        keywords["Gamma"]       = MTokenType::VARIABLE;
        keywords["\\Gamma"]       = MTokenType::VARIABLE;
        keywords["delta"]       = MTokenType::VARIABLE;
        keywords["\\delta"]       = MTokenType::VARIABLE;
        keywords["Delta"]       = MTokenType::VARIABLE;
        keywords["\\Delta"]       = MTokenType::VARIABLE;
        keywords["epsilon"]       = MTokenType::VARIABLE;
        keywords["\\epsilon"]       = MTokenType::VARIABLE;
        keywords["varepsilon"]       = MTokenType::VARIABLE;
        keywords["\\varepsilon"]       = MTokenType::VARIABLE;
        keywords["zeta"]       = MTokenType::VARIABLE;
        keywords["\\zeta"]       = MTokenType::VARIABLE;
        keywords["eta"]       = MTokenType::VARIABLE;
        keywords["\\eta"]       = MTokenType::VARIABLE;
        keywords["theta"]       = MTokenType::VARIABLE;
        keywords["\\theta"]       = MTokenType::VARIABLE;
        keywords["Theta"]       = MTokenType::VARIABLE;
        keywords["\\Theta"]       = MTokenType::VARIABLE;
        keywords["vartheta"]       = MTokenType::VARIABLE;
        keywords["\\vartheta"]       = MTokenType::VARIABLE;
        keywords["iota"]       = MTokenType::VARIABLE;
        keywords["\\iota"]       = MTokenType::VARIABLE;
        keywords["kappa"]       = MTokenType::VARIABLE;
        keywords["\\kappa"]       = MTokenType::VARIABLE;
        keywords["lambda"]       = MTokenType::VARIABLE;
        keywords["\\lambda"]       = MTokenType::VARIABLE;
        keywords["Lambda"]       = MTokenType::VARIABLE;
        keywords["\\Lambda"]       = MTokenType::VARIABLE;
        keywords["mu"]       = MTokenType::VARIABLE;
        keywords["\\mu"]       = MTokenType::VARIABLE;
        keywords["nu"]       = MTokenType::VARIABLE;
        keywords["\\nu"]       = MTokenType::VARIABLE;
        keywords["xi"]       = MTokenType::VARIABLE;
        keywords["\\xi"]       = MTokenType::VARIABLE;
        keywords["Xi"]       = MTokenType::VARIABLE;
        keywords["\\Xi"]       = MTokenType::VARIABLE;

        keywords["pi"]       = MTokenType::CONSTANT;
        keywords["\\Pi"]       = MTokenType::CONSTANT;

        keywords["rho"]       = MTokenType::VARIABLE;
        keywords["\\rho"]       = MTokenType::VARIABLE;
        keywords["sigma"]       = MTokenType::VARIABLE;
        keywords["\\sigma"]       = MTokenType::VARIABLE;
        keywords["Sigma"]       = MTokenType::VARIABLE;
        keywords["\\Sigma"]       = MTokenType::VARIABLE;
        keywords["tau"]       = MTokenType::VARIABLE;
        keywords["\\tau"]       = MTokenType::VARIABLE;
        keywords["upsilon"]       = MTokenType::VARIABLE;
        keywords["\\upsilon"]       = MTokenType::VARIABLE;
        keywords["phi"]       = MTokenType::VARIABLE;
        keywords["\\phi"]       = MTokenType::VARIABLE;
        keywords["Phi"]       = MTokenType::VARIABLE;
        keywords["\\Phi"]       = MTokenType::VARIABLE;
        keywords["varphi"]       = MTokenType::VARIABLE;
        keywords["\\varphi"]       = MTokenType::VARIABLE;
        keywords["chi"]       = MTokenType::VARIABLE;
        keywords["\\chi"]       = MTokenType::VARIABLE;
        keywords["psi"]       = MTokenType::VARIABLE;
        keywords["\\psi"]       = MTokenType::VARIABLE;
        keywords["Psi"]       = MTokenType::VARIABLE;
        keywords["\\Psi"]       = MTokenType::VARIABLE;
        keywords["omega"]       = MTokenType::VARIABLE;
        keywords["\\omega"]       = MTokenType::VARIABLE;
        keywords["Omega"]       = MTokenType::VARIABLE;
        keywords["\\Omega"]       = MTokenType::VARIABLE;
    }

#define INIT_FUNCTIONS_END }


bool Lexer::start(QStringList *formulas)
{
    //search through text for formuals
    if(formulas!=nullptr)
    {
        lexing(formulas);
        return true;
    }
    else
    {
        //emit Errormessage: no formulas found
        //ErrorMessage *msg = new ErrorMessage(nullptr,ERROR_ID::LEXER_NoFormulasFound, nullptr);
        //emit sendError(msg);
        return false;
    }
}


#define LEXING_FUNCTIONS_START {

QList< QList<MToken *> > Lexer::lexing(QStringList *formulasFromText)
{
    QList< QList<MToken *> > tf_list;
    tf_list.clear();

     if(!formulasFromText->isEmpty())
     {


        int noOfLBrackets;
        int noOfRBrackets;
        int noOfUnclosedBrakets;
        bool underScoreFound;

        //for each formula:
        for(int i = 0; i< formulasFromText->count();i++)
        {

            QString formula =formulasFromText->at(i);//replaceEscapeSequences(formulasFromText.at(i));

            QList<MToken *> tokenList;
            QString buffer ="";
            MTokenType tempType = MTokenType::UNDEFINED;


            //for each char in the formulas-String:
            for(int k=0;k<formula.length();k++)
            {
                QChar cypher = formula.at(k);
                CType type = getType(cypher);

                if(buffer.isEmpty())
                {
                    switch(type)
                    {
                        case CType::LeftBracket:
                            //save as Prioritizer
                            tokenList.append(new MToken(nullptr,cypher,MTokenType::PRIORITIZER));
                            break;

                        case CType::RightBracket:
                            // don't ignore!! -> leads to errors
                            tokenList.append(new MToken(nullptr,cypher,MTokenType::PRIORITIZER));
                            break;

                        case CType::Operator:
                            //save as Operator
                            tokenList.append(new MToken(nullptr,cypher,MTokenType::OPERATOR));
                            break;

                        case CType::Digit:
                            //write into Buffer
                            buffer = cypher;
                            tempType = MTokenType::NUMBER;
                            break;

                        case CType::Letter:
                            //write into buffer
                            buffer = cypher;
                            tempType = MTokenType::VARIABLE;
                            break;

                        case CType::Symbol:
                            //handle like a Variable
                            buffer = cypher;
                            tempType = MTokenType::VARIABLE;
                            break;

                        case CType::Comparator:
                            //save as Comparator
                            tokenList.append(new MToken(nullptr,cypher,MTokenType::COMPARATOR));
                            break;

                        case CType::Dot:
                            //ignore
                            break;

                        case CType::Space:
                            //ignore
                            break;

                        case CType::Backslash:
                            //write into buffer
                            buffer = cypher;
                            tempType = MTokenType::VARIABLE;
                            break;

                        case CType::UnderLine_Apostrophe:
                            //ignore
                            break;
                    }
                }
                else
                {
                    switch(tempType)
                    {
                    case MTokenType::NUMBER:
                        switch(type)
                        {
                            case CType::LeftBracket:
                                //save buffer as number and current char as Prioritizer
                                tokenList.append(new MToken(nullptr,buffer,MTokenType::NUMBER));
                                tokenList.append(new MToken(nullptr,cypher,MTokenType::PRIORITIZER));
                                //reset buffer and tempType-Element
                                buffer = "";
                                tempType = MTokenType::UNDEFINED;
                                break;

                            case CType::RightBracket:
                                //save buffer as number and current char as Prioritizer
                                tokenList.append(new MToken(nullptr,buffer,MTokenType::NUMBER));
                                tokenList.append(new MToken(nullptr,cypher,MTokenType::PRIORITIZER));
                                //reset buffer and tempType-Element
                                buffer = "";
                                tempType = MTokenType::UNDEFINED;
                                break;

                            case CType::Operator:
                                //save buffer as number and current char as Operator
                                tokenList.append(new MToken(nullptr,buffer,MTokenType::NUMBER));
                                tokenList.append(new MToken(nullptr,cypher,MTokenType::OPERATOR));
                                //reset buffer and tempType-Element
                                buffer = "";
                                tempType = MTokenType::UNDEFINED;
                                break;

                            case CType::Digit:
                                //append buffer, tempType stays the same
                                buffer.append(cypher);
                                break;

                            case CType::Letter:
                                //append buffer, change Type to variable
                                buffer.append(cypher);
                                tempType = MTokenType::VARIABLE;
                                break;

                            case CType::Symbol:
                                //like Letter
                                buffer.append(cypher);
                                tempType = MTokenType::VARIABLE;
                                break;

                            case CType::Comparator:
                                //save buffer as number and current char as Comparator
                                tokenList.append(new MToken(nullptr,buffer,MTokenType::NUMBER));
                                tokenList.append(new MToken(nullptr,cypher,MTokenType::COMPARATOR));
                                //reset buffer and tempType-Element
                                buffer = "";
                                tempType = MTokenType::UNDEFINED;
                                break;

                            case CType::Dot:
                                //append buffer, check if there is already a dot in the buffer
                                if(buffer.contains(".") || buffer.contains(","))
                                {
                                    //save buffer as number, ignore current dot
                                    tokenList.append(new MToken(nullptr,buffer,MTokenType::NUMBER));
                                    //reset buffer and tempType-Element
                                    buffer = "";
                                    tempType = MTokenType::UNDEFINED;
                                }
                                else
                                {
                                    //append buffer
                                    buffer.append(cypher);
                                }
                                break;

                            case CType::Space:
                                //save buffer as number
                                tokenList.append(new MToken(nullptr,buffer,MTokenType::NUMBER));
                                //reset buffer and tempType-Element
                                buffer = "";
                                tempType = MTokenType::UNDEFINED;
                                break;

                            case CType::Backslash:
                                //save buffer as number
                                tokenList.append(new MToken(nullptr,buffer,MTokenType::NUMBER));
                                //set new buffer and Type
                                buffer = cypher;
                                tempType = MTokenType::VARIABLE;
                                break;

                            case CType::UnderLine_Apostrophe:
                                //append buffer, set Type to Variable
                                buffer.append(cypher);
                                tempType = MTokenType::VARIABLE;
                                break;
                        }
                        break;
                    case MTokenType::VARIABLE:
                        switch(type)
                        {
                            case CType::LeftBracket:
                                //write to buffer
                                buffer.append(cypher);
                                break;

                            case CType::RightBracket:
                                //check if there are Leftbrackets in the buffer
                                //if number of leftbrackets = number of right brackets -> either function or variable (char before first Leftbraket has to be underscore)
                                //if number of leftbrackets = 0, save as variable and current char as Bracket
                                if(checkBrackets(buffer, noOfLBrackets,noOfRBrackets,noOfUnclosedBrakets, underScoreFound))
                                {
                                    bool unclosedBefore = (noOfUnclosedBrakets>0);


                                    QString checkHelp = buffer + cypher;
                                    //brackets are in the buffer
                                    checkBrackets(checkHelp, noOfLBrackets,noOfRBrackets,noOfUnclosedBrakets, underScoreFound);
                                    if(noOfUnclosedBrakets==0)
                                    {
                                        buffer.append(cypher);
                                        if(underScoreFound)
                                        {
                                            //save as varaible, reset tempType and buffer
                                            //splitVariableString(buffer, tokenList);
                                             tokenList.append(new MToken(nullptr,buffer,MTokenType::VARIABLE));
                                            //reset buffer and tempType-Element
                                            buffer = "";
                                            tempType = MTokenType::UNDEFINED;
                                        }
                                        else
                                        {
                                            //save as function, reset tempType and buffer
                                            if(buffer.toLower().contains("link"))
                                            {
                                                tokenList.append(new MToken(nullptr,buffer,MTokenType::LINK));
                                            }
                                            else
                                            {
                                                tokenList.append(new MToken(nullptr,buffer,MTokenType::FUNCTION));
                                            }
                                            //reset buffer and tempType-Element
                                            buffer = "";
                                            tempType = MTokenType::UNDEFINED;
                                        }
                                    }
                                    else
                                    {
                                        //with the current bracket added the term is still not closed -> check if he was without the current bracket
                                        if(unclosedBefore==false)
                                        {
                                            //save buffer as varaible and current bracket as prioritizer
                                            //splitVariableString(buffer, tokenList);
                                            tokenList.append(new MToken(nullptr,buffer,MTokenType::VARIABLE));
                                            tokenList.append(new MToken(nullptr,cypher,MTokenType::PRIORITIZER));
                                            buffer = "";
                                            tempType = MTokenType::UNDEFINED;
                                        }
                                        else
                                        {
                                            //unclosed Bracket before and with current bracket -> append buffer
                                            buffer.append(cypher);
                                        }
                                    }


                                }
                                else
                                {
                                    //no brackets found
                                    //splitVariableString(buffer,tokenList);
                                    tokenList.append(new MToken(nullptr,buffer,MTokenType::VARIABLE));
                                    tokenList.append(new MToken(nullptr,cypher,MTokenType::PRIORITIZER));
                                    buffer = "";
                                    tempType = MTokenType::UNDEFINED;
                                }
                                break;

                            case CType::Operator:
                                //save buffer as variable and current char as Operator
                                //splitVariableString(buffer,tokenList);
                                tokenList.append(new MToken(nullptr,buffer,MTokenType::VARIABLE));
                                tokenList.append(new MToken(nullptr,cypher,MTokenType::OPERATOR));
                                //reset buffer and tempType-Element
                                buffer = "";
                                tempType = MTokenType::UNDEFINED;
                                break;

                            case CType::Digit:
                                //append buffer
                                buffer.append(cypher);
                                break;

                            case CType::Letter:
                                //append buffer
                                buffer.append(cypher);
                                break;

                            case CType::Symbol:
                                //append buffer
                                buffer.append(cypher);
                                break;

                            case CType::Comparator:
                                //save buffer as variable and current char as Comparator
                                //splitVariableString(buffer,tokenList);
                                tokenList.append(new MToken(nullptr,buffer,MTokenType::VARIABLE));
                                tokenList.append(new MToken(nullptr,cypher,MTokenType::COMPARATOR));
                                //reset buffer and tempType-Element
                                buffer = "";
                                tempType = MTokenType::UNDEFINED;
                                break;

                            case CType::Dot:
                                //check if open brakets -> if there are none, save as variable and ignore dot, else: append
                                if(checkBrackets(buffer, noOfLBrackets,noOfRBrackets,noOfUnclosedBrakets, underScoreFound))
                                {
                                    if(noOfUnclosedBrakets>0)
                                    {
                                        buffer.append(cypher);
                                    }
                                    else
                                    {
                                        tokenList.append(new MToken(nullptr,buffer,tempType));
                                        buffer="";
                                        tempType = MTokenType::UNDEFINED;
                                    }
                                }
                                else
                                {
                                    //no brackets found
                                    tokenList.append(new MToken(nullptr,buffer,tempType));
                                    buffer="";
                                    tempType = MTokenType::UNDEFINED;

                                }
                                break;

                            case CType::Space:
                                //check if open brackets in buffer -> if there are, append; otherwise save buffer and ignore current char
                                if(checkBrackets(buffer, noOfLBrackets,noOfRBrackets,noOfUnclosedBrakets,underScoreFound))
                                {
                                    if(noOfUnclosedBrakets>0)
                                    {
                                        buffer.append(cypher);
                                    }
                                    else
                                    {
                                        //there are brackets but they're all closed
                                        tokenList.append(new MToken(nullptr,buffer,tempType));
                                        buffer="";
                                        tempType = MTokenType::UNDEFINED;
                                    }
                                }
                                else
                                {
                                    //no brakets
                                    tokenList.append(new MToken(nullptr,buffer,tempType));
                                    buffer="";
                                    tempType = MTokenType::UNDEFINED;
                                }
                                break;

                            case CType::Backslash:
                                //save buffer as variable
                                //splitVariableString(buffer,tokenList);
                                tokenList.append(new MToken(nullptr,buffer,MTokenType::VARIABLE));

                                //set buffer and tempType-Element to new Variable
                                buffer = cypher;
                                tempType = MTokenType::VARIABLE;
                                break;

                            case CType::UnderLine_Apostrophe:
                                //append buffer
                                buffer.append(cypher);
                                break;
                        }
                        break;

                    default:
                        break;
                    }

                }

                if((k == (formula.length()-1)) && !(tempType==MTokenType::UNDEFINED))
                {
                    //add last token to list
                    //if(tempType==MTokenType::VARIABLE)
                    //{
                        //splitVariableString(buffer,tokenList);
                    //}

                    tokenList.append(new MToken(nullptr,buffer,tempType));
                }
            }



            tf_list.append(tokenList);
        }


/*
        for(int i=0; i<tf_list.count(); i++)
        {
            qDebug()<<"Lexer:\tFormula: "<<formulasFromText->at(i);
            QList<MToken *> currentTokenList = tf_list.at(i);

            for(int k = 0; k < currentTokenList.count(); k++)
            {
                qDebug()<<currentTokenList.at(k)->toString();
            }
            qDebug()<<"---------------------------\n\n";
        }
*/
        formulasFromText->clear();

     }
     return tf_list;
 }


CType Lexer::getType(QChar alpha)
{
     CType retVal;
     char a = alpha.unicode();

     if( isalpha(a) )
        return CType::Letter;

     if( isdigit(a) )
         return CType::Digit;

     switch(a)
     {
         //LeftBracket
         case '(':
         case '[':
         case '{':
            retVal = CType::LeftBracket;
            break;

         //RightBracket
         case ')':
         case ']':
         case '}':
             retVal = CType::RightBracket;
             break;

         //operator
         case '+':
         case '-':
         case '*':
         case '/':
         case '^':
             retVal = CType::Operator;
             break;

         //comparator
         case '<':
         case '>':
         case '=':
         case '!':
             retVal = CType::Comparator;
             break;

         //Dot
         case '.':
         case ',':
             retVal = CType::Dot;
             break;

         //space
         case ' ':
             retVal = CType::Space;
             break;

         //backslash
         case '\\':
             retVal = CType::Backslash;
             break;

         //underline or apostrophe
         case '\''://the ' character (for derivations and similar things)
         case '_':
             retVal = CType::UnderLine_Apostrophe;
             break;

         default:
            retVal = CType::Symbol;
     }

     return retVal;
 }

//true if there are Brackets in checkStr
bool Lexer::checkBrackets(QString checkStr, int & noOfLBrackets, int & noOfRBrackets, int & noOfUnclosedBrakets, bool & underScoreFound)
{

    noOfUnclosedBrakets = 0;

    std::string openBrackets="";

    int noOfClosedRoundBrackets = 0;
    int noOfClosedSquareBrackets = 0;
    int noOfClosedWavyBrackets = 0;

    int noOfLRoundBrackets = 0;
    int noOfRRoundBrackets = 0;

    int noOfLWavyBrackets = 0;
    int noOfRWavyBrackets = 0;

    int noOfLSquareBrackets = 0;
    int noOfRSquareBrackets = 0;

    //qDebug() <<"";
    //qDebug() <<"Brackettesting: " << checkStr;
    //qDebug() <<"";
    underScoreFound = false;

    for(int i =0; i < checkStr.size(); i++)
    {

        char a = checkStr.at(i).unicode();
        switch(a)
        {
            case '_':
                //-> needed in the main function (differentiate between function and varaible)
                if (!underScoreFound)
                    underScoreFound = ((noOfLRoundBrackets <= 0) && (noOfRRoundBrackets <= 0) && (noOfLWavyBrackets <= 0) && (noOfRWavyBrackets <= 0) && (noOfLSquareBrackets <= 0) && (noOfRSquareBrackets <= 0));
                break;

        //LeftBrackets
            case '(':
                openBrackets += a;
                noOfLRoundBrackets++;
                noOfUnclosedBrakets++;
                break;
            case '{':
                openBrackets += a;
                noOfLWavyBrackets++;
                noOfUnclosedBrakets++;
                break;
            case '[':
                openBrackets += a;
                noOfLSquareBrackets++;
                noOfUnclosedBrakets++;
                break;

        //Rightbrackets
            case ')':
                noOfRRoundBrackets++;
                if(openBrackets.size()>0)
                {
                    if(openBrackets.back() == '(')
                    {
                        openBrackets.resize(openBrackets.size()-1);
                        noOfClosedRoundBrackets++;
                        noOfUnclosedBrakets -= 1;
                    }
                    else
                    {
                        //noOfUnclosedBrakets = openBrackets.size()+1;
                        openBrackets.clear();
                        noOfUnclosedBrakets++;
                    }
                }
                else
                {
                    //
                    noOfUnclosedBrakets++;
                }

                break;
            case '}':
                noOfRWavyBrackets++;
                if(openBrackets.size()>0)
                {
                    if(openBrackets.back() == '{')
                    {
                        openBrackets.resize(openBrackets.size()-1);
                        noOfClosedWavyBrackets++;
                        noOfUnclosedBrakets -= 1;
                    }
                    else
                    {
                        //noOfUnclosedBrakets = openBrackets.size()+1;
                        openBrackets.clear();
                        noOfUnclosedBrakets++;
                    }
                }
                else
                {
                    //
                    noOfUnclosedBrakets++;
                }
                break;
            case ']':
                noOfRSquareBrackets++;
                if(openBrackets.size()>0)
                {
                    if(openBrackets.back() == '[')
                    {
                        openBrackets.resize(openBrackets.size()-1);
                        noOfClosedSquareBrackets++;
                        noOfUnclosedBrakets -= 1;
                    }
                    else
                    {
                        //noOfUnclosedBrakets = openBrackets.size()+1;
                        openBrackets.clear();
                        noOfUnclosedBrakets++;
                    }
                }
                else
                {
                    //
                    noOfUnclosedBrakets++;
                }
                break;

            default:
                //do nothing
                break;
        }
        //qDebug() << checkStr.mid(0,i+1);
        //qDebug() << "number of unclosed Brackets: " << noOfUnclosedBrakets;
    }

    //qDebug() <<"";

    noOfLBrackets = noOfLRoundBrackets + noOfLSquareBrackets + noOfLWavyBrackets;
    noOfRBrackets = noOfRRoundBrackets + noOfRSquareBrackets + noOfRWavyBrackets;

     //noOfUnclosedBrakets += openBrackets.size();


    return ((noOfLBrackets + noOfRBrackets) > 0);
}


#define LEXING_FUNCTIONS_END }




