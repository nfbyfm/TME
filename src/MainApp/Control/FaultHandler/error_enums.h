#ifndef ERROR_ENUMS_H
#define ERROR_ENUMS_H
#include <QObject>
#include <QString>

//Type of Error
/**
 * @brief Type of Error. If NONE a simple message gets shown
 *
 */
enum class ErrorType
{
    ET_WARNING,     //simple waring
    ET_ERROR,        //strong error
    ET_NONE            //no Error
};

//How the Error is supposed to be shown to the user
/**
 * @brief How the errormessage is supposed to be shown to the user
 *
 */
enum class ErrorViewMedium
{
    MSG_POPUP,      //Popup-Message
    MSG_STATUSBAR,      //Message to be shown in the Statusbar
    MSG_LISTDIALOG,     //List multiple Errors and show them in a table
    NONE            //no Error
};
//Q_ENUM(ErrorLevel);

/**
 * @brief Enum for all kind of error-messages. The message itself get defined in the initMaps-function of the faulthandler.
 *
 */
enum class ERROR_ID
{
    UNDEFINED,
    FAULTHANDLER_UnknownError,

    MATHENGINE_TextIsEmpty,
    MATHENGINE_TextIsNull,
    MATHENGINE_NoFormulasFoundInMathModel,
    MATHENGINE_NoFormulasFoundInText,
    MATHENGINE_NoFormulasInBothLists,
    MATHENGINE_NoVariableInForumla,

    LEXER_NoFormulasFound,

    PARSER_ContainsFunctions,
    PARSER_TooManyComparators,
    PARSER_ComparatorNotSupported,
    PARSER_NoComparatorInEquation,
    PARSER_NoVariableFound,
    PARSER_ContainsPowerFunction,
    PARSER_Contains_Brackets,

    MATHSOLVER_NotEnoughEquations,
    MATHSOLVER_TooManyEquations,

    SETTINGS_SettingNotFound,
    SETTINGS_StylesheetNotFound,

    DOCHANDLER_FileDoesNotExist,
    DOCHANDLER_FileCanNotBeOpened,
    DOCHANDLER_FileAlreadyOpen,
    DOCHANDLER_CouldNotSaveFile,
    DOCHANDLER_WrongXMLVersion,
    DOCHANDLER_XMLError,
    DOCHANDLER_FileError,

    MATHINPUT_FormulaAlreadyInList,
    MATHINPUT_VariableAlreadyInList,
    MATHINPUT_NoVariableSelected,
    MATHINPUT_NoFormulaSelected
};



#endif // ERROR_ENUMS_H
