#define COREN_CNORA_CPP 1
#include "CNora.h"

#include <boost/algorithm/string/trim.hpp>

namespace CoreN {

CNora::CNora(const InterfacePtr& I, const Service::Address& remote_,
        const boost::chrono::milliseconds& timeout_)
    : ASN1_Service_Complex_Type(cnora_label, DbResponse, DbRequest)(I),
      remote(remote_), timeout(timeout_)
{
}

std::string TrimSQL(const std::string& sql)
{
    std::istringstream iss(sql);
    std::ostringstream oss;

    for (std::string line; std::getline(iss, line); ) {
        boost::trim(line);
        oss << line << ' ';
    }

    return oss.str();
}

void CNora::Request(const std::string& sql, const Values& values, int flags,
        DataHandler d_handler, FinishHandler f_handler)
{
    const auto& sess = NewSession(remote);
    const auto& msg = MakeMessage();
    asn1::cast::stringToAsnUTF8String(&msg->request, TrimSQL(sql));
    asn1::cast::intToAsnINTEGER(&msg->flags, flags);
    if (!values.empty()) {
        msg->params = reinterpret_cast<DbValues*>(malloc(sizeof(DbValues)));
        if (msg->params) {
            memset(msg->params, 0, sizeof(DbValues));
        } else {
            throw std::bad_alloc();
        }
        EncodeValues(msg->params, values);
    }
    start(
        sess,
        msg,
        boost::bind(&CNora::Helper, this, sess, _1, _2, _3, d_handler, f_handler),
        timeout
    );
}

void CNora::EncodeValues(DbValues* p_values, const Values& values)
{
    class Visitor : public boost::static_visitor<DbValue*>
    {
        DbValue* alloc() const
        {
            DbValue* res = reinterpret_cast<DbValue*>(malloc(sizeof(DbValue)));
            if (res) {
                memset(res, 0, sizeof(DbValue));
            } else {
                throw std::bad_alloc();
            }
            return res;
        }
    public:
        DbValue* operator()(nullptr_t /*value*/) const
        {
            DbValue* res = alloc();
            res->present = DbValue_PR_null;
            res->choice.null = 0;
            return res;
        }

        DbValue* operator()(long value) const
        {
            DbValue* res = alloc();
            res->present = DbValue_PR_integer;
            asn_long2INTEGER(&res->choice.integer, value);
            return res;
        }
/*
        DbValue* operator()(unsigned long value) const
        {
            DbValue* res = alloc();
            res->present = DbValue_PR_integer;
            asn_ulong2INTEGER(&res->choice.integer, value);
            return res;
        }
*/
        DbValue* operator()(double value) const
        {
            DbValue* res = alloc();
            res->present = DbValue_PR_number;
            asn_double2REAL(&res->choice.number, value);
            return res;
        }

        DbValue* operator()(const std::string& value) const
        {
            DbValue* res = alloc();
            res->present = DbValue_PR_string;
            OCTET_STRING_fromBuf(&res->choice.string, value.data(), value.size());
            return res;
        }
    };
    static const Visitor visitor;

    for (auto v : values) {
        DbValue* p_v = boost::apply_visitor( visitor, v );
        ASN_SEQUENCE_ADD(p_values, p_v);
    }
}

void CNora::DecodeDataset(Rows& rows, const DbRows* p_dataset)
{
    if (!p_dataset) {
        return;
    }
    for (int i = 0; i < p_dataset->list.count; ++i) {
        const DbRow* p_row = p_dataset->list.array[i];
        Row row;
        for (int j = 0; j < p_row->list.count; ++j) {
            const DbValue* p_value = p_row->list.array[j];
            Value value;
            switch (p_value->present) {
                case DbValue_PR_integer: {
                    long res = 0;
                    if (asn_INTEGER2long(&p_value->choice.integer, &res) != -1) {
                        value = res;
                    } else {
                        value = nullptr;
                    }
                    break;
                }
                case DbValue_PR_string: {
                    const UTF8String_t& str = p_value->choice.string;
                    std::string res(
                        reinterpret_cast<char*>(str.buf),
                        reinterpret_cast<char*>(str.buf+str.size)
                    );
                    value = res;
                    break;
                }
                case DbValue_PR_number: {
                    double res = 0.0;
                    if (asn_REAL2double(&p_value->choice.number, &res) != -1) {
                        value = res;
                    } else {
                        value = nullptr;
                    }
                    break;
                }
                case DbValue_PR_null:
                default: {
                    value = nullptr;
                    break;
                }
            }
            row.emplace_back(value);
        }
        rows.emplace_back(row);
    }
}

void CNora::Helper(const SessionTPtr& sess, const CoreN::Error& error,
        const RecvMessagePtr& body, Session::Flags flags,
        DataHandler d_handler, FinishHandler f_handler)
{
    if (error) {
        if (f_handler) {
            f_handler(error);
        }
        return;
    }

    const CoreN::Error err {
        asn1::cast::asnINTEGERToInt(&body->code),
        asn1::cast::asnUTF8StringToString(body->message)
    };

    {
        Rows rows;
        DecodeDataset(rows, body->dataset);
        if (!rows.empty() && d_handler) {
            d_handler(rows);
        }
    }

    if (!(flags & Session::Stop) && (err.code == CNE_MORE)) {
        recv(sess, boost::bind(&CNora::Helper, this, sess, _1, _2, _3, d_handler, f_handler));
    } else {
        if (f_handler) {
            f_handler(err);
        }
    }
}

}

