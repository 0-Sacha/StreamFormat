#pragma once

#include "Detail.h"

namespace EngineCore::LoggerManager::Detail {

    template <typename Master>
	class XLogger : public Master
    {
        public:
            template <typename... Args>
            XLogger(Args&&... args)
                : Master(std::forward<Args>(args)...)
            {}

	    public:
            template<typename Severity, typename Format = std::string_view, typename ...Args>
		    requires FMT::Detail::IsFmtConvertible<Format>::Value
		    void Log(Severity status, const Format& format, Args&& ...args) const { Master::template Log(status, format, std::forward<Args>(args)...); }

		    template<typename Severity, typename T>
		    void Log(Severity status, T&& t) const { Master::template Log(status, std::forward<T>(t)); }

        public:
            /////---------- Logger Severity with array as format ----------/////
            template<typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::IsFmtConvertible<Format>::Value
            inline void Trace(const Format& format, Args&& ...args) const   { return Log(LogSeverity::Trace, format, std::forward<Args>(args)...); }
            template<typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::IsFmtConvertible<Format>::Value
            inline void Debug(const Format& format, Args&& ...args) const   { return Log(LogSeverity::Debug, format, std::forward<Args>(args)...); }
            template<typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::IsFmtConvertible<Format>::Value
            inline void Info(const Format& format, Args&& ...args) const    { return Log(LogSeverity::Info, format, std::forward<Args>(args)...); }
            template<typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::IsFmtConvertible<Format>::Value
            inline void Warn(const Format& format, Args&& ...args) const    { return Log(LogSeverity::Warn, format, std::forward<Args>(args)...); }
            template<typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::IsFmtConvertible<Format>::Value
            inline void Error(const Format& format, Args&& ...args) const   { return Log(LogSeverity::Error, format, std::forward<Args>(args)...); }
            template<typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::IsFmtConvertible<Format>::Value
            inline void Fatal(const Format& format, Args&& ...args) const   { return Log(LogSeverity::Fatal, format, std::forward<Args>(args)...); }

            /////---------- NO-FORMAT Logger Severity ----------/////
            template<typename T>
            inline void Trace(T&& t) const  { return Log(LogSeverity::Trace, std::forward<T>(t)); }
            template<typename T>
            inline void Debug(T&& t) const  { return Log(LogSeverity::Debug, std::forward<T>(t)); }
            template<typename T>
            inline void Info(T&& t) const   { return Log(LogSeverity::Info, std::forward<T>(t)); }
            template<typename T>
            inline void Warn(T&& t) const   { return Log(LogSeverity::Warn, std::forward<T>(t)); }
            template<typename T>
            inline void Error(T&& t) const  { return Log(LogSeverity::Error, std::forward<T>(t)); }
            template<typename T>
            inline void Fatal(T&& t) const  { return Log(LogSeverity::Fatal, std::forward<T>(t)); }

        public:
            /////---------- Logger Status with array as format ----------/////
            template<typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::IsFmtConvertible<Format>::Value
            inline void Ok(const Format& format, Args&& ...args) const      { return Log(LogStatus::OK, format, std::forward<Args>(args)...); }
            template<typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::IsFmtConvertible<Format>::Value
            inline void Fail(const Format& format, Args&& ...args) const    { return Log(LogStatus::FAIL, format, std::forward<Args>(args)...); }

            /////---------- NO-FORMAT Logger Status ----------/////
            template<typename T>
            inline void Ok(T&& t) const { return Log(LogStatus::OK, std::forward<T>(t)); }
            template<typename T>
            inline void Fail(T&& t) const { return Log(LogStatus::FAIL, std::forward<T>(t)); }

        public:
            template<typename Format = std::string_view, typename ...Args>
            requires FMT::Detail::IsFmtConvertible<Format>::Value
            inline void Basic(const Format& format, Args&& ...args) const   { return Log(LogBasic{}, format, std::forward<Args>(args)...); }

            template<typename T>
            inline void Basic(T&& t) const                                  { return Log(LogBasic{}, std::forward<T>(t)); }
	};
}
