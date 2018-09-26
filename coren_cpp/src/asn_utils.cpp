#include "asn_utils.h"

#include "logger.h"

namespace asn1 {

    namespace encode {
        int string_buffer_cb(const void *buffer, size_t size, void *key)
        {
            std::string* str = reinterpret_cast<std::string *>(key);
            const char *b = reinterpret_cast<const char *>(buffer);
            str->append(b, b + size);
            return 0;
        }
    }

    namespace cast {

        int asnINTEGERToInt(const INTEGER_t *i) {
            long l = 0;
            int r = asn_INTEGER2long(i, &l);
            if (r) {
                log_error("Error " << __FUNCTION__);
            }
            return (int) l;
        }

        long asnINTEGERToLong(const INTEGER_t *i) {
            long l = 0;
            int r = asn_INTEGER2long(i, &l);
            if (r) {
                log_error("Error " << __FUNCTION__);
            }
            return l;
        }

#ifdef INCLUDE_BOOLEAN_H

bool asnBOOLEANToBool(const BOOLEAN_t *i) {
            bool b = false;
            if (*i != 0)
                b = true;
            return b;
        }
#endif

        void intToAsnINTEGER(INTEGER_t *i, int j) {
            if (i == NULL) {
                log_error("Error pointer==NULL " << __FUNCTION__);
            }
            int r = asn_long2INTEGER(i, j);
            if (r) {
                log_error("Error " << __FUNCTION__);
            }
        }

        void intToAsnINTEGER(INTEGER_t **i, int j) {
            if (*i == NULL) {
                *i = (INTEGER_t*) malloc(sizeof (INTEGER_t));
                memset(*i, 0, sizeof (INTEGER_t));
            }
            int r = asn_long2INTEGER(*i, j);
            if (r) {
                log_error("Error " << __FUNCTION__);
            }
        }

#ifdef INCLUDE_BOOLEAN_H

        void boolToAsnBOOLEAN(BOOLEAN_t *i, bool b) {
            if (i == NULL) {
                log_error("Error pointer==NULL " << __FUNCTION__);
                return;
            }
            *i = b;
        }

        void boolToAsnBOOLEAN(BOOLEAN_t **i, bool b) {
            if (*i == NULL) {
                *i = (BOOLEAN_t*) malloc(sizeof (BOOLEAN_t));
                memset(*i, 0, sizeof (BOOLEAN_t));
            }
            **i = b;
        }
#endif

        void longToAsnINTEGER(INTEGER_t *i, long j) {
            if (i == NULL) {
                log_error("Error pointer==NULL " << __FUNCTION__);
            }
            int r = asn_long2INTEGER(i, j);
            if (r) {
                log_error("Error " << __FUNCTION__);
            }
        }

        void longToAsnINTEGER(INTEGER_t **i, long j) {
            if (*i == NULL) {
                *i = (INTEGER_t*) malloc(sizeof (INTEGER_t));
                memset(*i, 0, sizeof (INTEGER_t));
            }
            int r = asn_long2INTEGER(*i, j);
            if (r) {
                log_error("Error " << __FUNCTION__);
            }
        }

        void stringToAsnUTF8String(UTF8String_t *s, const std::string& str) {
            if (s == NULL) {
                log_error("Error pointer==NULL " << __FUNCTION__);
            } else {
                OCTET_STRING_fromString(s, str.c_str());
            }
        }

        void stringToAsnUTF8String(UTF8String_t **s, const std::string& str) {
            if (*s == NULL) {
                *s = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, str.c_str(), str.size());
            } else {
                OCTET_STRING_fromString(*s, str.c_str());
            }
        }

        std::string asnUTF8StringToString(const UTF8String_t *s) {
            if (s == NULL) {
                return std::string();
            }
            return std::string((char*) s->buf, s->size);
        }

        void dataToAsnOCTET_STRING(OCTET_STRING_t* a, const void* data, size_t length) {
            if (a == NULL) {
                log_error("Error pointer==NULL " << __FUNCTION__);
            } else {
                OCTET_STRING_fromBuf(a, (const char*) data, length);
            }
        }

        void dataToAsnOCTET_STRING(OCTET_STRING_t** a, const void* data, size_t length) {
            if (*a == NULL) {
                *a = /*(OCTET_STRING_t*)*/OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, (char*) data, length);
            } else {
                OCTET_STRING_fromBuf((OCTET_STRING_t*) * a, (const char*) data, length);
            }
        }

        void* asnOCTET_STRINGToData(const OCTET_STRING_t* a, size_t& length) {
            length = 0;
            if (a == NULL)
                return NULL;
            char* r = new char[a->size];
            memcpy(r, a->buf, a->size);
            length = a->size;
            return r;
        }

        std::string asnOCTET_STRINGToString(const OCTET_STRING_t* a) {
            if (a == NULL) {
                return std::string();
            }
            return std::string((char*) a->buf, a->size);
        }

    }
}

