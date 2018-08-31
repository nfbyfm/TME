#ifndef MGROUPINGTYPE_H
#define MGROUPINGTYPE_H

/**
 * @brief Enum for defining the Type of a MFPart
 *
 */
enum MFPartType
{
    NUMERIC,                //contains only numeric Values
    VARIABLE_ONLY,           //contains only variables
    NUMERIC_AND_VARIABLE,    //Contains combination of numeric Values and variables
    UNDEF
};
#endif // MGROUPINGTYPE_H
