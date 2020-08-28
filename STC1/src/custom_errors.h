#ifndef CUSTOM_ERRORS_H
#define CUSTOM_ERRORS_H

#include <system_error>

#include "constants.h"

//-----------------------------------------------------------------------------
/**
 * @brief The CustomErrorCodes enum - Множество кодов ошибок
 */
enum class CustomErrorCodes
{
    cecNoError = 0,                                 ///< Нет ошибки

    cecParserNotFoundParamTextEditor,               ///< Парсер не смог найти параметр "texteditor"
    cecParserNotFoundParamFileFormats,              ///< Парсер не смог найти параметр "fileformats"
    cecParserNotFoundParamEncoding,                 ///< Парсер не смог найти параметр "encoding"
    cecParserNotFoundParamHasPlugin,                ///< Парсер не смог найти параметр "hasplugins"
    cecParserNotFoundParamCanCompile,               ///< Парсер не смог найти параметр "cancompile"
    cecParserNotFoundParamHasIntelLisense,          ///< Парсер не смог найти параметр "hasintellisense"

    cecParserXmlFileNotExists,                      ///< Парсер XML не смог найти указанный файл
    cecParserXmlFileOpenFail,                       ///< Парсер XML не смог открыть указанный файл
    cecParserXmlParseFail,                          ///< Парсер XML зафиксировал ошибку парсинга

    cecWriterXmlFileOpenFail,                       ///< Врайтер XML не смог открыть указанный файл

    cecParserDbConnectFail,                         ///< Парсер DB не смог получить доступ к бд
    cecParserDbNotFoundID,                          ///< Парсер DB не смог найти идентификатор                        

    cecWriterDbConnectFail,                         ///< Врайтер DB не смог получить доступ к бд
    cecWriterDbWriteFail,                           ///< Врайтер DB не смог записать строку в бд




    cecCount                                        ///< Количество кодов ошибок
};
//-----------------------------------------------------------------------------
namespace std
{
    template <>
        struct is_error_code_enum<CustomErrorCodes> : true_type {};
}
//-----------------------------------------------------------------------------
namespace // anonymous namespace
{
    //-----------------------------------------------------------------------------
    /**
     * @brief The CustomErrCategory struct - Структур, наследуемая от системной категории ошибки
     */
    struct CustomErrCategory : std::error_category
    {
        const char* name() const noexcept override;
        std::string message(int inErrCode) const override;
    };
    //-----------------------------------------------------------------------------
    /**
     * @brief CustomErrCategory::name - Метод вернёт наименование категории
     * @return
     */
    const char* CustomErrCategory::name() const noexcept
    {
        return "Custom Errors";
    }
    //-----------------------------------------------------------------------------
    /**
     * @brief CustomErrCategory::message - Метод вернёт сообщение по коду ошибки
     * @param ev - Код ошибки
     * @return Вернёт сообщение о типе ошибке
     */
    std::string CustomErrCategory::message(int inErrCode) const
    {
        switch (static_cast<CustomErrorCodes>(inErrCode))
        {

            case CustomErrorCodes::cecParserNotFoundParamTextEditor:
                return "Not found parameter \"" + cTextEditor + "\".";

            case CustomErrorCodes::cecParserNotFoundParamFileFormats:
                return "Not found parameter \"" + cFileFormats + "\".";

            case CustomErrorCodes::cecParserNotFoundParamEncoding:
                return "Not found parameter \"" + cEncoding + "\".";

            case CustomErrorCodes::cecParserNotFoundParamHasPlugin:
                return "Not found parameter \"" + cHasPlugins + "\".";

            case CustomErrorCodes::cecParserNotFoundParamCanCompile:
                return "Not found parameter \"" + cCanCompile + "\".";


            case CustomErrorCodes::cecParserNotFoundParamHasIntelLisense:
                return "Not found parameter \"" + cHasIntelLisense + "\".";

            case CustomErrorCodes::cecParserXmlFileNotExists:
                return "Xml input file not found.";

            case CustomErrorCodes::cecParserXmlFileOpenFail:
                return "Xml input file open fail.";

            case CustomErrorCodes::cecParserXmlParseFail:
                return "Xml parse fail.";



            case CustomErrorCodes::cecWriterXmlFileOpenFail:
                return "Xml output file open fail.";



            case CustomErrorCodes::cecParserDbConnectFail:
                return "DB parser not found db connect.";

            case CustomErrorCodes::cecParserDbNotFoundID:
                return "DB record not contain id.";



            case CustomErrorCodes::cecWriterDbConnectFail:
                return "DB writer not found db connect.";

            case CustomErrorCodes::cecWriterDbWriteFail:
                return "DB writer write record fail.";



            default:
                return "Unknown error!";
        }
    }
    //-----------------------------------------------------------------------------
    const CustomErrCategory theCustomErrCategory {};
    //-----------------------------------------------------------------------------
} // anonymous namespace
//-----------------------------------------------------------------------------
inline std::error_code make_error_code(CustomErrorCodes inErrCode)
{
    return { static_cast<int>(inErrCode), theCustomErrCategory };
}
//-----------------------------------------------------------------------------

#endif // CUSTOM_ERRORS_H
