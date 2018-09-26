#ifndef ASN_UTILS_H
#define ASN_UTILS_H

#include <string>

#include <INTEGER.h>
#include <UTF8String.h>
#include <OCTET_STRING.h>

namespace asn1 {

namespace encode {
    int string_buffer_cb(const void *buffer, size_t size, void *key);
}

namespace cast {

    /**
    * Функция перевода целого числа asn в простой тип int.
    * @param i Целое число типа asn.
    * @return Целое число типа int.
    */
    int asnINTEGERToInt(const INTEGER_t *i);

    /**
    * Функция перевода целого числа asn в простой тип long.
    * @param i Целое число типа asn.
    * @return Целое число типа long.
    */
    long asnINTEGERToLong(const INTEGER_t *i);

#ifdef INCLUDE_BOOLEAN_H
    /**
    * Функция перевода логического типа asn в простой тип bool.
    * @param i Логическая переменая типа asn.
    * @return Целое число типа int.
    */
    bool asnBOOLEANToBool(const BOOLEAN_t *i);
#endif

    /**
    * Функция перевода числа типа int в целое числа asn.
    * @param i Указатель на целое число asn.
    * @param j Целое число типа int, которое будет переведено в число asn.
    */
    void intToAsnINTEGER(INTEGER_t *i, int j);

    /**
    * Функция перевода числа типа int в целое числа asn.
    * @param i Указатель на указатель целого число asn. По указателю выделяется память, если он равен NULL.
    * @param j Целое число типа int, которое будет переведено в число asn.
    */
    void intToAsnINTEGER(INTEGER_t **i, int j);

#ifdef INCLUDE_BOOLEAN_H
    /**
    * Функция перевода логического значения типа bool в логическое значение asn.
    * @param i Указатель на логическое значение asn.
    * @param j Логическое значение типа bool, которое будет переведено в логическое значение asn.
    */
    void boolToAsnBOOLEAN(BOOLEAN_t *i, bool b);

    /**
    * Функция перевода логического значения типа bool в логическое значение asn.
    * @param i Указатель на указатель логического значения asn. По указателю выделяется память, если он равен NULL.
    * @param j Логическое значение типа bool, которое будет переведено в логическое значение asn.
    */
    void boolToAsnBOOLEAN(BOOLEAN_t **i, bool b);
#endif

    /**
    * Функция перевода числа типа int в целое числа asn.
    * @param i Указатель на целое число asn.
    * @param j Целое число типа long, которое будет переведено в число asn.
    */
    void longToAsnINTEGER(INTEGER_t *i, long j);

    /**
    * Функция перевода числа типа int в целое числа asn.
    * @param i Указатель на указатель целого число asn. По указателю выделяется память, если он равен NULL.
    * @param j Целое число типа int, которое будет переведено в число asn.
    */
    void longToAsnINTEGER(INTEGER_t **i, long j);

    /**
    * Функция перевода строки типа std::string в строку типа asn Utf8String.
    * @param s Указатель на указатель строки типа asn Utf8String. По указателю выделяется память, если он равен NULL.
    * @param str Строка типа std::string, которая будет переведена в строку asn.
    */
    void stringToAsnUTF8String(UTF8String_t **s, const std::string& str);

    /**
    * Функция перевода строки типа std::string в строку типа asn Utf8String.
    * @param s Указатель на строку типа asn Utf8String.
    * @param str Строка типа std::string, которая будет переведена в строку asn.
    */
    void stringToAsnUTF8String(UTF8String_t *s, const std::string& str);

    /**
    * Функция перевода строки типа asn Utf8String в строку std::string.
    * @param s Указатель на строку типа asn Utf8String.
    * @return Строка типа std::string, которая была получена из строки asn.
    */
    std::string asnUTF8StringToString(const UTF8String_t *s);

    /**
    * Функция записи двоичных данных в двоичную строку типа asn OCTET_STRING.
    * @param a Указатель на двоичную строку типа asn OCTET_STRING.
    * @param data Указатель на двоичные данные, которые будут скопированы в строку asn,
    * @paran length Длина двоичных данных в байтах.
    */
    void dataToAsnOCTET_STRING(OCTET_STRING_t* a, const  void* data, size_t length);

    /**
    * Функция записи двоичных данных в двоичную строку типа asn OCTET_STRING.
    * @param a Указатель на указатель двоичной строки типа asn OCTET_STRING. По указателю выделяется память, если он равен NULL.
    * @param data Указатель на двоичные данные, которые будут скопированы в строку asn,
    * @paran length Длина двоичных данных в байтах.
    */
    void dataToAsnOCTET_STRING(OCTET_STRING_t** a, const  void* data, size_t length);

    /**
    * Функция записи двоичных данных в память из типа asn OCTET_STRING.
    * @param a Указатель на двоичную строку типа asn OCTET_STRING.
    * @param[out] length Длина двоичных данных в байтах.
    * @return void Указатель на двоичные данные, которые будут скопированы из строки asn OCTET_STRING.
    */
    void* asnOCTET_STRINGToData(const OCTET_STRING_t* a, size_t& length);

    std::string asnOCTET_STRINGToString(const OCTET_STRING_t* a);

}

}

#endif // ASN_UTILS_H
