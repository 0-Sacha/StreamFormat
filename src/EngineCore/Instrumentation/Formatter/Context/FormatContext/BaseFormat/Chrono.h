#pragma once

#include "Formatter/Context/FormatContext/BasicFormatContext.h"
#include <chrono>

namespace EngineCore::FMT::ChronoDetail {

	template<typename Clock, typename Duration, typename PatternFormat, typename FormatContext>
	void WriteSubTimeFull(const std::chrono::time_point<Clock, Duration>& value, PatternFormat& pattern, FormatContext& context) {
		if (pattern.NextIsSame("ns"))		context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count()));
		else if (pattern.NextIsSame("us"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::microseconds>(value).time_since_epoch().count()));
		else if (pattern.NextIsSame("ms"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(value).time_since_epoch().count()));
		else if (pattern.NextIsSame("s"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::seconds>(value).time_since_epoch().count()));
		else if (pattern.NextIsSame("m"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::minutes>(value).time_since_epoch().count()));
		else if (pattern.NextIsSame("h"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::hours>(value).time_since_epoch().count()));
	}

	template<typename Clock, typename Duration, typename PatternFormat, typename FormatContext>
	void WriteSubTimeMod(const std::chrono::time_point<Clock, Duration>& value, PatternFormat& pattern, FormatContext& context) {
		if (pattern.NextIsSame("ns"))		context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count()	% 1000), 	Detail::ShiftType::Right, Detail::ShiftSize(3), Detail::ShiftPrint_Zeros);
		else if (pattern.NextIsSame("us"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::microseconds>(value).time_since_epoch().count()	% 1000), 	Detail::ShiftType::Right, Detail::ShiftSize(3), Detail::ShiftPrint_Zeros);
		else if (pattern.NextIsSame("ms"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(value).time_since_epoch().count()	% 1000), 	Detail::ShiftType::Right, Detail::ShiftSize(3), Detail::ShiftPrint_Zeros);
		else if (pattern.NextIsSame("s"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::seconds>(value).time_since_epoch().count()		% 60),		Detail::ShiftType::Right, Detail::ShiftSize(2), Detail::ShiftPrint_Zeros);
		else if (pattern.NextIsSame("m"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::minutes>(value).time_since_epoch().count()		% 60),		Detail::ShiftType::Right, Detail::ShiftSize(2), Detail::ShiftPrint_Zeros);
		else if (pattern.NextIsSame("h"))	context.BufferOut().BasicWriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::hours>(value).time_since_epoch().count()			% 24),		Detail::ShiftType::Right, Detail::ShiftSize(2), Detail::ShiftPrint_Zeros);
	}

	template<typename Clock, typename Duration, typename PatternFormat, typename FormatContext>
	void WriteSubTimeSub([[maybe_unused]] const std::chrono::time_point<Clock, Duration>& value, [[maybe_unused]] PatternFormat& pattern, [[maybe_unused]] FormatContext& context)  {}

	template<typename Clock, typename Duration, typename FormatContext>
	bool WriteTime(const std::chrono::time_point<Clock, Duration>& value, FormatContext& context, bool useDefaultPattern = true) {
		auto patternPtr = context.GetFormatData().GetSpecifierOnlyText("pattern");
		if (patternPtr == nullptr && useDefaultPattern == false)
			return false;

		std::basic_string_view<typename FormatContext::CharFormatType> patternStr = "%h:%m:%s.%ms";
		
		if (patternPtr != nullptr)
			patternStr = patternPtr->ValueAsText;

		Detail::FormatterMemoryFormat pattern(patternStr);
		context.Print(pattern.ParamGoToAndGetStr('%', '#', '/'));
		while (!pattern.IsEnd()) {

			if (pattern.IsEqualForward('%'))		WriteSubTimeMod(value, pattern, context);
			else if (pattern.IsEqualForward('#'))	WriteSubTimeFull(value, pattern, context);
			else if (pattern.IsEqualForward('/'))	WriteSubTimeSub(value, pattern, context);

			context.Print(pattern.ParamGoToAndGetStr('%', '#', '/'));
		}

		return true;
	}

}


namespace EngineCore::FMT {
	template<typename FormatContext>
	struct FormatType<std::chrono::time_point<std::chrono::high_resolution_clock>, FormatContext>
	{
		static void Write(const std::chrono::time_point<std::chrono::high_resolution_clock>& t, FormatContext& context) {
			ChronoDetail::WriteTime(t, context);
		}
	};

#ifdef ENGINECORE_COMPILER_MSVC
	template<typename FormatContext>
	struct FormatType<std::chrono::time_point<std::chrono::system_clock>, FormatContext>
	{
		static void Write(const std::chrono::time_point<std::chrono::system_clock>& t, FormatContext& context) {
			ChronoDetail::WriteTime(t, context);
		}
	};
#endif

	template<typename FormatContext>
	struct FormatType<std::chrono::seconds, FormatContext>
	{
		static void Write(const std::chrono::seconds& t, FormatContext& context) {
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::seconds> time(t);
			if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::seconds>(time, context)) {
				context.BufferOut().BasicWriteType(t.count());
				context.BufferOut().PushBack('s');
			}
		}
	};

	template<typename FormatContext>
	struct FormatType<std::chrono::minutes, FormatContext>
	{
		static void Write(const std::chrono::minutes& t, FormatContext& context) {
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::minutes> time(t);
			if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::minutes>(time, context)) {
				context.BufferOut().BasicWriteType(t.count());
				context.BufferOut().PushBack('m');
			}
		}
	};

	template<typename FormatContext>
	struct FormatType<std::chrono::hours, FormatContext>
	{
		static void Write(const std::chrono::hours& t, FormatContext& context) {
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::hours> time(t);
			if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::hours>(time, context)) {
				context.BufferOut().BasicWriteType(t.count());
				context.BufferOut().PushBack('h');
			}
		}
	};

	template<typename FormatContext>
	struct FormatType<std::chrono::milliseconds, FormatContext>
	{
		static void Write(const std::chrono::milliseconds& t, FormatContext& context) {
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::milliseconds> time(t);
			if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::milliseconds>(time, context)) {
				context.BufferOut().BasicWriteType(t.count());
				context.BufferOut().PushBack('m');
				context.BufferOut().PushBack('s');
			}
		}
	};

	template<typename FormatContext>
	struct FormatType<std::chrono::microseconds, FormatContext>
	{
		static void Write(const std::chrono::microseconds& t, FormatContext& context) {
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::microseconds> time(t);
			if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::microseconds>(time, context)) {
				context.BufferOut().BasicWriteType(t.count());
				context.BufferOut().PushBack('u');
				context.BufferOut().PushBack('s');
			}
		}
	};

	template<typename FormatContext>
	struct FormatType<std::chrono::nanoseconds, FormatContext>
	{
		static void Write(const std::chrono::nanoseconds& t, FormatContext& context) {
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> time(t);
			if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::nanoseconds>(time, context)) {
				context.BufferOut().BasicWriteType(t.count());
				context.BufferOut().PushBack('n');
				context.BufferOut().PushBack('s');
			}
		}
	};
}