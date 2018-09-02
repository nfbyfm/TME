#ifndef SETTINGS_ENUMS_H
#define SETTINGS_ENUMS_H

/**
 * @brief enum for the various settings.
 * Map with actual QStrings gets set in the settingsHandler. *
 */
enum class SETTINGS_ID
{
    LANGUAGE,
    STYLESHEETNAME,
    MATHSOLVER_SHOWERRORLIST,
    AUTOSAVE_ENABLE,
    AUTOSAVE_TIMEOUT,
    SHOW_PDF_AFTER_EXPORT
};

#endif // SETTINGS_ENUMS_H
